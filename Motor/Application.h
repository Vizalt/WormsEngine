#pragma once

#include "p2List.h"
#include "Globals.h"
#include "Module.h"
#include "Dummy.h"
#include "ModuleWindow.h"
#include "ModuleRender.h"
#include "ModuleTextures.h"
#include "ModuleInput.h"
#include "ModuleAudio.h"
#include "ModulePlayer.h"
#include "Motor.h"
#include "ModuleSceneIntro.h"
#include "ModuleCollisions.h"

class Application
{
public:
	ModuleRender* renderer;
	ModuleWindow* window;
	ModuleTextures* textures;
	ModuleInput* input;
	ModuleAudio* audio;
	ModulePlayer* player;
	ModuleSceneIntro* scene_intro;
	Motor* motor;
	ModuleCollisions* coll;

private:

	p2List<Module*> list_modules;

public:

	Application();
	~Application();

	bool Init();
	bool Update();
	bool CleanUp();

private:

	void AddModule(Module* mod);
};