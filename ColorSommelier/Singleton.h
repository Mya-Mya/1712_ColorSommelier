#pragma once

template <typename _T>
class Singleton {

protected:
	Singleton() {}
	virtual ~Singleton() {}
	Singleton(const Singleton& r) {}
	Singleton& operator=(const Singleton& r) {}

public:
	static _T* Instance() {
		static _T inst;
		return &inst;
	};

};

class Keyboard : public Singleton<Keyboard> {

	friend Singleton< Keyboard >;

public:
	//キーの入力状態を更新
	void Update();

	//引数のキーコードのキーの入力状態を返す
	int Get(int KeyCode);

private:
	int m_Key[256];  // キーの入力状態格納用変数
};

class Mouse : public Singleton<Mouse> {

	Mouse();
	friend Singleton<Mouse>;

public:
	bool Update();	//更新
	int GetPressingCount(int keyCode);//keyCodeのキーが押されているフレーム数を取得
	int GetReleasingCount(int keyCode);//keyCodeのキーが離されているフレーム数を取得
	int GetX();
	int GetY();
	const static int LEFT = 0;
	const static int RIGHT = 1;
	const static int MIDDLE = 2;

private:
	const static int BUTTON_NUM = 8;
	int mKeyPressingCount[BUTTON_NUM];//押されカウンタ
	int mKeyReleasingCount[BUTTON_NUM];//離されカウンタ
	int mX, mY;

	bool IsAvailableCode(int keyCode);//keyCodeが有効なキー番号か問う
};