#include "raylib.h"
#include <stdio.h>
#include <string.h>
#include <time.h>
#include <stdlib.h>

#define MAX_GUESSES 3
#define MAX_INPUT_CHARS 9

void DrawHangman(int lives) {
    // Draw the hangman based on the number of lives remaining
    // Adjust the positions and sizes as needed
    
    // Hangman stand
    DrawLineEx((Vector2){150, 350},(Vector2){ 250, 350},5.0, DARKBROWN); // Base
    DrawLineEx((Vector2){200, 350}, (Vector2){200, 150},5.0, DARKBROWN); // Stand
    DrawLineEx((Vector2){200, 150},(Vector2) {300, 150},5.0, DARKBROWN); // Top
    DrawLineEx((Vector2){300, 150}, (Vector2){300, 200},5.0, BROWN); // Noose
    Color pastelPink = {255, 182, 193, 255};
    
    // Hangman body parts
    if (lives <= 2) DrawCircle(300, 220, 20, BEIGE); // Head
    
    if (lives <= 1) DrawTriangle((Vector2){ 300, 240 },
                                 (Vector2){ 280, 300 },
                                 (Vector2){ 320, 300 }, pastelPink); // Body
    if (lives == 0) {
        DrawLine(300, 250, 270, 280, BEIGE); // Left arm
        DrawLine(300, 250, 330, 280, BEIGE); // Right arm
        DrawLine(300, 300, 270, 330, BEIGE); // Left leg
        DrawLine(300, 300, 330, 330, BEIGE); // Right leg
    }
}

