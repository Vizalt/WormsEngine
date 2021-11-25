#include "Application.h"

class ModulePhysics :public Module {
public:
	ModulePhysics(Application* app, bool start_enabled = true);
	virtual ~ModulePhysics();
	bool Start();
	update_status Update();
	bool CleanUp();
	void integrator_velocity_verlet(Ball& ball, double dt);
	Ball ball;

};



class Ball
{
public:

	// Position
	// You could also use an array/vector
	double x;
	double y;

	// Velocity
	double vx;
	double vy;

	// Acceleration
	double ax;
	double ay;

	// Force (total) applied to the ball
	double fx;
	double fy;

	// Mass
	double mass;

	// Aerodynamics stuff
	double surface; // Effective wet surface
	double cl; // Lift coefficient
	double cd; // Drag coefficient

	// Has physics enabled?
	bool physics_enabled = true;
};


