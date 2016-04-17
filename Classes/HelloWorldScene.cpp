﻿#include "HelloWorldScene.h"
#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"
#include "GameManager.h"
#include "LevelSelect.h"

USING_NS_CC;

using namespace cocostudio::timeline;


Scene* HelloWorld::createScene(string level)
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = HelloWorld::create();
	layer->LoadLevel(level);
    // add layer as a child to scene
    scene->addChild(layer);
    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool HelloWorld::init()
{
    //////////////////////////////
    // 1. super init first
	
    if ( !Layer::init() )
    {
        return false;
    }    
	GameManager::sharedGameManager()->isGameLive = false;

	inputState = 0;
	jetpack = false;

	//call the touch functions when the touch listener detects a touch;
	auto touchListener = EventListenerTouchOneByOne::create();
	touchListener->setSwallowTouches(true);
	touchListener->onTouchBegan = CC_CALLBACK_2(HelloWorld::onTouchBegan, this);
	touchListener->onTouchEnded = CC_CALLBACK_2(HelloWorld::onTouchEnded, this);
	touchListener->onTouchMoved = CC_CALLBACK_2(HelloWorld::onTouchMoved, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(touchListener, this);

	difficulty = Difficulty::MEDIUM;

	this->scheduleUpdate();

    return true;
}

void HelloWorld::update(float dTime)
{
	if (GameManager::sharedGameManager()->isGameLive && !GameManager::sharedGameManager()->isDead)
		{
			if (isTouching)
				onTouching();
			
		//PLAYER GRAVITY
		if (playerIsFalling)
		{
			player->setPositionY(player->getPositionY() - playerFallSpeed);
		}
		else{
			if (playerFallSpeed <= 0)
				player->setPositionY(player->getPositionY() - playerFallSpeed);
		}
		if (playerFallSpeed < 3)
		{
			playerFallSpeed += 0.1;
		}

		//PLAYER JETPACK CONTROL
		if (jetpack){
			if (_ScreenResolution.x / 2 < oldPoint.x){

				playerDirection = Direction::RIGHT;

			}
			else{

				playerDirection = Direction::LEFT;

			}
			if (playerFallSpeed > -5.0f){
				playerFallSpeed += -0.25f;
			}
		}

		checkFloorCollision();
		CheckIfDead(player->getBoundingBox());
		checkSpringCollision(player->getBoundingBox());
		if (checkTerrainCollision(player->getBoundingBox()))
		{
			//playerIsFalling = false;
			//playerFallSpeed = -0.1f;

		}


		//PLAYER DIRECTION CONTROL
		if (playerDirection == Direction::LEFT)
		{
			player->setFlippedX(true);
			player->setPositionX(player->getPositionX() - moveSpeed*2);
		}

		if (playerDirection == Direction::RIGHT)
		{
			player->setFlippedX(false);
			player->setPositionX(player->getPositionX() + moveSpeed);
		}

			lineDrawNode->clear();

			for (int i = 0; i < 500 - 1; i++)
			{
				switch (difficulty)
				{
				case EASY:
					lineDrawNode->drawPoint(LineArray[i], 10, Color4F(0.062f, 0.388f, 0.176f, 1.0f));
					break;
				case MEDIUM:
					lineDrawNode->drawPoint(LineArray[i], 10, Color4F(1.0f, 1.0f, 0.0f, 1.0f));
					break;
				case HARD:
					lineDrawNode->drawPoint(LineArray[i], 10, Color4F(0.694f, 0.835f, 0.878f, 1.0f));
					break;
				}
				
				if (LineArray[i].x > 5 && LineArray[i].y > 5)
				{


					drawLayer[(int)LineArray[i].x - 1][(int)LineArray[i].y] = false;
					drawLayer[(int)LineArray[i].x + 1][(int)LineArray[i].y] = false;
					drawLayer[(int)LineArray[i].x - 1][(int)LineArray[i].y - 1] = false;
					drawLayer[(int)LineArray[i].x + 1][(int)LineArray[i].y - 1] = false;
					drawLayer[(int)LineArray[i].x - 1][(int)LineArray[i].y + 1] = false;
					drawLayer[(int)LineArray[i].x + 1][(int)LineArray[i].y + 1] = false;

					drawLayer[(int)LineArray[i].x - 2][(int)LineArray[i].y] = false;
					drawLayer[(int)LineArray[i].x + 2][(int)LineArray[i].y] = false;
					drawLayer[(int)LineArray[i].x - 2][(int)LineArray[i].y - 1] = false;
					drawLayer[(int)LineArray[i].x + 2][(int)LineArray[i].y - 1] = false;
					drawLayer[(int)LineArray[i].x - 2][(int)LineArray[i].y + 1] = false;
					drawLayer[(int)LineArray[i].x + 2][(int)LineArray[i].y + 1] = false;

					drawLayer[(int)LineArray[i].x][(int)LineArray[i].y] = false;

					drawLayer[(int)LineArray[i].x-1][(int)LineArray[i].y + 2] = false;
					drawLayer[(int)LineArray[i].x+1][(int)LineArray[i].y + 2] = false;
					drawLayer[(int)LineArray[i].x][(int)LineArray[i].y + 2] = false;

					drawLayer[(int)LineArray[i].x-1][(int)LineArray[i].y - 2] = false;
					drawLayer[(int)LineArray[i].x+1][(int)LineArray[i].y - 2] = false;
					drawLayer[(int)LineArray[i].x][(int)LineArray[i].y - 2] = false;

					if (LineArray[i].x - moveSpeed >= 0)
					{
						LineArray[i].x = LineArray[i].x - moveSpeed;
					}


					drawLayer[(int)LineArray[i].x - 1][(int)LineArray[i].y] = true;
					drawLayer[(int)LineArray[i].x + 1][(int)LineArray[i].y] = true;
					drawLayer[(int)LineArray[i].x - 1][(int)LineArray[i].y - 1] = true;
					drawLayer[(int)LineArray[i].x + 1][(int)LineArray[i].y - 1] = true;
					drawLayer[(int)LineArray[i].x - 1][(int)LineArray[i].y + 1] = true;
					drawLayer[(int)LineArray[i].x + 1][(int)LineArray[i].y + 1] = true;

					drawLayer[(int)LineArray[i].x - 2][(int)LineArray[i].y] = true;
					drawLayer[(int)LineArray[i].x + 2][(int)LineArray[i].y] = true;

					drawLayer[(int)LineArray[i].x - 2][(int)LineArray[i].y - 1] = true;
					drawLayer[(int)LineArray[i].x + 2][(int)LineArray[i].y - 1] = true;

					drawLayer[(int)LineArray[i].x - 2][(int)LineArray[i].y + 1] = true;
					drawLayer[(int)LineArray[i].x + 2][(int)LineArray[i].y + 1] = true;
				}
				
			}

			backgroundParallaxMain->setPositionX(backgroundParallaxMain->getPositionX() - moveSpeed * 0.65);
			backgroundParallaxRight->setPositionX(backgroundParallaxRight->getPositionX() - moveSpeed * 0.65);

			if (backgroundParallaxMain->getPositionX() <= -_ScreenResolution.x)
			{
				backgroundParallaxMain->setPositionX(_ScreenResolution.x - (-_ScreenResolution.x - backgroundParallaxMain->getPositionX()));
			}
			if (backgroundParallaxRight->getPositionX() <= -_ScreenResolution.x)
			{
				backgroundParallaxRight->setPositionX(_ScreenResolution.x - (-_ScreenResolution.x - backgroundParallaxMain->getPositionX()));
			}


			for (int i = 0; i < Squares->getChildren().size(); i++)
			{
				Sprite* currentSquare = (Sprite*)Squares->getChildren().at(i);
				currentSquare->setPositionX(currentSquare->getPositionX() - moveSpeed);
			}

			for (int i = 0; i < Windows->getChildren().size(); i++)
			{
				Sprite* currentWindow = (Sprite*)Windows->getChildren().at(i);
				currentWindow->setPositionX(currentWindow->getPositionX() - moveSpeed);
			}

			for (int i = 0; i < Springs->getChildren().size(); i++)
			{
				Sprite* currentSpring = (Sprite*)Springs->getChildren().at(i);
				currentSpring->setPositionX(currentSpring->getPositionX() - moveSpeed);
			}
			for (int i = 0; i < Spikes->getChildren().size(); i++){
				Sprite* currentSpikes = (Sprite*)Spikes->getChildren().at(i);
				currentSpikes->setPositionX(currentSpikes->getPositionX() - moveSpeed);
			}

			EndBlock->setPositionX(EndBlock->getPositionX() - moveSpeed);

			secondCounter += dTime;
		}
}

bool HelloWorld::onTouchBegan(cocos2d::Touch* touch, cocos2d::Event* event)
{
	oldPoint = touch->getLocation();
	isTouching = true;
	switch (inputState)
	{
	case 0:
		return 1;

	case 1:
		jetpack = true;
		return 1;

	default:return false;
	}
}

void HelloWorld::onTouching()
{
	Vec2 newPoint = oldPoint;


	//draw a line in pixels between the new point and the previous point
	int x2 = newPoint.x;
	int x1 = oldPoint.x;
	int y2 = newPoint.y;
	int y1 = oldPoint.y;

	int x, y, dx1, dy1, px, py, xe, ye, i;
	float dx, dy;
	dx = x2 - x1;
	dy = y2 - y1;
	dx1 = fabs(dx);
	dy1 = fabs(dy);
	px = 2 * dy1 - dx1;
	py = 2 * dx1 - dy1;
	if (dy1 <= dx1)
	{
		if (dx >= 0)
		{
			x = x1;
			y = y1;
			xe = x2;
		}
		else
		{
			x = x2;
			y = y2;
			xe = x1;
		}
		drawPoint(x, y);////////////////
		for (i = 0; x < xe; i++)
		{
			x = x + 1;
			if (px < 0)
			{
				px = px + 2 * dy1;
			}
			else
			{
				if ((dx < 0 && dy < 0) || (dx>0 && dy>0))
				{
					y = y + 1;
				}
				else
				{
					y = y - 1;
				}
				px = px + 2 * (dy1 - dx1);
			}
			drawPoint(x, y);////////////////
		}
	}
	else
	{
		if (dy >= 0)
		{
			x = x1;
			y = y1;
			ye = y2;
		}
		else
		{
			x = x2;
			y = y2;
			ye = y1;
		}
		drawPoint(x, y);////////////////
		for (i = 0; y < ye; i++)
		{
			y = y + 1;
			if (py <= 0)
			{
				py = py + 2 * dx1;
			}
			else
			{
				if ((dx < 0 && dy < 0) || (dx>0 && dy>0))
				{
					x = x + 1;
				}
				else
				{
					x = x - 1;
				}
				py = py + 2 * (dx1 - dy1);
			}
			drawPoint(x, y);////////////////
		}
	}
}

void HelloWorld::onTouchMoved(cocos2d::Touch* touch, cocos2d::Event* event)
{
	switch (inputState)
	{

	case 0:
		updateline(touch, event);
		break;
	case 1:
		updateJetpackDirection(touch);
		break;
	default:break;

	}
}

void HelloWorld::onTouchEnded(cocos2d::Touch* touch, cocos2d::Event* event)
{
	isTouching = false;
	switch (inputState){

	case 0:
		break;
	case 1:
		jetpack = false;
		break;
	default:
		break;
	}
}

void HelloWorld::updateJetpackDirection(cocos2d::Touch* touch){

	oldPoint = touch->getLocation();

}

void HelloWorld::updateline(cocos2d::Touch* touch, cocos2d::Event* event){

	Vec2 newPoint = touch->getLocation();

	//draw a line in pixels between the new point and the previous point
	int x2 = newPoint.x;
	int x1 = oldPoint.x;
	int y2 = newPoint.y;
	int y1 = oldPoint.y;

	int x, y, dx1, dy1, px, py, xe, ye, i;
	float dx, dy;
	dx = x2 - x1;
	dy = y2 - y1;
	dx1 = fabs(dx);
	dy1 = fabs(dy);
	px = 2 * dy1 - dx1;
	py = 2 * dx1 - dy1;
	if (dy1 <= dx1)
	{
		if (dx >= 0)
		{
			x = x1;
			y = y1;
			xe = x2;
		}
		else
		{
			x = x2;
			y = y2;
			xe = x1;
		}
		drawPoint(x, y);////////////////
		for (i = 0; x < xe; i++)
		{
			x = x + 1;
			if (px < 0)
			{
				px = px + 2 * dy1;
			}
			else
			{
				if ((dx < 0 && dy < 0) || (dx>0 && dy>0))
				{
					y = y + 1;
				}
				else
				{
					y = y - 1;
				}
				px = px + 2 * (dy1 - dx1);
			}
			drawPoint(x, y);////////////////
		}
	}
	else
	{
		if (dy >= 0)
		{
			x = x1;
			y = y1;
			ye = y2;
		}
		else
		{
			x = x2;
			y = y2;
			ye = y1;
		}
		drawPoint(x, y);////////////////
		for (i = 0; y < ye; i++)
		{
			y = y + 1;
			if (py <= 0)
			{
				py = py + 2 * dx1;
			}
			else
			{
				if ((dx < 0 && dy < 0) || (dx>0 && dy>0))
				{
					x = x + 1;
				}
				else
				{
					x = x - 1;
				}
				py = py + 2 * (dx1 - dy1);
			}
			drawPoint(x, y);////////////////
		}
	}
	oldPoint = touch->getLocation();
}

bool HelloWorld::checkPlayerCollision()
{
	if (drawLayer[(int)player->getBoundingBox().getMinX()][(int)player->getBoundingBox().getMinY()] == true)
	{
		return true;
	}
	return false;
}

void HelloWorld::drawPoint(int x, int y)
{
	if (GameManager::sharedGameManager()->isGameLive && !GameManager::sharedGameManager()->isDead)
	{
		Vec2 drawPoint = Vec2(x, y);
		if (drawPoint.x > 0 + lineSize && drawPoint.y > 0 + lineSize && drawPoint.x < _ScreenResolution.x - lineSize && drawPoint.y < _ScreenResolution.y - lineSize)
		{
			if (drawLayer[(int)drawPoint.x][(int)drawPoint.y] == false)
			{
				if (lineArrayCount < 500)
				{
					drawLayer[(int)drawPoint.x][(int)drawPoint.y] = true;

					if (LineArray[lineArrayCount].x > 0 && LineArray[lineArrayCount].y > 0)
					{
						drawLayer[(int)LineArray[lineArrayCount].x][(int)LineArray[lineArrayCount].y] = false;
						drawLayer[(int)LineArray[lineArrayCount].x - 1][(int)LineArray[lineArrayCount].y] = false;
						drawLayer[(int)LineArray[lineArrayCount].x + 1][(int)LineArray[lineArrayCount].y] = false;
						drawLayer[(int)LineArray[lineArrayCount].x][(int)LineArray[lineArrayCount].y + 1] = false;
						drawLayer[(int)LineArray[lineArrayCount].x][(int)LineArray[lineArrayCount].y - 1] = false;
						drawLayer[(int)LineArray[lineArrayCount].x - 1][(int)LineArray[lineArrayCount].y - 1] = false;
						drawLayer[(int)LineArray[lineArrayCount].x + 1][(int)LineArray[lineArrayCount].y - 1] = false;
						drawLayer[(int)LineArray[lineArrayCount].x - 1][(int)LineArray[lineArrayCount].y + 1] = false;
						drawLayer[(int)LineArray[lineArrayCount].x + 1][(int)LineArray[lineArrayCount].y + 1] = false;


						drawLayer[(int)LineArray[lineArrayCount].x - 1][(int)LineArray[lineArrayCount].y] = false;
						drawLayer[(int)LineArray[lineArrayCount].x + 1][(int)LineArray[lineArrayCount].y] = false;
						drawLayer[(int)LineArray[lineArrayCount].x - 1][(int)LineArray[lineArrayCount].y - 1] = false;
						drawLayer[(int)LineArray[lineArrayCount].x + 1][(int)LineArray[lineArrayCount].y - 1] = false;
						drawLayer[(int)LineArray[lineArrayCount].x - 1][(int)LineArray[lineArrayCount].y + 1] = false;
						drawLayer[(int)LineArray[lineArrayCount].x + 1][(int)LineArray[lineArrayCount].y + 1] = false;

						drawLayer[(int)LineArray[lineArrayCount].x - 2][(int)LineArray[lineArrayCount].y] = false;
						drawLayer[(int)LineArray[lineArrayCount].x + 2][(int)LineArray[lineArrayCount].y] = false;
						drawLayer[(int)LineArray[lineArrayCount].x - 2][(int)LineArray[lineArrayCount].y - 1] = false;
						drawLayer[(int)LineArray[lineArrayCount].x + 2][(int)LineArray[lineArrayCount].y - 1] = false;
						drawLayer[(int)LineArray[lineArrayCount].x - 2][(int)LineArray[lineArrayCount].y + 1] = false;
						drawLayer[(int)LineArray[lineArrayCount].x + 2][(int)LineArray[lineArrayCount].y + 1] = false;

						drawLayer[(int)LineArray[lineArrayCount].x][(int)LineArray[lineArrayCount].y] = false;

						drawLayer[(int)LineArray[lineArrayCount].x - 1][(int)LineArray[lineArrayCount].y + 2] = false;
						drawLayer[(int)LineArray[lineArrayCount].x + 1][(int)LineArray[lineArrayCount].y + 2] = false;
						drawLayer[(int)LineArray[lineArrayCount].x][(int)LineArray[lineArrayCount].y + 2] = false;

						drawLayer[(int)LineArray[lineArrayCount].x - 1][(int)LineArray[lineArrayCount].y - 2] = false;
						drawLayer[(int)LineArray[lineArrayCount].x + 1][(int)LineArray[lineArrayCount].y - 2] = false;
						drawLayer[(int)LineArray[lineArrayCount].x][(int)LineArray[lineArrayCount].y - 2] = false;
					}

					LineArray[lineArrayCount] = Vec2((int)drawPoint.x, (int)drawPoint.y);
					lineArrayCount++;
				}
				else
				{
					lineArrayCount = 0;
				}

				drawLayer[(int)drawPoint.x][(int)drawPoint.y] = true;
			}
		}
	}
}

void HelloWorld::PausePressed(Ref *pSender, cocos2d::ui::Widget::TouchEventType type)
{
	if (type == cocos2d::ui::Widget::TouchEventType::ENDED)
	{
		GameManager::sharedGameManager()->isGameLive = !GameManager::sharedGameManager()->isGameLive;

		auto winSize = Director::getInstance()->getVisibleSize();
		auto moveSelectTo = MoveTo::create(0.3, Vec2(winSize.width*0.5f, winSize.height * 0.65f / 1.0));
		auto moveNextTo = MoveTo::create(0.3, Vec2(winSize.width*0.5f, winSize.height * 0.40f / 1.0));
		auto moveBackgroundTo = MoveTo::create(0.3, Vec2(winSize.width*0.5f, winSize.height * 0.5f / 1.0));

		if (!menuDown)
		{
			pauseButton->setBright(false);
			OBackToSelectButton->runAction(moveSelectTo);
			ONextLevelButton->runAction(moveNextTo);		
			overlayBackground->runAction(moveBackgroundTo);		
			menuDown = true;
		}
		else
		{
			pauseButton->setBright(true);
			OBackToSelectButton->stopAllActions();
			ONextLevelButton->stopAllActions();
			overlayBackground->stopAllActions();
			ONextLevelButton->setPosition(ONextLevelButtonStartPos);
			OBackToSelectButton->setPosition(OBackToSelectButtonStartPos);
			overlayBackground->setPosition(overlayBackgroundStartPos);
			menuDown = false;
		}
	}
}

void HelloWorld::RestartPressed(Ref *pSender, cocos2d::ui::Widget::TouchEventType type, string level)
{
	if (type == cocos2d::ui::Widget::TouchEventType::ENDED)
	{
		Scene* scene = HelloWorld::createScene(level);

		Director::getInstance()->replaceScene(TransitionMoveInR::create(0.5, scene));
	}
}

//void HelloWorld::NextLevelPressed(Ref *pSender, cocos2d::ui::Widget::TouchEventType type, string level)
//{
//	if (type == cocos2d::ui::Widget::TouchEventType::ENDED)
//	{
//		Scene* scene = HelloWorld::createScene(level);
//
//		Director::getInstance()->replaceScene(TransitionMoveInR::create(0.5, scene));
//	}
//}

void HelloWorld::BackToSelectPressed(Ref *pSender, cocos2d::ui::Widget::TouchEventType type)
{
	if (type == cocos2d::ui::Widget::TouchEventType::ENDED)
	{
		Scene* scene = LevelSelect::createScene();

		Director::getInstance()->replaceScene(TransitionSlideInL::create(0.3, scene));
	}
}

void HelloWorld::checkSpringCollision(Rect collisionBox)
{
	for (int i = 0; i < Springs->getChildren().size(); i++)
	{
		Rect currentSpring = (Rect)Springs->getChildren().at(i)->getBoundingBox();

		if (currentSpring.intersectsRect(player->getBoundingBox()))
		{
			playerFallSpeed *= -0.6f;
			playerFallSpeed -= 10;
		}
	}

	//Rect mSpring_0 = spring_0->getBoundingBox();

	/*if (mSpring_0.intersectsRect(player->getBoundingBox())){
		playerFallSpeed *= -0.6f;
		playerFallSpeed += -6;
	}*/
}

bool HelloWorld::checkTerrainCollision(Rect collisionBox)//this will only work with the player at the moment
{
	for (int i = 0; i < Squares->getChildren().size(); i++)
	{
		Rect currentSquare = (Rect)Squares->getChildren().at(i)->getBoundingBox();
		Rect playerBox = Rect(Vec2(player->getPositionX()-10, player->getPositionY()), Size(player->getBoundingBox().size.width + 5, player->getBoundingBox().size.height/2));

		if (currentSquare.intersectsRect(collisionBox))//comparing the modified collision box
		{
			if (playerBox.intersectsRect(currentSquare))
			{
				if (playerDirection == Direction::LEFT)
				{
					playerDirection = Direction::RIGHT;
					player->setPositionX(player->getPositionX() + moveSpeed);
				}
				else if (playerDirection == Direction::RIGHT)
				{
					playerDirection = Direction::LEFT;
					player->setPositionX(player->getPositionX() - moveSpeed);
				}
				//if (playerBox.getMaxX() > currentSquare.getMinX() && playerBox.getMaxX() + moveSpeed < currentSquare.getMinX())
				//{
				//	playerDirection = Direction::LEFT;
				//	player->setPositionX(player->getPositionX() - moveSpeed);
				//}
				//else if (playerBox.getMinX() < currentSquare.getMaxX() && playerBox.getMinX() - moveSpeed > currentSquare.getMaxX())
				//{
				//	playerDirection = Direction::RIGHT;
				//	player->setPositionX(player->getPositionX() + moveSpeed);
				//}
				return true;
			}
		}

		if (collisionBox.intersectsRect(currentSquare))//comparing the full collision box
		{
			if (collisionBox.getMinY() < currentSquare.getMaxY() && collisionBox.getMinY() > (currentSquare.getMaxY() - 5))//if the bottom of the player is not as high as the collision box, but is close, set it to be the same height.
			{
				player->setPositionY(player->getPositionY() + 1);
				playerIsFalling = false;
				playerFallSpeed = -0.1f;
			}
		}
	}
	return false;
}

bool HelloWorld::checkEndBlockCollision(Rect collisionBox)
{
	Rect mEndBlock = EndBlock->getBoundingBox();
	if (mEndBlock.intersectsRect(collisionBox))
	{
		if (player->getBoundingBox().getMaxX() > mEndBlock.getMinX() && player->getBoundingBox().getMaxX() - 5 < mEndBlock.getMinX())
		{
			PlayerDead();
		}
		return true;
	}
	return false;
}

void HelloWorld::checkFloorCollision()
{
	for (int i = 0; i < player->getBoundingBox().size.width; i++)
	{
		if (drawLayer[(int)player->getBoundingBox().getMinX() + i][(int)player->getBoundingBox().getMinY() - 1] == true || drawLayer[(int)player->getBoundingBox().getMinX() + i][(int)player->getBoundingBox().getMinY() - 2] == true)
		{
			playerIsFalling = false;
			playerFallSpeed = 0.4;
		}
		else
		{
			playerIsFalling = true;
		}
	}


	if (playerDirection == Direction::RIGHT)
	{
		for (int i = 0; i < player->getBoundingBox().size.height / 2; i++)
		{
			for (int ii = 0; ii < 10; ii++)
			{
				if (drawLayer[(int)player->getBoundingBox().getMaxX() + 1 + ii][(int)player->getBoundingBox().getMaxY() - i] == true)
				{
					playerDirection = Direction::LEFT;
				}
			}
				
		}
	}
	else if (playerDirection == Direction::LEFT)
	{
		for (int i = 0; i < player->getBoundingBox().size.height / 2; i++)
		{
			for (int ii = 0; ii < 10; ii++)
			{
				if (drawLayer[(int)player->getBoundingBox().getMinX() - 1 - ii][(int)player->getBoundingBox().getMaxY() - i] == true)
				{
					playerDirection = Direction::RIGHT;
				}
			}

		}
	}


	if (playerDirection == Direction::RIGHT)
	{
		for (int i = 0; i < player->getBoundingBox().size.height / 2; i++)
		{
			if (drawLayer[(int)player->getBoundingBox().getMaxX() + 1][(int)player->getBoundingBox().getMinY() + i] == true)
			{
				player->setPositionY(player->getPositionY() + 1);
			}
			if (drawLayer[(int)player->getBoundingBox().getMaxX() + 2][(int)player->getBoundingBox().getMinY() + i] == true)
			{
				player->setPositionY(player->getPositionY() + 1);
			}
		}
	}

	if (playerDirection == Direction::LEFT)
	{
		for (int i = 0; i < player->getBoundingBox().size.height / 2; i++)
		{
			if (drawLayer[(int)player->getBoundingBox().getMinX() - 1][(int)player->getBoundingBox().getMinY() + i] == true)
			{
				player->setPositionY(player->getPositionY() + 1);
			}
			if (drawLayer[(int)player->getBoundingBox().getMinX() - 2][(int)player->getBoundingBox().getMinY() + i] == true)
			{
				player->setPositionY(player->getPositionY() + 1);
			}
		}
	}
}

void HelloWorld::CheckIfDead(Rect collisionBox)
{
	//checks if player hits the edge of the screen
	if (player->getPosition().y < 0 || (player->getBoundingBox().getMaxX() + 13) > _ScreenResolution.x || (player->getBoundingBox().getMinX() - 13) < 0)
	{
		PlayerDead();
	}

	//checks if players hits spikes
	for (int i = 0; i < Spikes->getChildren().size(); i++)
	{
		Rect currentSpike = (Rect)Spikes->getChildren().at(i)->getBoundingBox();

		if (currentSpike.intersectsRect(collisionBox))
		{
			PlayerDead();
		}
	}

	/*Rect mSpikes_0 = spikes_0->getBoundingBox();

	if (mSpikes_0.intersectsRect(collisionBox)){
		PlayerDead();
	}*/

}

void HelloWorld::PlayerDead(){

	GameManager::sharedGameManager()->isDead = true;

	//auto winSize = Director::getInstance()->getVisibleSize();
	//auto moveButtonTo = MoveTo::create(0.5, Vec2(winSize.width*0.5f, winSize.height / 0.5f * 0.25));
	//auto moveBackgroundTo = MoveTo::create(0.5, Vec2(winSize.width*0.5f, winSize.height / 0.5f * 0.25));
	//restartMenuButton->runAction(moveButtonTo);
	//restartBackground->runAction(moveBackgroundTo);

	for (int i = 0; i < _ScreenResolution.x - 1; i++)
	{
		for (int ii = 0; ii < _ScreenResolution.y - 1; ii++)
		{
			drawLayer[i][ii] = false;//set each value int the array to false
		}
	}
}

void HelloWorld::LoadLevel(string level)
{
	GameManager::sharedGameManager()->isGameLive = true;
	auto rootNode = CSLoader::createNode(level);
	
	//auto currentScene = Director::getInstance()->getRunningScene();
    //this->getBoundingBox();
    _ScreenResolution = Vec2(1920, 1080); //rootNode->getBoundingBox().getMaxX(), rootNode->getBoundingBox().getMaxY());//get the resolution of the screen.

	player = (Sprite*)rootNode->getChildByName("Player");
	playerStartPos = Vec2(player->getPosition().x, player->getPosition().y);
	backgroundParallaxMain = (Sprite*)rootNode->getChildByName("BackgroundParallaxMain");
	backgroundParallaxRight = (Sprite*)rootNode->getChildByName("BackgroundParallaxRight");

	Squares = (Node*)rootNode->getChildByName("Squares");
	Windows = (Node*)rootNode->getChildByName("Windows");
	Springs = (Node*)rootNode->getChildByName("Springs");
	Spikes = (Node*)rootNode->getChildByName("Spikes");
	
	EndBlock = (Sprite*)rootNode->getChildByName("EndBlock");

	pauseButton = (ui::Button*)rootNode->getChildByName("pause");	
	pauseButton->addTouchEventListener(CC_CALLBACK_2(HelloWorld::PausePressed, this));
	
	restartButton = (ui::Button*)rootNode->getChildByName("restart");
	restartButton->addTouchEventListener(CC_CALLBACK_2(HelloWorld::RestartPressed, this, level));

	//////Overlay/////
	OBackToSelectButton = (ui::Button*)rootNode->getChildByName("backToLevelSelect");
	OBackToSelectButton->addTouchEventListener(CC_CALLBACK_2(HelloWorld::BackToSelectPressed, this));
	OBackToSelectButtonStartPos = Vec2(OBackToSelectButton->getPosition().x, OBackToSelectButton->getPosition().y);;

	ONextLevelButton = (ui::Button*)rootNode->getChildByName("nextLevel");
	//ONextLevelButton->addTouchEventListener(CC_CALLBACK_2(HelloWorld::NextLevelPressed, this));
	ONextLevelButtonStartPos = Vec2(ONextLevelButton->getPosition().x, ONextLevelButton->getPosition().y);

	overlayBackground = (Sprite*)rootNode->getChildByName("overlayBackground");
	overlayBackgroundStartPos = Vec2(overlayBackground->getPosition().x, overlayBackground->getPosition().y);
	///////////////////////////////////////////////////////////

	isTouching = false;//set the touching to not be happening

	drawLayer = new bool*[(int)_ScreenResolution.x];//init the width of the array
	for (int i = 0; i < _ScreenResolution.x - 1; i++)
	{
		drawLayer[i] = new bool[(int)_ScreenResolution.y];//init the height of the array
	}

	lineSize = 10;
	moveSpeed = 2;

	for (int i = 0; i < _ScreenResolution.x - 1; i++)
	{
		for (int ii = 0; ii < _ScreenResolution .y - 1; ii++)
		{
			drawLayer[i][ii] = false;//set each value int the array to false
		}
	}

	for (int i = 0; i < 500; i++)
	{
		LineArray[i] = Vec2(0, 0);
	}

	lineArrayCount = 0;
	playerDirection = Direction::RIGHT;
	playerIsFalling = true;
	secondCounter = 0;
	lineDrawNode = DrawNode::create();

	addChild(rootNode);
	addChild(lineDrawNode);
	addChild(player);

	//this will change the level's content to move at different speeds depending on the difficulty
	switch (difficulty)
	{
	case EASY:
		moveSpeed = 1.0f;
		break;
	case MEDIUM:
		moveSpeed = 2.0f;
		break;
	case HARD:
		moveSpeed = 3.0f;
		break;
	}
}
