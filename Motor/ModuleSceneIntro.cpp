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


	return ret;
}

// Load assets
bool ModuleSceneIntro::CleanUp()
{
	LOG("Unloading Intro scene");

	return true;
}

update_status ModuleSceneIntro::PreUpdate()
{


	return UPDATE_CONTINUE;
}

// Update: draw background
update_status ModuleSceneIntro::Update()
{
	App->renderer->DrawLine(-1000, App->motor->ground.y, 2000, App->motor->ground.y, 255, 0, 0);

	SDL_Rect Suelo{sx, sy, sw, sh};
	App->renderer->DrawQuad(Suelo, 30, 202, 150);

	SDL_Rect Suelo2 { sx2, sy2, sw2, sh2 };
	App->renderer->DrawQuad(Suelo2, 162, 34, 102);

	//Boxes
	SDL_Rect Box1{ b1x,b1y,b1w,b1h };
	App->renderer->DrawQuad(Box1, 129, 30, 216);

	SDL_Rect Box2{ b2x,b2y,b2w,b2h };
	App->renderer->DrawQuad(Box2, 129, 30, 216);

	SDL_Rect Box3{ b3x,b3y,b3w,b3h };
	App->renderer->DrawQuad(Box3, 129, 30, 216);

	SDL_Rect Box4{ b4x,b4y,b4w,b4h };
	App->renderer->DrawQuad(Box4, 129, 30, 216);

	return UPDATE_CONTINUE;
}

update_status ModuleSceneIntro::PostUpdate()
{
	//SString title(TITLE "Angle: %d ", App->player->PlayerRotation);
	//App->window->SetTitle(title);

	return UPDATE_CONTINUE;
}
