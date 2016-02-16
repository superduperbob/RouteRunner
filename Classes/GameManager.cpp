#include "GameManager.h"

GameManager* GameManager::instance = NULL;

GameManager* GameManager::sharedGameManager()
{
	if (instance == NULL)
	{
		instance = new GameManager();
	}


	return instance;
}

GameManager::GameManager()
{
	
	isGameLive = false;
	isDead = false;
}

GameManager::~GameManager()
{

}

//void GameManager::UpdateScore(int increment)
//{
//	this->score += increment;
//}
//
//void GameManager::ResetScore()
//{
//	score = 0;
//}
//
//int GameManager::GetScore()
//{
//	return score;
//}