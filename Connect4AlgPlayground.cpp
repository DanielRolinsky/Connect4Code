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

int minimaxAlg(int boardArray[BOARD_ROWS][BOARD_COLUMNS], int columnHeights[BOARD_COLUMNS], int &finalMove, int depth, bool maxPlayer, int columnOfMove = 0);;
void displayScore(int boardArray[BOARD_ROWS][BOARD_COLUMNS], int columnOfMove, int score);

int scoreBoard(int boardArray[BOARD_ROWS][BOARD_COLUMNS], int columnHeights[BOARD_COLUMNS], int columnOfMove, int playerToken, int oppoToken);
int scorePoints(int playerToken, int sum);
int horizontalCheck(int boardArray[BOARD_ROWS][BOARD_COLUMNS], int columnHeights[BOARD_COLUMNS], int columnOfMove, int playerToken, int oppoToken);
int verticalCheck(int boardArray[BOARD_ROWS][BOARD_COLUMNS], int columnHeights[BOARD_COLUMNS], int columnOfMove, int playerToken, int oppoToken);

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

int scorePoints(int playerToken, int sum)
{
  if(sum == 2)
  {
    return 2;
  }
  else if(sum == 3)
  {
    return 5;
  }
  else if(sum == 4)
  {
    return 999;
  }
  
  return 0;
}

int horizontalCheck(int boardArray[BOARD_ROWS][BOARD_COLUMNS], int columnHeights[BOARD_COLUMNS], int columnOfMove, int playerToken, int oppoToken)
{
  int score = 0;
   
  const int TOKEN_ROW = BOARD_ROWS - columnHeights[columnOfMove];
  const int TOKEN_COLUMN = columnOfMove;
  
  int startRow[2] = {-1, -2}; //can maybe intialize with token row for horizontal...
  int startCol[2] = {-3, -4};
  int endRow[2] = {-5, -6};
  int endCol[2] = {-7, -8};
  
  bool hitBarrier = false;
  int sum = 1;
  int spacesLeft = 3;
  
  for(int colOffset = 1; colOffset <= spacesLeft && !hitBarrier; colOffset++)
  {
    int currentToken = boardArray[TOKEN_ROW][TOKEN_COLUMN + colOffset];
    
    if(currentToken == oppoToken || TOKEN_COLUMN + colOffset == BOARD_COLUMNS)
    {
      hitBarrier = true;
      startRow[0] = TOKEN_ROW;
      startCol[0] = TOKEN_COLUMN + colOffset - 1;
      spacesLeft -= (colOffset - 1);
    }
    else if(currentToken == playerToken)
    {
      sum++;
    }
  }
  
  if(hitBarrier)
  {
    hitBarrier = false;
    
    for(int colOffset = 1; colOffset <= spacesLeft && !hitBarrier; colOffset++)
    {
      int currentToken = boardArray[TOKEN_ROW][TOKEN_COLUMN - colOffset];
      
      if(currentToken == oppoToken || TOKEN_COLUMN - colOffset == -1)
      {
        hitBarrier = true;
        startRow[0] = -1;
        startCol[0] = -3;
      }
      else if(currentToken == playerToken)
      {
        sum++;
      }
    }
    
    if(!hitBarrier)
    {
      endRow[0] = TOKEN_ROW;
      endCol[0] = TOKEN_COLUMN - spacesLeft;
    }
  }
  else
  {
    startRow[0] = TOKEN_ROW;
    startCol[0] = TOKEN_COLUMN;
    endRow[0] = TOKEN_ROW;
    endCol[0] = TOKEN_COLUMN + spacesLeft;
  }
  //cout << endl << "Line 1: " << startCol[0] << ", " << endCol[0] << " Sum: " << sum << endl;
  
  if(!hitBarrier)
  {
    score += scorePoints(playerToken, sum);
  }
  
  hitBarrier = false;
  sum = 1;
  spacesLeft = 3;
  
  for(int colOffset = 1; colOffset <= spacesLeft && !hitBarrier; colOffset++)
  {
    int currentToken = boardArray[TOKEN_ROW][TOKEN_COLUMN - colOffset];
    
    if(currentToken == oppoToken || TOKEN_COLUMN - colOffset == -1)
    {
      hitBarrier = true;
      startRow[1] = TOKEN_ROW;
      startCol[1] = TOKEN_COLUMN - colOffset + 1;
      spacesLeft -= (colOffset - 1);
    }
    else if(currentToken == playerToken)
    {
      sum++;
    }
  }
  
  if(hitBarrier)
  {
    hitBarrier = false;
    
    for(int colOffset = 1; colOffset <= spacesLeft && !hitBarrier; colOffset++)
    {
      int currentToken = boardArray[TOKEN_ROW][TOKEN_COLUMN + colOffset];
      
      if(currentToken == oppoToken || TOKEN_COLUMN + colOffset == BOARD_COLUMNS)
      {
        hitBarrier = true;
        startRow[1] = -2;
        startCol[1] = -4;
      }
      else if(currentToken == playerToken)
      {
        sum++;
      }
    }
    
    if(!hitBarrier)
    {
      endRow[1] = TOKEN_ROW;
      endCol[1] = TOKEN_COLUMN + spacesLeft;
    }
  }
  else
  {
    startRow[1] = TOKEN_ROW;
    startCol[1] = TOKEN_COLUMN;
    endRow[1] = TOKEN_ROW;
    endCol[1] = TOKEN_COLUMN - spacesLeft;
  }
  //cout << "Line 2: " << startCol[1] << ", " << endCol[1] << " Sum: " << sum;
  
  if(!hitBarrier && !(startCol[0] == endCol[1] && startCol[1] == endCol[0] || startCol[0] == startCol[1] && endCol[0] == endCol[1]))
  {
    score += scorePoints(playerToken, sum);
  }
  
  return score;
  
}

