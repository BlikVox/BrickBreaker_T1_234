#pragma once

class Ball;
class Paddle;
class Brick;

class GameMain
{
	Array<Brick> bricks;
	Ball* ball;
	Paddle* paddle;

public:
	GameMain();
	~GameMain();

	void update();
	void draw();
};

