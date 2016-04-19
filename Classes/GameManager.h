#ifndef GameManager_h
#define GameManager_h
#include "SimpleAudioEngine.h"

#include <stdio.h>

class GameManager
{
	enum Difficulty
	{
		EASY,
		MEDIUM,
		HARD,
	};


public:
	~GameManager();
	static GameManager* sharedGameManager();

	bool isGameLive;
	bool isDead;
	
	void UpdateScore(int increment);
	void ResetScore();
	int GetScore();

	int GetDifficulty();
	void setDifficulty(int);

private:
	GameManager();
	static GameManager* instance;
	Difficulty difficulty;
	
	int score;
};

#endif 

