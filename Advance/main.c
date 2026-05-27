#include <stdio.h>
#include <stdlib.h> // PARA TRABALHAR COM MEMÓRIA NESSESITA USAR ESSA BIBLIOTECA;
#include <windows.h> // USA UTF-8
#include <string.h> // USA UTF-8 [strcmp() ]

// "==" compara endereços de memória, não o conteúdo da string.
// "||" OU
// "&&" E

// fgets(buffer, tamanho, entrada); - Lê uma string da entrada (stdin).
// fgets() - Input melhor que scanf()
// strcspn() - Procura caracteres específicos dentro da string. EX: strcspn(name, "\n") encontre a posição do primeiro \n
// strlen() - Retorna o tamanho da string. Conta caracteres até: '\0'
// strcmp() - compara duas strings EX: `strcmp(nome, "gui") == 0` caractere por caractere até encontrar um diferença ou \0 
// stricmp(nome, "guilherme") == 0 - case-insensitive: Aceita: Guilherme, GUILHERME, guiLHerme


// malloc(4); - aloca memoria para uma endereço de Memoria.
// int *v = malloc(4 * sizeof(int)); reserva memória na heap


// realloc(VARIAVEL, TAMANHO); - redimensionar um bloco de memória já alocado dinamicamente.
// 1° primeiro argumento é um ponteiro para memória alocada dinamicamente,
// 2° segundo é o novo tamanho em bytes (8 bytes).
// v = realloc(v, 8 * sizeof(int));
// só funciona corretamente em ponteiros obtidos com:
// malloc()
// calloc()
// realloc()


// free() libera uma memória que foi alocada dinamicamente.
// free(ptr); - ibera uma memória que foi alocada *ptr devolve essa memória para o sistema.
// ptr = NULL; - Assim evita uso acidental de (dangling pointer).
// free() duas vezes Chamado de double free (corrupção de memória, vulnerabilidades).


// = Memória estática ==========================================================================================
// Memória estática é a memória reservada para variáveis antes da execução do programa. 
// A alocação de memória estática também é conhecida como alocação de memória em tempo de compilação.
// Mas quando o semestre começa, descobrimos que apenas 12 alunos estão participando. 
// Então você desperdiçou o espaço de 8 elementos não utilizados.
// Como você não pode alterar o tamanho do array, fica com memória reservada desnecessária.



void staticMemory(){
 printf("= Memória estática =\n");
 int students[20];
 printf("[Static Memory]: %zu\n", sizeof(students)); // 80 bytes

}



// = Memória Dinâmica ==========================================================================================
// Memória dinâmica é a memória alocada após o início da execução do programa. 
// A alocação de memória dinâmica também pode ser chamada de alocação de memória em tempo de execução.

// Diferente da memória estática, você tem controle total sobre quanta memória está sendo usada a qualquer momento.
// Você pode escrever código para determinar quanta memória precisa e alocá-la.

// A memória dinâmica não pertence a uma variável, ela só pode ser acessada com ponteiros.

// Para alocar memória dinâmica, você pode usar as funções ou. É necessário incluir o cabeçalho para usá-los.
// As funções e alocam alguma memória e retornam um ponteiro para seu endereço.malloc()calloc()<stdlib.h>malloc()calloc

// A função possui um parâmetro, tamanho, que especifica quanta memória deve ser alocada, medida em bytes.malloc()
// A função possui dois parâmetros:calloc()

// amount - Especifica a quantidade de itens a serem alocados
// tamanho - Especifica o tamanho de cada item medido em bytes



void dynamicMemory(){
 printf("= Memória Dinâmica =\n");
 //int *ptr1 = malloc(size);
 //int *ptr2 = calloc(amount, size);

 int *ptr3, *ptr4;
 ptr3 = malloc(sizeof(*ptr3));
 ptr4 = calloc(1, sizeof(*ptr4));

 int *students;
 int numStudents = 12;
 students = calloc(numStudents, sizeof(*students));
 printf("[dynamic Memory]: %d\n", numStudents * sizeof(*students)); // 48 bytes
 printf("\n");


}



// = Access Dynamic Memory ==========================================================================================
// A memória dinâmica não possui seu próprio tipo de dado, é apenas uma sequência de bytes.
// Os dados na memória podem ser interpretados como um tipo baseado no tipo de dado do ponteiro.
// Neste exemplo, um ponteiro para quatro bytes pode ser interpretado como um valor (4 bytes)
// ou como um array de 4 valores (1 byte cada). intchar

