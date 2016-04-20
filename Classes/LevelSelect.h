#ifndef __LEVELSELECT_SCENE_H__
#define __LEVELSELECT_SCENE_H__

#include "cocostudio/CocoStudio.h"
#include "GameManager.h"
#include "ui/CocosGUI.h"
#include "HelloWorldScene.h"
#include "SimpleAudioEngine.h"

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
	ui::Button* easyButton;
	ui::Button* normalButton;
	ui::Button* hardButton;

	//void LoadLevel(string level);
	void LevelPressed(Ref *pSender, cocos2d::ui::Widget::TouchEventType type, int levelID);
	void BackToStartPressed(Ref *pSender, cocos2d::ui::Widget::TouchEventType type);
	void DifficultyLevel(Ref *pSender, cocos2d::ui::Widget::TouchEventType type, int difficulty);

	string level_1 = "Level1.csb";
	string level_2 = "Level2.csb";
	string level_3 = "Level3.csb";
	string level_4 = "Level4.csb";
	string level_5 = "Level5.csb";
	string level_6 = "Level6.csb";
};

#endif