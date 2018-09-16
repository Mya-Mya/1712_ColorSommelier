#include "Singleton.h"
#include"DxLib.h"

void Keyboard::Update()
{
	char tmpKey[256];             // 現在のキーの入力状態を格納する
	GetHitKeyStateAll(tmpKey);  // 全てのキーの入力状態を得る
	for (int i = 0; i<256; i++) {
		if (tmpKey[i] != 0) { // i番のキーコードに対応するキーが押されていたら
			m_Key[i]++;   // 加算
		}
		else {              // 押されていなければ
			m_Key[i] = 0; // 0にする
		}
	}
}

int Keyboard::Get(int KeyCode)
{
	return m_Key[KeyCode]; // KeyCodeの入力状態を返す
}

Mouse::Mouse() :
	mX(0)
	, mY(0)
{
	memset(mKeyPressingCount, 0, sizeof(mKeyPressingCount));
	memset(mKeyReleasingCount, 0, sizeof(mKeyReleasingCount));
}

//更新
bool Mouse::Update() {
	int nowInput = GetMouseInput();      //今のキーの入力状態を取得
	for (int i = 0; i<BUTTON_NUM; i++) {
		if ((nowInput >> i) & 0x01) {    //i番のキーが押されていたら
			if (mKeyReleasingCount[i] > 0) {//離されカウンタが0より大きければ
				mKeyReleasingCount[i] = 0;   //0に戻す
			}
			mKeyPressingCount[i]++;          //押されカウンタを増やす
		}
		else {                             //i番のキーが離されていたら
			if (mKeyPressingCount[i] > 0) { //押されカウンタが0より大きければ
				mKeyPressingCount[i] = 0;    //0に戻す
			}
			mKeyReleasingCount[i]++;         //離されカウンタを増やす
		}
	}
	GetMousePoint(&mX, &mY);
	return true;
}

//keyCodeのキーが押されているフレーム数を返す
int Mouse::GetPressingCount(int keyCode) {
	if (!Mouse::IsAvailableCode(keyCode)) {
		return -1;
	}
	return mKeyPressingCount[keyCode];
}

//keyCodeのキーが離されているフレーム数を返す
int Mouse::GetReleasingCount(int keyCode) {
	if (!Mouse::IsAvailableCode(keyCode)) {
		return -1;
	}
	return mKeyReleasingCount[keyCode];
}

//keyCodeが有効な値かチェックする
bool Mouse::IsAvailableCode(int keyCode) {
	if (0 <= keyCode && keyCode<BUTTON_NUM) {
		return true;
	}
	return false;
}

int Mouse::GetX() {
	return mX;
}

int Mouse::GetY() {
	return mY;
}
