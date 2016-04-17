#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"
#include "ui/CocosGUI.h"
#
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

enum Difficulty
{
	EASY,
	MEDIUM,
	HARD,
};

class HelloWorld : public cocos2d::Layer
{
public:
    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::Scene* createScene(string level);

    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();

    // implement the "static create()" method manually
    CREATE_FUNC(HelloWorld);

	bool onTouchBegan(cocos2d::Touch* touch, cocos2d::Event* event);//as soon as a touch is detected on screen.
	void onTouchMoved(cocos2d::Touch* touch, cocos2d::Event* event);//when a movement is detected
	void onTouchEnded(cocos2d::Touch* touch, cocos2d::Event* event);//when the players finger is removed form the screen
	void onTouching();//while the player has their finger on the screen, does not have to be moving their finger.
	
	void PausePressed(Ref *pSender, cocos2d::ui::Widget::TouchEventType type);
	void RestartPressed(Ref *pSender, cocos2d::ui::Widget::TouchEventType type, string level);
	void BackToSelectPressed(Ref *pSender, cocos2d::ui::Widget::TouchEventType type);
	void NextLevelPressed(Ref *pSender, cocos2d::ui::Widget::TouchEventType type, string level);
	
	//void LevelPressed(Ref *pSender, cocos2d::ui::Widget::TouchEventType type, int levelID);

	void CheckIfDead(Rect);
	void PlayerDead();

	void update(float);

	bool checkPlayerCollision();
	bool checkTerrainCollision(Rect);
	void checkFloorCollision();
	void checkSpringCollision(Rect);
	bool checkEndBlockCollision(Rect);

	void drawPoint(int x, int y);

	//void LoadStartMenu();
	//void LoadLevelSelect();
	void LoadGameMenu();
	void LoadLevel(string level);

private:

	void updateline(cocos2d::Touch* touch, cocos2d::Event* event);
	void updateJetpackDirection(cocos2d::Touch* touch);
    void ButtonSleep(ui::Button* button);
    
	Direction playerDirection;

	DrawNode* lineDrawNode;
    
	bool **drawLayer;
    bool playerIsFalling;
    bool jetpack;
	bool isTouching;//this boolean is true if the player is touching the screen, so we can call this during update
    
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

	Difficulty difficulty;
    
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

	string level_1 = "level1.csb";
	string level_2 = "level2.csb";
	string level_3 = "level3.csb";
	string level_4 = "level4.csb";
	string level_5 = "level5.csb";
	string level_6 = "level6.csb";

};

#endif // __HELLOWORLD_SCENE_H__
