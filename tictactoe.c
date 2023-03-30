/*
    Kazi Amin
    Project #1
    Tic Tac Toe Game

    To Do
    - Hard Difficulty
*/ 

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// Stores X, O 
char boardValues[10];

// Function Prototypes
void printBoard(char* player1Name, char* player2Name);
void inputChoice(int userChoiceRow, int userChoiceColumn, char symbol);
void computerEasySelection(int* randRow, int* randColumn);
void validPlayerChoice(int* validRow, int* validColumn, char* playerName);
void initializeBoard(void);
void getName(char* playerName, int playerNumber);
int resetGame(int* exitKey, int* turn);
int menuSelect(void);
int checkRow(void);
int checkColumn(void);
int checkDiagonal(void);
int checkWin(int turn);
int checkDif(int playerRow, int playerColumn);
int checkRange(int playerRow, int playerColumn);

typedef struct Players
{
    char playerName[20];
    char playerSymbol;   
    int rowChoice;
    int columnChoice;
} Players;

int main(void)
{   
    srand(time(0));
    Players player1, player2, computerEasy;
    player1.playerSymbol = 'X';
    player2.playerSymbol = 'O';
    computerEasy.playerSymbol = 'O';
    strcpy(computerEasy.playerName, "Computer(Easy)");
    printf("Welcome to the Tic-Tac-Toe Game\n");
    int userSelection = menuSelect();
    // Player Vs Player
    if (userSelection == 1)
    {
        getName(player1.playerName, 1);
        getName(player2.playerName, 2);

        int turn = 0, exitKey;
        while (true)
        {
            // Resets exit key 
            exitKey = 0;
            //  Initializes Empty Values into boardValues Array for the first turn
            if (turn == 0)
            {
                initializeBoard();
                printBoard(player1.playerName, player2.playerName);
                turn++;
            }

            // If there is no winner on turn 9, draw is declared and User is given option to play again or exit game 
            else if (turn == 10)
            {
                printf("There are no winners.\n");
                if (resetGame(&exitKey, &turn) == 0)
                    return 0;
                
            }

            // If turn is not divisible by 2 -- Player 1 Turn
            else if (turn % 2 != 0 && exitKey == 0)
            {
                // Player 1 Location Selector
                validPlayerChoice(&player1.rowChoice, &player1.columnChoice, player1.playerName);

                // Places designated symbol of player to desired location
                inputChoice(player1.rowChoice, player1.columnChoice, player1.playerSymbol);

                // Checks if Player 1 has Won
                if (checkWin(turn) == 1)
                {
                    printBoard(player1.playerName, player2.playerName);
                    printf("%s Wins!\n\n", player1.playerName);
                    if (resetGame(&exitKey, &turn) == 0)
                        return 0;
                }
                // Else increases turn by 1
                else
                {
                    printBoard(player1.playerName, player2.playerName);
                    turn++;
                }

            }

            // If turn is divisible by 2 -- Player 2 Turn
            else if (turn % 2 == 0 && exitKey == 0)
            {
                validPlayerChoice(&player2.rowChoice, &player2.columnChoice, player2.playerName);

                // Places Valid Location in boardValues array
                inputChoice(player2.rowChoice, player2.columnChoice, player2.playerSymbol);

                // Checks for Player 2 Win
                if (checkWin(turn) == 2)
                {
                    printBoard(player1.playerName, player2.playerName);
                    printf("%s Wins!\n\n", player2.playerName);
                    if (resetGame(&exitKey, &turn) == 0)
                        return 0;
                }
                // Prints Board & Increases Turn by 1
                else
                {
                    printBoard(player1.playerName, player2.playerName);
                    turn++;
                }
            }
        }
    }
    else if (userSelection == 2)
    {
        getName(player1.playerName, 1);
        int turn = 0, exitKey;
        while (true)
        {
            // Resets exit key 
            exitKey = 0;
            //  Initializes Empty Values into boardValues Array for the first turn
            if (turn == 0)
            {
                initializeBoard();
                printBoard(player1.playerName, computerEasy.playerName);
                turn++;
            }

            // If there is no winner on turn 9, draw is declared and User is given option to play again or exit game 
            else if (turn == 10)
            {
                printf("There are no winners.\n");
                if (resetGame(&exitKey, &turn) == 0)
                    return 0;
                
            }

            // If turn is not divisible by 2 -- Player 1 Turn
            else if (turn % 2 != 0 && exitKey == 0)
            {
                // Player 1 Location Selector
                validPlayerChoice(&player1.rowChoice, &player1.columnChoice, player1.playerName);

                // Places designated symbol of player to desired location
                inputChoice(player1.rowChoice, player1.columnChoice, player1.playerSymbol);

                // Checks if Player 1 has Won
                if (checkWin(turn) == 1)
                {
                    printBoard(player1.playerName, computerEasy.playerName);
                    printf("%s Wins!\n\n", player1.playerName);
                    if (resetGame(&exitKey, &turn) == 0)
                        return 0;
                }
                // Else increases turn by 1
                else
                {
                    printBoard(player1.playerName, computerEasy.playerName);
                    turn++;
                }

            }

            // If turn is divisible by 2 -- Computer(Easy)Turn
            else if (turn % 2 == 0 && exitKey == 0)
            {
                // Player 2 Turn
                computerEasySelection(&computerEasy.rowChoice, &computerEasy.columnChoice);

                // Places Valid Location in boardValues array
                inputChoice(computerEasy.rowChoice, computerEasy.columnChoice, computerEasy.playerSymbol);

                // Checks for Computer Win
                if (checkWin(turn) == 2)
                {
                    printBoard(player1.playerName, computerEasy.playerName);
                    printf("%s Wins!\n\n", computerEasy.playerName);
                    if (resetGame(&exitKey, &turn) == 0)
                        return 0;
                }
                // Prints Board & Increases Turn by 1
                else
                {
                    printBoard(player1.playerName, computerEasy.playerName);
                    turn++;
                }
            }
        }
    }
    return 0;
}

