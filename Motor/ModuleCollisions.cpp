#include "ModuleCollisions.h"
#include "Globals.h"
#include "Application.h"
#include "Module.h"
//#include "ModuleIntroScene.h"

#include "ModuleRender.h"
#include "SDL/include/SDL_Scancode.h"

ModuleCollisions::ModuleCollisions(Application* app, bool start_enabled) : Module(app, start_enabled)
{
	debug = true;

	for(uint i = 0; i < MAX_COLLIDERS; ++i)
		colliders[i] = nullptr;

	//PLAYER
	matrix[Collider::Type::PLAYER][Collider::Type::PLAYER] = false;
	matrix[Collider::Type::PLAYER][Collider::Type::PLAYER2] = false;
	matrix[Collider::Type::PLAYER][Collider::Type::BOX1] = false;
	matrix[Collider::Type::PLAYER][Collider::Type::BOX2] = false;
	matrix[Collider::Type::PLAYER][Collider::Type::BOX3] = false;
	matrix[Collider::Type::PLAYER][Collider::Type::BOX4] = false;

	//PLAYER2
	matrix[Collider::Type::PLAYER2][Collider::Type::PLAYER2] = false;
	matrix[Collider::Type::PLAYER2][Collider::Type::PLAYER] = false;
	matrix[Collider::Type::PLAYER2][Collider::Type::BOX1] = false;
	matrix[Collider::Type::PLAYER2][Collider::Type::BOX2] = false;
	matrix[Collider::Type::PLAYER2][Collider::Type::BOX3] = false;
	matrix[Collider::Type::PLAYER2][Collider::Type::BOX4] = false;

	//BOX1
	matrix[Collider::Type::BOX1][Collider::Type::BOX1] = false;
	matrix[Collider::Type::BOX1][Collider::Type::BOX2] = false;
	matrix[Collider::Type::BOX1][Collider::Type::BOX3] = false;
	matrix[Collider::Type::BOX1][Collider::Type::BOX4] = false;
	matrix[Collider::Type::BOX1][Collider::Type::PLAYER] = false;
	matrix[Collider::Type::BOX1][Collider::Type::PLAYER2] = false;

}

// Destructor
ModuleCollisions::~ModuleCollisions()
{

}

bool ModuleCollisions::Start()
{
	return true;
}

bool ModuleCollisions::PreUpdate() {
	for (uint i = 0; i < MAX_COLLIDERS; i++) {
		if (colliders[i] != nullptr && colliders[i]->pendingToDelete == true) {
			delete colliders[i];
			colliders[i] = nullptr;
		}
	}

	Collider* c1;
	Collider* c2;

	for (uint i = 0; i < MAX_COLLIDERS; i++) {
		if (colliders[i] == nullptr) {
			continue;
		}
		c1 = colliders[i];
		for (uint k = i + 1; k < MAX_COLLIDERS; ++k) {
			if (colliders[k] == nullptr) {
				continue;
			}
			c2 = colliders[k];

			if (matrix[c1->type][c2->type] && c1->Intersects(c2->rect))
			{
				for (uint i = 0; i < MAX_LISTENERS; ++i)
				{
					if (c1->listeners[i] != nullptr)
					{
						c1->listeners[i]->OnCollision(c1, c2);
					}
				}
				for (uint i = 0; i < MAX_LISTENERS; ++i)
				{
					if (c2->listeners[i] != nullptr) {
						c2->listeners[i]->OnCollision(c2, c1);
					}
				}
			}
		}
	}
	return true;
}

bool ModuleCollisions::Update()
{

	if ((App->input->GetKey(SDL_SCANCODE_F9) == KEY_DOWN) ) {
		debug = !debug;
	}

	return true;
}

bool ModuleCollisions::PostUpdate()
{
	return true;
}

void ModuleCollisions::DebugDraw()
{
	Uint8 alpha = 80;
	for(uint i = 0; i < MAX_COLLIDERS; ++i)
	{
		if(colliders[i] == nullptr)
			continue;
		
		switch(colliders[i]->type)
		{
			case Collider::Type::NONE: // white
			App->renderer->DrawQuad(colliders[i]->rect, 255, 255, 255, alpha);
			break;
			case Collider::Type::PLAYER: // green
			App->renderer->DrawQuad(colliders[i]->rect, 0, 255, 0, alpha);
			break;
			case Collider::Type::PLAYER2: // green
			App->renderer->DrawQuad(colliders[i]->rect, 0, 255, 0, alpha);
			break;
			case Collider::Type::BOX1: //
			App->renderer->DrawQuad(colliders[i]->rect, 10, 255, 0, alpha);
			break;
			case Collider::Type::BOX2: //
			App->renderer->DrawQuad(colliders[i]->rect, 255, 255, 10, alpha);
			break;
			case Collider::Type::BOX3: //
			App->renderer->DrawQuad(colliders[i]->rect,8, 255, 0, alpha);
			break;
			case Collider::Type::BOX4: //
			App->renderer->DrawQuad(colliders[i]->rect, 255,2, 0, alpha);
			break;
		
		}
	}
}

// Called before quitting
bool ModuleCollisions::CleanUp()
{
	LOG("Freeing all colliders");

	for(uint i = 0; i < MAX_COLLIDERS; ++i)
	{
		if(colliders[i] != nullptr)
		{
			delete colliders[i];
			colliders[i] = nullptr;
		}
	}

	return true;
}

Collider* ModuleCollisions::AddCollider(SDL_Rect rect, Collider::Type type, Module* listener)
{
	Collider* ret = nullptr;

	for(uint i = 0; i < MAX_COLLIDERS; ++i)
	{
		if(colliders[i] == nullptr)
		{
			ret = colliders[i] = new Collider(rect, type, listener);
			break;
		}
	}

	return ret;
}

void ModuleCollisions::clean()
{
	LOG("Freeing all colliders");

	for (uint i = 0; i < MAX_COLLIDERS; ++i)
	{
		if (colliders[i] != nullptr)
		{
			delete colliders[i];
			colliders[i] = nullptr;
		}
	}

}