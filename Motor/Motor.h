#pragma once
#include "Module.h"
#include "Globals.h"
#include "Animation.h"
#include "p2Point.h"

//enum
//{
//	VERLET
//	EULER
//
//
//};
enum types
{
	PLAYER,
	PLAYER2,
	BALL
};

class Ball
{
public:
	// Position
	// You could also use an array/vector
	
	types type;

	double x=0;
	double y = 0;

	// Velocity
	float vx = 0;
	float vy = 0;

	// Acceleration
	double ax = 0;
	double ay = 0;

	// Force (total) applied to the ball
	double fx = 0;
	double fy = 0;

	double fgx = 0;
	double fgy = 0;
	// Mass
	double mass;

	// Aerodynamics stuff
	double surface; // Effective wet surface
	double cl = 0.9; // Lift coefficient
	double cd = 0.9; // Drag coefficient

	float g = 280.0f;
	bool other = true;
	// Has physics enabled?
	bool physics_enabled = true;

	int rad = 0;

	SDL_Rect rectan;

//	Ball* NewBall(int rad, double mass, double x, double y, float v);

	Ball(int rad, double mass, double x, double y, float v, float angle, types ty)
	{
		this->rad = rad;
		this->mass = mass;
		this->surface = 3.14 * rad;
		this->x = x;
		this->y = y;
		this->vx = v * cos(-angle * DEGTORAD);
		this->vy = v * sin(-angle * DEGTORAD);
		this->type = ty;
	}

	Ball(SDL_Rect rect, double mass, double x, double y, types ty)
	{
		this->rectan = rect;
		this->mass = mass;
		this->surface = 3.14 * rad;
		this->x = x;
		this->y = y;
		this->type = ty;
	}



	~Ball()
	{}

};
//a
class Atmosphere
{
public:

	float windx = 1.0;
	float windy = 1.0;

	float density = 0.225;
};

struct Ground {
	int x = 0;
	int y = 650;
};

class Box {
public:
	float x;
	float y;
	float w;
	float h;

	Box(SDL_Rect Rect, float w, float h) {

	}

	~Box()
	{}
};

class Motor : public Module
{
public:
	
	Motor(Application* app, bool start_enabled = true);
	~Motor();

	//Create a ball
	//Ball ball;
	Atmosphere atmosphere;
	Ground ground;

	p2List<Ball*> Balls;

	p2List<Box*> Boxes;

	bool Start();
	update_status PreUpdate();
	update_status Update();
	update_status PostUpdate();
	bool CleanUp();
	/*void integrator_velocity_verlet(Ball* ball, float dt);
	void integrator_bw_euler(Ball* ball, float dt);
	void integrator_fw_euler(Ball* ball, float dt);*/

	double CalculateModule(float x, float y);

	void Unitari(float x, float y);

	void newton_law(Ball* ball, float dt);

	void ComputeForces(Ball* ball, float dt);

	Ball* NewBall(int rad, double mass, double x, double y, float v , float angle);

	Ball* NewPlayer(double, double mass, double x, double y);

	Ball* NewPlayer2(SDL_Rect rect, double mass, double x, double y);

	Box* CreateBoxes(SDL_Rect rect, float w, float h);

	void DragForce(Ball* a);

	void LiftForce(Ball* a);

	bool checkCollision(Ball* a, SDL_Rect b);

	void AddForce(Ball* obj ,float fx, float fy);

	void adios();

	void integrators(Ball* ball, float dt);

	int moto = 1;

	bool DragActive=true;
	bool LiftActive = true;
	bool NewtonActive = true;

private:

	float dt = 1.0f/60;
	
	//SDL_Texture* BALL;
	bool debug;
};


