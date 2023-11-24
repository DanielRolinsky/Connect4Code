//Libraries
#include <iostream>
#include <cstdlib>
using namespace std;

//Constants
const int BOARD_ROWS = 6;
const int BOARD_COLUMNS = 7;

const int HUMAN_TOKEN_TYPE = 1;
const int ROBOT_TOKEN_TYPE = 2;

const int MIDDLE_COLUMN = 4;
const int TWO_LINE = 2;
const int THREE_LINE = 5;
const int FOUR_LINE = 900;
const int NEXT_FOUR_LINE = 100;

//Type Structs
typedef struct
{
  int score, columnOfMove;
} minimaxReturns;

//Function Prototypes
void displayBoard(int boardArray[BOARD_ROWS][BOARD_COLUMNS]);

int gameWon(int boardArray[BOARD_ROWS][BOARD_COLUMNS], int currentPlayer);
bool legalMove(int boardArray[BOARD_ROWS][BOARD_COLUMNS], int choiceCol);
void dropToken(int boardArray[BOARD_ROWS][BOARD_COLUMNS], int columnHeights[BOARD_COLUMNS], int choiceCol, int tokenType);
void addTokenToArray(int boardArray[BOARD_ROWS][BOARD_COLUMNS], int columnHeights[BOARD_COLUMNS], int row, int column, int tokenType);
void removeTokenInArray(int boardArray[BOARD_ROWS][BOARD_COLUMNS], int columnHeights[BOARD_COLUMNS], int row, int column);

int humanMove(int boardArray[BOARD_ROWS][BOARD_COLUMNS], int columnHeights[BOARD_COLUMNS], int currentCol);
int robotMove(int boardArray[BOARD_ROWS][BOARD_COLUMNS], int columnHeights[BOARD_COLUMNS]);

void minimaxAlg(int boardArray[BOARD_ROWS][BOARD_COLUMNS], int columnHeights[BOARD_COLUMNS], int depth, bool maxPlayer, minimaxReturns &values, int columnOfMove = 0);
void displayScore(int boardArray[BOARD_ROWS][BOARD_COLUMNS], int columnOfMove, int score);

int scoreBoard(int boardArray[BOARD_ROWS][BOARD_COLUMNS], int columnHeights[BOARD_COLUMNS], int columnOfMove, int playerToken, int oppoToken);
int scorePoints(int sum, bool oppoCheck); //placeholder

int horizontalCheck(int boardArray[BOARD_ROWS][BOARD_COLUMNS], int columnHeights[BOARD_COLUMNS], int columnOfMove, int playerToken, int oppoToken, bool oppoCheck = false);
int verticalCheck(int boardArray[BOARD_ROWS][BOARD_COLUMNS], int columnHeights[BOARD_COLUMNS], int columnOfMove, int playerToken, int oppoToken, bool oppoCheck = false);
int positiveSlopeCheck(int boardArray[BOARD_ROWS][BOARD_COLUMNS], int columnHeights[BOARD_COLUMNS], int columnOfMove, int playerToken, int oppoToken, bool oppoCheck = false);
int negativeSlopeCheck(int boardArray[BOARD_ROWS][BOARD_COLUMNS], int columnHeights[BOARD_COLUMNS], int columnOfMove, int playerToken, int oppoToken, bool oppoCheck = false);

