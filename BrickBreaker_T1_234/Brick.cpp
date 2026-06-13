#include "stdafx.h"
#include "Brick.h"
#include "Ball.h"

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
