#include "LevelSelect.h"
#include "StartMenu.h"

USING_NS_CC;

Scene* LevelSelect::createScene()
{
	// 'scene' is an autorelease object
	auto scene = Scene::create();

	// 'layer' is an autorelease object
	auto layer = LevelSelect::create();

	// add layer as a child to scene
	scene->addChild(layer);

	// return the scene
	return scene;
}

// on "init" you need to initialize your instance
bool LevelSelect::init()
{
	if (!Layer::init())
	{
		return false;
	}
	auto rootNode = CSLoader::createNode("LevelSelect.csb");

	//rootNode->setPosition(0, 0);

	SelectLevel1 = (ui::Button*)rootNode->getChildByName("SelectLevel1");
	SelectLevel1->addTouchEventListener(CC_CALLBACK_2(LevelSelect::LevelPressed, this, 0));

	SelectLevel2 = (ui::Button*)rootNode->getChildByName("SelectLevel2");
	SelectLevel2->addTouchEventListener(CC_CALLBACK_2(LevelSelect::LevelPressed, this, 1));

	SelectLevel3 = (ui::Button*)rootNode->getChildByName("SelectLevel3");
	SelectLevel3->addTouchEventListener(CC_CALLBACK_2(LevelSelect::LevelPressed, this, 2));

	SelectLevel4 = (ui::Button*)rootNode->getChildByName("SelectLevel4");
	SelectLevel4->addTouchEventListener(CC_CALLBACK_2(LevelSelect::LevelPressed, this, 3));

	SelectLevel5 = (ui::Button*)rootNode->getChildByName("SelectLevel5");
	SelectLevel5->addTouchEventListener(CC_CALLBACK_2(LevelSelect::LevelPressed, this, 4));

	SelectLevel6 = (ui::Button*)rootNode->getChildByName("SelectLevel6");
	SelectLevel6->addTouchEventListener(CC_CALLBACK_2(LevelSelect::LevelPressed, this, 5));

	backButton = (ui::Button*)rootNode->getChildByName("backButton");
	backButton->addTouchEventListener(CC_CALLBACK_2(LevelSelect::BackToStartPressed, this));

	addChild(rootNode);
    
    return true;
}
void LevelSelect::LevelPressed(Ref *pSender, cocos2d::ui::Widget::TouchEventType type, int levelID)
{

	if (type == cocos2d::ui::Widget::TouchEventType::ENDED)
	{
		CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("ConfirmSound.wav");
		Scene* scene = HelloWorld::createScene(levelID);

		Director::getInstance()->replaceScene(scene);	
	}
}

void LevelSelect::BackToStartPressed(Ref *pSender, cocos2d::ui::Widget::TouchEventType type)
{
	if (type == cocos2d::ui::Widget::TouchEventType::ENDED)
	{
		CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("BackSound.wav");
		Scene* scene = StartMenu::createScene();

		Director::getInstance()->replaceScene(TransitionSlideInL::create(0.3, scene) );
	}
}
