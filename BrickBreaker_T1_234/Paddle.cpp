#include "stdafx.h"
#include "Paddle.h"
#include "Ball.h"

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
