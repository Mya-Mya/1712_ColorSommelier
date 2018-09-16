#include "Slider.h"
#include"Singleton.h"
#include"DxLib.h"

SliderBox::SliderBox(int inLOW, int inHIGH, int inX, int inY, int inPixperdegree)
{
	LOW = inLOW, HIGH = inHIGH, LeftX = inX, LeftY = inY, pixperdegree = inPixperdegree;
	degree = 0;
	DroppingOnFlag = false, DraggingFlag = false;
	Font = CreateFontToHandle("メイリオ", 12, 2, DX_FONTTYPE_NORMAL);
}

int SliderBox::Get()
{
	return degree;
}

void SliderBox::DO()
{
	//マウス座標の取得
	MouseX = Mouse::Instance()->GetX();
	MouseY = Mouse::Instance()->GetY();

	//かざしているか調べる
	DroppingOnFlag = false;
	if (NowX - 17 < MouseX && MouseX < NowX + 17) {
		if (LeftY - 12 < MouseY && MouseY < LeftY + 12) {
			DroppingOnFlag = true;
		}
	}

	//つかみはじめを調べる
	if (Mouse::Instance()->GetPressingCount(Mouse::LEFT) == 1) {
		if(DroppingOnFlag==true){
			DraggingFlag = true;
		}
	}

	//つかみおわりを調べる
	if (Mouse::Instance()->GetReleasingCount(Mouse::LEFT) == 1) {
		DraggingFlag = false;
	}

	//(つかんでいる時)マウス座標からdegreeを求める・修正
	if (DraggingFlag == true) {
		degree = (MouseX - LeftX) / pixperdegree + LOW;
		if (degree < LOW) degree = LOW;
		if (HIGH < degree)degree = HIGH;
	}

	//NowXを求める
	NowX = LeftX + (degree - LOW)*pixperdegree;

	//描画
	DrawBox(NowX - 15, LeftY - 10, NowX + 15, LeftY + 10, GetColor(120, 120, 120), TRUE);
	DrawFormatStringToHandle(NowX - 11, LeftY - 6, GetColor(240, 240, 240),Font,"%d",degree);
}

void SliderBox::Change(int change)
{
	degree = change;
}

bool SliderBox::Dragging()
{
	return DraggingFlag;
}

Slider::Slider(int inLOW, int inHIGH, int inX, int inY, int inPixperdegree)
{
	LOW = inLOW, HIGH = inHIGH, LeftX = inX, LeftY = inY, pixperdegree = inPixperdegree;
	H = new SliderBox(inLOW, inHIGH, inX, inY - 13, inPixperdegree);
	L = new SliderBox(inLOW, inHIGH, inX, inY + 13, inPixperdegree);
}

int Slider::GetL()
{
	return L->Get();
}

int Slider::GetH()
{
	return H->Get();
}

int Slider::Dragging()
{
	//大小関係の逆転を防ぐ
	if (L->Dragging() == true) {
		if (L->Get() > H->Get()) H->Change(L->Get());
		return 1;
	}
	if (H->Dragging() == true) {
		if (H->Get() < L->Get()) L->Change(H->Get());
		return 1;
	}
	return 0;
}

void Slider::DO()
{
	DrawLine(LeftX, LeftY, LeftX+(HIGH - LOW)*pixperdegree, LeftY, GetColor(210, 210, 210), 4);
		
	L->DO();
	H->DO();
}

mSlider::mSlider()
{
	R = new Slider(0, 255, 160, 150, 2);
	G = new Slider(0, 255, 160, 250, 2);
	B = new Slider(0, 255, 160, 350, 2);
	T = new mTile();
	Font= CreateFontToHandle("メイリオ", 45, 2, DX_FONTTYPE_NORMAL);
}

void mSlider::DO()
{
	DrawBox(100, 100, 700, 400, GetColor(80, 80, 80), TRUE);

	DrawFormatStringFToHandle(8 + 100, 30 + 100, GetColor(230, 230, 230), Font, "R");
	DrawFormatStringFToHandle(8 + 100, 30 + 200, GetColor(230, 230, 230), Font, "G");
	DrawFormatStringFToHandle(8 + 100, 30 + 300, GetColor(230, 230, 230), Font, "B");

	if ((R->Dragging() + G->Dragging()+B->Dragging()) != 0) {
		T->ReMake(
			R->GetL(), R->GetH(),
			G->GetL(), G->GetH(),
			B->GetL(), B->GetH()
		);
	}

	R->DO();
	G->DO();
	B->DO();

	T->DO();
}
