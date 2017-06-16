#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define DEFAULT_WORD_LEN 256

typedef struct{
    char word[DEFAULT_WORD_LEN];
    struct words *next;
}words;

words* initNode(char *val){
    words *newElement = (words *)malloc(sizeof(words));
    strcpy(newElement->word,val);
    return newElement;
}

words* pushOnStart(words *element, char *val){
    words *new = initNode(val);
    new->next = element;
    element = new;
    return element;
}

words* pushOnEnd(words *element, char *val){
    words *new = initNode(val);
    words *start = element;
    while( element->next != NULL)
        element = element->next;
    new->next = NULL;
    element->next = new;
    return start;
}


void printList(words* element){
    words* printedElement = element;
    while( printedElement ){
        printf("%s \n", printedElement->word);
        printedElement = printedElement->next;
    }
}

words* pushInMiddle(words *element, char *val){
    words *start = element;
    words *node = initNode(val);
    
    while(element != NULL){
        words *nextNode = element->next; //Linia pozwalająca sprawdzić wartość następnego elementu
        
        if(nextNode == NULL){
            pushOnEnd(start, val);
            return start;
        }
        
        if( strcmp(nextNode->word, val) == 1 ){
            node->next = nextNode;
            element->next = node;           
            return start;
        }
        element = element->next;
    } 
}

words* pushInOrderTest2(words *element, char *val ){
    words *node = element;
   
    if( (node == NULL) || strcmp( node->word, val) == 1 ){
        node = pushOnStart(node, val);
        return node;
    }
    else if( node->next == NULL && strcmp(node->word,val) == -1 ){
        pushOnEnd(node, val);
    }else{
        pushInMiddle(node, val);
    }
}

int main() {
    words *head = NULL;
    
    head = pushInOrderTest2(head, "bbb");
    head = pushInOrderTest2(head, "ddd");
    head = pushInOrderTest2(head, "ccc");
    head = pushInOrderTest2(head, "eee");
    head = pushInOrderTest2(head, "aa");
    head = pushInOrderTest2(head, "ff");
    //head = pushInOrderTest2(head, 2);
    printList(head);
    return 0;
}