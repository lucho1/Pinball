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

	circle = App->textures->Load("pinball/wheel4.png"); 
	box = App->textures->Load("pinball/crate.png");
	bonus_fx = App->audio->LoadFx("pinball/bonus.wav");

	BackGroundImg = App->textures->Load("assets/Background.png");
	TrampolineImg = App->textures->Load("assets/Trampoline.png");
	Spiralimg = App->textures->Load("assets/Trampoline_Spiral.png");
	Buttonsimg = App->textures->Load("assets/PIMBALL_LIGHTS.png");
	r = { 0, 0, 1103, 1836 };

	//LIGHTS AND BUTTONS

	RLight1 = { 0,0,56,95 };
	RLight2 = { 0,0,56,95 };
	RLight3 = { 0,0,56,95 };  //PINK LIGHTS BUTTONS
	RLight4 = { 0,0,56,95 };
	RLight5 = { 0,0,56,95 };
	PinkButton = App->textures->Load("assets/LIGHTS/PinkButton.png");

	RLight6 = { 0,0,204,206 };
	RLight7 = { 0,0,204,206 };
	RLight8 = { 0,0,204,206 };
	GreenButtonDown = App->textures->Load("assets/LIGHTS/GreenButton.png");

	RLight24 = { 0,0,309,345 };
	PurpleButton = App->textures->Load("assets/LIGHTS/24.png");
	RLight25 = { 0,0,320,338 };
	BlueButton = App->textures->Load("assets/LIGHTS/25.png");
	RLight26 = { 0,0,320,338 };
	GreenButton = App->textures->Load("assets/LIGHTS/26.png");
	RLight27 = { 0,0,309,345 };
	YellowButton = App->textures->Load("assets/LIGHTS/27.png");

	
	RLight12 = { 0,0,56,95 };
	RLight13 = { 0,0,56,95 };  //PINK LIGHTS BUTTONS
	RLight14 = { 0,0,56,95 };
	RLight15 = { 0,0,56,95 };
	PinkButtonFlipped = App->textures->Load("assets/LIGHTS/PinkButton2.png");
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
	Light24 = false;
	Light10 = false;
	 Light11 = false;
	 Light12 = false;
	 Light13 = false;
	 Light14 = false;
	 Light15 = false;
	Light16 = false;
	 Light17 = false;
      Light18 = false;
	 Light19 = false;
     Light20 = false;
	 Light21 = false;
     Light22 = false;
	 Light23 = false;
     Light24 = false;
	 Light25 = false;
      Light26 = false;
      Light27 = false;
	 Light28 = false;
	 Light29 = false;
      Light30 = false;
	 Light31 = false;
	 Light32 = false;
	 Light33 = false;
	Light34 = false;
	Light35 = false;
	 Light36 = false;
	 Light37 = false;
	 Light38 = false;
     Light39 = false;
	 Light40 = false;
	 circlecreated = false;
	 App->audio->PlayMusic("assets/SOUNDS/AlienMusic.wav", 1.0);
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

	
	if (TurnOffAll) {
		Light1 = false;
		Light2 = false;
		Light3 = false;
		Light4 = false;
		Light5 = false;
		Light6 = false;
		Light7 = false;
		Light8 = false;
		Light24 = false;
		Light10 = false;
		Light11 = false;
		Light12 = false;
		Light13 = false;
		Light14 = false;
		Light15 = false;
		Light16 = false;
		Light17 = false;
		Light18 = false;
		Light19 = false;
		Light20 = false;
		Light21 = false;
		Light22 = false;
		Light23 = false;
		Light24 = false;
		Light25 = false;
		Light26 = false;
		Light27 = false;
		Light28 = false;
		Light29 = false;
		Light30 = false;
		Light31 = false;
		Light32 = false;
		Light33 = false;
		Light34 = false;
		Light35 = false;
		Light36 = false;
		Light37 = false;
		Light38 = false;
		Light39 = false;
		Light40 = false;
	}
	//BackGround of the entire game
	App->renderer->Blit(BackGroundImg, 0, 0, &r);

	//light 1,2,3,4,5
	if (Light1)
	App->renderer->Blit(PinkButton, 7, 1032, &RLight1);
	
	if (Light2)
	App->renderer->Blit(PinkButton, 7, 966, &RLight2);
	if (Light3)
	App->renderer->Blit(PinkButton, 7, 900, &RLight3);
	if (Light4)
	App->renderer->Blit(PinkButton, 7, 834, &RLight4);
	if (Light5)
	App->renderer->Blit(PinkButton, 7, 768, &RLight5);
	if (Light6)
		App->renderer->Blit(GreenButtonDown, 217, 705, &RLight6);
	if (Light7)
		App->renderer->Blit(GreenButtonDown, 275, 705, &RLight7);
	if (Light8)
		App->renderer->Blit(GreenButtonDown, 330, 705, &RLight8);
	if (Light24)
		App->renderer->Blit(PurpleButton, 248, 105, &RLight24);
	if (Light25)
		App->renderer->Blit(BlueButton, 355, 129, &RLight25);
	if (Light26)
		App->renderer->Blit(GreenButton, 460, 129, &RLight26);
	if (Light27)
		App->renderer->Blit(YellowButton, 577, 108, &RLight27);
	if (Light12)
		App->renderer->Blit(PinkButtonFlipped, 850, 966+115, &RLight12);
	if (Light13)
		App->renderer->Blit(PinkButtonFlipped, 850, 900 + 115, &RLight13);
	if (Light14)
		App->renderer->Blit(PinkButtonFlipped, 850, 834 + 115, &RLight14);
	if (Light15)
		App->renderer->Blit(PinkButtonFlipped, 850, 760 + 125, &RLight15);


	if(App->input->GetKey(SDL_SCANCODE_1) == KEY_DOWN)
	{
		circlecreated = true;
		//circles.del(circles.getFirst());
		circles.clear();
		circles.add(App->physics->CreateCircle(App->input->GetMouseX(), App->input->GetMouseY(), 18,b2_dynamicBody,true));

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
