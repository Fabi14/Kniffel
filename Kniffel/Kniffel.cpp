#define OLC_PGE_APPLICATION
#include "olcPixelGameEngine.h"
#include "KniffelGame.h"


int main()
{
	KniffelGame game;
	if (game.Construct(256, 240, 4, 4))
		game.Start();
	return 0;
}
