#ifndef GameManager_h
#define GameManager_h

#include <stdio.h>

class GameManager
{
public:
	~GameManager();
	static GameManager* sharedGameManager();

	bool isGameLive;
	bool isDead;
	void UpdateScore(int increment);
	void ResetScore();
	int GetScore();


private:
	GameManager();
	static GameManager* instance;
	int score;
};

#endif 

