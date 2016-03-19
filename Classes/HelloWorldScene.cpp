#include "HelloWorldScene.h"
#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"
#include "GameManager.h"

USING_NS_CC;

using namespace cocostudio::timeline;

Scene* HelloWorld::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = HelloWorld::create();

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

	LoadStartMenu();

	//call the touch functions when the touch listener detects a touch;
	auto touchListener = EventListenerTouchOneByOne::create();
	touchListener->setSwallowTouches(true);
	touchListener->onTouchBegan = CC_CALLBACK_2(HelloWorld::onTouchBegan, this);
	touchListener->onTouchEnded = CC_CALLBACK_2(HelloWorld::onTouchEnded, this);
	touchListener->onTouchMoved = CC_CALLBACK_2(HelloWorld::onTouchMoved, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(touchListener, this);

	this->scheduleUpdate();

    return true;
}

void HelloWorld::update(float dTime)
{
	if (GameManager::sharedGameManager()->isGameLive && !GameManager::sharedGameManager()->isDead)
		{
			
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
			if (ScreenResolution.x / 2 < oldPoint.x){

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
			playerIsFalling = false;
			playerFallSpeed = -0.1f;

		}


		//PLAYER DIRECTION CONTROL
		if (playerDirection == Direction::LEFT)
		{
			player->setFlippedX(true);
			player->setPositionX(player->getPositionX() - moveSpeed - 1);
		}

		if (playerDirection == Direction::RIGHT)
		{
			player->setFlippedX(false);
			player->setPositionX(player->getPositionX() + moveSpeed);
		}

			lineDrawNode->clear();

			for (int i = 0; i < 500 - 1; i++)
			{
				lineDrawNode->drawPoint(LineArray[i], 10, Color4F(1.0f, 1.0f, 0.0f, 1.0f));
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

					
					LineArray[i].x = LineArray[i].x - 1;


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

			backgroundParallaxMain->setPositionX(backgroundParallaxMain->getPositionX() - moveSpeed / 2);
			backgroundParallaxRight->setPositionX(backgroundParallaxRight->getPositionX() - moveSpeed / 2);

			if (backgroundParallaxMain->getPositionX() <= -1920)
			{
				backgroundParallaxMain->setPositionX(1920 - (-1920 - backgroundParallaxMain->getPositionX()));
			}
			if (backgroundParallaxRight->getPositionX() <= -1920)
			{
				backgroundParallaxRight->setPositionX(1920 - (-1920 - backgroundParallaxMain->getPositionX()));
			}

			float moveSpeed = 1.0f;


			/*Squares->setPositionX(Squares->getPositionX() - squareSpeed);
			Windows->setPositionX(Windows->getPositionX() - squareSpeed);
			Springs->setPositionX(Springs->getPositionX() - squareSpeed);
			Spikes->setPositionX(Spikes->getPositionX() - squareSpeed);*/


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
		if (drawPoint.x > 0 + lineSize && drawPoint.y > 0 + lineSize && drawPoint.x < ScreenResolution.x - lineSize && drawPoint.y < ScreenResolution.y - lineSize)
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

void HelloWorld::StartPressed(Ref *pSender, cocos2d::ui::Widget::TouchEventType type)
{
	if (type == cocos2d::ui::Widget::TouchEventType::ENDED)
	{
		//auto winSize = Director::getInstance()->getVisibleSize();	

		LoadLevelSelect();
	}
}

void HelloWorld::PausePressed(Ref *pSender, cocos2d::ui::Widget::TouchEventType type)
{
	bool GameMenu = false;
	if (type == cocos2d::ui::Widget::TouchEventType::ENDED)
	{
		GameManager::sharedGameManager()->isGameLive = !GameManager::sharedGameManager()->isGameLive;
		LoadGameMenu();
	}
}

void HelloWorld::RestartPressed(Ref *pSender, cocos2d::ui::Widget::TouchEventType type)
{
	if (type == cocos2d::ui::Widget::TouchEventType::ENDED)
	{
		//auto scene = Scene::create();
		//Director::getInstance()->replaceScene(scene);
		//Director::getInstance()->restart();
		//player->setPosition(Vec2(playerStartPos));
		GameManager::sharedGameManager()->isDead = false;
		//playerDirection = Direction::RIGHT;
		//playerFallSpeed = 0.0;

		auto currentScene = Director::getInstance()->getRunningScene();
		Director::getInstance()->replaceScene(currentScene);

		auto winSize = Director::getInstance()->getVisibleSize();
		auto moveButtonTo = MoveTo::create(0.5, Vec2(winSize.width*0.5f, winSize.height * 0.5f / 0.25));
		auto moveBackgroundTo = MoveTo::create(0.5, Vec2(winSize.width*0.5f, winSize.height * 0.5f / 0.25));
	}
}

void HelloWorld::LevelPressed(Ref *pSender, cocos2d::ui::Widget::TouchEventType type, int levelID){

	if (type == cocos2d::ui::Widget::TouchEventType::ENDED)
	{
		auto winSize = Director::getInstance()->getVisibleSize();

		switch (levelID)
		{
		case 0: LoadLevel1(); break;
		case 1: LoadLevel2(); break;
		case 2: LoadLevel3(); break;
		case 3: LoadLevel4(); break;
		case 4: LoadLevel5(); break;
		case 5: LoadLevel6(); break;
		default: break;
		}
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
			playerFallSpeed += -6;
		}
	}

	//Rect mSpring_0 = spring_0->getBoundingBox();

	/*if (mSpring_0.intersectsRect(player->getBoundingBox())){
		playerFallSpeed *= -0.6f;
		playerFallSpeed += -6;
	}*/
}

bool HelloWorld::checkTerrainCollision(Rect collisionBox)
{
	for (int i = 0; i < Squares->getChildren().size(); i++)
	{
		Rect currentSquare = (Rect)Squares->getChildren().at(i)->getBoundingBox();

		if (currentSquare.intersectsRect(collisionBox))
		{
			if (player->getBoundingBox().getMaxX() > currentSquare.getMinX() && player->getBoundingBox().getMaxX() - 5 < currentSquare.getMinX())
			{
				playerDirection = Direction::LEFT;
				player->setPositionX(player->getPositionX() - 5);
			}
			else if (player->getBoundingBox().getMinX() < currentSquare.getMaxX() && player->getBoundingBox().getMinX() + 5 > currentSquare.getMaxX())
			{
				playerDirection = Direction::RIGHT;
				player->setPositionX(player->getPositionX() + 5);
			}
			return true;
		}
	}
	return false;

	/*Rect mSquare_5 = square_5->getBoundingBox();
	Rect mSquare_6 = square_6->getBoundingBox();
	Rect mSquare_7 = square_7->getBoundingBox();
	Rect mSquare_8 = square_8->getBoundingBox();
	Rect mSquare_9 = square_9->getBoundingBox();
	Rect mSquare_10 = square_10->getBoundingBox();
	Rect mSquare_11 = square_11->getBoundingBox();
	Rect mSquare_12 = square_12->getBoundingBox();
	Rect mSquare_13 = square_13->getBoundingBox();
	Rect mSquare_14 = square_14->getBoundingBox();
	Rect mSquare_15 = square_15->getBoundingBox();


	if (mSquare_5.intersectsRect(collisionBox) || mSquare_6.intersectsRect(collisionBox) || mSquare_7.intersectsRect(collisionBox) || mSquare_8.intersectsRect(collisionBox) || mSquare_9.intersectsRect(collisionBox) || mSquare_10.intersectsRect(collisionBox) || mSquare_11.intersectsRect(collisionBox) || mSquare_12.intersectsRect(collisionBox) || mSquare_13.intersectsRect(collisionBox) || mSquare_14.intersectsRect(collisionBox) || mSquare_15.intersectsRect(collisionBox))
	{
		if (player->getBoundingBox().getMaxX() > mSquare_5.getMinX() && player->getBoundingBox().getMaxX() - 5 < mSquare_5.getMinX()
			|| player->getBoundingBox().getMaxX() > mSquare_6.getMinX() && player->getBoundingBox().getMaxX() - 5 < mSquare_6.getMinX()
			|| player->getBoundingBox().getMaxX() > mSquare_7.getMinX() && player->getBoundingBox().getMaxX() - 5 < mSquare_7.getMinX()
			|| player->getBoundingBox().getMaxX() > mSquare_8.getMinX() && player->getBoundingBox().getMaxX() - 5 < mSquare_8.getMinX()
			|| player->getBoundingBox().getMaxX() > mSquare_9.getMinX() && player->getBoundingBox().getMaxX() - 5 < mSquare_9.getMinX()
			|| player->getBoundingBox().getMaxX() > mSquare_10.getMinX() && player->getBoundingBox().getMaxX() - 5 < mSquare_10.getMinX()
			|| player->getBoundingBox().getMaxX() > mSquare_11.getMinX() && player->getBoundingBox().getMaxX() - 5 < mSquare_11.getMinX()
			|| player->getBoundingBox().getMaxX() > mSquare_12.getMinX() && player->getBoundingBox().getMaxX() - 5 < mSquare_12.getMinX()
			|| player->getBoundingBox().getMaxX() > mSquare_13.getMinX() && player->getBoundingBox().getMaxX() - 5 < mSquare_13.getMinX()
			|| player->getBoundingBox().getMaxX() > mSquare_14.getMinX() && player->getBoundingBox().getMaxX() - 5 < mSquare_14.getMinX()
			|| player->getBoundingBox().getMaxX() > mSquare_15.getMinX() && player->getBoundingBox().getMaxX() - 5 < mSquare_15.getMinX())
		{
				playerDirection = Direction::LEFT;
				player->setPositionX(player->getPositionX() - 5);
		}
		else if (player->getBoundingBox().getMinX() < mSquare_5.getMaxX() && player->getBoundingBox().getMinX() + 5 > mSquare_5.getMaxX()
			|| player->getBoundingBox().getMinX() < mSquare_6.getMaxX() && player->getBoundingBox().getMinX() + 5 > mSquare_6.getMaxX()
			|| player->getBoundingBox().getMinX() < mSquare_7.getMaxX() && player->getBoundingBox().getMinX() + 5 > mSquare_7.getMaxX()
			|| player->getBoundingBox().getMinX() < mSquare_8.getMaxX() && player->getBoundingBox().getMinX() + 5 > mSquare_8.getMaxX()
			|| player->getBoundingBox().getMinX() < mSquare_9.getMaxX() && player->getBoundingBox().getMinX() + 5 > mSquare_9.getMaxX()
			|| player->getBoundingBox().getMinX() < mSquare_10.getMaxX() && player->getBoundingBox().getMinX() + 5 > mSquare_10.getMaxX()
			|| player->getBoundingBox().getMinX() < mSquare_11.getMaxX() && player->getBoundingBox().getMinX() + 5 > mSquare_11.getMaxX()
			|| player->getBoundingBox().getMinX() < mSquare_12.getMaxX() && player->getBoundingBox().getMinX() + 5 > mSquare_12.getMaxX()
			|| player->getBoundingBox().getMinX() < mSquare_13.getMaxX() && player->getBoundingBox().getMinX() + 5 > mSquare_13.getMaxX()
			|| player->getBoundingBox().getMinX() < mSquare_14.getMaxX() && player->getBoundingBox().getMinX() + 5 > mSquare_14.getMaxX()
			|| player->getBoundingBox().getMinX() < mSquare_15.getMaxX() && player->getBoundingBox().getMinX() + 5 > mSquare_15.getMaxX())
		{
			playerDirection = Direction::RIGHT;
			player->setPositionX(player->getPositionX() + 5);
		}
		return true;
	}
	return false;*/
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

		//if (playerDirection == Direction::RIGHT)
		//{
		//	if (drawLayer[(int)player->getBoundingBox().getMaxX() + 1][(int)player->getBoundingBox().getMinY()] == true)
		//	{
		//		if (drawLayer[(int)player->getBoundingBox().getMaxX() + 1][(int)player->getBoundingBox().getMinY() + 1] == true)
		//		{
		//			player->setPositionY(player->getPositionY() + 3);

		//			if (drawLayer[(int)player->getBoundingBox().getMaxX() + 1][(int)player->getBoundingBox().getMinY() + 1] == true)
		//			{
		//				player->setPositionY(player->getPositionY() + 3);
		//			}
		//		}
		//		player->setPositionY(player->getPositionY() + 3);
		//	}
		//}

		//if (playerDirection == Direction::LEFT)
		//{
		//	if (drawLayer[(int)player->getBoundingBox().getMinX() - 1][(int)player->getBoundingBox().getMinY()] == true)
		//	{
		//		if (drawLayer[(int)player->getBoundingBox().getMinX() - 1][(int)player->getBoundingBox().getMinY() + 1] == true)
		//		{
		//			player->setPositionY(player->getPositionY() + 3);

		//			if (drawLayer[(int)player->getBoundingBox().getMinX() - 1][(int)player->getBoundingBox().getMinY() + 1] == true)
		//			{
		//				player->setPositionY(player->getPositionY() + 3);
		//			}
		//		}
		//		player->setPositionY(player->getPositionY() + 3);
		//	}
		//}

		//if (playerDirection == Direction::RIGHT)
		//{
		//	//check for a direction change
		//	if (drawLayer[(int)player->getBoundingBox().getMaxX() + 1][(int)player->getBoundingBox().getMaxY() + 2] == true)
		//	{
		//		playerDirection = Direction::LEFT;
		//	}
		//}
		//if (playerDirection == Direction::LEFT)
		//{
		//	//check for a direction change
		//	if (drawLayer[(int)player->getBoundingBox().getMinX() - 1][(int)player->getBoundingBox().getMaxY() + 2] == true)
		//	{
		//		playerDirection = Direction::RIGHT;
		//	}
		//}
}

void HelloWorld::CheckIfDead(Rect collisionBox)
{
	//checks if player hits the edge of the screen
	if (player->getPosition().y < 0 || (player->getBoundingBox().getMaxX() + 13) > ScreenResolution.x || (player->getBoundingBox().getMinX() - 13) < 0)
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

	auto winSize = Director::getInstance()->getVisibleSize();
	auto moveButtonTo = MoveTo::create(0.5, Vec2(winSize.width*0.5f, winSize.height / 0.5f * 0.25));
	auto moveBackgroundTo = MoveTo::create(0.5, Vec2(winSize.width*0.5f, winSize.height / 0.5f * 0.25));
	//restartMenuButton->runAction(moveButtonTo);
	//restartBackground->runAction(moveBackgroundTo);

	for (int i = 0; i < ScreenResolution.x - 1; i++)
	{
		for (int ii = 0; ii < ScreenResolution.y - 1; ii++)
		{
			drawLayer[i][ii] = false;//set each value int the array to false
		}
	}

}

void HelloWorld::LoadStartMenu()
{
	auto rootNode = CSLoader::createNode("StartMenu.csb");
	startMenuButton = (ui::Button*)rootNode->getChildByName("startMenuButton");
	startMenuButton->addTouchEventListener(CC_CALLBACK_2(HelloWorld::StartPressed, this));
	startBackground = (Sprite*)rootNode->getChildByName("startBackground");
	addChild(rootNode);
}

void HelloWorld::LoadLevelSelect()
{
	auto rootNode = CSLoader::createNode("LevelSelect.csb");

	SelectLevel1 = (ui::Button*)rootNode->getChildByName("SelectLevel1");
	SelectLevel1->addTouchEventListener(CC_CALLBACK_2(HelloWorld::LevelPressed, this, 0));

	SelectLevel2 = (ui::Button*)rootNode->getChildByName("SelectLevel2");
	SelectLevel2->addTouchEventListener(CC_CALLBACK_2(HelloWorld::LevelPressed, this, 1));

	SelectLevel3 = (ui::Button*)rootNode->getChildByName("SelectLevel3");
	SelectLevel3->addTouchEventListener(CC_CALLBACK_2(HelloWorld::LevelPressed, this, 2));

	SelectLevel4 = (ui::Button*)rootNode->getChildByName("SelectLevel4");
	SelectLevel4->addTouchEventListener(CC_CALLBACK_2(HelloWorld::LevelPressed, this, 3));

	SelectLevel5 = (ui::Button*)rootNode->getChildByName("SelectLevel5");
	SelectLevel5->addTouchEventListener(CC_CALLBACK_2(HelloWorld::LevelPressed, this, 4));

	SelectLevel6 = (ui::Button*)rootNode->getChildByName("SelectLevel6");
	SelectLevel6->addTouchEventListener(CC_CALLBACK_2(HelloWorld::LevelPressed, this, 5));
	addChild(rootNode);
}

void HelloWorld::LoadGameMenu()
{
	auto rootNode = CSLoader::createNode("GameMenu.csb");

	backToSelect = (ui::Button*)rootNode->getChildByName("backToSelect");
	backToSelect->addTouchEventListener(CC_CALLBACK_2(HelloWorld::StartPressed, this));

	restartButton = (ui::Button*)rootNode->getChildByName("restartButton");
	restartButton->addTouchEventListener(CC_CALLBACK_2(HelloWorld::StartPressed, this));

	resumeButton = (ui::Button*)rootNode->getChildByName("resumeButton");
	resumeButton->addTouchEventListener(CC_CALLBACK_2(HelloWorld::PausePressed, this));

	addChild(rootNode);
}

void HelloWorld::LoadLevel1()
{
	//Initialize all level1 sprites/buttons
	GameManager::sharedGameManager()->isGameLive = true;

	/*auto myScene = Scene::create();
	Director::getInstance()->replaceScene(TransitionFlipX::create(0.5, myScene));*/

	auto rootNode = CSLoader::createNode("Level1.csb");

	ScreenResolution = Vec2(rootNode->getBoundingBox().getMaxX(), rootNode->getBoundingBox().getMaxY());//get the resolution of the screen.

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
	restartButton->addTouchEventListener(CC_CALLBACK_2(HelloWorld::RestartPressed, this));

	drawLayer = new bool*[(int)ScreenResolution.x];//init the width of the array
	for (int i = 0; i < ScreenResolution.x - 1; i++)
	{
		drawLayer[i] = new bool[(int)ScreenResolution.y];//init the height of the array
	}

	lineSize = 10;
	moveSpeed = 2;

	for (int i = 0; i < ScreenResolution.x - 1; i++)
	{
		for (int ii = 0; ii < ScreenResolution.y - 1; ii++)
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
	//addChild(background);
	addChild(lineDrawNode);
	addChild(player);
}

void HelloWorld::LoadLevel2()
{
	//Initialize all level2 sprites/buttons
	GameManager::sharedGameManager()->isGameLive = true;

	/*auto myScene = Scene::create();
	Director::getInstance()->replaceScene(TransitionFlipX::create(0.5, myScene));*/

	auto rootNode = CSLoader::createNode("Level2.csb");
	
	ScreenResolution = Vec2(rootNode->getBoundingBox().getMaxX(), rootNode->getBoundingBox().getMaxY());//get the resolution of the screen.

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
	restartButton->addTouchEventListener(CC_CALLBACK_2(HelloWorld::RestartPressed, this));

	drawLayer = new bool*[(int)ScreenResolution.x];//init the width of the array
	for (int i = 0; i < ScreenResolution.x - 1; i++)
	{
		drawLayer[i] = new bool[(int)ScreenResolution.y];//init the height of the array
	}

	lineSize = 10;
	moveSpeed = 2;

	for (int i = 0; i < ScreenResolution.x - 1; i++)
	{
		for (int ii = 0; ii < ScreenResolution.y - 1; ii++)
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
	//addChild(background);
	addChild(lineDrawNode);
	addChild(player);
}

void HelloWorld::LoadLevel3()
{
	//Initialize all level3 sprites/buttons
	//auto myScene = Scene::create();
	//Director::getInstance()->replaceScene(TransitionFlipX::create(2, myScene));

	auto rootNode = CSLoader::createNode("Level3.csb");

	ScreenResolution = Vec2(rootNode->getBoundingBox().getMaxX(), rootNode->getBoundingBox().getMaxY());//get the resolution of the screen.

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
	restartButton->addTouchEventListener(CC_CALLBACK_2(HelloWorld::RestartPressed, this));

	drawLayer = new bool*[(int)ScreenResolution.x];//init the width of the array
	for (int i = 0; i < ScreenResolution.x - 1; i++)
	{
		drawLayer[i] = new bool[(int)ScreenResolution.y];//init the height of the array
	}

	lineSize = 10;
	moveSpeed = 2;

	for (int i = 0; i < ScreenResolution.x - 1; i++)
	{
		for (int ii = 0; ii < ScreenResolution.y - 1; ii++)
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
	////addChild(background);
	addChild(lineDrawNode);
	addChild(player);

	GameManager::sharedGameManager()->isGameLive = true;
}

void HelloWorld::LoadLevel4()
{
	//Initialize all level4 sprites/buttons
	//auto myScene = Scene::create();
	//Director::getInstance()->replaceScene(TransitionFlipX::create(2, myScene));

	auto rootNode = CSLoader::createNode("Level4.csb");

	ScreenResolution = Vec2(rootNode->getBoundingBox().getMaxX(), rootNode->getBoundingBox().getMaxY());//get the resolution of the screen.

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
	restartButton->addTouchEventListener(CC_CALLBACK_2(HelloWorld::RestartPressed, this));

	drawLayer = new bool*[(int)ScreenResolution.x];//init the width of the array
	for (int i = 0; i < ScreenResolution.x - 1; i++)
	{
		drawLayer[i] = new bool[(int)ScreenResolution.y];//init the height of the array
	}

	lineSize = 10;
	moveSpeed = 2;

	for (int i = 0; i < ScreenResolution.x - 1; i++)
	{
		for (int ii = 0; ii < ScreenResolution.y - 1; ii++)
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
	////addChild(background);
	addChild(lineDrawNode);
	addChild(player);

	GameManager::sharedGameManager()->isGameLive = true;
}

void HelloWorld::LoadLevel5()
{
	//Initialize all level5 sprites/buttons
	//auto myScene = Scene::create();
	//Director::getInstance()->replaceScene(TransitionFlipX::create(2, myScene));

	auto rootNode = CSLoader::createNode("Level5.csb");

	ScreenResolution = Vec2(rootNode->getBoundingBox().getMaxX(), rootNode->getBoundingBox().getMaxY());//get the resolution of the screen.

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
	restartButton->addTouchEventListener(CC_CALLBACK_2(HelloWorld::RestartPressed, this));

	drawLayer = new bool*[(int)ScreenResolution.x];//init the width of the array
	for (int i = 0; i < ScreenResolution.x - 1; i++)
	{
		drawLayer[i] = new bool[(int)ScreenResolution.y];//init the height of the array
	}

	lineSize = 10;
	moveSpeed = 2;

	for (int i = 0; i < ScreenResolution.x - 1; i++)
	{
		for (int ii = 0; ii < ScreenResolution.y - 1; ii++)
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
	////addChild(background);
	addChild(lineDrawNode);
	addChild(player);

	GameManager::sharedGameManager()->isGameLive = true;
}

void HelloWorld::LoadLevel6()
{
	//Initialize all level6 sprites/buttons
	GameManager::sharedGameManager()->isGameLive = true;

	/*auto myScene = Scene::create();
	Director::getInstance()->replaceScene(TransitionFlipX::create(0.5, myScene));*/

	auto rootNode = CSLoader::createNode("Level6.csb");

	ScreenResolution = Vec2(rootNode->getBoundingBox().getMaxX(), rootNode->getBoundingBox().getMaxY());//get the resolution of the screen.

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
	restartButton->addTouchEventListener(CC_CALLBACK_2(HelloWorld::RestartPressed, this));

	drawLayer = new bool*[(int)ScreenResolution.x];//init the width of the array
	for (int i = 0; i < ScreenResolution.x - 1; i++)
	{
		drawLayer[i] = new bool[(int)ScreenResolution.y];//init the height of the array
	}

	lineSize = 10;
	moveSpeed = 2;

	for (int i = 0; i < ScreenResolution.x - 1; i++)
	{
		for (int ii = 0; ii < ScreenResolution.y - 1; ii++)
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
	//addChild(background);
	addChild(lineDrawNode);
	addChild(player);
}