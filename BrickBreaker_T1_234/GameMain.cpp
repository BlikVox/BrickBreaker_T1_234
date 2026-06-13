#include "stdafx.h"
#include "GameMain.h"
#include "Ball.h"
#include "Paddle.h"
#include "Brick.h"



GameMain::GameMain()
	: ball(new Ball()), paddle(new Paddle())
{
	for (int32 y = 0; y < 5; ++y)
	{
		for (int32 x = 0; x < (Scene::Width() / 40); ++x)
		{
			bricks << Brick(x, y);
		}
	}
}

GameMain::~GameMain()
{
	delete ball;
	delete paddle;
}

void GameMain::update()
{
	// 更新
	for (auto& brick : bricks) {
		brick.update();
	}
	ball->update();
	paddle->update();

	// 衝突判定
	for (auto it = bricks.begin(); it != bricks.end(); ++it) {
		if (it->reflect(*ball)) {
			bricks.erase(it);	// ブロックを消す
			break;
		}
	}
	paddle->reflect(*ball);
}

void GameMain::draw()
{
	// 描画
	for (auto& brick : bricks) {
		brick.draw();
	}
	ball->draw();
	paddle->draw();
}
