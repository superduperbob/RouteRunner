#include "LevelSelect.h"
#include "StartMenu.h"
#include "GameManager.h"

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
	
	//CocosDenshion::SimpleAudioEngine::sharedEngine()->stopBackgroundMusic();

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

	easyButton = (ui::Button*)rootNode->getChildByName("easyButton");
	easyButton->addTouchEventListener(CC_CALLBACK_2(LevelSelect::DifficultyLevel, this, 1));

	normalButton = (ui::Button*)rootNode->getChildByName("normalButton");
	normalButton->addTouchEventListener(CC_CALLBACK_2(LevelSelect::DifficultyLevel, this, 2));

	hardButton = (ui::Button*)rootNode->getChildByName("hardButton");
	hardButton->addTouchEventListener(CC_CALLBACK_2(LevelSelect::DifficultyLevel, this, 3));

	switch (GameManager::sharedGameManager()->GetDifficulty())
	{
	case 1:
		easyButton->setBright(false);
		break;
	case 2:
		normalButton->setBright(false);
		break;
	case 3:
		hardButton->setBright(false);
		break;
	}
	

	addChild(rootNode);
    
    return true;
}
void LevelSelect::LevelPressed(Ref *pSender, cocos2d::ui::Widget::TouchEventType type, int levelID)
{

	if (type == cocos2d::ui::Widget::TouchEventType::ENDED)
	{
		CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("ConfirmSound.mp3");
		CocosDenshion::SimpleAudioEngine::sharedEngine()->playBackgroundMusic("Blip_Stream.mp3", true);
		Scene* scene = HelloWorld::createScene(levelID);

		Director::getInstance()->replaceScene(scene);	
	}
}

void LevelSelect::BackToStartPressed(Ref *pSender, cocos2d::ui::Widget::TouchEventType type)
{
	if (type == cocos2d::ui::Widget::TouchEventType::ENDED)
	{
		CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("ConfirmSound.mp3");
		Scene* scene = StartMenu::createScene();

		Director::getInstance()->replaceScene(TransitionSlideInL::create(0.3, scene) );
	}
}

void LevelSelect::DifficultyLevel(Ref *pSender, cocos2d::ui::Widget::TouchEventType type, int difficulty)
{
	if (type == cocos2d::ui::Widget::TouchEventType::ENDED)
	{
		easyButton->setBright(true);
		normalButton->setBright(true);
		hardButton->setBright(true);

		if (difficulty == 1)
		{
			GameManager::sharedGameManager()->setDifficulty(1);
			easyButton->setBright(false);
		}	
		if (difficulty == 2)
		{
			GameManager::sharedGameManager()->setDifficulty(2);
			normalButton->setBright(false);
		}
		if (difficulty == 3)
		{
			GameManager::sharedGameManager()->setDifficulty(3);
			hardButton->setBright(false);
		}
	}
}
