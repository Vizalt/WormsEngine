#include "Globals.h"
#include "Application.h"
#include "Motor.h"
#include "math.h"
#include "ModuleCollisions.h"
#include "ModuleSceneIntro.h"
#include <iostream>
#include <stdlib.h>
// TODO 1: Include Box 2 header and library

Motor::Motor(Application* app, bool start_enabled) : Module(app, start_enabled)
{
	debug = true;
}

// Destructor
Motor::~Motor()
{
}

bool Motor::Start()
{
	LOG("Creating Physics 2D environment");
	
	

	//BALL = App->textures->Load("pinball/sol.png");
	return true;
}

// 
bool Motor::PreUpdate()
{
	
	return UPDATE_CONTINUE;
}

bool Motor::Update()
{
	// Step #0: Reset total acceleration and total accumulated force of the ball (clear old values)
	p2List_item<Ball*>* b = Balls.getFirst();
	p2List_item<Box*>* c = Boxes.getFirst();
	while (b != NULL)
	{
		
		
			if(b->data->type==BALL){

				App->renderer->DrawCircle(b->data->x, b->data->y, b->data->rad, 255, 255, 255);
				if (b->data->physics_enabled == true) {
					b->data->fx = b->data->fy = 0.0;
					b->data->ax = b->data->ay = 0.0;
					b->data->ball_collider->SetPos(b->data->x - b->data->rad, b->data->y - b->data->rad);
					
					
					ComputeForces(b->data, dt);
					if (DragActive == true) {
						DragForce(b->data);
						integrators(b->data, dt);
					}
					if (LiftActive == true) {
						LiftForce(b->data);
						integrators(b->data, dt);
					}
					if (NewtonActive == true) {
						newton_law(b->data, dt);
						integrators(b->data, dt);
					}

					if ((b->data->y + b->data->rad + 5 > ground.y) || (b->data->y + b->data->rad + 5 <= 135))
					{
						// For now, just stop the ball when it reaches the ground.

						b->data->vx = b->data->vx * 0.9f;
						b->data->vy = -b->data->vy * 0.8f;
						b->data->ax = -b->data->ay;
						//	ball.physics_enabled = false;
					}

					if (b->data->other == true && b->data->y <= 379)
					{
						b->data->other = false;
						b->data->g = -b->data->g;
					}
					if (b->data->other == false && b->data->y >= 379)
					{
						b->data->other = true;
						b->data->g = b->data->g * -1;
					}
					Colls(b->data);
				}
			}
			if (b->data->type == PLAYER)
			{ 
				int xp = b->data->x, yp = b->data->y;
				SDL_Rect owo{ b->data->x - 5,b->data->y - 4,b->data->w, b->data->h };
				App->renderer->DrawQuad(owo, 255, 20, 20, 255, false);
				App->player->Player1Coll->SetPos(b->data->x - 5, b->data->y - 4);
				App->renderer->Blit(App->player->CannonTex, xp - 15, yp - 10, NULL, 1.0f, -App->player->PlayerRotation);
				App->renderer->Blit(App->player->SupportCannonTex, xp - 6, yp + 30, NULL, 1.0f);

				if (b->data->physics_enabled == true)
				{
					b->data->fx = b->data->fy = 0.0;
					b->data->ax = b->data->ay = 0.0;
					integrators(b->data, dt);
				}
			}

			if (b->data->type == PLAYER2)
			{

				int xp = b->data->x, yp = b->data->y;
				SDL_Rect uwu{ b->data->x - 5,b->data->y - 4,b->data->w, b->data->h };
				App->player->Player2Coll->SetPos(b->data->x - 5, b->data->y - 4);
				App->renderer->DrawQuad(uwu, 255, 20, 20, 255, false);
				App->renderer->Blit(App->player->CannonTex2, xp - 15, yp - 10, NULL, 1.0f, App->player->PlayerRotation2);
				App->renderer->Blit(App->player->SupportCannonTex, xp - 6, yp - 5, NULL, 1.0f, 180);

				if (b->data->physics_enabled == true)
				{
					b->data->fx = b->data->fy = 0.0;
					b->data->ax = b->data->ay = 0.0;
					integrators(b->data, dt);
				}
			}
			if (b->data->type == PLAYER || b->data->type == PLAYER2)
			{
				if (b->data->x < 0)
				{
					b->data->vx = -b->data->vx;
				}
				if (b->data->x > 1000)
				{
					b->data->vx = -b->data->vx;
				}
			}

			
		
		b = b->next;
	}

	while (c != NULL) {


		App->renderer->DrawQuad(c->data->rect, c->data->r, c->data->g, c->data->b);

		c = c->next;
	}

	return UPDATE_CONTINUE;
}




