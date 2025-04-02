#include "OthelloComputer.h"
#include <algorithm>
#include <ctime>
#include <climits>

OthelloComputer::OthelloComputer() {}

int OthelloComputer::EvaluateBoard(const OthelloBoard& board, char player) const {
    const int CORNER_VALUE = 20;
    const int DISK_WEIGHT = 1;

    char opponent = (player == 'B') ? 'W' : 'B';
    int playerDisks = 0;
    int opponentDisks = 0;
    int cornerScore = 0;

    // �p�̕]���iGetTile���g�p�j
    const std::vector<std::pair<int, int>> corners = { {0,0}, {0,7}, {7,0}, {7,7} };
    for (const auto& corner : corners) {
        char tile = board.GetTile(corner.first, corner.second);
        if (tile == player) cornerScore += CORNER_VALUE;
        else if (tile == opponent) cornerScore -= CORNER_VALUE;
    }

    // �f�B�X�N���]��
    playerDisks = board.CountTiles(player);
    opponentDisks = board.CountTiles(opponent);
    int diskDiff = (playerDisks - opponentDisks) * DISK_WEIGHT;

    return cornerScore + diskDiff;
}

int OthelloComputer::Minimax(OthelloBoard& board, int depth, bool maximizingPlayer, int alpha, int beta, char player) {
    if (depth == 0 || !board.HasValidMove(player)) {
        return EvaluateBoard(board, player);
    }

    char currentPlayer = maximizingPlayer ? player : (player == 'B' ? 'W' : 'B');
    std::vector<Move> validMoves;

    // �L���Ȏ�̗�
    for (int i = 0; i < OthelloBoard::BOARD_SIZE; ++i) {
        for (int j = 0; j < OthelloBoard::BOARD_SIZE; ++j) {
            if (board.IsValidMove(i, j, currentPlayer)) {
                validMoves.push_back({ i, j, 0 });
            }
        }
    }

    if (maximizingPlayer) {
        int maxEval = INT_MIN;
        for (auto& move : validMoves) {
            OthelloBoard newBoard = board; // �{�[�h�̃R�s�[���K�v
            newBoard.MakeMove(move.row, move.col, player);
            int eval = Minimax(newBoard, depth - 1, false, alpha, beta, player);
            maxEval = std::max(maxEval, eval);
            alpha = std::max(alpha, eval);
            if (beta <= alpha) break; // �����J�b�g
        }
        return maxEval;
    }
    else {
        int minEval = INT_MAX;
        for (auto& move : validMoves) {
            OthelloBoard newBoard = board;
            newBoard.MakeMove(move.row, move.col, currentPlayer);
            int eval = Minimax(newBoard, depth - 1, true, alpha, beta, player);
            minEval = std::min(minEval, eval);
            beta = std::min(beta, eval);
            if (beta <= alpha) break;
        }
        return minEval;
    }
}

void OthelloComputer::MakeMove(OthelloBoard& board, char currentPlayer) {
    int bestRow = -1, bestCol = -1;
    FindBestMove(board, currentPlayer, bestRow, bestCol);
    if (bestRow != -1 && bestCol != -1) {
        board.MakeMove(bestRow, bestCol, currentPlayer);
    }
}

int OthelloComputer::FindBestMove(OthelloBoard& board, char currentPlayer, int& bestRow, int& bestCol) {
    std::vector<Move> validMoves;
    int maxScore = INT_MIN;

    // �L���Ȏ�̎��W
    for (int i = 0; i < OthelloBoard::BOARD_SIZE; ++i) {
        for (int j = 0; j < OthelloBoard::BOARD_SIZE; ++j) {
            if (board.IsValidMove(i, j, currentPlayer)) {
                validMoves.push_back({ i, j, 0 });
            }
        }
    }

    // �L���Ȏ肪�Ȃ��ꍇ
    if (validMoves.empty()) {
        bestRow = bestCol = -1;
        return -1;
    }

    // �œK�Ȏ��T��
    for (auto& move : validMoves) {
        OthelloBoard newBoard = board;
        newBoard.MakeMove(move.row, move.col, currentPlayer);
        int score = Minimax(newBoard, MAX_DEPTH, false, INT_MIN, INT_MAX, currentPlayer);

        if (score > maxScore) {
            maxScore = score;
            bestRow = move.row;
            bestCol = move.col;
        }
    }

    // ���X�R�A�̎肪��������ꍇ�����_���I��
    std::vector<Move> bestMoves;
    for (const auto& move : validMoves) {
        OthelloBoard newBoard = board;
        newBoard.MakeMove(move.row, move.col, currentPlayer);
        if (EvaluateBoard(newBoard, currentPlayer) == maxScore) {
            bestMoves.push_back(move);
        }
    }

    if (!bestMoves.empty()) {
        int randomIndex = rand() % bestMoves.size();
        bestRow = bestMoves[randomIndex].row;
        bestCol = bestMoves[randomIndex].col;
    }

    return maxScore;
}