#include "Globals.h"
#include "Application.h"
#include "ModulePlayer.h"
#include "ModuleSceneIntro.h"
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
	
	
	CannonTex = App->textures->Load("pinball/CannonTex.png");
	CannonTex2 = App->textures->Load("pinball/Cannon2Tex.png");
	SupportCannonTex= App->textures->Load("pinball/SupportCannonTex.png");
	
	position.x = 40;
	position.y = 593;

	cy = PIXEL_TO_METERS(position.y);
	cx = PIXEL_TO_METERS(position.x);

	App->motor->NewPlayer(PIXEL_TO_METERS(50), PIXEL_TO_METERS(50), 20000, cx, cy+15);
	Player1Coll = App->coll->AddCollider({cx, cy + 15,w1, w1 }, Collider::Type::PLAYER, this);
	 
	position.x = 100;
	position.y = 90;

	cy = PIXEL_TO_METERS(position.y);
	cx = PIXEL_TO_METERS(position.x);

	App->motor->NewPlayer2(PIXEL_TO_METERS(50), PIXEL_TO_METERS(50), 20000, cx, cy + 15);
	Player2Coll = App->coll->AddCollider({ cx, cy + 15,w1, w1 }, Collider::Type::PLAYER2, this);

	return true;
}

// Unload assets
bool ModulePlayer::CleanUp()
{
	LOG("Unloading player");

	return true;
}

// Update: draw background
bool ModulePlayer::Update()
{
	if (App->scene_intro->p1Win == false && App->scene_intro->p2Win == false) {
			MovementPlayer();
	
	
		/*SDL_Rect player = { position.x, position.y, 50, 50 };*/

		/*App->renderer->Blit(PlayerTex, position.x, position.y, NULL, 1.0f);*/
		/*App->renderer->Blit(CannonTex, cx-15, cy+8, NULL, 1.0f,-PlayerRotation);
		App->renderer->Blit(SupportCannonTex, cx - 6, cy + 46, NULL, 1.0f);*/


		p2List_item<Ball*>* b = App->motor->Balls.getFirst();

		while (b != NULL)
		{
			if (App->scene_intro->p1Win == false && App->scene_intro->p2Win == false) {

				if (b->data->type == PLAYER)
				{


					if (turn == 1) {
					
						if (App->input->GetKey(SDL_SCANCODE_A) == KEY_REPEAT) {
							App->motor->AddForce(b->data, -2, 0);
							//b->data->vx -= 2;
						}

						if (App->input->GetKey(SDL_SCANCODE_D) == KEY_REPEAT) {
							App->motor->AddForce(b->data, 2, 0);
							//b->data->vx += 2;
						}
						if ((App->input->GetKey(SDL_SCANCODE_SPACE) == KEY_DOWN) && shot1 == true) {
							App->motor->NewBall(rad, mass, b->data->x + 20, b->data->y + 15, velo, PlayerRotation);
							turn = 2;
							App->coll->matrix[Collider::Type::BALL][Collider::Type::PLAYER] = false;
							App->coll->matrix[Collider::Type::BALL][Collider::Type::PLAYER2] = true;
							App->coll->matrix[Collider::Type::PLAYER][Collider::Type::BALL] = false;
							App->coll->matrix[Collider::Type::PLAYER2][Collider::Type::BALL] = true;

							b->data->physics_enabled = false;
							shot2 = false;
						}
						if (shot1 == false)
						{
							b->data->vx = b->data->vy = 0.0f;
							b->data->physics_enabled = true;
							shot1 = true;
						}

					}
				}
			
				if (b->data->type == PLAYER2)
				{

					if (turn == 2) {
					
						if (App->input->GetKey(SDL_SCANCODE_A) == KEY_REPEAT) {
							App->motor->AddForce(b->data, -2, 0);
							//b->data->vx -= 2;
						}

						if (App->input->GetKey(SDL_SCANCODE_D) == KEY_REPEAT) {
							App->motor->AddForce(b->data, 2, 0);
							//b->data->vx += 2;
						}
						if ((App->input->GetKey(SDL_SCANCODE_SPACE) == KEY_DOWN) && shot2 == true) {
							App->motor->NewBall(rad, mass, b->data->x + 20, b->data->y + 15, velo, -PlayerRotation2);
							shot1 = false;
							b->data->physics_enabled = false;
							turn = 1;
							App->coll->matrix[Collider::Type::BALL][Collider::Type::PLAYER] = true;
							App->coll->matrix[Collider::Type::BALL][Collider::Type::PLAYER2] = false;
							App->coll->matrix[Collider::Type::PLAYER][Collider::Type::BALL] = true;
							App->coll->matrix[Collider::Type::PLAYER2][Collider::Type::BALL] = false;
							
						}
						if (shot2 == false)
						{
							b->data->vx = b->data->vy = 0.0f;
							b->data->physics_enabled = true;
							shot2 = true;
						}

					}

				}

			}
		

			b = b->next;
		}
	}
	else {
		if (App->input->GetKey(SDL_SCANCODE_SPACE) == KEY_DOWN) {
			App->scene_intro->p1Win = false;
			App->scene_intro->p2Win = false;
		}
	}
	return true;
}


//void ModulePlayer::OnCollision(Collider* c1, Collider* c2) {
//	p2List_item<Ball*>* b = App->motor->Balls.getFirst();
//	while (b != NULL) {
//		if (c1->type == Collider::Type::BALL && c2->type == Collider::Type::PLAYER) {
//			App->scene_intro->p2Win = true;
//		}
//		if (c1->type == Collider::Type::BALL && c2->type == Collider::Type::PLAYER2) {
//			App->scene_intro->p1Win = true;
//		}
//		b = b->next;
//	}
//}


void ModulePlayer::MovementPlayer() {

	if (App->input->GetKey(SDL_SCANCODE_DOWN) == KEY_REPEAT) {
		velo -= 1;
	}

	if (App->input->GetKey(SDL_SCANCODE_UP) == KEY_REPEAT) {
		velo += 1;
	}

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

