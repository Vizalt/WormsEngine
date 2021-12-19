#include "Globals.h"
#include "Application.h"
#include "ModuleSceneIntro.h"
//#include "SString.h"



ModuleSceneIntro::ModuleSceneIntro(Application* app, bool start_enabled) : Module(app, start_enabled)
{
	graphics = NULL;
}

ModuleSceneIntro::~ModuleSceneIntro()
{}

// Load assets
bool ModuleSceneIntro::Start()
{
	LOG("Loading Intro assets");
	bool ret = true;

	App->renderer->camera.x = App->renderer->camera.y = 0;

	Box1Coll = App->coll->AddCollider({ b1x,b1y,b1w,b1h}, Collider::Type::BOX1, this);
	Box2Coll = App->coll->AddCollider({ b2x,b2y,b2w,b2h }, Collider::Type::BOX2, this);
	Box3Coll = App->coll->AddCollider({ b3x,b3y,b3w,b3h }, Collider::Type::BOX3, this);
	Box4Coll = App->coll->AddCollider({ b4x,b4y,b4w,b4h }, Collider::Type::BOX4, this);

	P1WIN = App->textures->Load("pinball/Win1.png");
	P2WIN = App->textures->Load("pinball/win2.png");

	return ret;
}

// Load assets
bool ModuleSceneIntro::CleanUp()
{
	LOG("Unloading Intro scene");

	return true;
}

bool ModuleSceneIntro::PreUpdate()
{


	return true;
}

// Update: draw background
bool ModuleSceneIntro::Update()
{
	
	App->coll->DebugDraw();

	App->renderer->DrawLine(-1000, App->motor->ground.y, 2000, App->motor->ground.y, 255, 0, 0);

	SDL_Rect Suelo{sx, sy, sw, sh};
	App->renderer->DrawQuad(Suelo, 30, 202, 150);

	SDL_Rect Suelo2 { sx2, sy2, sw2, sh2 };
	App->renderer->DrawQuad(Suelo2, 162, 34, 102);

	//Boxes
	SDL_Rect Box1{ b1x,b1y,b1w,b1h };
	App->motor->CreateBoxes(Box1, 129, 30, 216);

	SDL_Rect Box2{ b2x,b2y,b2w,b2h };
	App->motor->CreateBoxes(Box2, 129, 30, 216);
	
	SDL_Rect Box3{ b3x,b3y,b3w,b3h };
	App->motor->CreateBoxes(Box3, 129, 30, 216);

	SDL_Rect Box4{ b4x,b4y,b4w,b4h };
	App->motor->CreateBoxes(Box4, 129, 30, 216);

	if (p1Win == true) {
		App->renderer->Blit(P1WIN, 0, 0, NULL);
	}
	if (p2Win == true) {
		App->renderer->Blit(P2WIN, 0, 0, NULL);
	}
	
	return true;
}

bool ModuleSceneIntro::PostUpdate()
{
	//SString title(TITLE "Angle: %d ", App->player->PlayerRotation);
	//App->window->SetTitle(title);

	return true;
}