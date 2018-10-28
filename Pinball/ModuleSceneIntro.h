#pragma once
#include "Module.h"
#include "p2List.h"
#include "p2Point.h"
#include "Globals.h"

class PhysBody;

struct SpiralData {
	int x;
	int y;
	int yvel;
	bool GoingDown = false;
	bool NoMovement = true;
	bool Bottom = false;
	bool GoingUp = false;
};
struct PlayerBallData {
	float xvel;
	float yvel;
	float startyvel;
};
struct TrampolineData {
	int ypos;
	float yvel;
};


class ModuleSceneIntro : public Module
{
public:
	ModuleSceneIntro(Application* app, bool start_enabled = true);
	~ModuleSceneIntro();

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
	SDL_Texture* Spiralimg;
	SDL_Texture* Buttonsimg;
	SDL_Rect r;

public:
	SpiralData Spiral;
	PlayerBallData Ball;
	TrampolineData Trampoline;

public:
	//LUCHO NO T'ESPANTIS SÓN LES LLUMS DE TOT EL PIMBALL NOMÉS PUC CONTROLAR SI ESTAN ON/OFF AMB UN PUTO BOOL. SI, M'ACABO D'ADONAR Q PODRIA HAVER FET UNA ARRAY DE BOOLS EN FIN
	bool Light1;
	bool Light2;
	bool Light3;
	bool Light4;
	bool Light5;
	bool Light6;
	bool Light7;
	bool Light8;
	bool Light9;
	bool Light10;

	int Life = 3;

public:
	SDL_Rect RLight1;
	
};
