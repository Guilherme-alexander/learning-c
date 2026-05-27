/*
-----------------------------------------------
[+] array:
 |--> int *nums = malloc(5 * sizeof(int));
-----------------------------------------------
[+] calloc:
 |--> int *nums = calloc(5, sizeof(int));
-----------------------------------------------
[+] array:
 |--> nums = realloc(nums, 10 * sizeof(int));
-----------------------------------------------
*/

#include <stdio.h>
#include <stdlib.h>

int main() {

    int *ptr;

    // pede memória
    ptr = malloc(sizeof(int));

    // coloca valor ptr -----------> [ 50 ]
    *ptr = 50;

    // lê valor
    printf("%d\n", *ptr);

    // libera memória
    free(ptr);

    return 0;
}
