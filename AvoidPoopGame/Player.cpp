#include "Player.h"
#include "TimeManager.h"
#include "InputManager.h"
#include "Gun.h"
#include "Stage.h"
#include "Bullet.h"
#include "Core.h"

Player::Player()
	: Player(FPOINT{}, 60, 200.f)
{
}

Player::Player(FPOINT pos, int size, float speed)
	: Obj(pos, size)
	, mSpeed(speed)
	, mGun(new Gun(FPOINT{ mPos.mX + (mSize / 3), mPos.mY - mSize }, LENGTH{ mSize / 3, (int)mPos.mY }))
{
}

Player::~Player()
{
	delete mGun;
	mGun = nullptr;
}

void Player::init()
{
}

void Player::update()
{
	// 키 입력 이동 처리
	if (ISPRESS(KEY_LIST::LEFT))
	{
		if ((int)mPos.mX > 0) 
		{
			mPos.mX -= mSpeed * DS;
		}
		else 
		{
			mPos.mX = 0.f;
		}
	}

	if (ISPRESS(KEY_LIST::TOP))
	{
		if (!mGun->isTop()) 
		{
			mPos.mY -= mSpeed * DS;
		}
		else 
		{
			mPos.mY = 0.f + mGun->getLength().mVertical;
		}
	}

	if (ISPRESS(KEY_LIST::RIGHT))
	{
		if ((int)mPos.mX + mSize < WINDOW.right)
		{
			mPos.mX += mSpeed * DS;
		}
		else 
		{
			mPos.mX = (float)WINDOW.right - (float)mSize;
		}
	}

	if (ISPRESS(KEY_LIST::BOTTOM))
	{
		if ((int)mPos.mY + mSize < WINDOW.bottom) 
		{
			mPos.mY += mSpeed * DS;
		}
		else 
		{
			mPos.mY = (float)WINDOW.bottom - (float)mSize;
		}
	}

	if (ISTIC(KEY_LIST::SPACE))
	{
		mGun->createBullet();
	}

	mGun->update(FPOINT{ mPos.mX + (mSize / 3), mPos.mY - mSize }, LENGTH{ mSize / 3, (int)mPos.mY });
}

void Player::render(HDC backDC)
{
	Rectangle(backDC, (int)mPos.mX, (int)mPos.mY, (int)mPos.mX + mSize, (int)mPos.mY + mSize);
	mGun->render(backDC);
}
