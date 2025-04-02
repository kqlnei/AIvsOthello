#ifndef OTHELLO_BOARD_H
#define OTHELLO_BOARD_H

class OthelloBoard {
public:
    static const int BOARD_SIZE = 8;
    OthelloBoard();
    OthelloBoard(const OthelloBoard& other);
    void Initialize();// �{�[�h�̏�����
    void Display() const; // ���݂̃{�[�h�̏�Ԃ�\��
    bool IsValidMove(int row, int col, char currentPlayer) const;// �ړ����L�����ǂ������m�F
    void MakeMove(int row, int col, char currentPlayer); // �{�[�h��ł̈ړ����s���i�I�o���j
    bool HasValidMove(char currentPlayer) const;// ���݂̃v���C���[���ړ����Ă����������m�F
    int CountTiles(char player) const;// �v���C���[�̃I�Z���̐��𐔂���
    char GetTile(int row, int col) const;
    void SwitchPlayer(char& currentPlayer) const;// ���݂̃v���C���[��؂�ւ���

private:
    char board[BOARD_SIZE][BOARD_SIZE];// �Q�[���{�[�h�p2�����z��
};

#endif