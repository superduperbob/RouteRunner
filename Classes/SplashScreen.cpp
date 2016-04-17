//#include "SplashScreen.h"
//
//USING_NS_CC;
//
//Scene* SplashScreen::createScene()
//{
//	// 'scene' is an autorelease object
//	auto scene = Scene::create();
//
//	// 'layer' is an autorelease object
//	auto layer = SplashScreen::create();
//
//	// add layer as a child to scene
//	scene->addChild(layer);
//
//	// return the scene
//	return scene;
//}
//
//// on "init" you need to initialize your instance
//bool SplashScreen::init()
//{
//	if (!Layer::init())
//	{
//		return false;
//	}
//
//	splashIcon =
//
//	return true;
//}
//
//void SplashScreen::onEnter() {
//	Layer::onEnter();
//
//	// Wait for 0.5 seconds to load main scene
//	this->scheduleOnce(schedule_selector(SplashScreen::finishSplash), 0.5f);
//}
//
//void SplashScreen::finishSplash(float dt) {
//	// ... do whatever other initializations here
//	// Show the actual main scene
//	Director::getInstance()->replaceScene(HomeScene::createScene());
//}