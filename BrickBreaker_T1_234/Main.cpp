#include <Siv3D.hpp>
#include "GameMain.h"

void Main()
{
	GameMain game;

	while (System::Update())
	{
		game.update();
		game.draw();
	}
}
