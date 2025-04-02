#ifndef OTHELLO_BOARD_H
#define OTHELLO_BOARD_H

class OthelloBoard {
public:
    static const int BOARD_SIZE = 8;
    OthelloBoard();
    OthelloBoard(const OthelloBoard& other);
    void Initialize();// ボードの初期化
    void Display() const; // 現在のボードの状態を表示
    bool IsValidMove(int row, int col, char currentPlayer) const;// 移動が有効かどうかを確認
    void MakeMove(int row, int col, char currentPlayer); // ボード上での移動を行う（オバロ）
    bool HasValidMove(char currentPlayer) const;// 現在のプレイヤーが移動してもいいかを確認
    int CountTiles(char player) const;// プレイヤーのオセロの数を数える
    char GetTile(int row, int col) const;
    void SwitchPlayer(char& currentPlayer) const;// 現在のプレイヤーを切り替える

private:
    char board[BOARD_SIZE][BOARD_SIZE];// ゲームボード用2次元配列
};

#endif