void AccessDynamicMemory(){
 printf("= Access Dynamic Memor =\n");
 // Allocate memory
 int *ptr;
 ptr = calloc(4, sizeof(*ptr));

 // Write to the memory
 *ptr = 2;
 ptr[1] = 4;
 ptr[2] = 6;

 // Read from the memory
 printf("%d\n", *ptr);
 printf("%d %d %d", ptr[1], ptr[2], ptr[3]);
 printf("\n");
 printf("\n");
 printf("\n");
 int *ptr1 = malloc(4);
 char *ptr2 = (char*) ptr1;
 ptr1[0] = 1684234849;
 printf("%d is %c %c %c %c", *ptr1, ptr2[0], ptr2[1], ptr2[2], ptr2[3]);
}



// = Stack Memory ==========================================================================================
// Para completude, vale mencionar a memória de pilha. 
// Memória de pilha é um tipo de memória dinâmica reservada para variáveis declaradas dentro de funções. 
//Variáveis declaradas dentro de uma função usam memória de pilha em vez de memória estática.

// Quando uma função é chamada, memória de pilha é alocada para as variáveis da função. 
// Quando a função retorna, a memória da pilha é liberada.

// É bom estar ciente da memória de pilha para poder lidar com o uso de memória de chamadas de funções aninhadas e recursão. 
// Recursividade que se repete muitas vezes pode consumir muita memória de pilha. 
// Quando isso acontece, isso é chamado de stack overflow.



// = Realloc Memory ==========================================================================================
// Se a quantidade de memória reservada não for suficiente, você pode realocá-la para aumentá-la.
// Realocar reserva uma quantidade diferente (geralmente maior) de memória, mantendo os dados armazenados nela.
// Você pode alterar o tamanho da memória alocada com a função.realloc()
// A função assume dois parâmetros: realloc()
// int *ptr2 = realloc(ptr1, size);
// O primeiro parâmetro é um ponteiro para a memória que está sendo redimensionada.
// O segundo parâmetro especifica o novo tamanho da memória alocada, medido em bytes.
// A função tenta redimensionar a memória em ptr1 e retornar o mesmo endereço de memória. 
// Se não conseguir redimensionar a memória no endereço atual, 
// ele alocará a memória em um endereço diferente e retornará o novo endereço.realloc()



// = RESUMO ==========================================================================================

void resumo(){
 printf("\n");
 printf("malloc() - aloca memória \n");
 printf("calloc() - aloca + zera \n");
 printf("realloc() - redimensiona \n");
 printf("free() - libera memória \n");
}



void realloc_memory(){
 printf("= Realloc Memory =\n");
 int *ptr1, *ptr2, size;

 // Allocate memory for four integers
 size = 4 * sizeof(*ptr1);
 ptr1 = malloc(size);

 printf("%d bytes allocated at address %p \n", size, ptr1);

 // Resize the memory to hold six integers
 size = 6 * sizeof(*ptr1);
 ptr2 = realloc(ptr1, size);

 printf("%d bytes reallocated at address %p \n", size, ptr2);
}



void login(char user_name[], char user_password[]){
 if(strcmp(user_name, "gui") == 0 && strcmp(user_password, "123") == 0){
  printf("!LOGIN Olá %s\n", user_name);
 }else{
  printf("!Não Login Olá %s\n", user_name);
 } 
}



int main(){
 SetConsoleOutputCP(CP_UTF8); // UTF-8

 char nome[100];
 char senha[100];

 printf("LOGIN \n");
 printf("Digite seu nome:");
 scanf("%s", nome);

 printf("Digite sua senha:");
 scanf("%s", senha);

 login(nome, senha);
 
 char texto[100];
 // BUG: Usuário digita: 123[ENTER] O scanf("%s") lê: 123 MAS o ENTER: \n fica no buffer.
 while(getchar() != '\n'); // limpe o buffer:[ENTER] do scanf()
 printf("Digite seu Texto: "); // input 
 fgets(texto, sizeof(texto), stdin);
 printf("Você digitou: %s", texto);
 
 printf("Hello, World!\n");
 printf("Olá 😀\n");

 staticMemory();
 dynamicMemory();
 
 printf("\n");
 
 AccessDynamicMemory();
 
 printf("\n");

 realloc_memory();

 resumo();

 // Ao trabalhar com alocação dinâmica de memória, você também deve verificar erros e memória livre ao final do programa.
 return 0;
}
