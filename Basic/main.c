// [build] $ gcc main.c -o main.exe

#include <stdio.h>

// int		2 or 4 bytes
// float	4 bytes
// double	8 bytes
// char		1 byte

// Create a function
void myFunction() {
  printf("\n I just got executed! \n");
}

// criando arquivo modos:
// w - Writes to a file (Escrita)
// a - Appends new data to a file (Escrita Gravação Adição De novos Dados)
// r - Reads from a file (Leitura)
void createFile(){
 // Em C, você pode criar, abrir, ler e escrever em arquivos declarando um ponteiro do tipo , e usar a função:FILEfopen()
 FILE *fptr;

 // Create a file
 fptr = fopen("filename.txt", "w");

 // Write some text to the file
 fprintf(fptr, "Create File text Menssage!");
 fprintf(fptr, "\nHello World!");

 // Especifica o tamanho máximo dos dados a serem lidos
 //char myString[100];
 // Read the content and store it inside myString
 //fgets(myString, 100, fptr);

 // Close the file
 fclose(fptr);
}

// procurar se o arquivo existe
void getFile(){
 FILE *fptr;

 // Open a file in read mode
 fptr = fopen("filename.txt", "r");

 // Print some text if the file does not exist
 if(fptr == NULL) {
   printf("Not able to open the file.\n");
 }

 // Close the file
 fclose(fptr);
}


// parâmetros
void printName(char new_nomes[], int new_idade){
 printf("NOME: %s IDADE:%d\n", new_nomes, new_idade);
}

// callback!
void greetMorning() { printf("Good morning!\n"); }
void greetEvening() { printf("Good evening!\n"); }

void greet(void (*callback)()) {
  callback();
}

int main(){
 greet(greetMorning);
 greet(greetEvening);

 char name[50] = "Guilherme";
 int idade = 27;
 int* ptr = &idade;  // Pointer declaration

 printf("[+] Hello, World!\n");
 printf("Hi! %s", name);
 printf("\n");

 printf("[+] Escreva um texto: ");
 scanf("%49s", name);

 printf("Hi! %s", name);
 printf("\n"); 
 
 // ARQUIVOS
 getFile();
 createFile();

 printf("[NOME Memory Address]: ");
 printf("%p\n", &name);
 printf("[IDADE Memory Address]: ");
 printf("%p\n", &idade);

 myFunction();
 printName(name, idade); 

 printf("[+] Reference: Output the memory address of myAge with the pointer (Address): ");
 printf("%p\n", ptr);

 int myNumbers[4] = {25, 50, 75, 100};
 int i;

 for (i = 0; i < 4; i++) {
   printf("%d	:", myNumbers[i]);
   printf("%p\n", &myNumbers[i]);
 }

 return 0;
}