// 
bool Motor::PostUpdate()
{

	adios();
	if(App->input->GetKey(SDL_SCANCODE_F1) == KEY_DOWN)
		debug = !debug;

	if(!debug)
		return UPDATE_CONTINUE;

	return UPDATE_CONTINUE;
}

double Motor::CalculateModule(float x, float y) {
	double dir;
	dir = sqrt((x * x) + (y * y));

	return dir;
}

void Motor::Unitari(float x, float y) {
	double m;
	m = CalculateModule(x, y);
	x = x / m;
	y = y / m;
}

void Motor::DragForce(Ball* a) {
	float vxr = a->vx - atmosphere.windx;
	float vyr = a->vy - atmosphere.windy;
	double speed = CalculateModule(vxr, vyr);
	double fdrag = 0.5 * atmosphere.density * speed * speed * a->surface * a->cd;
	Unitari(vxr, vyr);
	double fdx = -vxr * fdrag; //Drag is antiparalel to the ball velocity
	double fdy = -vyr * fdrag;
	a->fx += fdx;
	a->fy += fdy;
}

void Motor::LiftForce(Ball* a) {
	float vxr = a->vx - atmosphere.windx;
	float vyr = a->vy - atmosphere.windy;
	double speed = CalculateModule(vxr, vyr);
	double flift = 0.5 * atmosphere.density * speed * speed * a->surface * a->cl;
	Unitari(vxr, vyr);
	double flx = vxr * flift; //Lift is perpendicular to the ball velocity
	double fly = vyr * flift;
	a->fx += flx;
	a->fy += fly;
}

// Integration scheme: Velocity Verlet
// You should modularise all your algorithms into subroutines. Including the ones to compute forces.
//void Motor::integrator_velocity_verlet(Ball* ball, float dt)
//{
//	ball->x += ball->vx * dt + 0.5 * ball->ax * dt * dt;
//	ball->y += ball->vy * dt + 0.5 * ball->ay * dt * dt;
//	ball->vx += ball->ax * dt;
//	ball->vy += ball->ay * dt;
//	//LOG("VX= %d, VY= %d ", ball->vx, ball->vy);
//}


// Called before quitting
bool Motor::CleanUp()
{
	LOG("Destroying physics world");

	// Delete the whole physics world!

	return true;
}

void Motor::newton_law(Ball* ball, float dt)
{

	ball->ax = ball->fx / ball->mass;
	ball->ay = ball->fy / ball->mass;
	//LOG("VX= %d, VY= %d ", ball->vx, ball->vy);

	
}

void Motor::ComputeForces(Ball* ball, float dt)
{

	// Compute Gravity force
	 ball->fgx = ball->mass * 0.0;
	 ball->fgy = ball->mass * ball->g; // Let's assume gravity is constant and downwards

	// Add gravity force to the total accumulated force of the ball
	ball->fx += ball->fgx;
	ball->fy += ball->fgy;

	//LOG("VX= %d, VY= %d ", ball->vx, ball->vy);
}

