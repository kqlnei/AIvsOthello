#include "OthelloBoard.h"
#include <iostream>

using namespace std;

OthelloBoard::OthelloBoard() {
    Initialize();
}
// コピーコンストラクタ
OthelloBoard::OthelloBoard(const OthelloBoard& other) {
    for (int i = 0; i < BOARD_SIZE; i++) {
        for (int j = 0; j < BOARD_SIZE; j++) {
            board[i][j] = other.board[i][j];
        }
    }
}

void OthelloBoard::Initialize() {
    for (int i = 0; i < BOARD_SIZE; i++) {
        for (int j = 0; j < BOARD_SIZE; j++) {
            board[i][j] = ' ';
        }
    }
    board[3][3] = board[4][4] = 'W';
    board[3][4] = board[4][3] = 'B';
}

void OthelloBoard::Display() const {
    cout << "   ";
    for (int i = 0; i < BOARD_SIZE; i++) {
        cout << i << ' ';
    }
    cout << endl;

    for (int i = 0; i < BOARD_SIZE; i++) {
        cout << i << "  ";
        for (int j = 0; j < BOARD_SIZE; j++) {
            cout << board[i][j] << ' ';
        }
        cout << endl;
    }
}

bool OthelloBoard::IsValidMove(int row, int col, char currentPlayer) const {
    if (row < 0 || row >= BOARD_SIZE || col < 0 || col >= BOARD_SIZE || board[row][col] != ' ') {
        return false;
    }

    char opponent = (currentPlayer == 'B') ? 'W' : 'B';//? if : else

    for (int i = -1; i <= 1; i++) {
        for (int j = -1; j <= 1; j++) {
            if (i == 0 && j == 0) continue;

            int r = row + i;
            int c = col + j;
            while (r >= 0 && r < BOARD_SIZE && c >= 0 && c < BOARD_SIZE && board[r][c] == opponent) {
                r += i;
                c += j;
                if (r >= 0 && r < BOARD_SIZE && c >= 0 && c < BOARD_SIZE && board[r][c] == currentPlayer) {
                    return true;
                }
            }
        }
    }

    return false;
}

void OthelloBoard::MakeMove(int row, int col, char currentPlayer) {
    board[row][col] = currentPlayer;

    char opponent = (currentPlayer == 'B') ? 'W' : 'B';

    for (int i = -1; i <= 1; i++) {
        for (int j = -1; j <= 1; j++) {
            if (i == 0 && j == 0) continue;

            int r = row + i;
            int c = col + j;
            while (r >= 0 && r < BOARD_SIZE && c >= 0 && c < BOARD_SIZE && board[r][c] == opponent) {
                r += i;
                c += j;
                if (r >= 0 && r < BOARD_SIZE && c >= 0 && c < BOARD_SIZE && board[r][c] == currentPlayer) {
                    while (r != row || c != col) {
                        r -= i;
                        c -= j;
                        board[r][c] = currentPlayer;
                    }
                }
            }
        }
    }
}

bool OthelloBoard::HasValidMove(char currentPlayer) const {
    for (int i = 0; i < BOARD_SIZE; i++) {
        for (int j = 0; j < BOARD_SIZE; j++) {
            if (IsValidMove(i, j, currentPlayer)) {
                return true;
            }
        }
    }
    return false;
}

int OthelloBoard::CountTiles(char player) const {
    int count = 0;
    for (int i = 0; i < BOARD_SIZE; i++) {
        for (int j = 0; j < BOARD_SIZE; j++) {
            if (board[i][j] == player) {
                count++;
            }
        }
    }
    return count;
}

char OthelloBoard::GetTile(int row, int col) const {
    if (row < 0 || row >= BOARD_SIZE || col < 0 || col >= BOARD_SIZE)
        return ' ';
    return board[row][col];
}

void OthelloBoard::SwitchPlayer(char& currentPlayer) const {
    currentPlayer = (currentPlayer == 'B') ? 'W' : 'B';
}

