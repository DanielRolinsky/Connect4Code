//Libraries
#include <iostream>
#include <cstdlib>
using namespace std;

//Constants
const int BOARD_ROWS = 6;
const int BOARD_COLUMNS = 7;

const int HUMAN_TOKEN_TYPE = 1;
const int ROBOT_TOKEN_TYPE = 2;

//Function Prototypes
void displayBoard(int boardArray[BOARD_ROWS][BOARD_COLUMNS]);

int gameWon(int boardArray[BOARD_ROWS][BOARD_COLUMNS]);
bool legalMove(int boardArray[BOARD_ROWS][BOARD_COLUMNS], int choiceCol);
void dropToken(int boardArray[BOARD_ROWS][BOARD_COLUMNS], int columnHeights[BOARD_COLUMNS], int choiceCol, int tokenType);
void addTokenToArray(int boardArray[BOARD_ROWS][BOARD_COLUMNS], int columnHeights[BOARD_COLUMNS], int row, int column, int tokenType);
void removeTokenInArray(int boardArray[BOARD_ROWS][BOARD_COLUMNS], int columnHeights[BOARD_COLUMNS], int row, int column);

int humanMove(int boardArray[BOARD_ROWS][BOARD_COLUMNS], int columnHeights[BOARD_COLUMNS], int currentCol);
int robotMove(int boardArray[BOARD_ROWS][BOARD_COLUMNS], int columnHeights[BOARD_COLUMNS]);

int minimaxAlg(int boardArray[BOARD_ROWS][BOARD_COLUMNS], int columnHeights[BOARD_COLUMNS], int &finalMove, int depth, bool maxPlayer, int columnOfMove = 0);
int scoreBoard(int boardArray[BOARD_ROWS][BOARD_COLUMNS], int columnOfMove);
void displayScore(int boardArray[BOARD_ROWS][BOARD_COLUMNS], int columnOfMove, int score);

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
    
    currentCol = robotMove(boardArray, columnHeights);
    displayBoard(boardArray);
  }
  
  return EXIT_SUCCESS;
}

//Human Player Functions
int humanMove(int boardArray[BOARD_ROWS][BOARD_COLUMNS], int columnHeights[BOARD_COLUMNS], int currentCol)
{
  int choiceCol = currentCol;
  
  do {
		cout << "Enter player move column: ";
    cin >> choiceCol;
	} while(!legalMove(boardArray, choiceCol));
  
  dropToken(boardArray, columnHeights, choiceCol, HUMAN_TOKEN_TYPE);
  
  return choiceCol;
}

bool legalMove(int boardArray[BOARD_ROWS][BOARD_COLUMNS], int choiceCol)
{
  if(boardArray[0][choiceCol - 1] == 0 && choiceCol >= 1 && choiceCol <= 7)
  {
    return true;
  }
  return false;
}

//Game State Functions
int gameWon(int boardArray[BOARD_ROWS][BOARD_COLUMNS])
{
  //placeholder
  return false;
}

