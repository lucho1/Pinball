#include "Globals.h"
#include "Application.h"
#include "ModuleRender.h"
#include "ModuleSceneIntro.h"
#include "ModuleInput.h"
#include "ModuleTextures.h"
#include "ModuleAudio.h"
#include "ModulePhysics.h"

ModuleSceneIntro::ModuleSceneIntro(Application* app, bool start_enabled) : Module(app, start_enabled)
{
	circle = box = NULL;
}

ModuleSceneIntro::~ModuleSceneIntro()
{}

// Load assets
bool ModuleSceneIntro::Start()
{
	LOG("Loading Intro assets");
	bool ret = true;

	App->renderer->camera.x = App->renderer->camera.y = 0;

	circle = App->textures->Load("pinball/wheel.png"); 
	box = App->textures->Load("pinball/crate.png");
	bonus_fx = App->audio->LoadFx("pinball/bonus.wav");

	BackGroundImg = App->textures->Load("assets/BUTTONS_ORDER_HERE.png");
	TrampolineImg = App->textures->Load("assets/Trampoline.png");
	Spiralimg = App->textures->Load("assets/Trampoline_Spiral.png");
	Buttonsimg = App->textures->Load("assets/PIMBALL_LIGHTS.png");
	r = { 0, 0, 1103, 1836 };

	//SPIRAL INITIAL POS: 
	
	Spiral.x = 1022;
	Spiral.y = 1710;
	Spiral.yvel = -20;
	Trampoline.yvel = 0;


	//LUCHO NO T'ESPANTIS S�N LES LLUMS DE TOT EL PIMBALL NOM�S PUC CONTROLAR SI ESTAN ON/OFF AMB UN PUTO BOOL. SI, M'ACABO D'ADONAR Q PODRIA HAVER FET UNA ARRAY DE BOOLS EN FIN
	Light1 = false;
	Light2 = false;
	Light3 = false;
	Light4 = false;
	Light5 = false;
	Light6 = false;
	Light7 = false;
	Light8 = false;
	Light9 = false;
	Light10 = false;


	return ret;
}

// Load assets
bool ModuleSceneIntro::CleanUp()
{
	LOG("Unloading Intro scene");
	App->textures->Unload(BackGroundImg);
	App->textures->Unload(circle);
	App->textures->Unload(box);
	App->textures->Unload(TrampolineImg);
	App->textures->Unload(Spiralimg);
	App->textures->Unload(Buttonsimg);
	return true;
}

// Update: draw background
update_status ModuleSceneIntro::Update()
{
	//BackGround of the entire game
	App->renderer->Blit(BackGroundImg, 0, 0, &r);

	if(App->input->GetKey(SDL_SCANCODE_1) == KEY_DOWN)
	{
	
		circles.add(App->physics->CreateCircle(App->input->GetMouseX(), App->input->GetMouseY(), 25,b2_dynamicBody,true));

		circles.getLast()->data->listener = this;
		LOG("MouseX: %i MouseY: %i", App->input->GetMouseX(), App->input->GetMouseY());
	}

	if(App->input->GetKey(SDL_SCANCODE_2) == KEY_DOWN)
	{
		boxes.add(App->physics->CreateRectangle(App->input->GetMouseX(), App->input->GetMouseY(), 100, 50));
	}

	//TRAMPOLIN IMPUT 1780
	if (App->input->GetKey(SDL_SCANCODE_DOWN) == KEY_REPEAT ){
		if (!Spiral.Bottom) {
			Spiral.y += 1;
			if (Spiral.y >= 1780) {
				Spiral.Bottom = true;
				Trampoline.yvel = -0.1;
			}
		}
		
	}
	if(Spiral.Bottom && !(App->input->GetKey(SDL_SCANCODE_DOWN) == KEY_REPEAT)){
		Spiral.y += Spiral.yvel;
		if (Spiral.y <= 1710) {
			Spiral.y = 1710;
			Spiral.Bottom = false;
			
		}
	}
	/*if (Ball.startyvel != 0) {
		Ball.startyvel += 0.1;
	}*/

	// Prepare for raycast ------------------------------------------------------
	iPoint mouse;
	mouse.x = App->input->GetMouseX();
	mouse.y = App->input->GetMouseY();

	// All draw functions ------------------------------------------------------
	p2List_item<PhysBody*>* c = circles.getFirst();

	while(c != NULL)
	{
		int x, y;
		if (App->physics->EffectiveCollision) {
			if (c->data->Type == PLAYER_BALL) {
				
			}
		}
		c->data->GetPosition(x, y);
		App->renderer->Blit(circle, x, y, NULL, 1.0f, c->data->GetRotation());
		c = c->next;  // tecnicamente solo deberia funcar con la primera bola
	}

	c = boxes.getFirst();

	while(c != NULL)
	{
		int x, y;
		if (c->data->Button == Buttonminus1) {
			c->data->body->SetTransform(b2Vec2(c->data->body->GetPosition().x, c->data->body->GetPosition().y + Trampoline.yvel), 0.0);
		}
		c->data->GetPosition(x, y);
		//App->renderer->Blit(box, x, y, NULL, 1.0f, c->data->GetRotation());
		c = c->next;
	}
	//Background prepared for the trampoline and other items that are upper the ball
	//Muelle
	App->renderer->Blit(Spiralimg, Spiral.x, Spiral.y, &r);

	//Marco de hierro
	App->renderer->Blit(TrampolineImg, 1004, 1695, &r);

	//LIGHTS HERE MOTHERFUCKERRRR
	Light1 = true;
	if(Light1)
		App->renderer->Blit(Buttonsimg, 0, 0, &RLight1);


	return UPDATE_CONTINUE;
}

void ModuleSceneIntro::OnCollision(PhysBody* bodyA, PhysBody* bodyB)
{
	if (bodyA->Button != Buttonminus1 && bodyB->Button != Buttonminus1) {
		if (bodyA->Type == PLAYER_BALL && bodyB->Button == Button0) {
			App->audio->PlayFx(bonus_fx);
		}

	}
	
}
