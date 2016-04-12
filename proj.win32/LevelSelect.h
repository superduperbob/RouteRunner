#ifndef __LEVELSELECT_SCENE_H__
#define __LEVELSELECT_SCENE_H__

#include "cocostudio/CocoStudio.h"
#include "GameManager.h"
#include "ui\CocosGUI.h"
#include "HelloWorldScene.h"

using namespace cocostudio::timeline;
using namespace cocos2d;
using namespace std;

class LevelSelect : public cocos2d::Layer
{
public:
	// there's no 'id' in cpp, so we recommend returning the class instance pointer
	static cocos2d::Scene* createScene();

	// Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
	virtual bool init();

	CREATE_FUNC(LevelSelect);
	
	//HelloWorld * world;

private:
	cocos2d::Sprite* EndBlock;
	ui::Button* SelectLevel1;
	ui::Button* SelectLevel2;
	ui::Button* SelectLevel3;
	ui::Button* SelectLevel4;
	ui::Button* SelectLevel5;
	ui::Button* SelectLevel6;
	ui::Button* backButton;

	//void LoadLevel(string level);
	void LevelPressed(Ref *pSender, cocos2d::ui::Widget::TouchEventType type, int levelID);
	void BackToStartPressed(Ref *pSender, cocos2d::ui::Widget::TouchEventType type);

	string level_1 = "level1.csb";
	string level_2 = "level2.csb";
	string level_3 = "level3.csb";
	string level_4 = "level4.csb";
	string level_5 = "level5.csb";
	string level_6 = "level6.csb";

	//Sprite* player;
	//Direction playerDirection;
	//bool playerIsFalling;
	//DrawNode* lineDrawNode;
	//bool **drawLayer;
	//Vec2 ScreenResolution;
	//float secondCounter;
	//Vec2 oldPoint;
	//float playerFallSpeed;
	//int lineSize;
	//Sprite* backgroundParallaxMain;
	//Sprite* backgroundParallaxRight;
	//float moveSpeed;
	//Vec2 LineArray[500];
	//int lineArrayCount;
};

#endif