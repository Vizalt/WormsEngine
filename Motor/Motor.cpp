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
	
	//// Set physics properties of the ball
	//ball.mass = 10; // kg
	////ball.surface = 2; // m^2
	////ball.cd = 0.4;
	////ball.cl = 1.2;
	//ball.rad = 10;
	//// Set initial position and velocity of the ball
	//ball.x = ball.y = 30.0;
	//ball.vx = 30;
	//ball.vy = 10;

	BALL = App->textures->Load("pinball/sol.png");
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
			b->data->fx = b->data->fy = 0.0;
			b->data->ax = b->data->ay = 0.0;
			App->renderer->DrawCircle(b->data->x, b->data->y, b->data->rad, 255, 0, 66);
			ComputeForces(b->data, dt);
			// Compute Aerodynamic Lift & Drag forces
			float vxr = b->data->vx - atmosphere.windx;
			float vyr = b->data->vy - atmosphere.windy;
			double speed = CalculateModule(vxr, vyr);
			double fdrag = 0.5 * atmosphere.density * speed * speed * b->data->surface * b->data->cd;
			Unitari(vxr, vyr, speed);
			double fdx = -vxr*fdrag; // Let's assume Drag is aligned with x-axis (in your game, generalize this)
			double fdy = -vyr * fdrag;
			// Add gravity force to the total accumulated force of the ball
			b->data->fx += fdx;
			b->data->fy += fdy;
			//b->data->fy += fdy;

			newton_law(b->data, dt);
			integrator_velocity_verlet(b->data, dt);


			if (b->data->y + b->data->rad + 5 > ground.y)
			{
				// For now, just stop the ball when it reaches the ground.
				//ball.vx = ball.vy = 0.0;
				/*ball.ax = ball.ay = 0.0;
				ball.fx = ball.fy = 0.0;*/
				b->data->vx = b->data->vx * 0.9f;
				b->data->vy = -b->data->vy * 0.9f;
				b->data->ax = -b->data->ay;
				//	ball.physics_enabled = false;
			}
		}

		b = b->next;
	}
	//App->renderer->Blit(BALL, ball.x, ball.y, NULL, 1.0f);
	
	//if(b->data->physics_enabled==true){
	//Balls. = ball.fy = 0.0;
	//balls.ax = ball.ay = 0.0;
	//// Step #1: Compute forces

	//ComputeForces(ball, dt);

	//// Step #2: 2nd Newton's Law: SUM_Forces = mass * accel --> accel = SUM_Forces / mass
	//newton_law(ball, dt);
	//// Step #3: Integrate --> from accel to new velocity & new position. 
	//integrator_velocity_verlet(ball, dt);
	////integrator_fw_euler(ball,dt);

	//// Step #4: solve collisions
	//if (ball.y+ball.rad+5> ground.y)
	//{
	//	// For now, just stop the ball when it reaches the ground.
	//	//ball.vx = ball.vy = 0.0;
	//	/*ball.ax = ball.ay = 0.0;
	//	ball.fx = ball.fy = 0.0;*/
	//	ball.vy = -ball.vy*0.9f;
	//	ball.vx = ball.vx * 0.9f;
	//	ball.ay = -ball.ay;
	////	ball.physics_enabled = false;
	//}
	//}
	return UPDATE_CONTINUE;
}




// 
update_status Motor::PostUpdate()
{
	


	if(App->input->GetKey(SDL_SCANCODE_F1) == KEY_DOWN)
		debug = !debug;

	if(!debug)
		return UPDATE_CONTINUE;




	return UPDATE_CONTINUE;
}

double Motor::CalculateModule(float x, float y) {
	double vel;
	vel = sqrt((x * x) + (y * y));

	return vel;
}

void Motor::Unitari(float x, float y, double m) {
	x = x / m;
	y = y / m;
}

// Integration scheme: Velocity Verlet
// You should modularise all your algorithms into subroutines. Including the ones to compute forces.
void Motor::integrator_velocity_verlet(Ball* ball, float dt)
{
	ball->x += ball->vx * dt + 0.5 * ball->ax * dt * dt;
	ball->y += ball->vy * dt + 0.5 * ball->ay * dt * dt;
	ball->vx += ball->ax * dt;
	ball->vy += ball->ay * dt;
	LOG("VX= %d, VY= %d ", ball->vx, ball->vy);
}


//void Motor::integrator_bw_euler(Ball* ball, float dt)
//{
//	ball.x = ball.x + ball.vx * dt;
//	ball.y = ball.y + ball.vy * dt;
//	ball.vx = ball.vx+ ball.ax * dt;
//	ball.vy = ball.vy + ball.ay * dt;
//	LOG("VX= %d, VY= %d ", ball.vx, ball.vy);
//}
//
//void Motor::integrator_fw_euler(Ball* ball, float dt)
//{
//	
//	ball.vx = ball.vx + ball.ax * dt;
//	ball.vy = ball.vy + ball.ay * dt;
//
//	ball.x = ball.x + ball.vx * dt;
//	ball.y = ball.y + ball.vy * dt;
//
//	LOG("VX= %d, VY= %d ", ball.vx, ball.vy);
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
	LOG("VX= %d, VY= %d ", ball->vx, ball->vy);

	
}

void Motor::ComputeForces(Ball* ball, float dt)
{

	// Compute Gravity force
	 ball->fgx = ball->mass * 0.0;
	 ball->fgy = ball->mass * g; // Let's assume gravity is constant and downwards

	// Add gravity force to the total accumulated force of the ball
	ball->fx += ball->fgx;
	ball->fy += ball->fgy;

	LOG("VX= %d, VY= %d ", ball->vx, ball->vy);
}

Ball* Motor::NewBall(int rad, double mass, double x, double y, float v, float angle) 
{
	Ball* a = new Ball( rad,  mass,  x,  y, v, angle);
	Balls.add(a);
	return a;
}