#include "ItemBox.h"
#include "App.h"
#include "Textures.h"
#include "Audio.h"
#include "Input.h"
#include "Render.h"
#include "Scene.h"
#include "Log.h"
#include "Point.h"
#include "Physics.h"


ItemBox::ItemBox() : Entity(EntityType::ITEM)
{
	name.Create("itembox");

	
	spritePositions = SPosition.SpritesPos(28, 60, 70, 480);


	/*openBox.PushBack({ 30,24,35,40 });
	openBox.PushBack({ 94,24,35,40 });
	openBox.PushBack({ 158,24,35,40 });
	openBox.PushBack({ 222,24,35,40 });
	openBox.PushBack({ 286,24,35,40 });*/

	for (int i = 0; i < 5; i++)
	{
		openBox.PushBack({ spritePositions[i] });
	}

	openBox.speed = 0.17f;
	openBox.loop = false;
	
	for (int i = 5; i >= 0; i--)
	{
		CloseBox.PushBack({ spritePositions[i] });
	}
	/*CloseBox.PushBack({ 350,24,35,40 });
	CloseBox.PushBack({ 414,24,35,40 });
	CloseBox.PushBack({ 158,24,35,40 });
	CloseBox.PushBack({ 94,24,35,40 });
	CloseBox.PushBack({ 30,24,35,40 });*/

	CloseBox.speed = 0.17f;
	CloseBox.loop = true;
}

ItemBox::~ItemBox() {}

bool ItemBox::Awake() {

	position.x = parameters.attribute("x").as_int();
	position.y = parameters.attribute("y").as_int();

	BoxPath = parameters.attribute("texturepath").as_string();

	return true;
}

bool ItemBox::Start() {


	//initilize textures
	Boxtexture = app->tex->Load(BoxPath);
	pbody = app->physics->CreateCircle(position.x + 16, position.y + 16, 16, bodyType::DYNAMIC);
	pbody->ctype = ColliderType::ITEM;

	currentAnimation = &CloseBox;

	return true;
}

bool ItemBox::Update(float dt)
{
	
	// L07 DONE 4: Add a physics to an item - update the position of the object from the physics.  
	position.x = METERS_TO_PIXELS(pbody->body->GetTransform().p.x) - 16;
	position.y = METERS_TO_PIXELS(pbody->body->GetTransform().p.y) - 16;

	
	SDL_Rect rect = currentAnimation->GetCurrentFrame();
	currentAnimation->Update();
	
	app->render->DrawTexture(Boxtexture, position.x, position.y, SDL_FLIP_NONE,&rect);
	//app->render->DrawTexture(Boxtexture, position.x, position.y);

	return true;
}

bool ItemBox::CleanUp()
{
	return true;
}