# include <Siv3D.hpp>

/// @brief ブロック
class Brick {
	const Size Size{ 40, 20 };

	Rect rect;

public:
	Brick(int32 x, int32 y)
		: rect((x* Size.x), (60 + y * Size.y), Size)
	{}

	void update() {}
	void draw() {
		rect.stretched(-1).draw(HSV{ rect.y - 40 });
	}
};

/// @brief ボール
class Ball {
	const double SpeedPerSec = 480.0;

	Vec2 velocity{ 0, -SpeedPerSec };
	Circle ball;

public:
	Ball()
		: ball(Circle{ 400, 400, 8 })
	{}

	void update() {
		ball.moveBy(velocity * Scene::DeltaTime());

		if ((ball.y < 0) && (velocity.y < 0))
		{
			velocity.y *= -1;
		}

		if (((ball.x < 0) && (velocity.x < 0)) || ((Scene::Width() < ball.x) && (0 < velocity.x)))
		{
			velocity.x *= -1;
		}

	}
	void draw() {
		ball.draw();
	}
};

/// @brief パドル
class Paddle {
public:
	void update() {}
	void draw() {
		const Rect paddle{ Arg::center(Cursor::Pos().x, 500), 60, 10 };
		paddle.rounded(3).draw();
	}
};

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

		// 描画
		for (auto& brick : bricks) {
			brick.draw();
		}
		ball.draw();
		paddle.draw();

		//// ブロックを順にチェックする | Check bricks in sequence
		//for (auto it = bricks.begin(); it != bricks.end(); ++it)
		//{
		//	// ブロックとボールが交差していたら | If block and ball intersect
		//	if (it->intersects(ball))
		//	{
		//		// ブロックの上辺、または底辺と交差していたら | If ball intersects with top or bottom of the block
		//		if (it->bottom().intersects(ball) || it->top().intersects(ball))
		//		{
		//			// ボールの速度の Y 成分の符号を反転する | Reverse the sign of the Y component of the ball's velocity
		//			ballVelocity.y *= -1;
		//		}
		//		else // ブロックの左辺または右辺と交差していたら
		//		{
		//			// ボールの速度の X 成分の符号を反転する | Reverse the sign of the X component of the ball's velocity
		//			ballVelocity.x *= -1;
		//		}

		//		// ブロックを配列から削除する（イテレータは無効になる） | Remove the block from the array (the iterator becomes invalid)
		//		bricks.erase(it);

		//		// これ以上チェックしない | Do not check any more
		//		break;
		//	}
		//}


		//// パドルにあたったら | If the ball hits the left or right wall
		//if ((0 < ballVelocity.y) && paddle.intersects(ball))
		//{
		//	// パドルの中心からの距離に応じてはね返る方向（速度ベクトル）を変える | Change the direction (velocity vector) of the ball depending on the distance from the center of the paddle
		//	ballVelocity = Vec2{ (ball.x - paddle.center().x) * 10, -ballVelocity.y }.setLength(BallSpeedPerSec);
		//}

		//// マウスカーソルを非表示にする | Hide the mouse cursor
		//Cursor::RequestStyle(CursorStyle::Hidden);
	}
}
