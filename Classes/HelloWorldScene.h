#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"
#include "ui/CocosGUI.h"
using namespace cocos2d;
using namespace std;

enum Direction
{
	LEFT,
	RIGHT
};

struct line
{
	Vec2 startPos;
	Vec2 endPos;
};

class HelloWorld : public cocos2d::Layer
{
public:
    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::Scene* createScene();

    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();

    // implement the "static create()" method manually
    CREATE_FUNC(HelloWorld);


	bool onTouchBegan(cocos2d::Touch* touch, cocos2d::Event* event);
	void onTouchMoved(cocos2d::Touch* touch, cocos2d::Event* event);
	void onTouchEnded(cocos2d::Touch* touch, cocos2d::Event* event);
	
	void StartPressed(Ref *pSender, cocos2d::ui::Widget::TouchEventType type);
	void PausePressed(Ref *pSender, cocos2d::ui::Widget::TouchEventType type);
	void RestartPressed(Ref *pSender, cocos2d::ui::Widget::TouchEventType type);
	void CheckIfDead();

	void update(float);

	bool checkPlayerCollision();
	bool checkTerrainCollision(Rect);
	void checkFloorCollision();

	void drawPoint(int x, int y);

private:
	Sprite* player;
	Direction playerDirection;
	bool playerIsFalling;
	DrawNode* lineDrawNode;
	bool **drawLayer;
	Vec2 ScreenResolution;
	float secondCounter;
	Vec2 oldPoint;
	float playerFallSpeed;
	int lineSize;
	Sprite* backgroundParallaxMain;
	Sprite* backgroundParallaxRight;
	float moveSpeed;
	Vec2 LineArray[500];
	int lineArrayCount;

	cocos2d::Sprite* square_5;
	cocos2d::Sprite* square_6;
	cocos2d::Sprite* square_7;

	cocos2d::Sprite* square_8;
	cocos2d::Sprite* square_9;
	cocos2d::Sprite* square_10;
	cocos2d::Sprite* square_11;
	cocos2d::Sprite* square_12;
	cocos2d::Sprite* square_13;
	cocos2d::Sprite* square_14;
	cocos2d::Sprite* square_15;

	ui::Button* startButton;
	ui::Button* pauseButton;
	ui::Button* restartButton;
	ui::Button* restartMenuButton;
	Sprite*		startBackground;
	Sprite*		restartBackground;
	Vec2		playerStartPos;
};

#endif // __HELLOWORLD_SCENE_H__