void Motor::NewBall(int rad, double mass, double x, double y, float v, float angle)
{
	Collider* col = App->coll->AddCollider({int(x - rad), int(y - rad), rad * 2, rad * 2 }, Collider::Type::BALL, this);
	Ball* a = new Ball( rad,  mass,  x,  y, v, angle, BALL, col);
	Balls.add(a);
	//return a;
}

void Motor::NewPlayer(double w, double h, double mass, double x, double y)
{
	Ball* a = new Ball(w,h, mass, x, y, PLAYER);
	Balls.add(a);
	//return a;
}

void Motor::NewPlayer2(double w, double h, double mass, double x, double y)
{
	Ball* a = new Ball(w, h, mass, x, y, PLAYER2);
	Balls.add(a);
	///return a;
}

//bool Motor::checkCollision(Ball* a, SDL_Rect b) {
//
//}

void Motor::AddForce(Ball* obj, float fx, float fy) {
	obj->vx += fx;
	obj->vy += fy;
}

void Motor::adios()
{

	p2List_item<Ball*>* b = Balls.getFirst();
	bool exit = false;
	
	while (b != NULL && !exit)
	{
		if (((abs(b->data->vx) < 0.3 && abs(b->data->vy < 0.3)) || b->data->x > 1024 || b->data->x < -10)&&b->data->type==BALL)
		{
			b->data->physics_enabled = false;
			App->coll->RemoveColl(b->data->ball_collider);
			Ball* a = b->data;
			Balls.del(Balls.findNode(a));
			delete a;
			exit = true;
			
			
		}
		else
		{
			b = b->next;
		}

	}

}

void Motor::integrators(Ball* ball, float dt)
{
	switch (moto)
	{
	case 1:  //Verlet
		ball->x += ball->vx * dt + 0.5 * ball->ax * dt * dt;
		ball->y += ball->vy * dt + 0.5 * ball->ay * dt * dt;
		ball->vx += ball->ax * dt;
		ball->vy += ball->ay * dt;

		break;

	case 2: //integrator_bw_euler

		ball->x = ball->x + ball->vx * dt;
		ball->y = ball->y + ball->vy * dt;
		ball->vx = ball->vx+ ball->ax * dt;
		ball->vy = ball->vy + ball->ay * dt;

		break;

	case 3:  //integrator_fw_euler

		ball->vx = ball->vx + ball->ax * dt;
		ball->vy = ball->vy + ball->ay * dt;
		
		ball->x = ball->x + ball->vx * dt;
		ball->y = ball->y + ball->vy * dt;

		break;


	}
}

void Motor::CreateBoxes(SDL_Rect rect, int r, int g, int b) {
	Box* c = new Box(rect, r, g, b);
	Boxes.add(c);
	//return c;
}

void Motor::OnCollision(Collider* c1, Collider* c2) {
	p2List_item<Ball*>* b = Balls.getFirst();
	while (b != NULL) {
		if (c1->type == Collider::Type::BALL && c2->type == Collider::Type::PLAYER) {
			App->scene_intro->p2Win = true;
		}
		if (c1->type == Collider::Type::BALL && c2->type == Collider::Type::PLAYER2) {
			App->scene_intro->p1Win = true;
		}
		b = b->next;
	}
	
}

