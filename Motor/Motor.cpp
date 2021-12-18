#include "Globals.h"
#include "Application.h"
#include "Motor.h"
#include "math.h"

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
update_status Motor::PreUpdate()
{
	
	return UPDATE_CONTINUE;
}

update_status Motor::Update()
{
	// Step #0: Reset total acceleration and total accumulated force of the ball (clear old values)
	p2List_item<Ball*>* b = Balls.getFirst();

	while (b != NULL)
	{
		
		if (b->data->physics_enabled == true) {
			if(b->data->type==BALL){

				b->data->fx = b->data->fy = 0.0;
				b->data->ax = b->data->ay = 0.0;
				App->renderer->DrawCircle(b->data->x, b->data->y, b->data->rad, 255, 255, 255);
				ComputeForces(b->data, dt);
				if(DragActive==true){
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
					b->data->g = b->data->g *-1;
				}
			}
			if (b->data->type == PLAYER)
			{



			}

			if (b->data->type == PLAYER2)
			{



			}
		}
		b = b->next;
	}

	return UPDATE_CONTINUE;
}




// 
update_status Motor::PostUpdate()
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

Ball* Motor::NewBall(int rad, double mass, double x, double y, float v, float angle) 
{
	Ball* a = new Ball( rad,  mass,  x,  y, v, angle, BALL);
	Balls.add(a);
	return a;
}

Ball* Motor::NewPlayer(SDL_Rect* rect, double mass, double x, double y)
{
	Ball* a = new Ball(rect, mass, x, y, PLAYER);
	Balls.add(a);
	return a;
}

Ball* Motor::NewPlayer2(SDL_Rect* rect, double mass, double x, double y)
{
	Ball* a = new Ball(rect, mass, x, y, PLAYER2);
	Balls.add(a);
	return a;
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
		if ((b->data->vx < 0.3 && b->data->vy < 0.3) || b->data->x > 1024)
		{
			b->data->physics_enabled = false;
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