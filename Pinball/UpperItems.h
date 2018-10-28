#pragma once
#include "Module.h"
#include "p2List.h"
#include "p2Point.h"
#include "Globals.h"

class PhysBody;

class ModuleUpperItems : public Module
{
public:
	ModuleUpperItems(Application* app, bool start_enabled = true);
	~ModuleUpperItems();

	bool Start();
	update_status Update();
	bool CleanUp();
	void OnCollision(PhysBody* bodyA, PhysBody* bodyB);

public:

	p2List<PhysBody*> circles;
	p2List<PhysBody*> boxes;
	p2List<PhysBody*> curve;

	SDL_Texture* circle;
	SDL_Texture* box;
	uint bonus_fx;

	SDL_Texture* BackGroundImg;
	SDL_Texture* TrampolineImg;
	SDL_Rect r;
};
