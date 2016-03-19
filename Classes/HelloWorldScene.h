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
	void LevelPressed(Ref *pSender, cocos2d::ui::Widget::TouchEventType type, int levelID);
	void CheckIfDead(Rect);
	void PlayerDead();

	void update(float);

	bool checkPlayerCollision();
	bool checkTerrainCollision(Rect);
	void checkFloorCollision();
	void checkSpringCollision(Rect);
	bool checkEndBlockCollision(Rect);

	void drawPoint(int x, int y);

	void LoadStartMenu();
	void LoadLevelSelect();
	void LoadGameMenu();
	void LoadLevel(string level);

private:

	void updateline(cocos2d::Touch* touch, cocos2d::Event* event);
	void updateJetpackDirection(cocos2d::Touch* touch);

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

	int inputState;
	bool jetpack;

	cocos2d::Sprite* EndBlock;
	ui::Button* SelectLevel1;
	ui::Button* SelectLevel2;
	ui::Button* SelectLevel3;
	ui::Button* SelectLevel4;
	ui::Button* SelectLevel5;
	ui::Button* SelectLevel6;

	ui::Button* backToSelect;
	ui::Button* restartMenuButton;
	ui::Button* resumeButton;
	
	cocos2d::Sprite* startBackground;
	ui::Button* startMenuButton;
	ui::Button* pauseButton;
	ui::Button* restartButton;
	Vec2		playerStartPos;

	Node* Squares;
	Node* Windows;
	Node* Springs;
	Node* Spikes;

	string level_1 = "level1.csb";
	string level_2 = "level2.csb";
	string level_3 = "level3.csb";
	string level_4 = "level4.csb";
	string level_5 = "level5.csb";
	string level_6 = "level6.csb";

};

#endif // __HELLOWORLD_SCENE_H__
