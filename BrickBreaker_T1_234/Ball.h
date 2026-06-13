#pragma once
class Ball
{
	const double SpeedPerSec = 480.0;

	Vec2 velocity{ 0, -SpeedPerSec };
	Circle ball;

public:
	Ball()
		: ball(Circle{ 400, 400, 8 })
	{
	}

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

