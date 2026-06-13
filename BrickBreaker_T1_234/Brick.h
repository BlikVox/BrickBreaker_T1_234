#pragma once

class Ball;

class Brick
{
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

