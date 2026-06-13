#include <Siv3D.hpp>
#include "GameMain.h"

void Main()
{
	GameMain game;

	int* pValue = new int(100);
	delete pValue;
	//pValue = nullptr;

	while (System::Update())
	{
		game.update();
		game.draw();
	}
}
