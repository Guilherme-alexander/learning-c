#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Random Numbers
// Em C, você pode criar números aleatórios com a função rand(), que está na biblioteca <stdlib.h>
// Por padrão, dá a mesma sequência de números toda vez que você roda o programa. 
// Para obter resultados diferentes em cada tentativa, você também pode usar para definir um "ponto de partida" (chamado seed).
// Como você acabou de aprender sobre data e hora, agora pode usar a hora atual como semente (porque ela está sempre mudando).
// Para isso, você inclui no seu programa.rand()srand()<time.h>

// rand(); - gerar número randomico padrão, Cada compilador pode implementar diferente.
// rand() - NÃO é seguro para: criptografia, senhas, tokens, chaves.

// srand(); - cria seeds para o rand()
// srand(time(NULL)); - cria seeds para o rand() usando tempo como seed.


void randomFunction(){
 srand(1);
 int r = rand();	// C usa uma seed padrão fixa. Então toda execução:41, 18467, 6334, 26500, ...

 printf("%d\n", r);
}


void randomTimeSeed(){
 srand(time(NULL));

 int x = rand() % 10;  // 0..9
 printf("%d\n", x);
}


void randomRollingDice(){
  srand(time(NULL));

  int dice1 = (rand() % 6) + 1;
  int dice2 = (rand() % 6) + 1;
  printf("You rolled %d and %d (total = %d)\n", dice1, dice2, dice1 + dice2);
}

int main(){
 printf("Run..!\n");

 printf("=== Default ===\n");
 randomFunction();

 printf("=== Random Number in a Range 0 .. 9 ===\n");
 randomTimeSeed();

 printf("=== Real-Life Example: Rolling Dice 1 to 6: ===\n");
 randomRollingDice();

 printf("=== Default Seeds ===\n");
 srand(1);

 printf("%d\n", rand()); 
 printf("%d\n", rand());
 printf("%d\n", rand());

 return 0;
}
