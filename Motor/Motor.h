#pragma once
#include "Module.h"
#include "Globals.h"
#include "Animation.h"
#include "ModuleCollisions.h"
#include "p2Point.h"
#include "ModuleSceneIntro.h"

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
	BALL,
	BOX
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
	double w = 0;
	double h = 0;
	SDL_Rect rectan;

	Collider* ball_collider = nullptr;

//	Ball* NewBall(int rad, double mass, double x, double y, float v);

	Ball(int rad, double mass, double x, double y, float v, float angle, types ty, Collider* col)
	{
		this->rad = rad;
		this->mass = mass;
		this->surface = 3.14 * rad;
		this->x = x;
		this->y = y;
		this->vx = v * cos(-angle * DEGTORAD);
		this->vy = v * sin(-angle * DEGTORAD);
		this->type = ty;
		this->ball_collider = col;
	}

	Ball(double w, double h, double mass, double x, double y, types ty)
	{
		this->w = w;
		this->h = h;
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
	SDL_Rect rect;
	int r = 0;
	int g = 0;
	int b = 0;

	Box(SDL_Rect rect, int r, int g, int b) {
		this->rect = rect;
		this->r = r;
		this->g = g;
		this->b = b;
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
	bool PreUpdate();
	bool Update();
	bool PostUpdate();
	bool CleanUp();
	/*void integrator_velocity_verlet(Ball* ball, float dt);
	void integrator_bw_euler(Ball* ball, float dt);
	void integrator_fw_euler(Ball* ball, float dt);*/

	double CalculateModule(float x, float y);

	void Unitari(float x, float y);

	void newton_law(Ball* ball, float dt);

	void ComputeForces(Ball* ball, float dt);

	void NewBall(int rad, double mass, double x, double y, float v , float angle);

	void NewPlayer(double w,double h, double mass, double x, double y);

	void NewPlayer2(double w, double h, double mass, double x, double y);

	void CreateBoxes(SDL_Rect rect, int r, int g, int b);

	void DragForce(Ball* a);

	void LiftForce(Ball* a);

	void OnCollision(Collider* c1, Collider* c2) override;

	void Colls(Ball* b);

	void AddForce(Ball* obj ,float fx, float fy);

	void adios();

	void integrators(Ball* ball, float dt);

	int moto = 1;

	bool DragActive=true;
	bool LiftActive = true;
	bool NewtonActive = true;

	float dt = 1.0f / 60;

private:
	//SDL_Texture* BALL;
	bool debug;
};