// Outputs Virtual Board containing boardValues from UserInputs
void printBoard(char* player1Name, char* player2Name)
{
    printf("\nTic Tac Toe Game\n");
    printf("%s: X\t\t%s: O\n", player1Name, player2Name);
    printf("\t 1   2   3  \n");
    printf("\t   |   | \n");
    printf("1\t %c | %c | %c \n", boardValues[1], boardValues[2], boardValues[3]);

    printf("\t___|___|___\n");
    printf("\t   |   | \n");
    printf("2\t %c | %c | %c \n", boardValues[4], boardValues[5], boardValues[6]);
    printf("\t___|___|___\n");
    printf("\t   |   | \n");

    printf("3\t %c | %c | %c \n", boardValues[7], boardValues[8], boardValues[9]);
    printf("\t   |   | \n");
}

// Inputs Proper Symbol in the designated boardValues index given the Row and Column Value
void inputChoice(int userChoiceRow, int userChoiceColumn, char symbol)
{
    int placeValue = 3 * userChoiceRow - (3 - userChoiceColumn);
    boardValues[placeValue] = symbol;
}

// Computer Easy Move on a Valid Location (Random-Free Location)
void computerEasySelection(int* randRow, int* randColumn)
{
    int randIndex;
    // Loops untill empty boardValue is found
    do
    {
        randIndex = rand() % 9 + 1;

    } while (boardValues[randIndex] != ' ');
    
    // Based on randIndex calculates the row and column
    if (randIndex % 3 == 0)
        *randRow = randIndex / 3;
    else
        *randRow = randIndex / 3 + 1;

    if (randIndex % 3 != 0)
        *randColumn = randIndex % 3;
    else
        *randColumn = 3;
    printf("The Computer Chose (%d,%d)", *randRow, *randColumn);
}

// Gathers Input from User untill given a valid location
void validPlayerChoice(int* validRow, int* validColumn, char* playerName)
{
    int rowChoice, columnChoice;
    printf("%s: Enter Row & Column Value (Seperated By Comma): ", playerName);
    scanf("%d,%d", &rowChoice, &columnChoice);

    // Loops untill location selection is valid
     while (checkDif(rowChoice, columnChoice) != 1 || checkRange(rowChoice, columnChoice) != 1)
    {
        printf("Invalid Place\n");
        printf("%s: Enter Row & Column Value (Seperated By Comma): ", playerName);
        scanf("%d,%d", &rowChoice, &columnChoice);
    }
    *validRow = rowChoice;
    *validColumn = columnChoice;
}

