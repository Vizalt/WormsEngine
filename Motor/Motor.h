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
class Motor : public Module
{
public:
	
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

	Motor(Application* app, bool start_enabled = true);
	~Motor();

	//Create a ball
	Ball ball;
	Ground ground;

	bool Start();
	update_status PreUpdate();
	update_status Update();
	update_status PostUpdate();
	bool CleanUp();
	void integrator_velocity_verlet(Ball& ball, double dt);
	void integrator_bw_euler(Ball& ball, double dt);
	void integrator_fw_euler(Ball& ball, double dt);

private:

	float dt = 1.0f/16;

	SDL_Texture* BALL;
	bool debug;
};


