#include "Player.h"
#include "App.h"
#include "Textures.h"
#include "Audio.h"
#include "Input.h"
#include "Render.h"
#include "Scene.h"
#include "Log.h"
#include "Point.h"
#include "Physics.h"
#include "Animation.h"

Player::Player() : Entity(EntityType::PLAYER)
{
	name.Create("Player");
	//Prime Linea
	idle.PushBack({ 14, 6, 19, 30 });//({最左边，最上面，最右边减去最左边，最下面-最上面})
	idle.PushBack({ 66, 6, 19, 30 });
	idle.PushBack({ 115,6, 19, 30 });
	idle.PushBack({ 163,6, 19, 30 });
	idle.PushBack({ 216,6, 19, 30 });
	idle.PushBack({ 265,6, 19, 30 });
	idle.PushBack({ 315, 6, 19, 30 });

	////Segundo Linea
	idle.PushBack({ 17, 45, 24, 28 });
	idle.PushBack({ 67, 45, 24, 28 });
	idle.PushBack({ 116,45, 24, 28 });
	idle.PushBack({ 166,45, 24, 28 });
	idle.PushBack({ 217,45, 24, 28 });
	idle.PushBack({ 266,45, 24, 28 });
	idle.PushBack({ 316, 45, 24, 28 });

	//Terce Linea
	idle.PushBack({ 15, 79, 24,31 });
	idle.PushBack({ 65, 79, 24,31 });
	idle.PushBack({ 117, 79, 24,31 });
	idle.PushBack({ 164, 79, 24,31 });
	idle.PushBack({ 218, 79, 24,31 });
	idle.PushBack({ 264, 79, 24,31 });
	idle.PushBack({ 320, 79, 24,31 });

	//Quarta Linea
	idle.PushBack({ 14, 112, 35, 35 });
	idle.PushBack({ 68, 112, 35, 35 });
	idle.PushBack({ 118, 112, 35, 35 });
	idle.PushBack({ 155, 112, 35, 35 });
	idle.PushBack({ 205, 112, 35, 35 });
	idle.PushBack({ 255, 112, 35, 35 });
	idle.PushBack({ 309, 112, 35, 35 });


	////Quinta Linea
	idle.PushBack({ 15, 151, 23,35  });
	idle.PushBack({ 72, 151, 23,35 });
	idle.PushBack({ 122, 151, 23,35 });
	idle.PushBack({ 170, 151, 23,35 });
	idle.PushBack({ 221, 151, 23,35 });
	idle.PushBack({ 271, 151, 23,35 });
	idle.PushBack({ 321, 151, 23,35 });
	

	////Sixta Linea
	idle.PushBack({ 20,190,24,31});
	idle.PushBack({ 71,190,24,31 });
	idle.PushBack({ 121,190,24,31 });
	idle.PushBack({ 160,190,24,31 });
	idle.PushBack({ 210,190,24,31 });
	idle.PushBack({ 259,190,24,31 });
	idle.PushBack({ 309,190,24,31 });



	idle.PushBack({ 7,221,35,37});
	idle.PushBack({ 58,221,35,37 });
	idle.PushBack({ 115,221,35,37 });
	idle.PushBack({ 165,221,35,37 });
	idle.PushBack({ 215,221,35,37 });
	idle.PushBack({ 265,221,35,37 });
	idle.PushBack({ 315,221,35,37 });

	idle.PushBack({ 13,265,33,30});
	idle.PushBack({ 60,265,39,30 });
	idle.PushBack({ 102,265,33,30 });
	idle.PushBack({ 152,265,33,30 });
	idle.PushBack({ 219,265,33,30 });
	idle.PushBack({ 270,265,33,30 });
	idle.PushBack({ 302,265,48,30 });

	idle.PushBack({ 3,307,35,25});
	idle.PushBack({ 50,307,35,25 });
	idle.PushBack({ 100,307,35,25 });
	idle.PushBack({ 166,307,35,25 });
	idle.PushBack({ 217,307,35,25 });
	idle.PushBack({ 265,307,35,25 });
	idle.PushBack({ 316,307,35,25 });

	idle.PushBack({ 17,339,24,30});
	idle.PushBack({ 65,339,24,30 });
	idle.PushBack({ 116,339,24,30 });
	idle.PushBack({ 168,339,24,30 });
	idle.PushBack({ 221,339,24,30 });
	idle.PushBack({ 268,339,24,30 });
	idle.PushBack({ 317,339,24,30 });


	idle.PushBack({ 18,376,23,30});
	idle.PushBack({ 68,376,23,30 });
	

	

	
	idle.speed = 0.08f;
	idle.loop = true;

}

Player::~Player() {

}

bool Player::Awake() {

	position.x = parameters.attribute("x").as_int();
	position.y = parameters.attribute("y").as_int();
	texturePath = parameters.attribute("texturepath").as_string();

	return true;
}

bool Player::Start() {

	//initilize textures
	texture = app->tex->Load(texturePath);

	pbody = app->physics->CreateCircle(position.x + 16, position.y + 16, 16, bodyType::DYNAMIC);
	pbody->listener = this;
	pbody->ctype = ColliderType::PLAYER;

	pickCoinFxId = app->audio->LoadFx("Assets/Audio/Fx/retro-video-game-coin-pickup-38299.ogg");
	currentAnimation = &idle;

	return true;
}

bool Player::Update(float dt)
{
	b2Vec2 vel = b2Vec2(0, -GRAVITY_Y);

	if (app->input->GetKey(SDL_SCANCODE_W) == KEY_REPEAT) {
		//
	}
	if (app->input->GetKey(SDL_SCANCODE_S) == KEY_REPEAT) {
		//
	}

	if (app->input->GetKey(SDL_SCANCODE_A) == KEY_REPEAT) {
		vel = b2Vec2(-speed*dt, -GRAVITY_Y);
	}

	if (app->input->GetKey(SDL_SCANCODE_D) == KEY_REPEAT) {
		vel = b2Vec2(speed*dt, -GRAVITY_Y);
	}

	//Set the velocity of the pbody of the player
	pbody->body->SetLinearVelocity(vel);

	//Update player position in pixels
	position.x = METERS_TO_PIXELS(pbody->body->GetTransform().p.x) - 16;
	position.y = METERS_TO_PIXELS(pbody->body->GetTransform().p.y) - 16;

	SDL_Rect rect = currentAnimation->GetCurrentFrame();
	currentAnimation->Update();

	app->render->DrawTexture(texture, position.x, position.y, &rect);

	//app->render->DrawTexture(texture, position.x, position.y);



	return true;
}

bool Player::CleanUp()
{

	return true;
}

void Player::OnCollision(PhysBody* physA, PhysBody* physB) {

	switch (physB->ctype)
	{
	case ColliderType::ITEM:
		LOG("Collision ITEM");
		app->audio->PlayFx(pickCoinFxId);
		break;
	case ColliderType::PLATFORM:
		LOG("Collision PLATFORM");
		break;
	case ColliderType::UNKNOWN:
		LOG("Collision UNKNOWN");
		break;
	}
}