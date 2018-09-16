#include "MyaSpaceVI.h"
#include"DxLib.h"
#include <stdlib.h> 
#include <time.h>
#include<vector>
#include<math.h>

void Mya::SpaceVI(int windowwidth, int windowheight, char * Kind, char * Name,char *Message)
{
	//ランダム種をまく
	unsigned int now = (unsigned int)time(0);
	srand(now);

	//フォントハンドルと色を作成
	int LargeFont = CreateFontToHandle("メイリオ", 50, 6, DX_FONTTYPE_ANTIALIASING);
	int LargeColor = GetColor(30, 30, 30);
	int MiddleFont = CreateFontToHandle("メイリオ", 30, 3, DX_FONTTYPE_ANTIALIASING);
	int MiddleColor = GetColor(100, 100, 100);
	int SmallFont = CreateFontToHandle("メイリオ", 15, 6, DX_FONTTYPE_ANTIALIASING);
	int SmallColor = GetColor(160, 160, 160);

	//パーティクルのクラスを作成
	mRingParticle instRingParticle;

	//座標位置記録のための構造体
	struct sCharacterPos {
		int width;
		int height;
		int x;
		int y;
	};

	//文字の表示座標計算
	sCharacterPos Center;
	Center.width = GetDrawFormatStringWidthToHandle(LargeFont,"::");
	Center.x = (windowwidth / 2) - (Center.width / 2);
	Center.height = GetDrawFormatStringWidthToHandle(LargeFont, "□");
	Center.y = (windowheight / 2) - (Center.height / 2);
	
	sCharacterPos Left;
	Left.width = GetDrawFormatStringWidthToHandle(LargeFont, "Mya ");
	Left.x = Center.x - Left.width;
	Left.height = GetDrawFormatStringWidthToHandle(LargeFont, "□");
	Left.y = (windowheight / 2) - (Left.height / 2);

	sCharacterPos Right;
	Right.width = GetDrawFormatStringWidthToHandle(LargeFont, " %s",Kind);
	Right.x = Center.x+Center.width ;
	Right.height = GetDrawFormatStringWidthToHandle(LargeFont, "□");
	Right.y = (windowheight / 2) - (Right.height / 2);

	sCharacterPos Middle;
	Middle.width = GetDrawFormatStringWidthToHandle(MiddleFont, "%s", Name);
	Middle.x = (windowwidth / 2) - (Middle.width / 2);
	Middle.height = GetDrawFormatStringWidthToHandle(MiddleFont, "□");
	Middle.y = (windowheight / 2) - (Middle.height / 2)+Center.height+5;

	sCharacterPos Bottom;
	Bottom.width = GetDrawFormatStringWidthToHandle(SmallFont, "%s", Message);
	Bottom.x = (windowwidth / 2) - (Bottom.width / 2);
	Bottom.height = GetDrawFormatStringWidthToHandle(MiddleFont, "□");
	Bottom.y = (windowheight / 2) -(Bottom.height/2)+ Middle.height + Center.height + 40;

	//ループ内用変数
	int clock = 0;
	int distance = 0;

	while (ScreenFlip() == 0 && ProcessMessage()==0 && ClearDrawScreen() == 0) {
		//アルファブレンド調整
		{
			if ( 0 <= clock && clock < 10) SetDrawBlendMode(DX_BLENDMODE_ALPHA, 25*clock);
			if (10 == clock) SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
			if (150 <= clock)SetDrawBlendMode(DX_BLENDMODE_ALPHA, 1250-5*clock);
		}

		//背景描画
		DrawBox(0, 0, windowwidth, windowheight, GetColor(220, 220, 220), TRUE);

		//パーティクル描画
		if (clock==30) instRingParticle.Sprash(windowwidth / 2, windowheight / 2);
		instRingParticle.DO();

		//文字描画のアニメーション要素
		{
			if (0 <= clock && clock < 30) distance = (pow((clock - 30), 6))/1000000;
			if (30 <= clock) distance = 0;
		}
		//文字描画
		DrawFormatStringToHandle(Center.x, Center.y, LargeColor, LargeFont, "::");
		DrawFormatStringToHandle(Left.x-distance, Left.y, LargeColor, LargeFont, "Mya ");
		DrawFormatStringToHandle(Right.x+distance, Right.y, LargeColor, LargeFont, " %s",Kind);
		DrawFormatStringToHandle(Middle.x, Middle.y+distance/2, MiddleColor, MiddleFont, " %s", Name);
		DrawFormatStringToHandle(Bottom.x, Bottom.y + distance, SmallColor, SmallFont, " %s", Message);

		//クロックを進める
		clock++;
		if (clock == 250) { SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0); return; }
	}
}

#define RINGPARTICLE_PosRedundancy 20
#define RINGPARTICLE_ColorRedundancy 170 + rand() % 65

Mya::iRingParticle::iRingParticle(int x, int y)
{
	inx = x + RINGPARTICLE_PosRedundancy - rand() % RINGPARTICLE_PosRedundancy*2;
	iny = y + RINGPARTICLE_PosRedundancy - rand() % RINGPARTICLE_PosRedundancy*2;
	r = 0;
	vr = 1+rand() % 3;
	limr = 70 + rand() % 70;
	color = GetColor(RINGPARTICLE_ColorRedundancy, RINGPARTICLE_ColorRedundancy, RINGPARTICLE_ColorRedundancy);
}

int Mya::iRingParticle::DO()
{
	DrawCircle(inx, iny, r, color, TRUE);

	r += vr;
	if (r > limr) return 1;
	return 0;
}

Mya::mRingParticle::mRingParticle()
{
}

void Mya::mRingParticle::DO()
{
	iP = lP.begin();
	while (iP != lP.end()) {
		if ((*iP)->DO() == 1) {
			iP = lP.erase(iP);
			return;
		};
		++iP;
	}
}

void Mya::mRingParticle::Sprash(int x, int y)
{
	for (int i = 0; i<8; i++) lP.push_back(new iRingParticle(x, y));
}

