#include "Tile.h"
#include"DxLib.h"
#include"Singleton.h"

Tile::Tile(int RL, int RH, int GL, int GH, int BL, int BH, int inx, int iny, iTile *in)
{
	r = RL; if (RH - RL > 0) r += rand() % (RH - RL);
	g = GL; if (GH - GL > 0) g += rand() % (GH - GL);
	b = BL; if (BH - BL > 0) b += rand() % (BH - BL);
	color = GetColor(r, g, b);
	x = inx, y = iny;
	Det = in;
}

void Tile::DO()
{
	//マウス座標の取得
	MouseX = Mouse::Instance()->GetX();
	MouseY = Mouse::Instance()->GetY();

	//通常描画
	DrawBox(x + 10, y + 10, x +90, y +90, color, TRUE);

	//かざしているか調べる
	if(x<MouseX&&MouseX<x+100){
		if (y < MouseY&&MouseY < y + 100) {
			DrawBox(x + 4, y + 4, x + 96, y + 96, color, TRUE);
			Det->DetailPrev(r,g,b,x,y);
			if (Mouse::Instance()->GetReleasingCount(Mouse::LEFT) ==1) Det->DetailShow(r, g, b);
		}
	}
}

mTile::mTile()
{
	SmallFont = CreateFontToHandle("メイリオ", 15, 4, DX_FONTTYPE_ANTIALIASING);
	LargeFont = CreateFontToHandle("メイリオ", 40, 5, DX_FONTTYPE_ANTIALIASING);
	DetailFlag = false;
}

void mTile::ReMake(int RL, int RH, int GL, int GH, int BL, int BH)
{
	//削除
	auto itr = lT.begin();
	while (itr != lT.end()) {
		lT.erase(itr);
		itr = lT.begin();
		continue;
	}

	//作成 ただし2,2~7,4を除く
	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 6; j++) {
			if (1 <= i && i <= 6 && 1 <= j && j <= 3) continue;
			lT.push_back(new Tile(RL, RH, GL, GH, BL, BH, 100 * i, 100 * j,this));
		}
	}
}

void mTile::DetailPrev(int R, int G, int B, int x, int y)
{
	DrawBox(x+3, y+13, x + 97, y + 30, GetColor(70, 70, 70), TRUE);
	DrawFormatStringToHandle(x+5, y+13, GetColor(250, 250, 250), SmallFont, "%d,%d,%d", R, G, B);
}

void mTile::DetailShow(int R, int G, int B)
{
	r = R, g = G, b = B;
	DetailFlag = true;
}

void mTile::DO()
{
	auto itr = lT.begin();
	while (itr != lT.end()) {
		(*itr)->DO();
		++itr;
	}

	//詳細表示
	if (DetailFlag == true) {
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, 200);
		DrawBox(0, 0, 800, 600, GetColor(0, 0, 0), TRUE);
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);

		DrawFormatStringToHandle(400-0.5*GetDrawFormatStringWidthToHandle(LargeFont, "%d,%d,%d,", r, g, b),20,GetColor(240,240,240),LargeFont,"%d,%d,%d",r,g,b);

		DrawBox(50, 80, 750, 400, GetColor(r, g, b), TRUE);
		
		DrawFormatStringFToHandle(50, 2 + 420, GetColor(230, 230, 230), LargeFont,"R");
		DrawLine(90, 20 + 420, 710, 20 + 420, GetColor(80, 80, 80), 8);
		DrawLine(90, 20 + 420, 90 + 620 * r / 255, 20 + 420, GetColor(240, 240, 240), 8);

		DrawFormatStringFToHandle(50, 2 + 470, GetColor(230, 230, 230), LargeFont, "G");
		DrawLine(90, 20 + 470, 710, 20 + 470, GetColor(80, 80, 80), 8);
		DrawLine(90, 20 + 470, 90 + 620 * g / 255, 20 + 470, GetColor(240, 240, 240), 8);

		DrawFormatStringFToHandle(50, 2 + 520, GetColor(230, 230, 230), LargeFont, "B");
		DrawLine(90, 20 + 520, 710, 20 + 520, GetColor(80, 80, 80), 8);
		DrawLine(90, 20 + 520, 90 + 620 * b / 255, 20 + 520, GetColor(240, 240, 240), 8);
		
		if (CheckHitKeyAll() != 0) DetailFlag = false;
	}
}
