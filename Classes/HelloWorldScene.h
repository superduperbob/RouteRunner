#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"
#include "ui/CocosGUI.h"


//#include "LevelSelect.h"

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
    static cocos2d::Scene* createScene(int level);

    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();

    // implement the "static create()" method manually
    CREATE_FUNC(HelloWorld);

	bool onTouchBegan(cocos2d::Touch* touch, cocos2d::Event* event);
	void onTouchMoved(cocos2d::Touch* touch, cocos2d::Event* event);
	void onTouchEnded(cocos2d::Touch* touch, cocos2d::Event* event);
	
	void PausePressed(Ref *pSender, cocos2d::ui::Widget::TouchEventType type);
	void RestartPressed(Ref *pSender, cocos2d::ui::Widget::TouchEventType type, int level);
	void BackToSelectPressed(Ref *pSender, cocos2d::ui::Widget::TouchEventType type);
	void NextLevelPressed(Ref *pSender, cocos2d::ui::Widget::TouchEventType type, int level);
	void DropDownMenu();
	void EndMenu();
	
	//void LevelPressed(Ref *pSender, cocos2d::ui::Widget::TouchEventType type, int levelID);

	void CheckIfDead(Rect);
	void PlayerDead();
	void PlayerAlive();

	void update(float);

	bool checkPlayerCollision();
	bool checkTerrainCollision(Rect collisionBox);
	void checkFloorCollision();
	void checkSpringCollision(Rect collisionBox);
	void checkPickupCollision(Rect collisionBox);
	bool checkEndBlockCollision(Rect);

	void drawPoint(int x, int y);

	//void LoadStartMenu();
	//void LoadLevelSelect();
	void LoadGameMenu();
	void LoadLevel(int level);

private:

	void updateline(cocos2d::Touch* touch, cocos2d::Event* event);
	void updateJetpackDirection(cocos2d::Touch* touch);
    void ButtonSleep(ui::Button* button);
    
	Direction playerDirection;

	DrawNode* lineDrawNode;
    
	bool **drawLayer;
    bool playerIsFalling;
    bool jetpack;
    
	Vec2 _ScreenResolution;
    Vec2 oldPoint;
    Vec2 LineArray[500];
    
	float secondCounter;
	float playerFallSpeed;
    float moveSpeed;
    
    Sprite* player;
	Sprite* backgroundParallaxMain;
	Sprite* backgroundParallaxRight;
    
	int lineArrayCount;
    int lineSize;
	int inputState;
	int currentLevel;
    
	cocos2d::Sprite* EndBlock;

	ui::Button* restartButton;
	ui::Button* pauseButton;
	ui::Button* restartMenuButton;
	ui::Button* ONextLevelButton;
	ui::Button* OBackToSelectButton;

	Vec2 OBackToSelectButtonStartPos;
	Vec2 ONextLevelButtonStartPos;
	Vec2 overlayBackgroundStartPos;

	Sprite* overlayBackground;

	Vec2		playerStartPos;

	bool menuDown = false;

	Node* Squares;
	Node* Windows;
	Node* Springs;
	Node* Spikes;

	Sprite* jetpackPickup;

	vector<string> levels = vector<string>{
		"1.csb",
		"2.csb",
		"3.csb",
		"4.csb",
		"5.csb",
		"6.csb"
	};
};

#endif // __HELLOWORLD_SCENE_H__
