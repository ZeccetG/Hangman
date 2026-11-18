#include <stdio.h>
#include <stdbool.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

bool checkForIncompletion(int size, char guessedWord[]);
int checkForLetterInWord(const char word[], char userWord[], char letterOrWord[], int size);
void gameInstruction(void);
void arrDisplay(char word[], int size);
void printHangMan(int maxLives, int hangedman);
int theGame(char word[], int difficultylvl, int wordLength);

int main() {

    srand(time(NULL)); // get random number
    int r = rand() % 9;

    char choice; // determine what the user wants to do at start menu 
    int difficultylvl; 
    int score;

    char *wordBank[3][15] = {
        {"flower", "ball", "person", "what", "place", "become", "large", "another", "group", "people", "school", "public", "possible", "develop", "little"},
        {"horizontal", "medieval", "revision", "derivative", "composition", "probation", "framework", "restoration", "discipline", "programmer", "recognition", "mountain", "battery", "splash", "backpack"},
        {"circumterrestrial", "polyglottist", "preadornment", "pedagogical", "paraphernalia", "micromorphology", "serpentises", "progymnasmata", "theorematically", "cannibalize", "silhouette", "characterized", "disenfranchised", "diachronous", "isophenomenal"}
    }; // Bare witness to 3d array of word bank

    do {
        printf("Hangman\ns|start\ni|instructions\ne|exit\nEnter one of the letters: ");
        scanf(" %c", &choice);

        choice = tolower(choice); //make sure capitial letter still works
        if (choice == 'i')
            gameInstruction();

    } while (choice != 's' && choice != 'e'); // keep looping til we get one of the options


    switch (choice) { // ??? i guess if you want to use switch case but a singlar if statement will do since only s will progress
        case 's':
            do {
                printf("Choose difficulty [1-3]: ");
                scanf("%d", &difficultylvl);
            } while (difficultylvl > 3 || difficultylvl < 1);
            break;

        case 'e':
            return 0;
    }

    while (getchar() != '\n'); // This gets rid of the residual character in the consoel. DO NOT REMOVE

    char *word = wordBank[difficultylvl - 1][r];
    int wordLength = strlen(word);
    score = theGame(word, difficultylvl, wordLength); //move that whole thing to make this easier to read
    printf("Score: %d", score); // also easier on making a loop and eventually a scoring 
    
    return 0;
}

// Displays any array
void arrDisplay(char word[], int size) {
    for (int i = 0; i < size; i++) {    // Simple display the array, self defining
        printf("%c", word[i]);
    }
}

int checkForLetterInWord(const char word[], char guessedWord[], char letterOrWord[], int size) {
     
    if (letterOrWord[1] == '\0'){ // This makes sure the letterOrWord is only one letter long
        int ifChange = 1; // I can't think of another way but this
        for(int i = 0; i < size; i++) {
            if (word[i] == letterOrWord[0]) {
                guessedWord[i] = letterOrWord[0]; 
                ifChange = 0; // no return here because we want all the avaiable letter to show first before return. 
            }
        }
        return ifChange; // returning 1 to indicate the live lost. 0 if the letter was correct or in it. 
    }

    else {
        if (strcmp(word, letterOrWord) == 0) { // any amount of letter greator than 1 will be assumed as guess of whole word
            return 3; // 3 indicate the game over
        }
        return 1; // 1 life lost
    }
}

bool checkForIncompletion(int size, char guessedWord[]) {
    for (int i = 0; i < size; i++) {
        if (guessedWord[i] == '_') { // if any "_" still there, game aint over
            return true;
        }
    }
    return false;
}

void printHangMan(int lives, int maxLives) {

    int mistakes = maxLives - lives; 
    int stage = (mistakes * 6 + maxLives / 2) / maxLives; // i gotta get a really weird formula but even if we change the lives, it still works fine

    printf("\n");
    printf(" +---+\n");
    printf(" |   |\n");

    // Head
    if (stage >= 1)
        printf(" O   |\n");
    else
        printf("     |\n");

    // Body and arms
    if (stage >= 2) {
        if (stage >= 3 && stage >= 4)
            printf("/|\\  |\n");
        else if (stage >= 3)
            printf("/|   |\n");
        else
            printf(" |   |\n");
    }
    else
        printf("     |\n");

    // Legs
    if (stage >= 5 && stage >= 6)
        printf("/ \\  |\n");
    else if (stage >= 5)
        printf("/    |\n");
    else
        printf("     |\n");

    printf("     |\n");
    printf("=======\n"); 
    // This fucking sucks to make
}

int theGame(char word[], int difficultylvl, int wordLength) {

    int maxLives = 5 + difficultylvl; // lives are now 9, 7, 5 for increasing difficulty respectivly
    int hangedman = maxLives;

    char userinput[wordLength+1]; // +1 because i also gotta include the \n when they hit enter and \0 when the string ends

    char guessedWord[wordLength]; 
    for(int i = 0; i < wordLength; i++) {
        guessedWord[i] = '_'; // fill it all with "_"
    }

    while (checkForIncompletion(wordLength, guessedWord) && hangedman > 0) { 

        printHangMan(hangedman, maxLives); // show the image of the hangman
        arrDisplay(guessedWord, wordLength); // show the silhouette of the word

        printf("\nYou got %d lives left. \nEnter your letter or word: ", hangedman);
        fgets(userinput, wordLength + 1, stdin);
        
        userinput[strcspn(userinput, "\n")] = '\0'; // find the first instance of \n and replace it with \0
        for (int i = 0; userinput[i] != '\0'; i++) {
            userinput[i] = tolower((unsigned char)userinput[i]); // make everything lowercase
        }

        if (userinput[0] == '\0') // if they only hit enter, repeat the loop without anything else
            continue;

        int life = checkForLetterInWord(word, guessedWord, userinput, wordLength); 
        if (life == 3) { // 3 means game over, guessed the whole word
            break;
            }
        hangedman -= life; // remove 0 or 1 live 
    }

    if (hangedman <= 0) { // no life on the hangman GG
        printHangMan(hangedman, maxLives);
        printf("\nSorry, You lost. The word was: ");
        arrDisplay(word, wordLength);
        printf("\n");
        return 0; // no points
    }
    else{ // any other instance ie not lose ie a win
        printHangMan(hangedman, maxLives);
        printf("You won! The word was: ");
        arrDisplay(word, wordLength);
        printf("\n");
        return hangedman * difficultylvl; // returns the points awarded. 
    }
    
}


void gameInstruction(void) {
    printf("smt smt instruction\n"); // TBD next time we meet
}

