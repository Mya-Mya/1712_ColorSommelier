#pragma once
#include<vector>

namespace Mya {
	void SpaceVI(int windowwidth, int windowheight, char * Kind, char * Name, char *Message);
	class iRingParticle {
	private:
		int inx, iny;
		int r;
		int vr;
		int limr;
		int color;
	public:
		iRingParticle(int x, int y);
		int DO();
	};
	class mRingParticle {
	private:
		std::vector<iRingParticle*> lP;
		std::vector<iRingParticle*>::iterator iP;
	public:
		mRingParticle();
		void DO();
		void Sprash(int x, int y);
	};
}