int main() {
    // Initialization
    const int screenWidth = 800;
    const int screenHeight = 450;
    
    InitWindow(screenWidth, screenHeight, "Hangman Game - Raylib");
    
    char *words[] = {"SALUT", "CODING", "CHRISTMAS", "HALLOWEEN"};
    char *selectedWord = NULL;
    int numberOfWords = sizeof(words) / sizeof(words[0]);
    srand(time(NULL));
    
    char guessedWord[MAX_INPUT_CHARS + 1] = "\0"; // Guessed word for single player
    char multiplayerWord[MAX_INPUT_CHARS + 1] = "\0"; // Word for multiplayer mode
    char inputWord[MAX_INPUT_CHARS + 1] = "\0"; // Buffer for input word in multiplayer
    int lives = MAX_GUESSES;
    bool gameOver = false;
    bool win = false;
    bool wordSet = false; // Flag to check if word is set in multiplayer mode
    int letterCount = 0; // Count of letters entered in multiplayer mode
    
    int gameState = 0; // 0 for menu, 1 for single player, 2 for multiplayer
    Rectangle singlePlayerBtn = { 320, 220, 150, 50 };
    Rectangle multiPlayerBtn = { 320, 280, 150, 50 };
    
    SetTargetFPS(60);
    
    // Main game loop
    while (!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(RAYWHITE);
        
        if (gameState == 0) {
            // Main menu
            DrawText("Main Menu", 340, 180, 20, LIGHTGRAY);
            
            // Single Player Button
            if (CheckCollisionPointRec(GetMousePosition(), singlePlayerBtn) && IsMouseButtonReleased(MOUSE_LEFT_BUTTON)) {
                gameState = 1;
                selectedWord = words[rand() % numberOfWords];
                strcpy(guessedWord, selectedWord);
                for (int i = 0; i < strlen(guessedWord); i++) {
                    guessedWord[i] = '_';
                }
                guessedWord[strlen(guessedWord)] = '\0'; // Null-terminate the guessed word
                lives = MAX_GUESSES;
                gameOver = false;
                win = false;
            }
            
            // Multiplayer Button
            if (CheckCollisionPointRec(GetMousePosition(), multiPlayerBtn) && IsMouseButtonReleased(MOUSE_LEFT_BUTTON)) {
                gameState = 2;
                memset(inputWord, 0, MAX_INPUT_CHARS + 1);
                memset(multiplayerWord, 0, MAX_INPUT_CHARS + 1);
                memset(guessedWord, 0, MAX_INPUT_CHARS + 1);
                wordSet = false;
                letterCount = 0;
                lives = MAX_GUESSES;
                gameOver = false;
                win = false;
            }
            
            // Drawing the buttons
            DrawRectangleRec(singlePlayerBtn, LIGHTGRAY);
            DrawRectangleRec(multiPlayerBtn, LIGHTGRAY);
            DrawText("Single Player", singlePlayerBtn.x + 10, singlePlayerBtn.y + 15, 20, BLACK);
            DrawText("Multiplayer", multiPlayerBtn.x + 10, multiPlayerBtn.y + 15, 20, BLACK);
        }
        else if (gameState == 1) {
            // Single Player game logic
            if (!gameOver) {
                int key = GetKeyPressed();
                
                // Convert lowercase input to uppercase
                if (key >= 'a' && key <= 'z') {
                    key -= ('a' - 'A'); // Convert to uppercase
                }
                
                // Check if the key is an uppercase letter
                if (key >= 'A' && key <= 'Z') {
                    bool found = false;
                    for (int i = 0; i < strlen(selectedWord); i++) {
                        // Convert character in word to uppercase for comparison
                        char wordChar = selectedWord[i];
                        if (wordChar >= 'a' && wordChar <= 'z') {
                            wordChar -= ('a' - 'A'); // Convert to uppercase
                        }
                        
                        if (wordChar == (char)key && guessedWord[i] == '_') {
                            guessedWord[i] = selectedWord[i]; // Update the guessed word with the original case
                            found = true;
                        }
                    }
                    
                    if (!found) {
                        lives--;
                    }
                    
                    // Check for win or lose
                    if (strcmp(guessedWord, selectedWord) == 0) { // Compare guessed word with the selected word
                        win = true;
                        gameOver = true;
                    } else if (lives <= 0) {
                        gameOver = true;
                    }
                }
            }
            
            // Draw the game state
            DrawText(guessedWord, 400, 200, 20, BLACK);
            DrawHangman(lives);
            if (gameOver) {
                if (win) {
                    DrawText("You Win!", 350, 250, 20, GREEN);
                } else {
                    DrawText("Game Over!", 350, 250, 20, RED);
                    DrawText(selectedWord, 350, 300, 20, BLACK); // Reveal the word
                }
            }
        }
        
        else if (gameState == 2) {
            if (!wordSet) {
                // Allow the first player to set the word
                DrawText("Enter a word: ", 300, 200, 20, LIGHTGRAY);
                DrawText(inputWord, 430, 200, 20, MAROON);
                
                int key = GetCharPressed();
                while (key > 0) {
                    if ((key >= 'A' && key <= 'Z') && (letterCount < MAX_INPUT_CHARS)) {
                        inputWord[letterCount] = (char)key;
                        inputWord[letterCount + 1] = '\0';
                        letterCount++;
                    }
                    key = GetCharPressed();
                }
                
                if (IsKeyPressed(KEY_ENTER) && letterCount > 0) {
                    wordSet = true;
                    strcpy(multiplayerWord, inputWord);
                    for (int i = 0; i < strlen(multiplayerWord); i++) {
                        guessedWord[i] = '_';
                    }
                    guessedWord[strlen(multiplayerWord)] = '\0';
                }
            } else {
                // Second player guesses the word
                if (!gameOver) {
                    // Handling key inputs for guessing the word
                    int key = GetKeyPressed();
                    if (key >= 'A' && key <= 'Z') {
                        bool found = false;
                        for (int i = 0; i < strlen(multiplayerWord); i++) {
                            if (multiplayerWord[i] == (char)key && guessedWord[i] == '_') {
                                guessedWord[i] = (char)key;
                                found = true;
                            }
                        }
                        if (!found) {
                            lives--;
                            if (lives <= 0) {
                                gameOver = true;
                            }
                        }
                    }
                    
                    // Check for win condition
                    if (strcmp(guessedWord, multiplayerWord) == 0) {
                        win = true;
                        gameOver = true;
                    }
                }
                
                // Drawing the guessed word and hangman
                DrawText(guessedWord, 400 - MeasureText(guessedWord, 20) / 2, 200, 20, BLACK);
                DrawHangman(lives);
                
                // Display win or lose message
                if (gameOver) {
                    if (win) {
                        DrawText("You Win!", 350, 250, 20, GREEN);
                    } else {
                        DrawText("Game Over!", 350, 250, 20, RED);
                        DrawText(multiplayerWord, 350 - MeasureText(multiplayerWord, 20) / 2, 300, 20, BLACK); // Reveal the word
                    }
                }
            }
            
        }
        
        EndDrawing();
    }
    
    CloseWindow();
    return 0;
}