// Sets every value of boardValues array to ' '.
void initializeBoard(void)
{
    for (int i = 1; i < 10; i++)
    {
        boardValues[i] = ' ';
    }
}

void getName(char* playerName, int playerNumber)
{
    char name[20];
    printf("Enter Player %d Name: ", playerNumber);
    scanf("%s", name);

    strcpy(playerName, name);
}

// Returns 1 if a row contains the same symbols, else returns 0
int checkRow(void)
{
    int iValue = 1;
    while (iValue < 10)
    {
        if (boardValues[iValue] == boardValues[iValue + 1] && boardValues[iValue + 1] == boardValues[iValue + 2] && boardValues[iValue] != ' ')
        {
            return 1;
        }
        else
            iValue += 3;
    }
    return 0;
}

// Resets Game if desired by user by setting the turn = 0, exitKey = 1 & returns 1 .. else returns 0
int resetGame(int* exitKey, int* turn)
{
    int userInput;
    printf("Would You Like to Play Again?\n");
    printf("1:Yes\t\t2:No\n");
    printf("Selection: ");
    scanf("%d", &userInput);
    // turn is reset and exit is declared
    if (userInput == 1)
    {
        *turn = 0;
        *exitKey = 1;
        return 1;
    }
    else
    {
        printf("Thanks for Playing!\n");
        return 0;
    }
}

// Menu Prompt
int menuSelect(void)
{
    int userInput = 0;
    do 
    {
        printf("Select Option:\n");
        printf("1: Player Vs Player\n");
        printf("2: Player Vs Computer (Easy Difficulty)\n");
        printf("3: Player Vs Computer (Hard Difficulty)\n");
        printf("Selection: ");
        scanf("%d", &userInput);
    } while(userInput < 1 || userInput > 3);
    switch (userInput)
    {
        case 1:
            return 1;
        case 2:
            return 2;
        case 3:
            return 3;
        default:
            return 0;
    }
}

// Returns 1 if a column contains the same symbols, else returns 0
int checkColumn(void)
{
    int checkValue = 1, iValue;
    while (checkValue < 4)
    {
        iValue = checkValue;
        if (boardValues[iValue] == boardValues[iValue + 3] && boardValues[iValue + 3] == boardValues[iValue + 6] && boardValues[iValue] != ' ')
            return 1;

        else
            checkValue++;
    }
    return 0;
}

// Returns 1 if a diagonal contains the same symbols, else returns 0
int checkDiagonal(void)
{
    int iValue = 1, jValue = 3;
    if (boardValues[iValue] == boardValues[iValue + 4] && boardValues[iValue + 4] == boardValues[iValue + 8] && boardValues[iValue] != ' ')
    {
        return 1;
    }
    else if (boardValues[jValue] == boardValues[jValue + 2] && boardValues[jValue + 2] == boardValues[jValue + 4] && boardValues[jValue] != ' ')
    {
        return 1;
    }
    else
        return 0;
}

// Decides Winning Player if applicable, else returns 0
int checkWin(int turn)
{
    // Player 1 Wins
    if (turn % 2 != 0 && (checkRow() == 1 || checkColumn() == 1 || checkDiagonal() == 1))
        return 1;

    // Player 2 Wins
    else if (turn % 2 == 0 && (checkRow() == 1 || checkColumn() == 1 || checkDiagonal() == 1))
        return 2;
    // Continues Game    
    else 
        return 0;
}

// Makes sure given location is an empty location
int checkDif(int playerRow, int playerColumn)
{
    int placeValue = 3 * playerRow - (3 - playerColumn);
    if (boardValues[placeValue] != 'X' && boardValues[placeValue] != 'O')
    {
        return 1;
    }
    else
        return 0;
}

// Makes sure given row and column from user is within the valid range
int checkRange(int playerRow, int playerColumn)
{
    if (playerRow < 1 || playerRow > 3 || playerColumn < 1 || playerColumn > 3)
        return 0;
    else 
        return 1;
}