int horizontalCheck((int boardArray[BOARD_ROWS][BOARD_COLUMNS], int columnHeights[BOARD_COLUMNS], int columnOfMove)
{
  int score = 0;
   
  const int tokenRow = BOARD_ROWS - columnHeights[columnOfMove];
  const int tokenColumn = columnOfMove;
  
  int startRow = tokenRow, startColumn = 0, endRow = 0, endColumn = 0;
  
  bool hitBorder = false; //If line of x tokens hits the end of the board or an enemy token
  int sum = 0;
  
  for(int columnOffset = 0; columnOffset < 4 && !hitBorder; columnOffset++)
  {
    if(tokenColumn + columnOffset == BOARD_COLUMN - 1 || boardArray[tokenRow][tokenColumn + columnOffset] == HUMAN_TOKEN_TYPE)
    {
      startRow = tokenRow; //can remove this for horizontal check
      startColumn = tokenColumn + columnOffset;
      hitBorder = true;
    }
    else
    {
      if(boardArray[tokenRow][tokenColumn + columnOffset] == ROBOT_TOKEN_TYPE)
      {
        sum++;
      }
      
      if(columnOffset == 3)
      {
        startRow = tokenRow; //can remove this for horizontal check
        startColumn = tokenColumn + columnOffset;
      }
    }
  }
  
  const int distanceDifference = startColumn - tokenColumn;
  
  if(distanceDifference < 3)
  {
    hitBorder = false;
    
    for(int columnOffset = 0; columnOffset > (3 - distanceDifference) * -1 && !hitBorder; column--)
    {
      if(tokenColumn + columnOffset == 0 || boardArray[tokenRow][tokenColumn + columnOffset] == HUMAN_TOKEN_TYPE)
      {
        endRow = tokenRow; //can remove this for horizontal check
        endColumn = tokenColumn + columnOffset;
        hitBorder = true;
      }
      else
      {
        if(boardArray[tokenRow][tokenColumn + columnOffset] == ROBOT_TOKEN_TYPE)
        {
          sum++;
        }
        
        if(columnOffset == (3 - distanceDifference) * -1 + 1)
        {
          endRow = tokenRow; //can remove this for horizontal check
          endColumn = tokenColumn + columnOffset;
        }
      }
      
    }
    
  }
  
  if(sum == 2)
  {
    score += 2;
  }
  else if(sum == 3)
  {
    score += 5;
  }
  
  return score;
  
}

int scoreBoard(int boardArray[BOARD_ROWS][BOARD_COLUMNS], int columnHeights[BOARD_COLUMNS], int columnOfMove)
{
  int score = 0;
  
  if(columnOfMove == 3)
  {
   score += 4; 
  }
  
  score += horizontalCheck();
  
  displayScore(boardArray, columnOfMove, score);
  
  return score;
  
}

void displayScore(int boardArray[BOARD_ROWS][BOARD_COLUMNS], int columnOfMove, int score)
{
  cout << endl;
  displayBoard(boardArray);
  cout << "Column: " << columnOfMove << ", Score: " << score << endl;
  
  return;
}

//Robot Player Functions
int robotMove(int boardArray[BOARD_ROWS][BOARD_COLUMNS], int columnHeights[BOARD_COLUMNS])
{
  
  int finalMove = 1;
  int minimaxPlaceholder = minimaxAlg(boardArray, columnHeights, finalMove, 1, true); //Remember: minimax returns a value
  
  dropToken(boardArray, columnHeights, finalMove, ROBOT_TOKEN_TYPE);
  
  return finalMove;
  
}

int minimaxAlg(int boardArray[BOARD_ROWS][BOARD_COLUMNS], int columnHeights[BOARD_COLUMNS], int &finalMove, int depth, bool maxPlayer, int columnOfMove) //maybe change colOfMove to bool "center"?
{
  
  if(depth == 0)
  {
    return scoreBoard(boardArray, columnOfMove);
  }
  
  if(maxPlayer)
  {
    int maxScore = -9999;
    
    for(int colDropIndex = 0; colDropIndex < BOARD_COLUMNS; colDropIndex++) //Drops a token in each column to score that potential move
    {
      const int emptyTokenRow = (BOARD_ROWS - 1) - columnHeights[colDropIndex]; //Checks if a column is not full
      
      if(emptyTokenRow > -1)
      {
        addTokenToArray(boardArray, columnHeights, emptyTokenRow, colDropIndex, ROBOT_TOKEN_TYPE);        
        
        int possibleMoveScore = minimaxAlg(boardArray, columnHeights, finalMove, depth - 1, false, colDropIndex);
        
        maxScore = max(maxScore, possibleMoveScore);
        if(maxScore == possibleMoveScore)
        {
          finalMove = colDropIndex + 1;
        }
        
        removeTokenInArray(boardArray, columnHeights, emptyTokenRow, colDropIndex);
     }
    
    }
    
    return maxScore;
  
  }
  else
  {
    
    int minScore = 9999;
    
    for(int colDropIndex = 0; colDropIndex < BOARD_COLUMNS; colDropIndex++) //Drops a token in each column to score that potential move
    {
      const int emptyTokenRow = (BOARD_ROWS - 1) - columnHeights[colDropIndex]; //Checks if a column is not full
      
      if(emptyTokenRow > -1)
      {
        addTokenToArray(boardArray, columnHeights, emptyTokenRow, colDropIndex, ROBOT_TOKEN_TYPE);  
        
        int possibleMoveScore = minimaxAlg(boardArray, columnHeights, finalMove, depth - 1, false, colDropIndex);
        
        minScore = min(minScore, possibleMoveScore);
        if(minScore == possibleMoveScore)
        {
          finalMove = colDropIndex + 1;
        }
        
        removeTokenInArray(boardArray, columnHeights, emptyTokenRow, colDropIndex);
     }
    
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
  const int emptyTokenRow = (BOARD_ROWS - 1) - columnHeights[choiceCol - 1];
  
  addTokenToArray(boardArray, columnHeights, emptyTokenRow, choiceCol - 1, tokenType);
  
  cout << "Token dropped to: (" << emptyTokenRow + 1 << ", " << choiceCol << ")" << endl;
  
  return;
}

void addTokenToArray(int boardArray[BOARD_ROWS][BOARD_COLUMNS], int columnHeights[BOARD_COLUMNS], int row, int column, int tokenType)
{
  boardArray[row][column] = tokenType;
  columnHeights[column] += 1;
  
  return;
}

void removeTokenInArray(int boardArray[BOARD_ROWS][BOARD_COLUMNS], int columnHeights[BOARD_COLUMNS], int row, int column)
{
  boardArray[row][column] = 0;
  columnHeights[column] -= 1;
  
  return;
}