#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define TABLE_MAX_LENGTH 100000
#define TAB_BASE 10000

void randomize(int *tab, int tabLen);
int lineSearch(int *tab, int tabLen, int elem);
int binarySearch(int *tab, int tabLen, int elem);

int main() {
    //srand( time( NULL ));
    int *mainTable = (int*)malloc( sizeof(int) * TABLE_MAX_LENGTH);
    randomize(mainTable, TABLE_MAX_LENGTH);
    
    printf("Wyszukiwanie liniowe \n");
    int i;
    for( i = 1; i <= 10; i++ ){
        printf("%d.000 : %d\n", i * 10, lineSearch(mainTable, TAB_BASE * i, TAB_BASE * i));
    }
    
    printf("Wyszukiwanie binarne \n");
    for( i = 1; i <= 10; i++ ){
        printf("%d.000 : %d\n", i * 10, binarySearch(mainTable, TAB_BASE * i, TAB_BASE * i ));
    }    
    return 0;
}
void randomize(int *tab, int tabLen){
    int i;
    for( i = 0; i < tabLen; i++)
        tab[i] = i + 1;
}
int lineSearch(int *tab, int tabLen, int elem){
    int i, c = 0;
    c += 2;
    for(i = 0; i <= tabLen; i++){
        if ( tab[i] == elem ){
            return c;          
        }
        c += 3;
    }
    return -1.0; 
}
int binarySearch(int *tab, int tabLen, int elem){
    int middle, left = 0, right = tabLen - 1, counter = 0;

    counter += 1;
    while( left <= right){
        middle = (left + right)/ 2;
        if( tab[middle] == elem){
            
            return counter;
        }
        if( tab[middle] < elem ){
            left = middle + 1;
            counter += 3;
        }
        else{
            right = middle - 1;
            counter += 3;
        }
    }
    return -1.0;
}





