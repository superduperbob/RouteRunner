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
	difficulty = Difficulty::MEDIUM;
}

int GameManager::GetDifficulty()
{
	if (difficulty == Difficulty::EASY)
		return 1;

	if (difficulty == Difficulty::MEDIUM)
		return 2;

	if (difficulty == Difficulty::HARD)
		return 3;
}

void GameManager::setDifficulty(int setNum)
{
	if (setNum == 1)
		difficulty = Difficulty::EASY;

	if (setNum == 2)
		difficulty = Difficulty::MEDIUM;

	if (setNum == 3)
		difficulty = Difficulty::HARD;
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