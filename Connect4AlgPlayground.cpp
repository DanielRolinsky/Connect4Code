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
void dropToken(int boardArray[BOARD_ROWS][BOARD_COLUMNS], int columnHeights[BOARD_COLUMNS], int choiceCol, int tokenType);

int humanMove(int boardArray[BOARD_ROWS][BOARD_COLUMNS], int columnHeights[BOARD_COLUMNS], int currentCol);
int robotMove(int boardArray[BOARD_ROWS][BOARD_COLUMNS], int columnHeights[BOARD_COLUMNS], int currentCol);

int minimaxAlg(int boardArray[BOARD_ROWS][BOARD_COLUMNS], int columnHeights[BOARD_COLUMNS], int depth, bool maxPlayer);
int scoreBoard(int boardArray[BOARD_ROWS][BOARD_COLUMNS]);

//Main
int main()
{
  //In boardArray: 0 = empty, 1 = red, 2 = yellow;
  int boardArray[BOARD_ROWS][BOARD_COLUMNS] = {0};
  int columnHeights[BOARD_COLUMNS] = {0};
  
  int currentCol = 1;
  
  while(!gameWon(boardArray))
  {
    currentCol = humanMove(boardArray, columnHeights, currentCol);
    displayBoard(boardArray);
    
    currentCol = robotMove(boardArray, columnHeights, currentCol);
    displayBoard(boardArray);
  }
  
  return EXIT_SUCCESS;
}

int humanMove(int boardArray[BOARD_ROWS][BOARD_COLUMNS], int columnHeights[BOARD_COLUMNS], int currentCol)
{
  int choiceCol = currentCol;
  
  do {
		cout << "Enter player move column: ";
    cin >> choiceCol;
	} while(!legalMove(boardArray, choiceCol));
  
  dropToken(boardArray, columnHeights, choiceCol, 1);
  
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

int scoreBoard(int boardArray[BOARD_ROWS][BOARD_COLUMNS])
{
  
  return -1;
  
}

//Robot AI
int robotMove(int boardArray[BOARD_ROWS][BOARD_COLUMNS], int columnHeights[BOARD_COLUMNS], int currentCol)
{
  
  int choiceCol = minimaxAlg(boardArray, columnHeights, 1, true);
  
}

int minimaxAlg(int boardArray[BOARD_ROWS][BOARD_COLUMNS], int columnHeights[BOARD_COLUMNS], int depth, bool maxPlayer)
{
  
  if(depth == 0)
  {
    return scoreBoard(boardArray);
  }
  
  if(maxPlayer)
  {
   int maxScore = -9999;
   
   for(int colDropIndex = 0; colDropIndex < BOARD_COLUMNS; colDropIndex++) //Drops a token in each column to score that potential move
   {
      int emptyTokenRow = (BOARD_ROWS - 1) - columnHeights[colDropIndex];
      boardArray[emptyTokenRow][colDropIndex] = 2;
      columnHeights[colDropIndex] += 1;
      
      int possibleMoveScore = minimaxAlg(boardArray, columnHeights, depth - 1, !maxPlayer);
      
      maxScore = max(maxScore, possibleMoveScore);
      
      boardArray[emptyTokenRow][colDropIndex] = 0;
      columnHeights[colDropIndex] -= 1;

   }
   
   return maxScore;
  
  }
  else
  {
    int minScore = 9999;
    
    for(int colDropIndex = 0; colDropIndex < BOARD_COLUMNS; colDropIndex++)
    {
      int emptyTokenRow = (BOARD_ROWS - 1) - columnHeights[colDropIndex];
      boardArray[emptyTokenRow][colDropIndex] = 2;
      columnHeights[colDropIndex] += 1;
      
      int possibleMoveScore = minimaxAlg(boardArray, columnHeights, depth - 1, !maxPlayer);
      
      minScore = min(minScore, possibleMoveScore);
      
      boardArray[emptyTokenRow][colDropIndex] = 0;
      columnHeights[colDropIndex] -= 1;
      
    }
    
    return minScore;
  }
  
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

void dropToken(int boardArray[BOARD_ROWS][BOARD_COLUMNS], int columnHeights[BOARD_COLUMNS], int choiceCol, int tokenType)
{
  int emptyTokenRow = (BOARD_ROWS - 1) - columnHeights[choiceCol - 1];
  
  boardArray[emptyTokenRow][choiceCol - 1] = tokenType;
  columnHeights[choiceCol - 1] += 1;
  
  cout << "Token dropped to: (" << emptyTokenRow + 1 << ", " << choiceCol << ")" << endl;
  
  return;
}