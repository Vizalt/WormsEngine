// A (very crude) schematic of the core components of a game physics engine.
// This code does not compile; just use it to understand the basic operations, then make your own code.
// Try to blindly copy-paste anything from here without understanding it and you'll get yourself in a world of endless pain and dreadful suffering.

// Class: Ball object (a simple stoopid physics object)

#include "ModulePhysics.h"

ModulePhysics::ModulePhysics(Application* app, bool start_enabled = true) : Module(app, start_enabled) {

}
ModulePhysics:: ~ModulePhysics() {

}

// Start() --> create objects & start-up
bool ModulePhysics::Start()
{

	// Set physics properties of the ball
	ball.mass = 10; // kg
	ball.surface = 2; // m^2
	ball.cd = 0.4;
	ball.cl = 1.2;

	// Set initial position and velocity of the ball
	ball.x = ball.y = 0.0;
	ball.vx = 10.0;
	ball.vy = 5.0;

	return true;
}

// Update() --> Run physics engine
update_status ModulePhysics::Update()
{
	// Step #0: Reset total acceleration and total accumulated force of the ball (clear old values)
	ball.fx = ball.fy = 0.0;
	ball.ax = ball.ay = 0.0;

	// Step #1: Compute forces

		// Compute Gravity force
	double fgx = ball.mass * 0.0;
	double fgy = ball.mass * -10.0; // Let's assume gravity is constant and downwards

	// Add gravity force to the total accumulated force of the ball
	ball.fx += fgx;
	ball.fy += fgy;

	// Compute Aerodynamic Lift & Drag forces
	double speed = ball.speed(ball.vx - atmosphere.windx, ball.vy - atmosphere.windy);
	double fdrag = 0.5 * atmosphere.density * speed * speed * ball.surface * ball.cd;
	double flift = 0.5 * atmosphere.density * speed * speed * ball.surface * ball.cl;
	double fdx = -fdrag; // Let's assume Drag is aligned with x-axis (in your game, generalize this)
	double fdy = flift; // Let's assume Lift is perpendicular with x-axis (in your game, generalize this)

	// Add gravity force to the total accumulated force of the ball
	ball.fx += fdx;
	ball.fy += fdy;

	// Other forces
	// ...

// Step #2: 2nd Newton's Law: SUM_Forces = mass * accel --> accel = SUM_Forces / mass
	ball.ax = ball.fx / ball.mass;
	ball.ay = ball.fy / ball.mass;

	// Step #3: Integrate --> from accel to new velocity & new position. 
	// We will use the 2nd order "Velocity Verlet" method for integration.
	// You can also move this code into a subroutine: integrator_velocity_verlet(ball, dt);
	ball.x += ball.vx * dt + 0.5 * ball.ax * dt * dt;
	ball.y += ball.vy * dt + 0.5 * ball.ay * dt * dt;
	ball.vx += ball.ax * dt;
	ball.vy += ball.ay * dt;

	// Step #4: solve collisions
	if (ball.y < ground.y)
	{
		// For now, just stop the ball when it reaches the ground.
		ball.vx = ball.vy = 0.0;
		ball.ax = ball.ay = 0.0;
		ball.fx = ball.fy = 0.0;
		ball.physics_enabled = false;
	}

	return true;

}


// Integration scheme: Velocity Verlet
// You should modularise all your algorithms into subroutines. Including the ones to compute forces.
void integrator_velocity_verlet(Ball& ball, double dt)
{
	ball.x += ball.vx * dt + 0.5 * ball.ax * dt * dt;
	ball.y += ball.vy * dt + 0.5 * ball.ay * dt * dt;
	ball.vx += ball.ax * dt;
	ball.vy += ball.ay * dt;
}