#include "LevelSelect.h"

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

	addChild(rootNode);

}
void LevelSelect::LevelPressed(Ref *pSender, cocos2d::ui::Widget::TouchEventType type, int levelID){

	if (type == cocos2d::ui::Widget::TouchEventType::ENDED)
	{
			Scene* scene = LevelSelect::createScene();

			Director::getInstance()->replaceScene(scene);
		
		
		switch (levelID)
		{
			
		case 0: world->LoadLevel(level_1); break;
		case 1: world->LoadLevel(level_2); break;
		case 2: world->LoadLevel(level_3); break;
		case 3: world->LoadLevel(level_4); break;
		case 4: world->LoadLevel(level_5); break;
		case 5: world->LoadLevel(level_6); break;
		default: break;
		}
	}
}
