#include "Globals.h"
#include "Application.h"
#include "ModulePlayer.h"
#include "Motor.h"

ModulePlayer::ModulePlayer(Application* app, bool start_enabled) : Module(app, start_enabled)
{
}

ModulePlayer::~ModulePlayer()
{}

// Load assets
bool ModulePlayer::Start()
{
	LOG("Loading player");
	position.x = 40;
	position.y = 593;
	PlayerTex = App->textures->Load("pinball/player.png");
	CannonTex = App->textures->Load("pinball/CannonTex.png");
	SupportCannonTex= App->textures->Load("pinball/SupportCannonTex.png");
	
	cy = PIXEL_TO_METERS(position.y);
	cx = PIXEL_TO_METERS(position.x);

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
	MovementPlayer();
	/*SDL_Rect player = { position.x, position.y, 50, 50 };*/

	/*App->renderer->Blit(PlayerTex, position.x, position.y, NULL, 1.0f);*/
	App->renderer->Blit(CannonTex, cx-15, cy+8, NULL, 1.0f,-PlayerRotation);
	App->renderer->Blit(SupportCannonTex, cx - 6, cy + 46, NULL, 1.0f);

	return UPDATE_CONTINUE;
}

void ModulePlayer::MovementPlayer() {
	if (App->input->GetKey(SDL_SCANCODE_D) == KEY_REPEAT) {
		cx += speed;
	}

	if (App->input->GetKey(SDL_SCANCODE_A) == KEY_REPEAT) {
		cx -= speed;
	}

	if (App->input->GetKey(SDL_SCANCODE_DOWN) == KEY_REPEAT) {
		velo -= 1;
	}

	if (App->input->GetKey(SDL_SCANCODE_UP) == KEY_REPEAT) {
		velo += 1;
	}

	//if (App->input->GetKey(SDL_SCANCODE_S) == KEY_REPEAT) {
	//	App->player->position.y += 8;
	//}
	//if (App->input->GetKey(SDL_SCANCODE_W) == KEY_REPEAT) {
	//	App->player->position.y -= 8;
	//}

	if (App->input->GetKey(SDL_SCANCODE_RIGHT) == KEY_REPEAT) {
		PlayerRotation -= 1;
	}
	if (App->input->GetKey(SDL_SCANCODE_LEFT) == KEY_REPEAT) {
		PlayerRotation += 1;
	}
	if (PlayerRotation > 180) {
		PlayerRotation = 180;
	}
	if (PlayerRotation < 0) {
		PlayerRotation = 0;
	}

	if ((App->input->GetKey(SDL_SCANCODE_RETURN) == KEY_REPEAT) || (App->input->GetKey(SDL_SCANCODE_SPACE) == KEY_REPEAT)) {
		App->motor->NewBall(rad, mass, cx + 20, cy + 15, velo, PlayerRotation);
	}
	if (App->input->GetKey(SDL_SCANCODE_Q) == KEY_REPEAT) {
		//SDL_Rect owo{40, 493, 20, 20};
		App->motor->NewPlayer(PIXEL_TO_METERS(20), PIXEL_TO_METERS(20), 20000, cx + 20, cy +15 );
	}

	if (App->input->GetKey(SDL_SCANCODE_1) == KEY_REPEAT) {
		App->motor->moto = 1;
	}
	if (App->input->GetKey(SDL_SCANCODE_2) == KEY_REPEAT) {
		App->motor->moto = 2;
	}
	if (App->input->GetKey(SDL_SCANCODE_3) == KEY_REPEAT) {
		App->motor->moto = 3;
	}

	if (App->input->GetKey(SDL_SCANCODE_F) == KEY_DOWN) {
		if (App->motor->DragActive == true) {
			App->motor->DragActive = false;
		}
		else if (App->motor->DragActive == false) {
			App->motor->DragActive = true;
		}
	}
	if (App->input->GetKey(SDL_SCANCODE_G) == KEY_DOWN) {
		if (App->motor->LiftActive == true) {
			App->motor->LiftActive = false;
		}
		else if (App->motor->LiftActive == false) {
			App->motor->LiftActive = true;
		}
	}
	if (App->input->GetKey(SDL_SCANCODE_H) == KEY_DOWN) {
		if (App->motor->NewtonActive == true) {
			App->motor->NewtonActive = false;
		}
		else if (App->motor->NewtonActive == false) {
			App->motor->NewtonActive = true;
		}
	}
}
