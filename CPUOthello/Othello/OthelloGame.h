#ifndef OTHELLO_GAME_H
#define OTHELLO_GAME_H

#include "OthelloBoard.h"

class OthelloGame {
public:
    OthelloGame();
    void Play();
    bool IsGameOver() const;// �Q�[�����I�����������m�F
    void DisplayResult() const;// �Q�[���̌��ʂ�\��

private:
    OthelloBoard board;
    char currentPlayer;// ���݂̃v���C���[�i'B'�܂���'W'�j

    void PlayerMove(); // �v���C���[�̈ړ�
    void PlayerSurrender();// �v���C���[�̍~�Q
};

#endif
