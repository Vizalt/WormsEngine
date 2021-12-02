#include "Globals.h"
#include "Application.h"
#include "ModulePlayer.h"

ModulePlayer::ModulePlayer(Application* app, bool start_enabled) : Module(app, start_enabled)
{
}

ModulePlayer::~ModulePlayer()
{}

// Load assets
bool ModulePlayer::Start()
{
	LOG("Loading player");
	position.x = 100;
	position.y = 430;
	PlayerTex = App->textures->Load("pinball/player.png");
	CannonTex = App->textures->Load("pinball/CannonTex.png");
	SupportCannonTex= App->textures->Load("pinball/SupportCannonTex.png");
	
	return true;
}

// Unload assets
bool ModulePlayer::CleanUp()
{
	LOG("Unloading player");

	return true;
}

// Update: draw background
update_status ModulePlayer::Update()
{
	App->renderer->DrawCircle(position.x+10, position.y+5, App->motor->ball.rad, 255, 0, 66);

	SDL_Rect player = { position.x, position.y, 50, 50 };

	if (App->input->GetKey(SDL_SCANCODE_D) == KEY_REPEAT) {
		App->player->position.x += 8;
	}
	if (App->input->GetKey(SDL_SCANCODE_A) == KEY_REPEAT) {
		App->player->position.x -= 8;
	}
	//if (App->input->GetKey(SDL_SCANCODE_S) == KEY_REPEAT) {
	//	App->player->position.y += 8;
	//}
	//if (App->input->GetKey(SDL_SCANCODE_W) == KEY_REPEAT) {
	//	App->player->position.y -= 8;
	//}

	if (App->input->GetKey(SDL_SCANCODE_RIGHT) == KEY_REPEAT) {
		PlayerRotation += 1;
	}
	if (App->input->GetKey(SDL_SCANCODE_LEFT) == KEY_REPEAT) {
		PlayerRotation -= 1;
	}
	if (PlayerRotation > 90) {
		PlayerRotation = 90;
	}
	if (PlayerRotation < 0) {
		PlayerRotation = 0;
	}

	/*App->renderer->Blit(PlayerTex, position.x, position.y, NULL, 1.0f);*/
	App->renderer->Blit(CannonTex, position.x, position.y, NULL, 1.0f,PlayerRotation);
	App->renderer->Blit(SupportCannonTex, position.x - 6, position.y + 50, NULL, 1.0f);
	return UPDATE_CONTINUE;
}