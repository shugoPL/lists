#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//Podstawowa struktura będąca elementem listy
typedef struct {
    char word[256];
    int counter;
    struct mainList *next;
}words;

//Deklaracje funkcji wykorzystanych w aplikacji

words* initNode(char *string);   //Obsługa utworzenia nowego elementu listy
words* pushOnStart(words *element, char *string);  //Dodawanie na początek
void pushInOrder(words *element, char *string );
void printList(words* element); //Wyświetlanie wszystkich elementów
void readFromFile(char *path);  //Funckaj odczytuje i wypisuje na standardowe wyjście zawartość pliku
words* readFromFileV2(char *path, words *element );
int searchList( words* element, char *string ); //Przeszukiwanie listy

//koniec deklaracji

int main(){
    words* head = NULL;    
    head = readFromFileV2("C:\\Users\\maciej.gora\\Desktop\\test.txt", head);
    printList(head);
    
    return 0;
}

//Funkcja inicjalizująca nowego noda na liście zwaraca adres nowego elementu
words* initNode(char *string){
    words *newElement = (words *)malloc(sizeof(words));
    strcpy(newElement->word, string);
    newElement->counter = 1;
    return newElement;
}
/*Funkcja która dodaje na początku listy jednokierunkowej nowy element.
 * Funkcja korzysta initNode do utworzenia nowego elementu na liście. */
 words* pushOnStart(words *element, char *string){
    words *new = initNode(string);
    
    new->next = element;
    element = new;
    return element;
}
/* Funkcja dodająca słowa w kolejności */
void pushInOrder(words *element, char *string ){
     words *node = element;
     while( node->next != NULL ){
         if ( strcmp( node->word, string) < 0 ){
            words* newElement = initNode(string);
            newElement->next = node->next;
            node->next = newElement;
        }
        node = node->next;
     }
 }
 
 //Standardowe wyświetlanie wszystkich elementów listy
void printList(words* element){
    words* printedElement = element;
    while( printedElement ){
        printf("%s , %d\n", printedElement->word, printedElement->counter);
        printedElement = printedElement->next;
    }
}
/* Funcka realizująca odczytywanie wartości z pliku tekstowego słowo po słowie
 nie uwzględniająca znaków takich jak kropki i inne */
void readFromFile(char *path){
    FILE *f = fopen(path, "r");
    char word[256];
    while( fscanf(f, "%s", word ) != EOF )
        printf("%s ", word);
    fclose(f);
}

words* readFromFileV2(char *path, words *element ){
    FILE *f = fopen(path, "r");
    char word[256];
    while( fscanf(f, "%s", word ) != EOF )
        if( searchList(element, word) == 0 ){
            if( element == NULL )
                element = pushOnStart(element, word);
            else
                pushInOrder(element, word);
        }
    fclose(f);
    return element;
}
/* Przeszukiwanie listy pod kątem podanego slowa
 * Jeżeli funkcja znajdzie dane słowo podnosi counter o 1
 * Jeżeli funkcja nie znajdzie słowa zwraca wartość 0
 */
int searchList( words* element, char *string ){
    words *node = element;
    while( node != NULL ){
        if( strcmp(node->word, string) == 0 ){
            node->counter++;
            return 1;
        }
        node = node->next;
    }
    return 0;
}
