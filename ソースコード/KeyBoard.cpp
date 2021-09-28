#include "DxLib.h"
#include "KeyBoard.h"

// �L�[�̓��͏�Ԃ��X�V����
void KeyBoardUpdate() {
	char tmpKey[256];
	GetHitKeyStateAll(tmpKey);

	for (int i = 0; i < 256; i++) {
		if (tmpKey[i] != 0) {
			key[i]++;
		}
		else {
			key[i] = 0;
		}
	}
}

// �����̃L�[�R�[�h�̃L�[�̓��͏�Ԃ�Ԃ�
int KeyBoardGet(int keyCode) {
	return key[keyCode];
}