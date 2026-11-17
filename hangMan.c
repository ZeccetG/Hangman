#include <stdio.h>
#include <stdbool.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

void checkForCompletion(const char word[], const char userinput[]);
int checkForWord(const char word[], const char userinput[]);
void gameInstruction(void);
void underscoredisplay(const char word[]);

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
        choice = tolower(choice);

        if (choice == 'i')
            gameInstruction();

    } while (choice != 's' && choice != 'e');

    switch (choice) {
        case 's':
            do {
                printf("Choose difficulty [1-3]: ");
                scanf("%d", &difficultylvl);
            } while (difficultylvl > 3 || difficultylvl < 1);

            break;

        case 'e':
            return 0;
    }

    const char *word = wordBank[difficultylvl - 1][r];
    char userinput[20];

    underscoredisplay(word);

    printf("\nEnter your guess: ");
    scanf("%19s", userinput);

    checkForCompletion(word, userinput);

    return 0;
}

// Takes the word and displays it as _
void underscoredisplay(const char word[]) {
    int size = strlen(word);

    for (int i = 1; i < size; i++) {
        printf("_ ");
    }

    printf("\n");
}

int checkForWord(const char word[], const char userinput[]) {

    int size = strlen(word);
    int verify = 0;

    for (int i = 0; i < size; i++) {
        if (i < strlen(userinput) && userinput[i] == word[i]) {
            printf("%c", userinput[i]);
            verify++;

        } else {
            printf("_ ");
        }
    }

    printf("\n");

    return verify;
}

void checkForCompletion(const char word[], const char userinput[]) {

    char guess[20];
    strcpy(guess, userinput);

    int verify = checkForWord(word, guess);

    while (strlen(word) != verify) {
        printf("\nTry again: ");
        scanf("%19s", guess);

        verify = checkForWord(word, guess);
    }

    printf("\nCongratulations! You guessed the word!\n");
}

void gameInstruction(void) {
    printf("smt smt instruction\n");
}
