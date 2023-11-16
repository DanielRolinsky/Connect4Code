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

int verticalCheck(int boardArray[BOARD_ROWS][BOARD_COLUMNS], int tokensPerLine, int tokenType);
int horizontalCheck(int boardArray[BOARD_ROWS][BOARD_COLUMNS], int tokensPerLine, int tokenType);

int humanMove(int boardArray[BOARD_ROWS][BOARD_COLUMNS], int columnHeights[BOARD_COLUMNS], int currentCol);
int robotMove(int boardArray[BOARD_ROWS][BOARD_COLUMNS], int columnHeights[BOARD_COLUMNS], int currentCol);

int minimaxAlg(int boardArray[BOARD_ROWS][BOARD_COLUMNS], int columnHeights[BOARD_COLUMNS], int depth, bool maxPlayer, int &finalRobotMove, int colOfMove = 0);
int scoreBoard(int boardArray[BOARD_ROWS][BOARD_COLUMNS], int columnOfMove);

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
  
  dropToken(boardArray, columnHeights, choiceCol, HUMAN_TOKEN_TYPE);
  
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

int scoreBoard(int boardArray[BOARD_ROWS][BOARD_COLUMNS], int columnOfMove)
{
  int score = 0;
  
  if(columnOfMove == 3)
  {
    score += 4;
  }
  
  //try and combine all these functions together into minimal loops
  score += verticalCheck(boardArray, 3, ROBOT_TOKEN_TYPE) * 5;
  score += horizontalCheck(boardArray, 3, ROBOT_TOKEN_TYPE) * 5;
  
  score += verticalCheck(boardArray, 2, ROBOT_TOKEN_TYPE) * 2;
  score += horizontalCheck(boardArray, 2, ROBOT_TOKEN_TYPE) * 5;
  
  score -= verticalCheck(boardArray, 2, HUMAN_TOKEN_TYPE) * 2;
  score -= horizontalCheck(boardArray, 2, ROBOT_TOKEN_TYPE) * 2;
  
  displayBoard(boardArray); //for debugging
  cout << endl << columnOfMove << " " << score << endl;
  
  return score;
  
}

int verticalCheck(int boardArray[BOARD_ROWS][BOARD_COLUMNS], int tokensPerLine, int tokenType)
{
  int lines = 0;
  int gaps = 1;
  if(tokensPerLine == 4) //perhaps change (and for other functions)
  {
    gaps = 0;
  }
  
  for(int columnIndex = 0; columnIndex < BOARD_COLUMNS; columnIndex++)
  {
    for(int rowIndex = BOARD_ROWS - 1; rowIndex > (tokensPerLine + gaps) - 2; rowIndex--) //condition from: (BOARD_ROWS - 1) - (BOARD_ROWS - (tokensPerLine + gaps) + 1)
    {
      if(boardArray[rowIndex][columnIndex] == tokenType)
      {
       int tokenSum = 0;
       
       for(int checkOffset = 0; checkOffset < tokensPerLine + gaps; checkOffset++)
       {
         if(boardArray[rowIndex - checkOffset][columnIndex] == tokenType)
         {
           tokenSum++;
         }
         
       }
       
       cout << endl << "Sum: " << tokenSum << ", Row: " << rowIndex + 1 << endl;
       if(tokenSum == tokensPerLine)
       {
         lines++;
       }
       
      }
      
    }
    
  }
  
  cout << endl << lines << endl;
  return lines;
  
}

int horizontalCheck(int boardArray[BOARD_ROWS][BOARD_COLUMNS], int tokensPerLine, int tokenType)
{
  int lines = 0;
  int gaps = 1;
  if(tokensPerLine == 4)
  {
    gaps = 0;
  }
  
  for(int rowIndex = 0; rowIndex < BOARD_ROWS; rowIndex++)
  {
    for(int columnIndex = 0; columnIndex < BOARD_COLUMNS - (tokensPerLine + gaps) + 1; columnIndex++)
    {
      if(boardArray[rowIndex][columnIndex] == tokenType)
      {
        int tokenSum = 0;
        
        for(int checkOffset = 0; checkOffset < tokensPerLine + gaps; checkOffset++)
        {
          if(boardArray[rowIndex][columnIndex + checkOffset] == tokenType)
          {
            tokenSum++;
            
          }
          
        }
        
        if(tokenSum == tokensPerLine)
        {
          lines++;
        }
        
      }
      
    }
    
  }
  
  return lines;
  
}

//Robot AI
int robotMove(int boardArray[BOARD_ROWS][BOARD_COLUMNS], int columnHeights[BOARD_COLUMNS], int currentCol)
{
  
  int finalRobotMove = 0; 
  minimaxAlg(boardArray, columnHeights, 1, true, finalRobotMove); //Remember: minimax returns a value
  
  dropToken(boardArray, columnHeights, finalRobotMove + 1, ROBOT_TOKEN_TYPE);
  
  return finalRobotMove;
  
}

int minimaxAlg(int boardArray[BOARD_ROWS][BOARD_COLUMNS], int columnHeights[BOARD_COLUMNS], int depth, bool maxPlayer, int &finalRobotMove, int columnOfMove)
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
      int emptyTokenRow = (BOARD_ROWS - 1) - columnHeights[colDropIndex];
      
      if(emptyTokenRow > -1)
      {
        boardArray[emptyTokenRow][colDropIndex] = ROBOT_TOKEN_TYPE;
        columnHeights[colDropIndex] += 1;
        
        int possibleMoveScore = minimaxAlg(boardArray, columnHeights, depth - 1, false, finalRobotMove, colDropIndex);
        
        maxScore = max(maxScore, possibleMoveScore);
        if(maxScore == possibleMoveScore)
        {
          finalRobotMove = colDropIndex;
        }
        
        boardArray[emptyTokenRow][colDropIndex] = 0;
        columnHeights[colDropIndex] -= 1;
     }

   }
   
   return maxScore;
  
  }
  else
  {
    int minScore = 9999;
    
    for(int colDropIndex = 0; colDropIndex < BOARD_COLUMNS; colDropIndex++)
    {
      int emptyTokenRow = (BOARD_ROWS - 1) - columnHeights[colDropIndex];
      
      if(emptyTokenRow > -1)
      {
        boardArray[emptyTokenRow][colDropIndex] = ROBOT_TOKEN_TYPE;
        columnHeights[colDropIndex] += 1;
        
        int possibleMoveScore = minimaxAlg(boardArray, columnHeights, depth - 1, true, finalRobotMove, colDropIndex);
        
        minScore = min(minScore, possibleMoveScore);
        if(minScore == possibleMoveScore)
        {
          finalRobotMove = colDropIndex;
        }
        
        boardArray[emptyTokenRow][colDropIndex] = 0;
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