#pragma once
#ifndef __ENEMY_FLYEYE_H__
#define __ENEMY_FLYEYE_H__

#include "Entity.h"
#include "Point.h"
#include "Animation.h"


struct SDL_Texture;

class Enemy_Flyeye : public Entity
{
public:

	Enemy_Flyeye();

	virtual ~Enemy_Flyeye();

	bool Awake();

	bool Start();

	bool Update(float dt);

	bool CleanUp();

public:

	bool isPicked = false;

	Animation* currentAnimation = nullptr;

	Animation idle;
	Animation atack;
	Animation die;
	Animation take_hit;
	Animation run;

	Animation SPosition;
	SDL_Rect* spritePositions;

	int TSprite;
	int SpriteX;
	int SpriteY;
	int PhotoWeight;

	int countFrame = 0;
	bool isFacingLeft;

private:

	SDL_Texture* Enemytexture;
	SDL_Texture* Pathfindingtexture;
	const char* EnemyPath;
	const char* PathfindingPath;
	PhysBody* pbody;
	PhysBody* pbody1;
};

#endif // __ITEM_H__