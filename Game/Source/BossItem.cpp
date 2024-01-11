#include "App.h"
#include "Textures.h"
#include "Audio.h"
#include "Input.h"
#include "Render.h"
#include "Scene.h"
#include "Log.h"
#include "Point.h"
#include "Physics.h"
#include "Boss.h"
#include "BossItem.h"
#include "Map.h"
#include "Timer.h"

#include "List.h"
#include <random>


BossItem::BossItem() : Entity(EntityType::BOSSITEM)
{
	name.Create("bossitem");
}

BossItem::~BossItem() {}

bool BossItem::Awake() {

	ball_blue_texture_Path = parameters.child("boss_ball").child("ball_blue").attribute("texturepath").as_string();
	TSprite = parameters.child("boss_ball").child("ball_blue").attribute("Tsprite").as_int();
	SpriteX = parameters.child("boss_ball").child("ball_blue").attribute("x").as_int();
	SpriteY = parameters.child("boss_ball").child("ball_blue").attribute("y").as_int();
	PhotoWeight = parameters.child("boss_ball").child("ball_blue").attribute("Pweight").as_int();
	spritePositions = SPosition.SpritesPos(TSprite, SpriteX, SpriteY, PhotoWeight);
	ball_blue_start.LoadAnim("BossItem", "ball_blue_start", spritePositions);
	ball_blue_running.LoadAnim("BossItem", "ball_blue_running", spritePositions);
	ball_blue_end.LoadAnim("BossItem", "ball_blue_end", spritePositions);

	return true;
}

bool BossItem::Start() {
	ball_blue_texture = app->tex->Load(ball_blue_texture_Path);


	currentAnimation1 = &ball_blue_start;



	return true;
}

bool BossItem::Update(float dt)
{
	/*currentAnimation1 = &ball_blue_running;*/

	rect_1 = currentAnimation1->GetCurrentFrame();

	iPoint p1 = iPoint(100, 100);
	iPoint p2 = iPoint(400, 300); 
	iPoint p3 = iPoint(700, 100); 

	double t = 0.5;  

	iPoint result;
	calculateNURBS(p1, p2, p3, t, &result);
	
	//printf("x: %d, y: %d\n", result.x, result.y);
	/*
	printf("x: %d, y: %d\n", p1.x, p1.y);
	*/

	app->render->DrawTexture(ball_blue_texture, result_x, result_y, 0.4, SDL_FLIP_NONE, &rect_1);


	currentAnimation1->Update();


	if (app->input->GetKey(SDL_SCANCODE_9) == KEY_DOWN) {
		currentAnimation1->Reset();
		currentAnimation1 = &ball_blue_end;
	}

	if (currentAnimation1->HasFinished())
	{

		if (currentAnimation1->getNameAnimation() == "ball_blue_start") {
			currentAnimation1->Reset();
			currentAnimation1 = &ball_blue_running;

		}
		if (currentAnimation1->getNameAnimation() == "ball_blue_end") {
			currentAnimation1->Reset();
			currentAnimation1 = &ball_blue_start;
		}
	}

	return true;
}

bool BossItem::CleanUp()
{
	return true;
}

void BossItem::calculateNURBS(iPoint p1, iPoint p2, iPoint p3, double t, iPoint* result) {
	// Implementation of calculateNURBS
	double N1 = (1 - t) * (1 - t);
	double N2 = 2 * t * (1 - t);
	double N3 = t * t;

	result->x = N1 * p1.x + N2 * p2.x + N3 * p3.x;
	result->y = N1 * p1.y + N2 * p2.y + N3 * p3.y;
}




void BossItem::OnCollision(PhysBody* physA, PhysBody* physB) {

	switch (physB->ctype)
	{
	case ColliderType::PLAYER:
		break;
	case ColliderType::UNKNOWN:
		LOG("Collision UNKNOWN");
		break;
	}
}

void BossItem::OnEndCollision(PhysBody* physA, PhysBody* physB) {

	switch (physB->ctype)
	{
	case ColliderType::PLAYER:
		break;


	case ColliderType::UNKNOWN:
		LOG("Collision UNKNOWN");
		break;
	}
}