void Motor::Colls(Ball* b)
{
	///box1
	int rig = App->scene_intro->b1x + App->scene_intro->b1w;
	int dw = App->scene_intro->b1y + App->scene_intro->b1h;

	if (b->x < rig &&
		(b->x + b->rad) > App->scene_intro->b1x &&
		b->y <dw &&
		(b->y + b->rad + b->y)   > App->scene_intro->b1y) {

		if (b->x < (rig))
		{
			b->vy = b->vy * 0.9;
			b->vx = -b->vx * 0.9;
			b->ax = -b->ax;
		}
		//izq
		if ((b->x + b->x + b->rad) > App->scene_intro->b1x)
		{
			b->vy = b->vy * 0.9;
			b->vx = -b->vx * 0.9;
			b->ax = -b->ax;
		}
		////dw
		if (b->y < (dw))
		{
			b->vy = -b->vy * 0.9;
			b->vx = b->vx * 0.9;
			b->ay = -b->ay;
		}
		////up
		if ((b->y + b->rad + b->y) > App->scene_intro->b1y)
		{
			b->vy = b->vy * 0.9;
			b->vx = b->vx * 0.9;
			b->ay = -b->ay;
		}
	}

	//box2
	int rig2 = App->scene_intro->b2x + App->scene_intro->b2w;
	int dw2 = App->scene_intro->b2y + App->scene_intro->b2h;

	if (b->x < rig2 &&
		(b->x + b->rad) > App->scene_intro->b2x &&
		b->y <dw2 &&
		(b->y + b->rad + b->y)   > App->scene_intro->b2y) {

		if (b->x < (rig2))
		{
			b->vy = b->vy * 0.9;
			b->vx = -b->vx * 0.9;
			b->ax = -b->ax;
		}
		//izq
		if ((b->x + b->x + b->rad) > App->scene_intro->b2x)
		{
			b->vy = b->vy * 0.9;
			b->vx = -b->vx * 0.9;
			b->ax = -b->ax;
		}
		////dw
		if (b->y < (dw2))
		{
			b->vy = -b->vy * 0.9;
			b->vx = b->vx * 0.9;
			b->ay = -b->ay;
		}
		////up
		if ((b->y + b->rad + b->y) > App->scene_intro->b2y)
		{
			b->vy = b->vy * 0.9;
			b->vx = b->vx * 0.9;
			b->ay = -b->ay;
		}
	}

	//box3
	int rig3 = App->scene_intro->b3x + App->scene_intro->b3w;
	int dw3 = App->scene_intro->b3y + App->scene_intro->b3h;

	if (b->x < rig3 &&
		(b->x + b->rad) > App->scene_intro->b3x &&
		b->y <dw3 &&
		(b->y + b->rad + b->y)   > App->scene_intro->b3y) {

		if (b->x < (rig3))
		{
			b->vy = b->vy * 0.9;
			b->vx = -b->vx * 0.9;
			b->ax = -b->ax;
		}
		//izq
		if ((b->x + b->x + b->rad) > App->scene_intro->b3x)
		{
			b->vy = b->vy * 0.9;
			b->vx = -b->vx * 0.9;
			b->ax = -b->ax;
		}
		////dw
		if (b->y < (dw3))
		{
			b->vy = -b->vy * 0.9;
			b->vx = b->vx * 0.9;
			b->ay = -b->ay;
		}
		////up
		if ((b->y + b->rad + b->y) > App->scene_intro->b3y)
		{
			b->vy = b->vy * 0.9;
			b->vx = b->vx * 0.9;
			b->ay = -b->ay;
		}
	}

	//box4
	int rig4 = App->scene_intro->b4x + App->scene_intro->b4w;
	int dw4 = App->scene_intro->b4y + App->scene_intro->b4h;

	if (b->x < rig4 &&
		(b->x + b->rad) > App->scene_intro->b4x &&
		b->y <dw4 &&
		(b->y + b->rad + b->y)   > App->scene_intro->b4y) {

		if (b->x < (rig4))
		{
			b->vy = b->vy * 0.9;
			b->vx = -b->vx * 0.9;
			b->ax = -b->ax;
		}
		//izq
		if ((b->x + b->x + b->rad) > App->scene_intro->b4x)
		{
			b->vy = b->vy * 0.9;
			b->vx = -b->vx * 0.9;
			b->ax = -b->ax;
		}
		////dw
		if (b->y < (dw4))
		{
			b->vy = -b->vy * 0.9;
			b->vx = b->vx * 0.9;
			b->ay = -b->ay;
		}
		////up
		if ((b->y + b->rad + b->y) > App->scene_intro->b4y)
		{
			b->vy = b->vy * 0.9;
			b->vx = b->vx * 0.9;
			b->ay = -b->ay;
		}
	}

}