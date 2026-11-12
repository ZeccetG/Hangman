#include <stdio.h>
#include <stdbool.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

void checkForLetterInWord(char word[], char userWord[], char letter, int size);
bool checkForCompletion(char word[], int size);
void gameInstruction(void);

int main() {

    srand(time(NULL));

    int r = rand() % 9;
    
    char choice = 0;
    int difficultylvl;

    const char *wordBank[3][9] = {
        {"flower", "ball", "car", "what", "place", "become", "large", "another", "group"},
        {"horizontal", "medieval", "revision", "derivative", "composition", "probation", "framework", "restoration", "discipline"},
        {"circumterrestrial", "polyglottist", "preadornment", "pedagogical", "paraphernalia", "micromorphology", "serpentises", "progymnasmata", "theorematically"}
    };  

    

    do {
    printf("Hangman\ns|start\ni|instructions\ne|exit\nEnter one of the letters: ");
    scanf(" %c", &choice);
    choice = tolower(choice);           // accept 'S', 'I', 'E' too
    if (choice == 'i')
        gameInstruction();
    } while (choice != 's' && choice != 'e');
    
    switch (choice){
        case 's':
            do{
                printf("Choose difficulty [1-3]: ");
                scanf("%d", &difficultylvl);
             } while (difficultylvl > 3 && difficultylvl < 1);

            break;
        case 'e':
            return 0;
        break;
    }


    const char *word = wordBank[difficultylvl - 1][r];
    
    


    return 0;
}



bool checkForCompletion(char word[], int size) {

    for (int i = 0; i < size; i++) {
        if (word[i] == '_') {
            return true;
        }
    }
    return false;
}

void checkForLetterInWord(char word[], char userWord[], char letter, int size) {

    for(int i = 0; i < size; i++) {
        if (word[i] == letter) {
            userWord[i] = letter; 
        }
    }
}

void gameInstruction(void) {
    printf("smt smt instruction"); 
}