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
	bool Update();
	bool CleanUp();
	void MovementPlayer();
	void MovementPlayer2();
public:
	
	p2Point<int> position;
	SDL_Texture* PlayerTex;
	SDL_Texture* CannonTex;
	SDL_Texture* CannonTex2;
	SDL_Texture* SupportCannonTex;

	float PlayerRotation = 0;
	float PlayerRotation2 = 180;
	int turn = 1;
	bool shot1 = true;
	bool shot2 = false;
	int cx;
	int cy;
	
	float speed = 7;
	float rad = PIXEL_TO_METERS(10);
	float mass = 10000;
	float velo = 300;

	int w1 = PIXEL_TO_METERS(50);

	Collider* Player1Coll = nullptr;
	Collider* Player2Coll = nullptr;
};