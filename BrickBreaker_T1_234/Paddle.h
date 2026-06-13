#pragma once

class Ball;

class Paddle
{
	Rect paddle;

public:
	Paddle()
		: paddle(Rect{ Arg::center(Cursor::Pos().x, 500), 60, 10 })
	{
	}

	void update() {
		paddle.pos.x = Cursor::Pos().x - 30;
		//paddle.setPos(Arg::center(Cursor::Pos().x, 500));
	}
	void draw() {
		paddle.rounded(3).draw();
	}

	bool reflect(Ball& refBall);
};

