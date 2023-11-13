//Libraries
#include <iostream>
#include <cstdlib>
using namespace std;

//Constants
const int BOARD_ROWS = 6;
const int BOARD_COLUMNS = 7;

//Function Prototypes
void displayBoard(int boardArray[BOARD_ROWS][BOARD_COLUMNS]);

int gameWon(int boardArray[BOARD_ROWS][BOARD_COLUMNS]);
bool legalMove(int boardArray[BOARD_ROWS][BOARD_COLUMNS], int choiceCol);
void dropToken(int boardArray[BOARD_ROWS][BOARD_COLUMNS], int choiceCol, int tokenColour);

int humanMove(int boardArray[BOARD_ROWS][BOARD_COLUMNS], int currentCol);

//Main
int main()
{
  //In boardArray: 0 = empty, 1 = red, 2 = yellow;
  int boardArray[BOARD_ROWS][BOARD_COLUMNS] = {0};
  
  int currentCol = 1;
  
  while(!gameWon(boardArray))
  {
    currentCol = humanMove(boardArray, currentCol);
    displayBoard(boardArray);
    currentCol = robotMove(boardArray, currentCol);
    displayBoard(boardArray);
  }
  
  return EXIT_SUCCESS;
}

int humanMove(int boardArray[BOARD_ROWS][BOARD_COLUMNS], int currentCol)
{
  int choiceCol = currentCol;
  
  do {
		cout << "Enter player move column: ";
    cin >> choiceCol;
	} while(!legalMove(boardArray, choiceCol));
  
  dropToken(boardArray, choiceCol, 1);
  
  return choiceCol;
}

//Game State Functions
bool legalMove(int boardArray[BOARD_ROWS][BOARD_COLUMNS], int choiceCol)
{
  if(boardArray[0][choiceCol - 1] != 0)
  {
    return false;
  }
  return true;
}

int gameWon(int boardArray[BOARD_ROWS][BOARD_COLUMNS])
{
  //placeholder
  return false;
}

//Robot AI
int robotMove(int boardArray[BOARD_ROWS][BOARD_COLUMNS], int currentCol)
{
  
  
  
}

//"Trivials"
void displayBoard(int boardArray[BOARD_ROWS][BOARD_COLUMNS])
{
  for (int rowIndex = 0; rowIndex < BOARD_ROWS; rowIndex++)
  {
    cout << "{";
    for (int colIndex = 0; colIndex < BOARD_COLUMNS; colIndex++)
    {
      cout << " " << boardArray[rowIndex][colIndex];
    }
    cout << " }" << endl;
  }
  
  return;
}

void dropToken(int boardArray[BOARD_ROWS][BOARD_COLUMNS], int choiceCol, int tokenColour)
{
  bool foundEmptySpot = false;
  
  for(int rowIndex = BOARD_ROWS - 1; rowIndex >= 0 && !foundEmptySpot; rowIndex--)
  {
    
    if(boardArray[rowIndex][choiceCol - 1] == 0)
    {
      boardArray[rowIndex][choiceCol - 1] = tokenColour;
      cout << "Token dropped to: (" << rowIndex + 1 << ", " << choiceCol << ")" << endl;
      foundEmptySpot = true;
    }
    
  }
  
  return;
}