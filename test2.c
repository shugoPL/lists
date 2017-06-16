#include <stdlib.h>
#include <stdio.h>
#include <string.h>

typedef struct {
    char word[256];
    unsigned int counter;
    struct words *next;
}words;

void printList(words *head);
words* elementInit( words *element);
words* readFromFile(char *path, words *head);
int searchList(words *head, char *string);
words* pushInOrderTest2(words *element, char *string );
words* pushInMiddle(words *element, char *string);
words* pushOnEnd(words *element, char *string);
words* pushOnStart(words *element, char *string);
words* initNode(char *string);



int main(){
    
    words *head = NULL;

    head = readFromFile("C:\\test.txt", head);
    printList(head);    
    
    return 0;
}


void printList(words* element){
    words* printedElement = element;
    while( printedElement ){
        printf("%s %d \n", printedElement->word,printedElement->counter);
        printedElement = printedElement->next;
    }
}
 
words* elementInit( words *element){
    element = (words *)malloc( sizeof( words ));
    element->counter = 0;
    return element;
}

words* readFromFile(char *path, words *head){
    FILE *f = fopen(path, "r");
    unsigned int enterCounter = 0;
    char test[256];
    while(fscanf(f, "%s", test) != EOF ){
        /*Sprawdzenie czy pierwsza litera jest duża i konwersja 
         * na małą jeżeli jest */
        if( test[0] >= 65 && test[0] <= 90)
            test[0] = test[0] + 32;
                
        /* Sprawdzenie czy słowo jest już na liście jeżeli jest dodanie ilości
         o 1 jeże nie ma dodanie do listy w kolejności alfabetycznej */
        if( searchList(head, test) == 0)
            head = pushInOrderTest2(head, test);
    }
    fclose(f);
    printf("w pliku są %u spacje\n", enterCounter);
    return head;
}

int searchList(words *head, char *string){
    words* element = head;
    while(element != NULL){
        if( strcmp(element->word, string) == 0 ){
            element->counter++;
            return 1;
        }
        element = element->next;
    }
    return 0;
}


words* initNode(char *string){
    words *newElement = (words *)malloc(sizeof(words));
    strcpy(newElement->word,string);
    newElement->counter = 1;
    return newElement;
}

words* pushOnStart(words *element, char *string){
    words *newElement = initNode(string);
    newElement->next = element;
    element = newElement;
    return element;
}

words* pushOnEnd(words *element, char *string){
    words *newElement = initNode(string);
    words *start = element;
    while( element->next != NULL)
        element = element->next;
    newElement->next = NULL;
    element->next = newElement;
    return start;
}



words* pushInMiddle(words *element, char *string){
    words *start = element;
    words *node = initNode(string);
    
    while(element != NULL){
        words *nextNode = element->next; //Linia pozwalaj¹ca sprawdziæ wartoœæ nastêpnego elementu
        
        if(nextNode == NULL){
            pushOnEnd(start, string);
            return start;
        }
        
        if( strcmp(nextNode->word, string) == 1 ){
            node->next = nextNode;
            element->next = node;           
            return start;
        }
        element = element->next;
    } 
}



words* pushInOrderTest2(words *element, char *string ){
    words *node = element;
   
    if( (node == NULL) || strcmp( node->word, string) == 1 ){
        node = pushOnStart(node, string);
        return node;
    }
    else if( node->next == NULL && strcmp(node->word,string) == -1 ){
        pushOnEnd(node, string);
    }else{
        pushInMiddle(node, string);
    }
}
