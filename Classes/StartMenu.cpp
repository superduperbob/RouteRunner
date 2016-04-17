#include "StartMenu.h"

USING_NS_CC;

Scene* StartMenu::createScene()
{
	// 'scene' is an autorelease object
	auto scene = Scene::create();

	// 'layer' is an autorelease object
	auto layer = StartMenu::create();

	// add layer as a child to scene
	scene->addChild(layer);

	// return the scene
	return scene;
}

// on "init" you need to initialize your instance
bool StartMenu::init()
{
	if (!Layer::init())
	{
		return false;
	}
	auto rootNode = CSLoader::createNode("StartMenu.csb");

	startMenuButton = (ui::Button*)rootNode->getChildByName("startMenuButton");
	startMenuButton->addTouchEventListener(CC_CALLBACK_2(StartMenu::StartPressed, this));
	startBackground = (Sprite*)rootNode->getChildByName("startBackground");
	addChild(rootNode);
    
    return true;
}
void StartMenu::StartPressed(Ref *pSender, cocos2d::ui::Widget::TouchEventType type)
{
	if (type == cocos2d::ui::Widget::TouchEventType::ENDED)
	{
		CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("ConfirmSound.wav");
		Scene* scene = LevelSelect::createScene();

		Director::getInstance()->replaceScene(TransitionSlideInR::create(0.3, scene));
	}
}

