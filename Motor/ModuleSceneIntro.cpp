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

	return UPDATE_CONTINUE;
}

update_status ModuleSceneIntro::PostUpdate()
{
	//SString title(TITLE "Angle: %d ", App->player->PlayerRotation);
	//App->window->SetTitle(title);

	return UPDATE_CONTINUE;
}
