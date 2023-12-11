
#include "raylib.h"
#include <stdio.h>
#include <string.h>

#define MAX_WORD_LENGTH 30
void clearScreen() {
    for (int i = 0; i < 100; i++) {  // Print 100 new lines
        printf("\n");
    }
}
int main() {
    
    int screenWidth = 600;
    int screenHeight = 450;
    InitWindow(screenWidth, screenHeight, "Hangman Game");

    char secretWord[MAX_WORD_LENGTH] = {0};
    char displayWord[MAX_WORD_LENGTH] = {0};
    int letterCount = 0;
    int incorrectGuesses = 0;
    bool gameWon = false;
    char player1[MAX_WORD_LENGTH] = {0};
    char player2[MAX_WORD_LENGTH] = {0};
    
    
    SetTargetFPS(60);

    printf("\n\n\n\n\n\n\n\n\n\n\n\n\n\n\nWelcome to the Hangman game!\n\n\n\n\n");
    printf("Player 1 please enter your name: \n\n\n");
    
    scanf("%s",player1);
    printf("Player 2 please enter your name: \n\n\n");
    scanf("%s",player2);
    printf("%s, please enter the secret word: ", player1);
    scanf("%s", secretWord);
    letterCount = strlen(secretWord);

    for (int i = 0; i < letterCount; i++) {
        displayWord[i] = '_';
    }
    displayWord[letterCount] = '\0';
   
    clearScreen();
    printf("%s, remember you have only three chances!",player2);
    while (!WindowShouldClose() && !gameWon && incorrectGuesses < 3) {
        

        printf("\n %s, guess a letter: \n",player2);
        char guess;
        scanf(" %c", &guess);
       
        bool found = false;
        for (int i = 0; i < letterCount; i++) {
            if (secretWord[i] == guess || secretWord[i] == (guess + ('a' - 'A')) || secretWord[i] == (guess - ('a' - 'A'))) {
                displayWord[i] = secretWord[i];
                found = true;
            }
        }

        if (!found) {
            incorrectGuesses++;
            int remaining=3-incorrectGuesses;
            printf("%s, Fail!!! You have %d chances remaining",player2,remaining );
        } else {
            printf("%s, Correct guess!\n",player2);
            if (strcmp(displayWord, secretWord) == 0) {
                gameWon = true;
            }
        }

        BeginDrawing();
        ClearBackground(RAYWHITE);
        DrawText(displayWord, 50, 100, 40, BLACK);

        if (incorrectGuesses >= 3) { int screenWidth = 600;
            int screenHeight = 450;

            InitWindow(screenWidth, screenHeight, "  Hangman ");

            SetTargetFPS(60);

          
            while (!WindowShouldClose()) {
            DrawText("YOU FAILED- LOOSER!", 190, 300, 20, RED);
            
            
                                  

                                   DrawLineEx((Vector2){150, 100}, (Vector2){150, 350}, 5.0, RED);
                                   DrawLineEx((Vector2){150,100}, (Vector2){450,100}, 5.0, RED);
                                       
                                   DrawLineEx((Vector2){300,100}, (Vector2){300,150}, 3.0, BROWN);// small vertical line

                                       // Draw hangman
                                       // Head
                                       DrawCircle(300, 170, 20, BEIGE);

                                       // Body
                                   DrawLineEx((Vector2){300, 190},(Vector2){ 300, 200},5.0, BROWN);
                                   Color pastelPink = {255, 182, 193, 255};
                                   // Triangle Body
                                   Vector2 bodyTop = (Vector2){300, 190}; // Top of the body (neck position)
                                   Vector2 bodyLeft = (Vector2){280, 250}; // Bottom-left of the body
                                   Vector2 bodyRight = (Vector2){320, 250}; // Bottom-right of the body
                                   DrawTriangle(bodyTop, bodyLeft, bodyRight, pastelPink);
                                       // Arms
                                   DrawLineEx((Vector2){300, 200},(Vector2){ 270, 230},2.0, BEIGE);
                                   DrawLineEx((Vector2){300, 200},(Vector2){ 330, 230},2.0, BEIGE);

                                       // Legs
                                   DrawLineEx((Vector2){300, 190},(Vector2){ 300, 200},5.0, BROWN);
                                   DrawLineEx((Vector2){295, 250},(Vector2){ 295, 280},2.0, BEIGE);
                                   DrawLineEx((Vector2){305, 250}, (Vector2){305, 280},2.0, BEIGE);
                EndDrawing();
                                      
                                  }

                                
                                  CloseWindow();

                                

                                   
        } else if (gameWon) {
            int screenWidth = 500;
            int screenHeight = 600;

                InitWindow(screenWidth, screenHeight, "  Hangman ");

                SetTargetFPS(60);

                
                while (!WindowShouldClose()) {
                DrawText("YOU WON!", 120, 190, 50, RED);
                    DrawText("The word you guessed is:", 50, 250, 30, RED);
                    DrawText(displayWord, 120, 310, 40, RED);
                
                    EndDrawing();
                                         
                                      }

                                      
                                      CloseWindow();

        }}
    return 0;
}
