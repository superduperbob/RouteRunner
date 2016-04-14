#ifndef __STARTMENU_SCENE_H__
#define __STARTMENU_SCENE_H__

#include "cocostudio/CocoStudio.h"
#include "GameManager.h"
#include "ui/CocosGUI.h"
#include "LevelSelect.h"

using namespace cocostudio::timeline;
using namespace cocos2d;
using namespace std;

class StartMenu : public cocos2d::Layer
{
public:
	// there's no 'id' in cpp, so we recommend returning the class instance pointer
	static cocos2d::Scene* createScene();

	// Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
	virtual bool init();

	CREATE_FUNC(StartMenu);

	void StartPressed(Ref *pSender, cocos2d::ui::Widget::TouchEventType type);
private:
	cocos2d::Sprite* startBackground;
	ui::Button* startMenuButton;

};

#endif