//Main
int main()
{
  //In boardArray: 0 = empty, 1 = red, 2 = yellow;
  int boardArray[BOARD_ROWS][BOARD_COLUMNS] = {0};
  int columnHeights[BOARD_COLUMNS] = {0};
  
  int currentCol = 1;
  int currentPlayer = 1;
  
  while(!gameWon(boardArray, currentPlayer))
  {
  	currentPlayer = 1;
    currentCol = humanMove(boardArray, columnHeights, currentCol);
    displayBoard(boardArray);
    

    if(!gameWon(boardArray, currentPlayer))
    {
      currentPlayer = 2;
      currentCol = robotMove(boardArray, columnHeights);
      displayBoard(boardArray);
    }
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
int gameWon(int boardArray[BOARD_ROWS][BOARD_COLUMNS], int currentPlayer)
{

// assumption: the red = 1 = human, yellow = 2 = robot

	const int draw = 3, notWon = 0;
  int win = 0;
  
	if(boardArray[0][0] != 0 && boardArray[0][1] != 0 && boardArray[0][2] != 0 && boardArray[0][3] != 0
		&& boardArray[0][4] != 0 && boardArray[0][5] != 0 && boardArray[0][6] != 0)
	{
		return draw;
	}
  if(currentPlayer == 1)
  {
		win = 1; // human won
	}
	else if(currentPlayer == 2)
	{
		win = 2; // robot won
	}
	

	for(int row = 5; row >= 0 ; row--)
	{
		for(int col = 0; col < 7; col++)
		{
			if(row > 2)
			{
				if(boardArray[row][col] == currentPlayer
					&& boardArray[row - 1][col] == currentPlayer
					&& boardArray[row - 2][col] == currentPlayer
					&& boardArray[row - 3][col] == currentPlayer)
				{
					return win;
				} // checks vertical
				
				if(col < 4)
				{
					if(boardArray[row][col] == currentPlayer
						&& boardArray[row][col + 1] == currentPlayer
						&& boardArray[row][col + 2] == currentPlayer
						&& boardArray[row][col + 3] == currentPlayer)
					{
						return win;
					} // checks horizontal
					
					if(boardArray[row][col] == currentPlayer
						&& boardArray[row - 1][col + 1] == currentPlayer
						&& boardArray[row - 2 ][col + 2] == currentPlayer
						&& boardArray[row - 3][col + 3] == currentPlayer)
					{
						return win;
					} // checks +ve slope
				}
			 
			}
			else if(col < 4)
			{
				if(boardArray[row][col] == currentPlayer
					&& boardArray[row][col + 1] == currentPlayer
					&& boardArray[row][col + 2] == currentPlayer
					&& boardArray[row][col + 3] == currentPlayer)
				{
					return win;
				} // checks horizontal
				
				if(boardArray[row][col] == currentPlayer
					&& boardArray[row + 1][col + 1] == currentPlayer
					&& boardArray[row + 2 ][col + 2] == currentPlayer
					&& boardArray[row + 3][col + 3] == currentPlayer)
				{
					return win;
				} // checks -ve slope
			}

		}
	}

	return notWon; //not won if neither the robot nor human has a connect 4

}

int scorePoints(int sum, bool oppoCheck)
{
  if(!oppoCheck) //2, 5, 777, -2, -10, -999
  {
    if(sum == 2)
    {
      return TWO_LINE;
    }
    else if(sum == 3)
    {
      return THREE_LINE;
    }
    else if(sum == 4)
    {
      return FOUR_LINE; //777
    }
  }
  else
  {
    if(sum == 3)
    {
      return -1 * TWO_LINE;
    }
    else if(sum == 4)
    {
      return -1 * NEXT_FOUR_LINE; //-999
    }
  }
  
  return 0;
}

int horizontalCheck(int boardArray[BOARD_ROWS][BOARD_COLUMNS], int columnHeights[BOARD_COLUMNS], int columnOfMove, int playerToken, int oppoToken, bool oppoCheck)
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
  
  if(!hitBarrier)
  {
    score += scorePoints(sum, oppoCheck);
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
  
  if(!hitBarrier && !(startCol[0] == endCol[1] && startCol[1] == endCol[0] || startCol[0] == startCol[1] && endCol[0] == endCol[1]))
  {
    score += scorePoints(sum, oppoCheck);
  }
  
  return score;
  
}

int verticalCheck(int boardArray[BOARD_ROWS][BOARD_COLUMNS], int columnHeights[BOARD_COLUMNS], int columnOfMove, int playerToken, int oppoToken, bool oppoCheck)
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
  
  if(!hitBarrier)
  {
    score += scorePoints(sum, oppoCheck);
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
  
  if(!hitBarrier && !(startRow[0] == endRow[1] && startRow[1] == endRow[0] || startRow[0] == startRow[1] && endRow[0] == endRow[1]))
  {
    score += scorePoints(sum, oppoCheck);
  }
  
  return score;
  
}

int positiveSlopeCheck(int boardArray[BOARD_ROWS][BOARD_COLUMNS], int columnHeights[BOARD_COLUMNS], int columnOfMove, int playerToken, int oppoToken, bool oppoCheck)
{
  int score = 0;
   
  const int TOKEN_ROW = BOARD_ROWS - columnHeights[columnOfMove];
  const int TOKEN_COLUMN = columnOfMove;
  
  int startRow[2] = {-1, -2};
  int startCol[2] = {-3, -4};
  int endRow[2] = {-5, -6};
  int endCol[2] = {-7, -8};
  
  bool hitBarrier = false;
  int sum = 1;
  int spacesLeft = 3;
  
  for(int slopeOffset = 1; slopeOffset <= spacesLeft && !hitBarrier; slopeOffset++)
  {
    int currentToken = boardArray[TOKEN_ROW - slopeOffset][TOKEN_COLUMN + slopeOffset];
    
    if(currentToken == oppoToken || TOKEN_ROW - slopeOffset == -1 || TOKEN_COLUMN + slopeOffset == BOARD_COLUMNS)
    {
      hitBarrier = true;
      startRow[0] = TOKEN_ROW - slopeOffset + 1;
      startCol[0] = TOKEN_COLUMN + slopeOffset - 1;
      spacesLeft -= (slopeOffset - 1);
    }
    else if(currentToken == playerToken)
    {
      sum++;
    }
  }
  
  if(hitBarrier)
  {
    hitBarrier = false;
    
    for(int slopeOffset = 1; slopeOffset <= spacesLeft && !hitBarrier; slopeOffset++)
    {
      int currentToken = boardArray[TOKEN_ROW + slopeOffset][TOKEN_COLUMN - slopeOffset];
      
      if(currentToken == oppoToken || TOKEN_ROW + slopeOffset == BOARD_ROWS || TOKEN_COLUMN - slopeOffset == -1)
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
      endCol[0] = TOKEN_COLUMN - spacesLeft;
    }
  }
  else
  {
    startRow[0] = TOKEN_ROW;
    startCol[0] = TOKEN_COLUMN;
    endRow[0] = TOKEN_ROW - spacesLeft;
    endCol[0] = TOKEN_COLUMN + spacesLeft;
  }
  
  if(!hitBarrier)
  {
    score += scorePoints(sum, oppoCheck);
  }
  
  hitBarrier = false;
  sum = 1;
  spacesLeft = 3;
  
  for(int slopeOffset = 1; slopeOffset <= spacesLeft && !hitBarrier; slopeOffset++)
  {
    int currentToken = boardArray[TOKEN_ROW + slopeOffset][TOKEN_COLUMN - slopeOffset];
    
    if(currentToken == oppoToken || TOKEN_ROW + slopeOffset == BOARD_ROWS || TOKEN_COLUMN - slopeOffset == -1)
    {
      hitBarrier = true;
      startRow[1] = TOKEN_ROW + slopeOffset - 1;
      startCol[1] = TOKEN_COLUMN - slopeOffset + 1;
      spacesLeft -= (slopeOffset - 1);
    }
    else if(currentToken == playerToken)
    {
      sum++;
    }
  }
  
  if(hitBarrier)
  {
    hitBarrier = false;
    
    for(int slopeOffset = 1; slopeOffset <= spacesLeft && !hitBarrier; slopeOffset++)
    {
      int currentToken = boardArray[TOKEN_ROW - slopeOffset][TOKEN_COLUMN + slopeOffset];
      
      if(currentToken == oppoToken || TOKEN_ROW - slopeOffset == -1 || TOKEN_COLUMN + slopeOffset == BOARD_COLUMNS)
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
      endCol[1] = TOKEN_COLUMN + spacesLeft;
    }
  }
  else
  {
    startRow[1] = TOKEN_ROW;
    startCol[1] = TOKEN_COLUMN;
    endRow[1] = TOKEN_ROW + spacesLeft;
    endCol[1] = TOKEN_COLUMN - spacesLeft;
  }
  
  if(!hitBarrier && !((startRow[0] == endRow[1] && startCol[0] == endCol[1] && endRow[0] == startRow[1] && endCol[0] == startCol[1]) || (startRow[0] == startRow[1] && startCol[0] == startCol[1] && endRow[0] == endRow[1] && endCol[0] == endCol[1])))
  {
    score += scorePoints(sum, oppoCheck);
  }
  
  return score;
  
}

int negativeSlopeCheck(int boardArray[BOARD_ROWS][BOARD_COLUMNS], int columnHeights[BOARD_COLUMNS], int columnOfMove, int playerToken, int oppoToken, bool oppoCheck)
{
  int score = 0;
   
  const int TOKEN_ROW = BOARD_ROWS - columnHeights[columnOfMove];
  const int TOKEN_COLUMN = columnOfMove;
  
  int startRow[2] = {-1, -2};
  int startCol[2] = {-3, -4};
  int endRow[2] = {-5, -6};
  int endCol[2] = {-7, -8};
  
  bool hitBarrier = false;
  int sum = 1;
  int spacesLeft = 3;
  
  for(int slopeOffset = 1; slopeOffset <= spacesLeft && !hitBarrier; slopeOffset++)
  {
    int currentToken = boardArray[TOKEN_ROW - slopeOffset][TOKEN_COLUMN - slopeOffset];
    
    if(currentToken == oppoToken || TOKEN_ROW - slopeOffset == -1 || TOKEN_COLUMN - slopeOffset == -1)
    {
      hitBarrier = true;
      startRow[0] = TOKEN_ROW - slopeOffset + 1;
      startCol[0] = TOKEN_COLUMN - slopeOffset + 1;
      spacesLeft -= (slopeOffset - 1);
    }
    else if(currentToken == playerToken)
    {
      sum++;
    }
  }
  
  if(hitBarrier)
  {
    hitBarrier = false;
    
    for(int slopeOffset = 1; slopeOffset <= spacesLeft && !hitBarrier; slopeOffset++)
    {
      int currentToken = boardArray[TOKEN_ROW + slopeOffset][TOKEN_COLUMN + slopeOffset];
      
      if(currentToken == oppoToken || TOKEN_ROW + slopeOffset == BOARD_ROWS || TOKEN_COLUMN + slopeOffset == BOARD_COLUMNS)
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
      endCol[0] = TOKEN_COLUMN + spacesLeft;
    }
  }
  else
  {
    startRow[0] = TOKEN_ROW;
    startCol[0] = TOKEN_COLUMN;
    endRow[0] = TOKEN_ROW - spacesLeft;
    endCol[0] = TOKEN_COLUMN - spacesLeft;
  }
  
  if(!hitBarrier)
  {
    score += scorePoints(sum, oppoCheck);
  }
  
  hitBarrier = false;
  sum = 1;
  spacesLeft = 3;
  
  for(int slopeOffset = 1; slopeOffset <= spacesLeft && !hitBarrier; slopeOffset++)
  {
    int currentToken = boardArray[TOKEN_ROW + slopeOffset][TOKEN_COLUMN + slopeOffset];
    
    if(currentToken == oppoToken || TOKEN_ROW + slopeOffset == BOARD_ROWS || TOKEN_COLUMN + slopeOffset == BOARD_COLUMNS)
    {
      hitBarrier = true;
      startRow[1] = TOKEN_ROW + slopeOffset - 1;
      startCol[1] = TOKEN_COLUMN + slopeOffset - 1;
      spacesLeft -= (slopeOffset - 1);
    }
    else if(currentToken == playerToken)
    {
      sum++;
    }
  }
  
  if(hitBarrier)
  {
    hitBarrier = false;
    
    for(int slopeOffset = 1; slopeOffset <= spacesLeft && !hitBarrier; slopeOffset++)
    {
      int currentToken = boardArray[TOKEN_ROW - slopeOffset][TOKEN_COLUMN - slopeOffset];
      
      if(currentToken == oppoToken || TOKEN_ROW - slopeOffset == -1 || TOKEN_COLUMN - slopeOffset == -1)
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
      endCol[1] = TOKEN_COLUMN - spacesLeft;
    }
  }
  else
  {
    startRow[1] = TOKEN_ROW;
    startCol[1] = TOKEN_COLUMN;
    endRow[1] = TOKEN_ROW + spacesLeft;
    endCol[1] = TOKEN_COLUMN + spacesLeft;
  }
  
  if(!hitBarrier && !((startRow[0] == endRow[1] && startCol[0] == endCol[1] && endRow[0] == startRow[1] && endCol[0] == startCol[1]) || (startRow[0] == startRow[1] && startCol[0] == startCol[1] && endRow[0] == endRow[1] && endCol[0] == endCol[1])))
  {
    score += scorePoints(sum, oppoCheck);
  }
  
  return score;
  
}

int scoreBoard(int boardArray[BOARD_ROWS][BOARD_COLUMNS], int columnHeights[BOARD_COLUMNS], int columnOfMove, int playerToken, int oppoToken)
{
  int score = 0;
  int scoreCoefficient = 1;
  if(playerToken == HUMAN_TOKEN_TYPE)
  {
    scoreCoefficient = -1;
  }
  
  for(int colDropIndex = 0; colDropIndex < BOARD_COLUMNS; colDropIndex++)
  {
    const int emptyTokenRow = (BOARD_ROWS - 1) - columnHeights[colDropIndex];
    if(emptyTokenRow > -1)
    {
      addTokenToArray(boardArray, columnHeights, emptyTokenRow, colDropIndex, oppoToken);
                  
      if(colDropIndex != columnOfMove && (horizontalCheck(boardArray, columnHeights, colDropIndex, oppoToken, playerToken, true) <= -100 || verticalCheck(boardArray, columnHeights, colDropIndex, oppoToken, playerToken, true) <= -100 || positiveSlopeCheck(boardArray, columnHeights, colDropIndex, oppoToken, playerToken, true) <= -100 || negativeSlopeCheck(boardArray, columnHeights, colDropIndex, oppoToken, playerToken, true) <= -100))
      {
        removeTokenInArray(boardArray, columnHeights, emptyTokenRow, colDropIndex);
        return -1 * NEXT_FOUR_LINE * scoreCoefficient;
      }
      else if(colDropIndex == columnOfMove)
      {
        score += horizontalCheck(boardArray, columnHeights, columnOfMove, oppoToken, playerToken, true);
        score += positiveSlopeCheck(boardArray, columnHeights, columnOfMove, oppoToken, playerToken, true);
        score += negativeSlopeCheck(boardArray, columnHeights, columnOfMove, oppoToken, playerToken, true);
      }
      
      removeTokenInArray(boardArray, columnHeights, emptyTokenRow, colDropIndex);
    }
  }
  
  if(columnOfMove == 3)
  {
    score += MIDDLE_COLUMN;
  }
  
  score += horizontalCheck(boardArray, columnHeights, columnOfMove, playerToken, oppoToken);
  score += verticalCheck(boardArray, columnHeights, columnOfMove, playerToken, oppoToken);
  score += positiveSlopeCheck(boardArray, columnHeights, columnOfMove, playerToken, oppoToken);
  score += negativeSlopeCheck(boardArray, columnHeights, columnOfMove, playerToken, oppoToken);
  
  score *= scoreCoefficient;
  
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
  
  minimaxReturns values;
  minimaxAlg(boardArray, columnHeights, 4, true, values);
  
  dropToken(boardArray, columnHeights, values.columnOfMove, ROBOT_TOKEN_TYPE);
  
  return values.columnOfMove;
  
}

void minimaxAlg(int boardArray[BOARD_ROWS][BOARD_COLUMNS], int columnHeights[BOARD_COLUMNS], int depth, bool maxPlayer, minimaxReturns &values, int columnOfMove)
{
  
  int wonRobot = gameWon(boardArray, ROBOT_TOKEN_TYPE);
  int wonHuman = gameWon(boardArray, HUMAN_TOKEN_TYPE);
  if(depth == 0 || wonRobot || wonHuman)
  {
    minimaxReturns scoreValue;
    
    if(maxPlayer)
    {
      if(wonRobot == ROBOT_TOKEN_TYPE)
      {
        values.score = FOUR_LINE;
        values.columnOfMove = scoreValue.columnOfMove;
        return;
      }
      else if(wonHuman == HUMAN_TOKEN_TYPE)
      {
        values.score = -1 * FOUR_LINE;
        values.columnOfMove = scoreValue.columnOfMove;
        return;
      }
      
      scoreValue.score = scoreBoard(boardArray, columnHeights, columnOfMove, HUMAN_TOKEN_TYPE, ROBOT_TOKEN_TYPE);
    }
    else
    {
      if(wonRobot == ROBOT_TOKEN_TYPE)
      {
        values.score = FOUR_LINE;
        values.columnOfMove = scoreValue.columnOfMove;
        return;
      }
      else if(wonHuman == HUMAN_TOKEN_TYPE)
      {
        values.score = -1 * FOUR_LINE;
        values.columnOfMove = scoreValue.columnOfMove;
        return;
      }
      
      scoreValue.score = scoreBoard(boardArray, columnHeights, columnOfMove, ROBOT_TOKEN_TYPE, HUMAN_TOKEN_TYPE);
    }
    
    values.score = scoreValue.score;
    values.columnOfMove = scoreValue.columnOfMove;
    return;
  }
  
  if(maxPlayer)
  {
    minimaxReturns maxValues;
    maxValues.score = -9999;
    maxValues.columnOfMove = 1;
    
    for(int colDropIndex = 0; colDropIndex < BOARD_COLUMNS; colDropIndex++) //Drops a token in each column to score that potential move
    {
      const int emptyTokenRow = (BOARD_ROWS - 1) - columnHeights[colDropIndex]; //Checks if a column is not full
      
      if(emptyTokenRow > -1)
      {
        addTokenToArray(boardArray, columnHeights, emptyTokenRow, colDropIndex, ROBOT_TOKEN_TYPE);        
        
        minimaxReturns possibleMoveScore;
        minimaxAlg(boardArray, columnHeights, depth - 1, false, possibleMoveScore, colDropIndex);
        
        displayScore(boardArray, colDropIndex, possibleMoveScore.score);
        
        if(max(maxValues.score, possibleMoveScore.score) == possibleMoveScore.score) /*&& possibleMoveScore.score != maxValues.score*/
        {
          maxValues.score = possibleMoveScore.score;
          maxValues.columnOfMove = colDropIndex + 1;
        }
        
        removeTokenInArray(boardArray, columnHeights, emptyTokenRow, colDropIndex);
     }
    
    }
    
    cout << depth << ": "<< maxValues.score << endl;
    cout << "FinalMove: " << maxValues.columnOfMove - 1 << endl;
    values.score = maxValues.score;
    values.columnOfMove = maxValues.columnOfMove;
    return;
  
  }
  else
  {
    minimaxReturns minValues;
    minValues.score = 9999;
    minValues.columnOfMove = 1;
    
    for(int colDropIndex = 0; colDropIndex < BOARD_COLUMNS; colDropIndex++) //Drops a token in each column to score that potential move
    {
      const int emptyTokenRow = (BOARD_ROWS - 1) - columnHeights[colDropIndex]; //Checks if a column is not full
      
      if(emptyTokenRow > -1)
      {
        addTokenToArray(boardArray, columnHeights, emptyTokenRow, colDropIndex, HUMAN_TOKEN_TYPE); //dont forget to do this in terms of min for human !!
        
        minimaxReturns possibleMoveScore;
        minimaxAlg(boardArray, columnHeights, depth - 1, true, possibleMoveScore, colDropIndex);
        
        displayScore(boardArray, colDropIndex, possibleMoveScore.score);
        
        if(min(minValues.score, possibleMoveScore.score) == possibleMoveScore.score) /*&& possibleMoveScore.score != minValues.score*/
        {
          minValues.score = possibleMoveScore.score;
          minValues.columnOfMove = colDropIndex + 1;
        }
        
        removeTokenInArray(boardArray, columnHeights, emptyTokenRow, colDropIndex);
     }
    
    }
    
    cout << depth << ": "<< minValues.score << endl;
    cout << "FinalMove: " << minValues.columnOfMove - 1 << endl;
    values.score = minValues.score;
    values.columnOfMove = minValues.columnOfMove;
    return;
    
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