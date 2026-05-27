
#include <stdio.h>
#include <time.h> // horário atual do sistema operacional

/*
%d dia
%m mês
%Y ano

%H hora 24h
%M minuto
%S segundo

%A nome do dia
%B nome do mês
*/

// Obtendo a Hora Atual
// A biblioteca possui diversas funções para medir datas e horários. <time.h>
// Por exemplo, a função retorna o tempo atual como um valor do tipo time() time_t
// Você pode usar para converter o tempo em uma string legível, como "Seg Jun 24 10:15:00 2025": ctime()

// time_t - TIPO definido pela biblioteca é algo parecido com: typedef long long time_t; ou typedef long time_t; depende do sistema
// time_t now; significa "crie uma variável chamada now do tipo time_t" Igual: int idade;
// now - é apenas o nome da variável
// O que fica armazenado em now é Um número representando tempo Unix Ex: 1747930000 Isso significa: quantidade de segundos desde 1 Jan 1970 UTC "Unix Timestamp"
// time() - FUNÇÃO da biblioteca <time.h>.
// time(NULL) - me devolva o horário atual, mas não escreva em nenhum ponteiro A função aceita um ponteiro opcional ou time(time_t *arg);
// NULL = não quero passar ponteiro nenhum
// Você pode fazer: time_t agora; e time(&agora); a função vai escreve o valor dentro de agora.
// localtime() - função do <time.h> converte o timestamp bruto nessa conversão:[ ano, mês, dia, hora, minuto, segundo ]


void getCurrentTime(){
 time_t currentTime;
 time(&currentTime); // Get the current time

 printf("Current time: %s", ctime(&currentTime));
}

void getTimeData(){
 time_t now = time(NULL);         // Get current time = now = 1747930000
 struct tm *t = localtime(&now);  // Convert to local time structure - Usamos porque retorna um ponteiro para um .->localtime()

 printf("Year: %d\n", t->tm_year + 1900);  // Add 1900 to get the actual year
 printf("Month: %d\n", t->tm_mon + 1);     // Months are numbered from 0 to 11, so add 1 to match real month numbers (1-12)
 printf("Day: %d\n", t->tm_mday);
 printf("Hour: %d\n", t->tm_hour);
 printf("Minute: %d\n", t->tm_min);
 printf("Second: %d\n", t->tm_sec);

 printf("DATA: %d/%d/%d HORA: %d:%d:%d \n", t->tm_mday, t->tm_mon + 1, t->tm_year + 1900, t->tm_hour, t->tm_min, t->tm_sec);
}

void getTimeDataFormatting(){
 time_t now = time(NULL);
 struct tm *t = localtime(&now);
 char buffer[100];

 strftime(buffer, sizeof(buffer), "%d-%m-%Y %H:%M:%S", t);
 printf("Formatted time: %s\n", buffer);
}

int main() {
 getCurrentTime();
 
 printf("\n");

 getTimeData();

 printf("\n");

 getTimeDataFormatting();

 return 0;
}
