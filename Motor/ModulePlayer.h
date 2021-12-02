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

	
public:
	p2List<Ball*>* balls;
	p2Point<int> position;
	SDL_Texture* PlayerTex;
	SDL_Texture* CannonTex;
	SDL_Texture* SupportCannonTex;

	int PlayerRotation = 0;
	
};