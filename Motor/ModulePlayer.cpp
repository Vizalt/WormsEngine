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
	
	PlayerTex = App->textures->Load("pinball/player.png");
	CannonTex = App->textures->Load("pinball/CannonTex.png");
	SupportCannonTex= App->textures->Load("pinball/SupportCannonTex.png");
	
	position.x = 40;
	position.y = 593;

	cy = PIXEL_TO_METERS(position.y);
	cx = PIXEL_TO_METERS(position.x);

	App->motor->NewPlayer(PIXEL_TO_METERS(50), PIXEL_TO_METERS(50), 20000, cx, cy+15);

	position.x = 100;
	position.y = 90;

	cy = PIXEL_TO_METERS(position.y);
	cx = PIXEL_TO_METERS(position.x);

	App->motor->NewPlayer2(PIXEL_TO_METERS(50), PIXEL_TO_METERS(50), 20000, cx, cy + 15);

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
	/*App->renderer->Blit(CannonTex, cx-15, cy+8, NULL, 1.0f,-PlayerRotation);
	App->renderer->Blit(SupportCannonTex, cx - 6, cy + 46, NULL, 1.0f);*/


	p2List_item<Ball*>* b = App->motor->Balls.getFirst();

	while (b != NULL)
	{

		if (b->data->type == PLAYER)
		{
			int xp = b->data->x, yp = b->data->y;
			SDL_Rect owo{ b->data->x-5,b->data->y-4,b->data->w, b->data->h };
			App->renderer->DrawQuad(owo, 255, 20, 20,255,  false);
			App->renderer->Blit(CannonTex, xp - 15, yp-10 , NULL, 1.0f, -PlayerRotation);
			App->renderer->Blit(SupportCannonTex, xp - 6, yp + 30, NULL, 1.0f);
			//ComputeForces(b->data, dt);
			//newton_law(b->data, dt);
			if (turn == 1) {
				if (App->input->GetKey(SDL_SCANCODE_A) == KEY_REPEAT) {
					//AddForce(b->data,10,0);
					b->data->vx -= 2;
				}

				if (App->input->GetKey(SDL_SCANCODE_D) == KEY_REPEAT) {
					//AddForce(b->data, -10, 0);
					b->data->vx += 2;
				}
				if ((App->input->GetKey(SDL_SCANCODE_RETURN) == KEY_DOWN) || (App->input->GetKey(SDL_SCANCODE_SPACE) == KEY_DOWN)) {
					App->motor->NewBall(rad, mass, xp + 20, yp + 15, velo, PlayerRotation);
					turn = 2;
				}
			}
		}

		else if (b->data->type == PLAYER2)
		{
			int xp = b->data->x, yp = b->data->y;
			SDL_Rect uwu{ b->data->x - 5,b->data->y - 4,b->data->w, b->data->h };
			App->renderer->DrawQuad(uwu, 255, 20, 20, 255, false);
			App->renderer->Blit(CannonTex, xp - 15, yp - 10, NULL, 1.0f, PlayerRotation2 );
			App->renderer->Blit(SupportCannonTex, xp - 6, yp-5 , NULL, 1.0f, 180);
			//ComputeForces(b->data, dt);
			//newton_law(b->data, dt);
			if (turn == 2) {
				if (App->input->GetKey(SDL_SCANCODE_A) == KEY_REPEAT) {
					//AddForce(b->data,10,0);
					b->data->vx -= 2;
				}

				if (App->input->GetKey(SDL_SCANCODE_D) == KEY_REPEAT) {
					//AddForce(b->data, -10, 0);
					b->data->vx += 2;
				}
				if ((App->input->GetKey(SDL_SCANCODE_RETURN) == KEY_DOWN) || (App->input->GetKey(SDL_SCANCODE_SPACE) == KEY_DOWN)) {
					App->motor->NewBall(rad, mass, xp + 20, yp + 15, velo, -PlayerRotation2);
					turn = 1;
				}
			}

		}
		if (b->data->type == PLAYER || b->data->type == PLAYER2)
		{
			if (b->data->x < 0 )
			{
				b->data->vx = -b->data->vx;
			}
			if ( b->data->x > 1000)
			{
				b->data->vx = -b->data->vx;
			}
		}

		b = b->next;
	}

	return UPDATE_CONTINUE;
}

