#ifndef OTHELLO_COMPUTER_H
#define OTHELLO_COMPUTER_H

#include "OthelloBoard.h"
#include <vector>

class OthelloComputer {
public:
    OthelloComputer();
    void MakeMove(OthelloBoard& board, char currentPlayer);

private:
    struct Move {
        int row;
        int col;
        int score;
    };

    int EvaluateBoard(const OthelloBoard& board, char player) const;
    int Minimax(OthelloBoard& board, int depth, bool maximizingPlayer, int alpha, int beta, char player);
    int FindBestMove(OthelloBoard& board, char currentPlayer, int& bestRow, int& bestCol);
    const int MAX_DEPTH = 3; // íTçıê[Ç≥
};

#endif