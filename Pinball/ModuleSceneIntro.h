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
	//BUTTONS
	SDL_Texture* PinkButton;
	SDL_Texture* PinkButtonFlipped;
	SDL_Texture* GreenButtonDown;
	SDL_Texture* PurpleButton;
	SDL_Texture* BlueButton;
	SDL_Texture* GreenButton;
	SDL_Texture* YellowButton;
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
	bool Light11;
	bool Light12;
	bool Light13;
	bool Light14;
	bool Light15;
	bool Light16;
	bool Light17;
	bool Light18;
	bool Light19;
	bool Light20;
	bool Light21;
	bool Light22;
	bool Light23;
	bool Light24;
	bool Light25;
	bool Light26;
	bool Light27;
	bool Light28;
	bool Light29;
	bool Light30;
	bool Light31;
	bool Light32;
	bool Light33;
	bool Light34;
	bool Light35;
	bool Light36;
	bool Light37;
	bool Light38;
	bool Light39;
	bool Light40;
	bool TurnOffAll;
	bool circlecreated;

	bool downpulsed= false;
	float vel = 0;
public:
	SDL_Rect RLight1;
	SDL_Rect RLight2;
	SDL_Rect RLight3; 
	SDL_Rect RLight4;
	SDL_Rect RLight5;

	SDL_Rect RLight6;
	SDL_Rect RLight7;
	SDL_Rect RLight8;

	SDL_Rect RLight9;
	SDL_Rect RLight10;
	SDL_Rect RLight11;
	SDL_Rect RLight12;
	SDL_Rect RLight13;
	SDL_Rect RLight14;
	SDL_Rect RLight15;
	SDL_Rect RLight16;
	SDL_Rect RLight17;
	SDL_Rect RLight18;
	SDL_Rect RLight19;
	SDL_Rect RLight20;
	SDL_Rect RLight21;
	SDL_Rect RLight22;
	SDL_Rect RLight23;
	SDL_Rect RLight24;
	SDL_Rect RLight25;
	SDL_Rect RLight26;
	SDL_Rect RLight27;
	SDL_Rect RLight28;
	
	public:
		float TrampolinedorXpos;
};
