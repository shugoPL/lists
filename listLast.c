#include <stdlib.h>
#include <stdio.h>
#include <string.h>

typedef struct {
    char word[256];
    unsigned int counter;
    struct words *next;
}words;
 

words* pushWord(words *element, char *string );
void printList(words *head);
words* elementInit( words *element);
words* readFromFile(char *path, words *head);
int searchList(words *head, char *string);

int main(){
    
    words *head = NULL;

    head = readFromFile("C:\\test.txt", head);
    printList(head);    
    
    return 0;
}

words* pushWord(words *element, char *string ){
    words *newElement = elementInit(newElement);
    
    strcpy(newElement->word, string);
    newElement->counter++;
    
    newElement->next = element;
    element = newElement;
    return element;
}

void printList(words *head){
    words *element = head;
    while( element != NULL ){
        printf("Slowo: %s wystapilo %d razy.\n", element->word, element->counter);
        element = element->next;
    }
}
 
words* elementInit( words *element){
    element = (words *)malloc( sizeof( words ));
    element->counter = 0;
    return element;
}

words* readFromFile(char *path, words *head){
    FILE *f = fopen(path, "r");
    char test[256];
    while(fscanf(f, "%s", test) != EOF ){
        if( searchList(head, test) == 0)
            head = pushWord(head, test);
    }
    fclose(f);
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