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

class Ball
{
public:
	// Position
	// You could also use an array/vector
	double x;
	double y;

	// Velocity
	float vx;
	float vy;

	// Acceleration
	double ax;
	double ay;

	// Force (total) applied to the ball
	double fx;
	double fy;

	double fgx;
	double fgy;
	// Mass
	double mass;

	// Aerodynamics stuff
	//double surface; // Effective wet surface
	//double cl; // Lift coefficient
	//double cd; // Drag coefficient

	// Has physics enabled?
	bool physics_enabled = true;

	int rad;
};

struct Ground {
	int x = 0;
	int y = 500;
};

class Motor : public Module
{
public:
	
	

	

	Motor(Application* app, bool start_enabled = true);
	~Motor();

	//Create a ball
	Ball ball;
	Ground ground;

	p2List<Ball*>* Balls;

	bool Start();
	update_status PreUpdate();
	update_status Update();
	update_status PostUpdate();
	bool CleanUp();
	void integrator_velocity_verlet(Ball& ball, float dt);
	void integrator_bw_euler(Ball& ball, float dt);
	void integrator_fw_euler(Ball& ball, float dt);

	void newton_law(Ball& ball, float dt);

	void ComputeForces(Ball& ball, float dt);



private:

	float dt = 1.0f/16;
	float g = 100.0f;
	SDL_Texture* BALL;
	bool debug;
};


