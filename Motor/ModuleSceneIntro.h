#pragma once
#include "Module.h"
#include "Animation.h"
#include "p2DynArray.h"
#include "Globals.h"

#define BOUNCER_TIME 200



enum lightTypes
{
	tiny,
	medium,
	big
};


struct obj
{

	double x;
	double y;

	double vx;
	double vy;

	double ax;
	double ay;

	double mass;


};

class ModuleSceneIntro;

struct Light
{
	/*Light() : body(NULL), texture(NULL), on(false), fx(0)
	{}*/

	//Light(ModuleSceneIntro* physics, int x, int y, lightTypes type);

	//lightTypes type;
	//PhysBody* body;
	SDL_Texture* texture;
	bool on;
	uint fx;
	int x, y;
};

class ModuleSceneIntro : public Module
{
public:
	ModuleSceneIntro(Application* app, bool start_enabled = true);
	~ModuleSceneIntro();

	bool Start();
	update_status PreUpdate();
	update_status Update();
	update_status PostUpdate();
	bool CleanUp();

public:

	SDL_Texture* graphics;
	PhysBody* background;

	/*Bouncer bouncer1;
	Bouncer bouncer2;

	Bouncer side_bouncer1;
	Bouncer side_bouncer2;*/

	//SDL_Texture* tex_light_tiny;
	//SDL_Texture* tex_light_medium;
	//SDL_Texture* tex_light_big;
	////
	//uint fx_light_tiny;
	//uint fx_light_medium;
	//uint fx_light_big;

	/*p2DynArray<Light> lights;*/

	PhysBody* player_lose;
	uint player_lose_fx;

	int sx = PIXEL_TO_METERS(0);
	int sy = PIXEL_TO_METERS(650);
	int sw = PIXEL_TO_METERS(1024);
	int sh = PIXEL_TO_METERS(280);

	int sx2 = PIXEL_TO_METERS(0);
	int sy2 = PIXEL_TO_METERS(0);
	int sw2 = PIXEL_TO_METERS(1024);
	int sh2 = PIXEL_TO_METERS(100);

};
