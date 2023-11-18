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

int scoreBoard(int boardArray[BOARD_ROWS][BOARD_COLUMNS], int columnOfMove)
{
  int score = 0;
  
  if(columnOfMove == 3)
  {
    score += 4;
  }
  
  for(int row = BOARD_ROWS - 1; row >= 0; row--)
  {
    
    for(int column = 0; column < BOARD_COLUMNS; column++)
    {
      
      bool opponentTokenFound = false;
      int sum = 0;
      
      if(column < 4)
      {
        for(int columnOffset = 0; columnOffset < 4 && !opponentTokenFound; columnOffset++)
        {
          if(boardArray[row][column + columnOffset] == HUMAN_TOKEN_TYPE)
          {
            opponentTokenFound = true;
          }
          else if(boardArray[row][column + columnOffset] == ROBOT_TOKEN_TYPE)
          {
            sum++;
          }
          
        }
        
        if(sum == 2)
        {
          score += 2;
        }
        else if(sum == 3)
        {
          score +=3;
        }
      
      }
      
      opponentTokenFound = false;
      sum = 0;
      
      if(row >= 3)
      {
        for(int rowOffset = 0; rowOffset < 4 && !opponentTokenFound; rowOffset++)
        {
          if(boardArray[row - rowOffset][column] == HUMAN_TOKEN_TYPE)
          {
            opponentTokenFound = true;
          }
          else if(boardArray[row - rowOffset][column] == ROBOT_TOKEN_TYPE)
          {
            sum++;
          }
          
        }
        
        if(sum == 2)
        {
          score += 2;
        }
        
      }
      
    }
    
  }
  
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
      int emptyTokenRow = (BOARD_ROWS - 1) - columnHeights[colDropIndex]; //Checks if a column is not full
      
      if(emptyTokenRow > -1)
      {
        boardArray[emptyTokenRow][colDropIndex] = ROBOT_TOKEN_TYPE; //Adding token to row for scoring
        columnHeights[colDropIndex] += 1;
        
        int possibleMoveScore = minimaxAlg(boardArray, columnHeights, finalMove, depth - 1, false, colDropIndex);
        
        maxScore = max(maxScore, possibleMoveScore);
        if(maxScore == possibleMoveScore)
        {
          finalMove = colDropIndex + 1;
        }
        
        boardArray[emptyTokenRow][colDropIndex] = 0; //Removing added token that was for scoring
        columnHeights[colDropIndex] -= 1;
     }
    
    }
    
    return maxScore;
  
  }
  else
  {
    
    int minScore = 9999;
    
    for(int colDropIndex = 0; colDropIndex < BOARD_COLUMNS; colDropIndex++) //Drops a token in each column to score that potential move
    {
      int emptyTokenRow = (BOARD_ROWS - 1) - columnHeights[colDropIndex]; //Checks if a column is not full
      
      if(emptyTokenRow > -1)
      {
        boardArray[emptyTokenRow][colDropIndex] = ROBOT_TOKEN_TYPE; //Adding token to row for scoring
        columnHeights[colDropIndex] += 1;
        
        int possibleMoveScore = minimaxAlg(boardArray, columnHeights, finalMove, depth - 1, false, colDropIndex);
        
        minScore = min(minScore, possibleMoveScore);
        if(minScore == possibleMoveScore)
        {
          finalMove = colDropIndex + 1;
        }
        
        boardArray[emptyTokenRow][colDropIndex] = 0; //Removing added token that was for scoring
        columnHeights[colDropIndex] -= 1;
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
  int emptyTokenRow = (BOARD_ROWS - 1) - columnHeights[choiceCol - 1];
  
  boardArray[emptyTokenRow][choiceCol - 1] = tokenType;
  columnHeights[choiceCol - 1] += 1;
  
  cout << "Token dropped to: (" << emptyTokenRow + 1 << ", " << choiceCol << ")" << endl;
  
  return;
}