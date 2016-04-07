#include "GameMenu.h"

USING_NS_CC;

Scene* GameMenu::createScene()
{
	// 'scene' is an autorelease object
	auto scene = Scene::create();

	// 'layer' is an autorelease object
	auto layer = GameMenu::create();

	// add layer as a child to scene
	scene->addChild(layer);

	// return the scene
	return scene;
}

// on "init" you need to initialize your instance
bool GameMenu::init()
{
	if (!Layer::init())
	{
		return false;
	}
	
	auto rootNode = CSLoader::createNode("GameMenu.csb");
	
	backToSelect = (ui::Button*)rootNode->getChildByName("backToSelect");
	backToSelect->addTouchEventListener(CC_CALLBACK_2(GameMenu::StartPressed, this));

	restartButton = (ui::Button*)rootNode->getChildByName("restartButton");
	restartButton->addTouchEventListener(CC_CALLBACK_2(GameMenu::StartPressed, this));

	//resumeButton = (ui::Button*)rootNode->getChildByName("resumeButton");
	//resumeButton->addTouchEventListener(CC_CALLBACK_2(GameMenu::PausePressed, this));

	addChild(rootNode);


}
void GameMenu::StartPressed(Ref *pSender, cocos2d::ui::Widget::TouchEventType type)
{
	if (type == cocos2d::ui::Widget::TouchEventType::ENDED)
	{
		Scene* scene = LevelSelect::createScene();

		Director::getInstance()->replaceScene(scene);
	}
}

//void GameMenu::PausePressed(Ref *pSender, cocos2d::ui::Widget::TouchEventType type)
//{
//	bool GameMenu = false;
//	if (type == cocos2d::ui::Widget::TouchEventType::ENDED)
//	{
//		GameManager::sharedGameManager()->isGameLive = !GameManager::sharedGameManager()->isGameLive;
//		LoadGameMenu();
//	}
//}
