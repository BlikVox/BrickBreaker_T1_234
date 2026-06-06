# include <Siv3D.hpp>

// 前方宣言
class Ball;

/// @brief ブロック
class Brick {
	inline static const Size Size{ 40, 20 };

	Rect rect;

public:
	Brick(int32 x, int32 y)
		: rect((x* Size.x), (60 + y * Size.y), Size)
	{}

	void update() {}
	void draw() {
		rect.stretched(-1).draw(HSV{ rect.y - 40 });
	}

	bool reflect(Ball& refBall);
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

	Vec2& getVelocity() { return velocity; }
	const Circle& getBall() const { return ball; }
	const double getSpeed() const { return SpeedPerSec; }
};

/// @brief パドル
class Paddle {
	Rect paddle;

public:
	Paddle()
		: paddle(Rect{ Arg::center(Cursor::Pos().x, 500), 60, 10 })
	{}

	void update() {
		paddle.pos.x = Cursor::Pos().x - 30;
		//paddle.setPos(Arg::center(Cursor::Pos().x, 500));
	}
	void draw() {
		paddle.rounded(3).draw();
	}

	bool reflect(Ball& refBall);
};

bool Brick::reflect(Ball& refBall)
{
	auto& ball	= refBall.getBall();
	auto& vec	= refBall.getVelocity();
	if (rect.intersects(ball)) {
		if (rect.bottom().intersects(ball) || rect.top().intersects(ball))
		{
			vec.y *= -1;
		}
		else // ブロックの左辺または右辺と交差していたら
		{
			vec.x *= -1;
		}

		return true;
	}
	return false;
}
bool Paddle::reflect(Ball& refBall)
{
	auto& ball = refBall.getBall();
	auto& vec = refBall.getVelocity();
	if ((0 < vec.y) && paddle.intersects(ball))
	{
		vec = Vec2{ (ball.x - paddle.center().x) * 10, -vec.y }.setLength(refBall.getSpeed());
		return true;
	}
	return false;
}

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
