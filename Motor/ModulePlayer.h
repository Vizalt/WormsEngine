#pragma once
#include "Module.h"
#include "Animation.h"
#include "Globals.h"
#include "p2Point.h"
#include "p2List.h"
#include "Motor.h"

class Ball;

class ModulePlayer : public Module
{
public:
	ModulePlayer(Application* app, bool start_enabled = true);
	virtual ~ModulePlayer();

	bool Start();
	update_status Update();
	bool CleanUp();
	void MovementPlayer();
	
public:
	
	p2Point<int> position;
	SDL_Texture* PlayerTex;
	SDL_Texture* CannonTex;
	SDL_Texture* SupportCannonTex;

	float PlayerRotation = 0;

	float cx;
	float cy;
	
	float speed = 7;
	float rad = PIXEL_TO_METERS(10);
	float mass = 10000;
	float velo = 300;

};