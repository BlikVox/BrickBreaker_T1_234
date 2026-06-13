#include <Siv3D.hpp>
#include "Ball.h"
#include "Paddle.h"
#include "Brick.h"

void Main()
{
	Array<Brick> bricks;
	Ball ball;
	Paddle paddle;

	for (int32 y = 0; y < 5; ++y)
	{
		for (int32 x = 0; x < (Scene::Width() / 40); ++x)
		{
			bricks << Brick(x, y);
		}
	}

	while (System::Update())
	{
		// 更新
		for (auto& brick : bricks) {
			brick.update();
		}
		ball.update();
		paddle.update();

		// 衝突判定
		for (auto it = bricks.begin(); it != bricks.end(); ++it) {
			if (it->reflect(ball)) {
				bricks.erase(it);	// ブロックを消す
				break;
			}
		}
		paddle.reflect( ball );

		// 描画
		for (auto& brick : bricks) {
			brick.draw();
		}
		ball.draw();
		paddle.draw();

		//// マウスカーソルを非表示にする | Hide the mouse cursor
		//Cursor::RequestStyle(CursorStyle::Hidden);
	}
}