int verticalCheck(int boardArray[BOARD_ROWS][BOARD_COLUMNS], int columnHeights[BOARD_COLUMNS], int columnOfMove, int playerToken, int oppoToken)
{
  int score = 0;
   
  const int TOKEN_ROW = BOARD_ROWS - columnHeights[columnOfMove];
  const int TOKEN_COLUMN = columnOfMove;
  
  int startRow[2] = {-1, -2};
  int startCol[2] = {-3, -4}; //can maybe intialize with token column for vertical...
  int endRow[2] = {-5, -6};
  int endCol[2] = {-7, -8};
  
  bool hitBarrier = false;
  int sum = 1;
  int spacesLeft = 3;
  
  for(int rowOffset = 1; rowOffset <= spacesLeft && !hitBarrier; rowOffset++)
  {
    int currentToken = boardArray[TOKEN_ROW - rowOffset][TOKEN_COLUMN];
    
    if(currentToken == oppoToken || TOKEN_ROW - rowOffset == -1)
    {
      hitBarrier = true;
      startRow[0] = TOKEN_ROW - rowOffset + 1;
      startCol[0] = TOKEN_COLUMN;
      spacesLeft -= (rowOffset - 1);
    }
    else if(currentToken == playerToken)
    {
      sum++;
    }
  }
  
  if(hitBarrier)
  {
    hitBarrier = false;
    
    for(int rowOffset = 1; rowOffset <= spacesLeft && !hitBarrier; rowOffset++)
    {
      int currentToken = boardArray[TOKEN_ROW + rowOffset][TOKEN_COLUMN];
      
      if(currentToken == oppoToken || TOKEN_ROW + rowOffset == BOARD_ROWS)
      {
        hitBarrier = true;
        startRow[0] = -1;
        startCol[0] = -3;
      }
      else if(currentToken == playerToken)
      {
        sum++;
      }
    }
    
    if(!hitBarrier)
    {
      endRow[0] = TOKEN_ROW + spacesLeft;
      endCol[0] = TOKEN_COLUMN;
    }
  }
  else
  {
    startRow[0] = TOKEN_ROW;
    startCol[0] = TOKEN_COLUMN;
    endRow[0] = TOKEN_ROW - spacesLeft;
    endCol[0] = TOKEN_COLUMN;
  }
  cout << endl << "Line 1: " << startCol[0] << ", " << endCol[0] << " Sum: " << sum << endl;
  
  if(!hitBarrier)
  {
    score += scorePoints(playerToken, sum);
  }
  
  hitBarrier = false;
  sum = 1;
  spacesLeft = 3;
  
  for(int rowOffset = 1; rowOffset <= spacesLeft && !hitBarrier; rowOffset++)
  {
    int currentToken = boardArray[TOKEN_ROW + rowOffset][TOKEN_COLUMN];
    
    if(currentToken == oppoToken || TOKEN_ROW + rowOffset == BOARD_ROWS)
    {
      hitBarrier = true;
      startRow[1] = TOKEN_ROW + rowOffset - 1;
      startCol[1] = TOKEN_COLUMN;
      spacesLeft -= (rowOffset - 1);
    }
    else if(currentToken == playerToken)
    {
      sum++;
    }
  }
  
  if(hitBarrier)
  {
    hitBarrier = false;
    
    for(int rowOffset = 1; rowOffset <= spacesLeft && !hitBarrier; rowOffset++)
    {
      int currentToken = boardArray[TOKEN_ROW - rowOffset][TOKEN_COLUMN];
      
      if(currentToken == oppoToken || TOKEN_ROW - rowOffset == -1)
      {
        hitBarrier = true;
        startRow[1] = -2;
        startCol[1] = -4;
      }
      else if(currentToken == playerToken)
      {
        sum++;
      }
    }
    
    if(!hitBarrier)
    {
      endRow[1] = TOKEN_ROW - spacesLeft;
      endCol[1] = TOKEN_COLUMN;
    }
  }
  else
  {
    startRow[1] = TOKEN_ROW;
    startCol[1] = TOKEN_COLUMN;
    endRow[1] = TOKEN_ROW + spacesLeft;
    endCol[1] = TOKEN_COLUMN;
  }
  cout << "Line 2: " << startCol[1] << ", " << endCol[1] << " Sum: " << sum;
  
  if(!hitBarrier && !(startRow[0] == endRow[1] && startRow[1] == endRow[0] || startRow[0] == startRow[1] && endRow[0] == endRow[1]))
  {
    score += scorePoints(playerToken, sum);
  }
  
  return score;
  
}

int scoreBoard(int boardArray[BOARD_ROWS][BOARD_COLUMNS], int columnHeights[BOARD_COLUMNS], int columnOfMove, int playerToken, int oppoToken)
{
  int score = 0;
  
  if(columnOfMove == 3)
  {
   score += 4; 
  }
  
  score += horizontalCheck(boardArray, columnHeights, columnOfMove, playerToken, oppoToken);
  score += verticalCheck(boardArray, columnHeights, columnOfMove, playerToken, oppoToken);
  
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
    return scoreBoard(boardArray, columnHeights, columnOfMove, ROBOT_TOKEN_TYPE, HUMAN_TOKEN_TYPE);
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