#include "OthelloGame.h"
#include "OthelloComputer.h"
#include <iostream>
#include <cstdlib>
#include <ctime>

using namespace std;

OthelloGame::OthelloGame() {
    currentPlayer = 'B';
}

void OthelloGame::Play() {
    srand(static_cast<unsigned>(time(nullptr)));
    while (!IsGameOver()) {
        board.Display();

        if (currentPlayer == 'B') {
            PlayerMove();
        }
        else {
            OthelloComputer computer;
            computer.MakeMove(board, currentPlayer);
        }

        board.SwitchPlayer(currentPlayer);
    }

    board.Display();
    DisplayResult();
}

void OthelloGame::PlayerMove() {
    bool validMove = false;
    while (!validMove) {
        cout << "プレイヤーのターン (B) - 行と列を入力してください (-1 -1でサレンダー)\n";
        cout << "(例：1 1(数値の間にスペースを入れてください)) : ";

        int row, col;

        if (cin >> row >> col) {
            if (row == -1 && col == -1) {
                PlayerSurrender();
                return;
            }

            if (board.IsValidMove(row, col, currentPlayer)) {
                board.MakeMove(row, col, currentPlayer);
                validMove = true;
            }
            else {
                cout << "無効な移動です。再試行してください。" << endl;
            }
        }
        else {//エラーリセット
            cout << "入力が無効です。再試行してください。" << endl;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
    }
}

void OthelloGame::PlayerSurrender() {
    cout << "プレイヤーが降参しました。COM (W) の勝ちです！" << endl;
    exit(0);
}

bool OthelloGame::IsGameOver() const {
    return !board.HasValidMove(currentPlayer);
}

void OthelloGame::DisplayResult() const {
    int blackCount = board.CountTiles('B');
    int whiteCount = board.CountTiles('W');

    board.Display();

    cout << "プレイヤー (B) の石の数: " << blackCount << endl;
    cout << "COM (W) の石の数: " << whiteCount << endl;

    if (blackCount > whiteCount) {
        cout << "プレイヤー (B) の勝ち！" << endl;
    }
    else if (whiteCount > blackCount) {
        cout << "COM (W) の勝ち！" << endl;
    }
    else {
        cout << "引き分けです。" << endl;
    }
}

int main() {
    OthelloGame game;
    game.Play();

    return 0;
}

