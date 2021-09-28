#include "DxLib.h"
#include "KeyBoard.h"

// キーの入力状態を更新する
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

// 引数のキーコードのキーの入力状態を返す
int KeyBoardGet(int keyCode) {
	return key[keyCode];
}