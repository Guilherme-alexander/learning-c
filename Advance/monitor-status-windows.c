// COMPILAR: gcc monitor.c -o monitor.exe -lpsapi -liphlpapi
// monitor-status-windows.c
// https://github.com/Guilherme-alexande

#include <windows.h>
#include <tlhelp32.h>
#include <psapi.h>
#include <iphlpapi.h>
#include <stdio.h>

#pragma comment(lib,"iphlpapi.lib")
#pragma comment(lib,"psapi.lib")

#define BAR_WIDTH 30
#define MAX_PROC 10

// Barra gráfica
// ------------------------------------------------
void draw_bar(float percent)
{
    int filled = (percent / 100.0) * BAR_WIDTH;

    printf("[");

    for(int i=0;i<BAR_WIDTH;i++)
        printf(i < filled ? "#" : ".");

    printf("] %.2f%%", percent);
}

// CPU USAGE
// ------------------------------------------------
float get_cpu_usage(){
  
    static FILETIME prev_idle, prev_kernel, prev_user;
    FILETIME idle, kernel, user;

    GetSystemTimes(&idle,&kernel,&user);

    ULONGLONG i = ((ULONGLONG)idle.dwHighDateTime<<32) | idle.dwLowDateTime;
    ULONGLONG k = ((ULONGLONG)kernel.dwHighDateTime<<32) | kernel.dwLowDateTime;
    ULONGLONG u = ((ULONGLONG)user.dwHighDateTime<<32) | user.dwLowDateTime;

    ULONGLONG pi = ((ULONGLONG)prev_idle.dwHighDateTime<<32) | prev_idle.dwLowDateTime;
    ULONGLONG pk = ((ULONGLONG)prev_kernel.dwHighDateTime<<32) | prev_kernel.dwLowDateTime;
    ULONGLONG pu = ((ULONGLONG)prev_user.dwHighDateTime<<32) | prev_user.dwLowDateTime;

    ULONGLONG idle_diff = i - pi;
    ULONGLONG total_diff = (k - pk) + (u - pu);

    prev_idle = idle;
    prev_kernel = kernel;
    prev_user = user;

    if(total_diff == 0) return 0;

    return 100.0 * (total_diff - idle_diff) / total_diff;
}

// RAM
// ------------------------------------------------
void get_memory(float *percent, unsigned long long *total, unsigned long long *free) {
    MEMORYSTATUSEX mem;

    mem.dwLength = sizeof(mem);

    GlobalMemoryStatusEx(&mem);

    *percent = mem.dwMemoryLoad;

    *total = mem.ullTotalPhys / (1024*1024);

    *free = mem.ullAvailPhys / (1024*1024);
}

// DISCO
// ------------------------------------------------
void get_disk(float *percent, unsigned long long *total, unsigned long long *free)
{
    ULARGE_INTEGER freeBytes, totalBytes, totalFree;

    GetDiskFreeSpaceEx("C:\\",&freeBytes,&totalBytes,&totalFree);

    *total = totalBytes.QuadPart / (1024*1024*1024);

    *free = totalFree.QuadPart / (1024*1024*1024);

    *percent = 100.0 * (1.0 - (double)*free / *total);
}

// REDE
// ------------------------------------------------
void get_network(double *rx,double *tx) {
    static ULONGLONG prev_rx = 0;
    static ULONGLONG prev_tx = 0;

    PMIB_IFTABLE table;

    DWORD size = 0;

    GetIfTable(NULL,&size,FALSE);

    table = (MIB_IFTABLE*)malloc(size);

    GetIfTable(table,&size,FALSE);

    ULONGLONG total_rx = 0;
    ULONGLONG total_tx = 0;

    for(DWORD i=0;i<table->dwNumEntries;i++)
    {
        total_rx += table->table[i].dwInOctets;
        total_tx += table->table[i].dwOutOctets;
    }

    *rx = (total_rx - prev_rx) / 1024.0 / 1024.0;
    *tx = (total_tx - prev_tx) / 1024.0 / 1024.0;

    prev_rx = total_rx;
    prev_tx = total_tx;

    free(table);
}

// PROCESSOS
// ------------------------------------------------
void show_processes(){
    HANDLE snap = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS,0);

    PROCESSENTRY32 pe;

    pe.dwSize = sizeof(pe);

    printf("\n| PID   | MEM   | PROCESS\n");
    printf("|------|-------|----------------\n");

    if(Process32First(snap,&pe))
    {
        int count = 0;

        do{

            HANDLE h = OpenProcess(PROCESS_QUERY_INFORMATION | PROCESS_VM_READ,FALSE,pe.th32ProcessID);

            SIZE_T mem = 0;

            if(h)
            {
                PROCESS_MEMORY_COUNTERS pmc;

                if(GetProcessMemoryInfo(h,&pmc,sizeof(pmc)))
                    mem = pmc.WorkingSetSize/(1024*1024);

                CloseHandle(h);
            }

            printf("| %-5d | %-4lluMB | %s\n",
                   pe.th32ProcessID,
                   mem,
                   pe.szExeFile);

            count++;

        }while(Process32Next(snap,&pe) && count < MAX_PROC);
    }

    CloseHandle(snap);
}

// MAIN
// ------------------------------------------------
int main() {
    SYSTEM_INFO sys;

    GetSystemInfo(&sys);

    while(1)
    {
        system("cls");

        float cpu = get_cpu_usage();

        float ram_percent;
        unsigned long long ram_total,ram_free;

        get_memory(&ram_percent,&ram_total,&ram_free);

        float disk_percent;
        unsigned long long disk_total,disk_free;

        get_disk(&disk_percent,&disk_total,&disk_free);

        double rx,tx;

        get_network(&rx,&tx);

        printf("========================================\n");
        printf("      MONITOR DE SISTEMA (WINDOWS)\n");
        printf("========================================\n\n");

        printf("CPU (%d cores)\n",sys.dwNumberOfProcessors);
        draw_bar(cpu);
        printf("\n\n");

        printf("RAM\n");
        draw_bar(ram_percent);
        printf("\nTotal: %llu MB  Livre: %llu MB\n\n",ram_total,ram_free);

        printf("DISCO C:\n");
        draw_bar(disk_percent);
        printf("\nTotal: %llu GB  Livre: %llu GB\n\n",disk_total,disk_free);

        printf("NET  ↓ %.2f MB/s   ↑ %.2f MB/s\n",rx,tx);

        show_processes();

        Sleep(1000);
    }

    return 0;
}
