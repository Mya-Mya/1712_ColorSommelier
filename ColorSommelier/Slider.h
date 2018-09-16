#pragma once
#include"Tile.h"

class SliderBox {
private:
	int LOW, HIGH;
	int LeftX, LeftY;
	int pixperdegree;
	int degree;

	int MouseX, MouseY;
	int NowX;
	bool DroppingOnFlag, DraggingFlag;

	int Font;
public:
	SliderBox(int inLOW, int inHIGH, int inX, int inY, int inPixperdegree);
	int Get();
	void DO();
	void Change(int change);
	bool Dragging();
};

class Slider {
private:
	int LOW, HIGH;
	int LeftX, LeftY;
	int pixperdegree;
	SliderBox *L;
	SliderBox *H;
public:
	Slider(int inLOW, int inHIGH, int inX, int inY, int inPixperdegree);
	int GetL();
	int GetH();
	int Dragging();
	void DO();
};

class mSlider {
private:
	Slider *R, *G, *B;
	mTile *T;
	int Font;
public:
	mSlider();
	void DO();
};