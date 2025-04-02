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
        cout << "�v���C���[�̃^�[�� (B) - �s�Ɨ����͂��Ă������� (-1 -1�ŃT�����_�[)\n";
        cout << "(��F1 1(���l�̊ԂɃX�y�[�X�����Ă�������)) : ";

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
                cout << "�����Ȉړ��ł��B�Ď��s���Ă��������B" << endl;
            }
        }
        else {//�G���[���Z�b�g
            cout << "���͂������ł��B�Ď��s���Ă��������B" << endl;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
    }
}

void OthelloGame::PlayerSurrender() {
    cout << "�v���C���[���~�Q���܂����BCOM (W) �̏����ł��I" << endl;
    exit(0);
}

bool OthelloGame::IsGameOver() const {
    return !board.HasValidMove(currentPlayer);
}

void OthelloGame::DisplayResult() const {
    int blackCount = board.CountTiles('B');
    int whiteCount = board.CountTiles('W');

    board.Display();

    cout << "�v���C���[ (B) �̐΂̐�: " << blackCount << endl;
    cout << "COM (W) �̐΂̐�: " << whiteCount << endl;

    if (blackCount > whiteCount) {
        cout << "�v���C���[ (B) �̏����I" << endl;
    }
    else if (whiteCount > blackCount) {
        cout << "COM (W) �̏����I" << endl;
    }
    else {
        cout << "���������ł��B" << endl;
    }
}

int main() {
    OthelloGame game;
    game.Play();

    return 0;
}

