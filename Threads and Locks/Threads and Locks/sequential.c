#include <stdio.h>
#include <stdlib.h>
#define ARRAY_SIZE 1000000

int sum = 0;

int main(){
    int i;
    int num[ARRAY_SIZE];
    srand(100);

    for(i=0; i< ARRAY_SIZE; i++){
        num[i] = rand() % 100;
    }

    for(i=0; i<ARRAY_SIZE; i++){
	sum += num[i];
    }

    printf("sum = %d\n", sum);
    return 0;
}