void ModulePlayer::MovementPlayer() {
	/*if (App->input->GetKey(SDL_SCANCODE_D) == KEY_REPEAT) {
		cx += speed;
	}

	if (App->input->GetKey(SDL_SCANCODE_A) == KEY_REPEAT) {
		cx -= speed;
	}*/

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

	if (turn == 1)
	{
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
	}
	if (turn == 2)
	{
		if (App->input->GetKey(SDL_SCANCODE_RIGHT) == KEY_REPEAT) {
			PlayerRotation2 += 1;
		}
		if (App->input->GetKey(SDL_SCANCODE_LEFT) == KEY_REPEAT) {
			PlayerRotation2 -= 1;
		}
		if (PlayerRotation2 < 0) {
			PlayerRotation2 = 0;
		}
		if (PlayerRotation2 > 180) {
			PlayerRotation2 = 180;
		}
	}

	/*if ((App->input->GetKey(SDL_SCANCODE_RETURN) == KEY_REPEAT) || (App->input->GetKey(SDL_SCANCODE_SPACE) == KEY_REPEAT)) {
		App->motor->NewBall(rad, mass, cx + 20, cy + 15, velo, PlayerRotation);
	}*/
	if (App->input->GetKey(SDL_SCANCODE_Q) == KEY_REPEAT) {
		//SDL_Rect owo{40, 493, 20, 20};
		App->motor->NewPlayer(PIXEL_TO_METERS(50), PIXEL_TO_METERS(50), 20000, cx , cy +15 );
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

	if (App->input->GetKey(SDL_SCANCODE_Z) == KEY_DOWN)
	{
		turn = 1;
	}
	if (App->input->GetKey(SDL_SCANCODE_X) == KEY_DOWN)
	{
		turn = 2;
	}
}

//void ModulePlayer::MovementPlayer2() {
//	/*if (App->input->GetKey(SDL_SCANCODE_D) == KEY_REPEAT) {
//		cx += speed;
//	}
//
//	if (App->input->GetKey(SDL_SCANCODE_A) == KEY_REPEAT) {
//		cx -= speed;
//	}*/
//
//	if (App->input->GetKey(SDL_SCANCODE_DOWN) == KEY_REPEAT) {
//		velo -= 1;
//	}
//
//	if (App->input->GetKey(SDL_SCANCODE_UP) == KEY_REPEAT) {
//		velo += 1;
//	}
//
//	//if (App->input->GetKey(SDL_SCANCODE_S) == KEY_REPEAT) {
//	//	App->player->position.y += 8;
//	//}
//	//if (App->input->GetKey(SDL_SCANCODE_W) == KEY_REPEAT) {
//	//	App->player->position.y -= 8;
//	//}
//	if (turn == 1) 
//	{
//		if (App->input->GetKey(SDL_SCANCODE_RIGHT) == KEY_REPEAT) {
//			PlayerRotation -= 1;
//		}
//		if (App->input->GetKey(SDL_SCANCODE_LEFT) == KEY_REPEAT) {
//			PlayerRotation += 1;
//		}
//		if (PlayerRotation > 180) {
//			PlayerRotation = 180;
//		}
//		if (PlayerRotation < 0) {
//			PlayerRotation = 0;
//		}
//	}
//	if (turn == 2)
//	{
//		if (App->input->GetKey(SDL_SCANCODE_RIGHT) == KEY_REPEAT) {
//			PlayerRotation2 += 1;
//		}
//		if (App->input->GetKey(SDL_SCANCODE_LEFT) == KEY_REPEAT) {
//			PlayerRotation2 -= 1;
//		}
//		if (PlayerRotation2 > 180) {
//			PlayerRotation2 = 180;
//		}
//		if (PlayerRotation2 < 0) {
//			PlayerRotation2 = 0;
//		}
//	
//	}
//	/*if ((App->input->GetKey(SDL_SCANCODE_RETURN) == KEY_REPEAT) || (App->input->GetKey(SDL_SCANCODE_SPACE) == KEY_REPEAT)) {
//		App->motor->NewBall(rad, mass, cx + 20, cy + 15, velo, PlayerRotation);
//	}*/
//	if (App->input->GetKey(SDL_SCANCODE_Q) == KEY_REPEAT) {
//		//SDL_Rect owo{40, 493, 20, 20};
//		App->motor->NewPlayer(PIXEL_TO_METERS(50), PIXEL_TO_METERS(50), 20000, cx, cy + 15);
//	}
//
//	if (App->input->GetKey(SDL_SCANCODE_1) == KEY_REPEAT) {
//		App->motor->moto = 1;
//	}
//	if (App->input->GetKey(SDL_SCANCODE_2) == KEY_REPEAT) {
//		App->motor->moto = 2;
//	}
//	if (App->input->GetKey(SDL_SCANCODE_3) == KEY_REPEAT) {
//		App->motor->moto = 3;
//	}
//
//	if (App->input->GetKey(SDL_SCANCODE_F) == KEY_DOWN) {
//		if (App->motor->DragActive == true) {
//			App->motor->DragActive = false;
//		}
//		else if (App->motor->DragActive == false) {
//			App->motor->DragActive = true;
//		}
//	}
//	if (App->input->GetKey(SDL_SCANCODE_G) == KEY_DOWN) {
//		if (App->motor->LiftActive == true) {
//			App->motor->LiftActive = false;
//		}
//		else if (App->motor->LiftActive == false) {
//			App->motor->LiftActive = true;
//		}
//	}
//	if (App->input->GetKey(SDL_SCANCODE_H) == KEY_DOWN) {
//		if (App->motor->NewtonActive == true) {
//			App->motor->NewtonActive = false;
//		}
//		else if (App->motor->NewtonActive == false) {
//			App->motor->NewtonActive = true;
//		}
//	}
//}