#include <iostream>
#include <cmath>
#include <cctype>
#include<cstdlib>
using namespace std;

const int SIZE = 8;

char board[SIZE][SIZE];
    int x, y;


void initializeBoard();
void printBoard();
bool isInBounds(int x, int y);
bool isPathClear(int startX, int startY, int endX, int endY);
bool isUnderAttack(int x, int y, bool isWhite);
bool isKingInCheck(bool isWhite);
bool isValidMove(char piece, int startX, int startY, int endX, int endY, bool isWhite);
bool movePiece(int startX, int startY, int endX, int endY, bool isWhite);
bool isCheckmate(bool isWhite);


void initializeBoard() {
    char initialBoard[SIZE][SIZE] = {
        {'R', 'N', 'B', 'Q', 'K', 'B', 'N', 'R'},
        {'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P'},
        {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
        {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
        {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
        {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
        {'p', 'p', 'p', 'p', 'p', 'p', 'p', 'p'},
        {'r', 'n', 'b', 'q', 'k', 'b', 'n', 'r'}
    };

    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            board[i][j] = initialBoard[i][j];
        }
    }
}


void printBoard() {
    cout << "  0 1 2 3 4 5 6 7" << endl;
    for (int i = 0; i < SIZE; i++) {
        cout << i << " ";
        for (int j = 0; j < SIZE; j++) {
            cout << board[i][j] << " ";
        }
        cout << endl;
    }
}


bool isInBounds(int x, int y) {
    return x >= 0 && x < SIZE && y >= 0 && y < SIZE;
}


bool isPathClear(int startX, int startY, int endX, int endY) {
    int dx = (endX - startX) == 0 ? 0 : (endX - startX) / abs(endX - startX);
    int dy = (endY - startY) == 0 ? 0 : (endY - startY) / abs(endY - startY);

    int x = startX + dx;
   int y = startY + dy;

    while (x != endX || y != endY) {
        if (board[x][y] != ' ') {
            return false;
       }
        x += dx;
        y += dy;
    }

    return true;
}


bool isUnderAttack(int x, int y, bool isWhite) {
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            char piece = board[i][j];
            if ((isWhite && islower(piece)) || (!isWhite && isupper(piece))) {
                if (isValidMove(piece, i, j, x, y, !isWhite)) {
                    return true;
                }
            }
        }
    }
    return false;
}


bool isKingInCheck(bool isWhite) {
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            if ((isWhite && board[i][j] == 'K') || (!isWhite && board[i][j] == 'k')) {
                return isUnderAttack(i, j, isWhite);
            }
        }
    }
    return false;
    
}


bool isValidMove(char piece, int startX, int startY, int endX, int endY, bool isWhite) {
    int dx = endX - startX;
    int dy = endY - startY;
    char target = board[endX][endY];

    
    if ((isWhite && isupper(target)) || (!isWhite && islower(target))) {
        return true;
    }     if ((isWhite && islower(target)) || (!isWhite && isupper(target))) {
        return false;
    }

    switch (toupper(piece)) {
        case 'P': // Pawn
            if (isWhite) {
                if ((dx == -1 && dy == 0 && target == ' ') 
                   || (dx == -1 && abs(dy) == 1 && islower(target) && target != ' ')) {
                    return true;
                }
                if(dx == -1 && dy == 0 && islower(target)){
                	return false;
				}
                
                
            } else {
                if ((dx == 1 && dy == 0 && target == ' ') 
                    || (dx == 1 && abs(dy) == 1 && isupper(target) && target != ' ')) {
                    return true;
                }
                if(dx == 1 && dy == 0 && isupper(target)){
                	return false;
				}
                
            }
            break;
        case 'R': // Rook
            if ((dx == 0 || dy == 0) && isPathClear(startX, startY, endX, endY)) {
                return true;
            }
            break;
        case 'N': // Knight
            if ((abs(dx) == 2 && abs(dy) == 1) || (abs(dx) == 1 && abs(dy) == 2)) {
                return true;
            }
            break;
        case 'B': // Bishop
            if (abs(dx) == abs(dy) && isPathClear(startX, startY, endX, endY)) {
                return true;
            }
            break;
        case 'Q': // Queen
            if (((dx == 0 || dy == 0) || (abs(dx) == abs(dy))) && isPathClear(startX, startY, endX, endY)) {
                return true;
            }
            break;
        case 'K': // King
            if (abs(dx) <= 1 && abs(dy) <= 1) {
                return true;
            }
            break;
    }

  return false;
}


bool movePiece(int startX, int startY, int endX, int endY, bool isWhite) {
    char piece = board[startX][startY];
    char target = board[endX][endY];

    if (isValidMove(piece, startX, startY, endX, endY, isWhite)) {

        
        board[endX][endY] = piece;
        board[startX][startY] = ' ';

      
        if (isKingInCheck(isWhite)) {
     
            board[startX][startY] = piece;
            board[endX][endY] = target;
            cout << "Invalid move! Your king would be in check." << endl;
            return false;
        }

        return true;
    }

    cout << "Invalid move!" << endl;
    printBoard();
   return false;
}


bool isCheckmate(bool isWhite) {
    for (int startX = 0; startX < SIZE; startX++) {
        for (int startY = 0; startY < SIZE; startY++) {
            if ((isWhite && isupper(board[startX][startY])) || (!isWhite && islower(board[startX][startY]))) {
                for (int endX = 0; endX < SIZE; endX++) {
                    for (int endY = 0; endY < SIZE; endY++) {
                        char piece = board[startX][startY];
                        if (isValidMove(piece, startX, startY, endX, endY, isWhite)) {
                            char target = board[endX][endY];

                           
                            board[endX][endY] = piece;
                            board[startX][startY] = ' ';

                            bool kingInCheck = isKingInCheck(isWhite);

                    
                            board[startX][startY] = piece;
                            board[endX][endY] = target;

                            if (!kingInCheck) {
                                return false; 
                            }
                        }
                    }
                }
            }
        }
    }
    return true;
}


int main() {
    initializeBoard();
    printBoard();

    bool isWhiteTurn = true; 

    while (true) {
        if (isKingInCheck(isWhiteTurn)) {
            cout << (isWhiteTurn ? "White" : "Black") << " is in check!" << endl;
            if (isCheckmate(isWhiteTurn)) {
                cout << (isWhiteTurn ? "White" : "Black") << " is in checkmate! Game over." << endl;
                break;
            }
        }

        int startX, startY, endX, endY;
        cout << (isWhiteTurn ? "White" : "Black") << "'s turn." << endl;

        cout << "Enter starting position (x y): ";
        cin >> startX >> startY;

        cout << "Enter ending position (x y): ";
        cin >> endX >> endY;
           
          system("cls");

    
        if (isInBounds(startX, startY) && isInBounds(endX, endY)) {
            if (!movePiece(startX, startY, endX, endY, isWhiteTurn)) {
                continue; 
            }

         
            printBoard();

         
            isWhiteTurn = !isWhiteTurn;
        } else {
            cout << "Invalid move! Out of bounds." << endl;
            printBoard();
        }
    }

    return 0;
}
