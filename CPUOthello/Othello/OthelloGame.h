#ifndef OTHELLO_GAME_H
#define OTHELLO_GAME_H

#include "OthelloBoard.h"

class OthelloGame {
public:
    OthelloGame();
    void Play();
    bool IsGameOver() const;// ゲームが終了したかを確認
    void DisplayResult() const;// ゲームの結果を表示

private:
    OthelloBoard board;
    char currentPlayer;// 現在のプレイヤー（'B'または'W'）

    void PlayerMove(); // プレイヤーの移動
    void PlayerSurrender();// プレイヤーの降参
};

#endif
