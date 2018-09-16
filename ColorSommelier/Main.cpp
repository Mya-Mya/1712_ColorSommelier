#include"DxLib.h"
#include"Slider.h"
#include"Singleton.h"
#include"MyaSpaceVI.h"

int main()
{
	SetGraphMode(800, 600, 32);
	ChangeWindowMode(TRUE), DxLib_Init(), SetDrawScreen(DX_SCREEN_BACK);

	Mya::SpaceVI(800, 600, "App",
		"Color Sommelier (RGB)",
		"‚ ‚È‚½‚Ì‚¨D‚Ý‚ÌF(RGB)‚ð‚Ç‚¤‚¼B"
	);

	mSlider *inst = new mSlider();
	while (ScreenFlip() == 0 && ProcessMessage() == 0 && ClearDrawScreen() == 0) {
		Mouse::Instance()->Update();
		Keyboard::Instance()->Update();
		DrawBox(0, 0, 800, 600, GetColor(255, 255, 255), TRUE);
		inst->DO();
	}
	DxLib_End();
	return 0;
}