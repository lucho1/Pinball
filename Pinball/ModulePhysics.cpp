#include "Globals.h"
#include "Application.h"
#include "ModuleInput.h"
#include "ModuleRender.h"
#include "ModulePhysics.h"
#include "p2Point.h"
#include "math.h"
#include "ModuleTextures.h"
#include "CollidersArrays.h"
#include "ModuleSceneIntro.h"
#include "ModuleAudio.h"

#include "Box2D\Box2D\Dynamics\Joints\b2RevoluteJoint.h"

#ifdef _DEBUG
#pragma comment( lib, "Box2D/libx86/Debug/Box2D.lib" )
#else
#pragma comment( lib, "Box2D/libx86/Release/Box2D.lib" )
#endif

ModulePhysics::ModulePhysics(Application* app, bool start_enabled) : Module(app, start_enabled)
{
	world = NULL;
	mouse_joint = NULL;
	debug = true;
}

// Destructor
ModulePhysics::~ModulePhysics()
{
}

// Called before quitting
bool ModulePhysics::CleanUp()
{
	LOG("Destroying physics world");

	// Delete the whole physics world!
	delete world;

	return true;
}

bool ModulePhysics::Start()
{
	LOG("Creating Physics 2D environment");

	EffectiveCollision = false;

	world = new b2World(b2Vec2(GRAVITY_X, -GRAVITY_Y));
	world->SetContactListener(this);
	soundfx = App->audio->LoadFx("assets/SOUNDS/Hit.wav");
	
	// needed to create joints like mouse joint
	b2BodyDef bd;
	ground = world->CreateBody(&bd);

	int x = SCREEN_WIDTH / 2;
	int y = SCREEN_HEIGHT / 1.5f;

	//Colliders & Body creations
	//Game Main Colliders
	CreateChain(0, 0, mons, GetArraySize(Monster), b2_staticBody,Buttonminus1); //1
	CreateChain(0, 0, rightred, GetArraySize(RightRed), b2_staticBody,1, Buttonminus1); //2
	CreateChain(0, 0, leftred, GetArraySize(LeftRed), b2_staticBody,1, Buttonminus1); //3
	CreateChain(0, 0, mons_met, GetArraySize(MonsterMetalic), b2_staticBody, Buttonminus1); //4
	CreateChain(0, 0, jackpot, GetArraySize(Jackpot), b2_staticBody, Buttonminus1); //6


	//Pills
	CreateChain(0, 0, pill1, GetArraySize(Pill1), b2_staticBody); //16
	CreateChain(0, 0, pill2, GetArraySize(Pill2), b2_staticBody); //7
	CreateChain(0, 0, pill3, GetArraySize(Pill3), b2_staticBody); //17
	CreateChain(0, 0, pill4, GetArraySize(Pill4), b2_staticBody); //18

  //Marcianitos
	CreateChain(0, 0, MarcianitoVec, GetArraySize(Marcianito), b2_staticBody,1, Buttonminus1); //16
	CreateChain(0, 0, MarcianitoVec2, GetArraySize(Marcianito2), b2_staticBody, 1, Buttonminus1);
	CreateChain(0, 0, MarcianitoVec3, GetArraySize(Marcianito3), b2_staticBody, 1, Buttonminus1);
  
	//Wall
	CreateChain(0, 0, wall_left, GetArraySize(WallLeft), b2_staticBody); //13

	//Create Flickers, Holders and their joints
	CreateChain(0, 0, holder_right, GetArraySize(HolderRight), b2_staticBody); //11
	CreateChain(0, 0, holder_left, GetArraySize(HolderLeft), b2_staticBody); //11

	//Right Joint Holder-Flicker
	RFlipper = CreateRectangle(597, 1635, 160, 30, b2_dynamicBody);
	RMotor = CreateCircle(683, 1635, 20, b2_staticBody);

	RFlipperJoint.bodyA = RFlipper->body;
	RFlipperJoint.bodyB = RMotor->body;

	RFlipperJoint.localAnchorA.Set(-PIXEL_TO_METERS(80), 0);
	RFlipperJoint.localAnchorB.Set(0, 0);

	RFlipperJoint.collideConnected = false;

	RFlipperJoint.enableLimit = true;
	RFlipperJoint.lowerAngle = -210 * DEGTORAD;
	RFlipperJoint.upperAngle = -160 * DEGTORAD;

	RFlipperJoint.maxMotorTorque = 80000.0f;
	RFlipperJoint.motorSpeed = 0;
	RFlipperJoint.enableMotor = true;

	RFJoint = (b2RevoluteJoint*)world->CreateJoint(&RFlipperJoint);

	//Left Joint Holder-Flicker
	LFlipper = CreateRectangle(413, 1635, 160, 30, b2_dynamicBody);
	LMotor = CreateCircle(327, 1635, 20, b2_staticBody);

	LFlipperJoint.bodyA = LFlipper->body;
	LFlipperJoint.bodyB = LMotor->body;
	LFlipperJoint.localAnchorA.Set(-PIXEL_TO_METERS(80), 0);
	LFlipperJoint.localAnchorB.Set(0, 0);

	LFlipperJoint.collideConnected = false;
  
	LFlipperJoint.enableLimit = true;
	LFlipperJoint.lowerAngle = -20 * DEGTORAD;
	LFlipperJoint.upperAngle = 30 * DEGTORAD;


	LFlipperJoint.maxMotorTorque = 80000.0f;
	LFlipperJoint.motorSpeed = 0;
	LFlipperJoint.enableMotor = true;

	LFJoint = (b2RevoluteJoint*)world->CreateJoint(&LFlipperJoint);

	App->physics->CreateChain(0, 0, wall_right, GetArraySize(WallRight), b2_staticBody); //13
	App->physics->CreateChain(0, 0, downer_vec, GetArraySize(Downer), b2_staticBody, false);

	PhysBody* TrampolineRocket = CreateChain(0, 0, TrampolineChainVec, GetArraySize(TrampolineChain), b2_staticBody,4,Buttonminus1);
	//App->scene_intro->boxes.add(TrampolineRocket);
	App->scene_intro->TrampolinedorXpos = 1040;
		

	//ALL RECTS FOR BUTTONS
	//pink buttons
	PhysBody *PinkLigh1Button = CreateRectangle(34,1082,10,57 ,b2_staticBody,Button1);
	PhysBody *PinkLigh2Button = CreateRectangle(34, 1018, 10, 57, b2_staticBody, Button2);
	PhysBody *PinkLigh3Button = CreateRectangle(34, 955, 10, 57, b2_staticBody, Button3);
	PhysBody *PinkLigh4Button = CreateRectangle(34, 887, 10, 57, b2_staticBody, Button4);
	PhysBody *PinkLigh5Button = CreateRectangle(34, 822, 10, 57, b2_staticBody, Button5);
	//rebote del los pink buttons
	CreateChain(0, 0, ReboteRosaVec, GetArraySize(ReboteRosa), b2_staticBody, 2, Buttonminus1); //3
	//pink buttons left side

	PhysBody *PinkLigh12Button = CreateRectangle(877, 1082 + 50, 10, 57, b2_staticBody, Button12);
	PhysBody *PinkLigh13Button = CreateRectangle(877, 1018 + 50, 10, 57, b2_staticBody, Button13);
	PhysBody *PinkLigh14Button = CreateRectangle(877, 955 + 50, 10, 57, b2_staticBody, Button14);
	PhysBody *PinkLigh15Button = CreateRectangle(877, 887 + 50, 10, 57, b2_staticBody, Button15);
	//rebote de los pink butons left side
	CreateChain(0, 0, ReboteRosaVec2, GetArraySize(ReboteRosa2), b2_staticBody, 2, Buttonminus1); //3.

	

	PhysBody *PinkLigh6Button = CreateRectangle(310, 795, 45, 40, b2_staticBody, Button6);
	PhysBody *PinkLigh7Button = CreateRectangle(370, 795, 45, 40, b2_staticBody, Button7);
	PhysBody *PinkLigh8Button = CreateRectangle(425, 795, 45, 40, b2_staticBody, Button8);

	PhysBody *PinkLigh24Button = CreateRectangle(410, 268, 56,80, b2_staticBody, Button24);
	PhysBody *PinkLigh25Button = CreateRectangle(517, 289, 55, 80, b2_staticBody, Button25);
	PhysBody *PinkLigh26Button = CreateRectangle(629, 289, 55, 80, b2_staticBody, Button26);

	PhysBody *PinkLigh27Button = CreateRectangle(737, 270, 55, 80, b2_staticBody, Button27);

	return true;
}

update_status ModulePhysics::PreUpdate()
{
	
	world->Step(1.0f / 60.0f, 6, 2);
	for(b2Contact* c = world->GetContactList(); c; c = c->GetNext())
	{
		if(c->GetFixtureA()->IsSensor() && c->IsTouching())
		{
			PhysBody* pb1 = (PhysBody*)c->GetFixtureA()->GetBody()->GetUserData();
			PhysBody* pb2 = (PhysBody*)c->GetFixtureB()->GetBody()->GetUserData();
			if(pb1 && pb2 && pb1->listener)
				pb1->listener->OnCollision(pb1, pb2);
		}
	}

	return UPDATE_CONTINUE;
}

update_status ModulePhysics::PostUpdate()
{
	

	if (App->input->GetKey(SDL_SCANCODE_RIGHT) == KEY_REPEAT)
		RFJoint->SetMotorSpeed(-100);

	if (App->input->GetKey(SDL_SCANCODE_LEFT) == KEY_REPEAT) 
		LFJoint->SetMotorSpeed(100);

	if (App->input->GetKey(SDL_SCANCODE_LEFT) == KEY_IDLE)
		LFJoint->SetMotorSpeed(-100);
	

	if (RFJoint->GetJointAngle() <= RFJoint->GetLowerLimit() && App->input->GetKey(SDL_SCANCODE_RIGHT) == KEY_IDLE)
		RFJoint->SetMotorSpeed(100);
	
	if (App->input->GetKey(SDL_SCANCODE_F1) == KEY_DOWN)
		debug = !debug;

	if (!debug)
		return UPDATE_CONTINUE;

	PhysBody * Trampolinebase = CreateRectangle(App->scene_intro->TrampolinedorXpos, 1724, 30, 5, b2_staticBody);


	// Bonus code: this will iterate all objects in the world and draw the circles
	// You need to provide your own macro to translate meters to pixels
	for (b2Body* b = world->GetBodyList(); b; b = b->GetNext())
	{
		for (b2Fixture* f = b->GetFixtureList(); f; f = f->GetNext())
		{
			switch (f->GetType())
			{
				// Draw circles ------------------------------------------------
			case b2Shape::e_circle:
			{				
				b2CircleShape* shape = (b2CircleShape*)f->GetShape();
			
				b2Vec2 pos = f->GetBody()->GetPosition();
				/*App->renderer->DrawCircle(METERS_TO_PIXELS(pos.x), METERS_TO_PIXELS(pos.y), METERS_TO_PIXELS(shape->m_radius), 255, 255, 255);*/
				App->renderer->DrawCircle(METERS_TO_PIXELS(pos.x + App->renderer->camera.x), METERS_TO_PIXELS(pos.y + App->renderer->camera.y), METERS_TO_PIXELS(shape->m_radius), 255, 255, 255);
			}
			break;

			// Draw polygons ------------------------------------------------
			case b2Shape::e_polygon:
			{
				b2PolygonShape* polygonShape = (b2PolygonShape*)f->GetShape();
				int32 count = polygonShape->GetVertexCount();
				b2Vec2 prev, v;

				for (int32 i = 0; i < count; ++i)
				{
					v = b->GetWorldPoint(polygonShape->GetVertex(i));
					if (i > 0)
						App->renderer->DrawLine(METERS_TO_PIXELS(prev.x), METERS_TO_PIXELS(prev.y), METERS_TO_PIXELS(v.x), METERS_TO_PIXELS(v.y), 255, 100, 100);

					prev = v;
				}

				v = b->GetWorldPoint(polygonShape->GetVertex(0));
				App->renderer->DrawLine(METERS_TO_PIXELS(prev.x), METERS_TO_PIXELS(prev.y), METERS_TO_PIXELS(v.x), METERS_TO_PIXELS(v.y), 255, 100, 100);
			}
			break;

			// Draw chains contour -------------------------------------------
			case b2Shape::e_chain:
			{
				b2ChainShape* shape = (b2ChainShape*)f->GetShape();
				b2Vec2 prev, v;

				for (int32 i = 0; i < shape->m_count; ++i)
				{
					v = b->GetWorldPoint(shape->m_vertices[i]);
					if (i > 0)
						App->renderer->DrawLine(METERS_TO_PIXELS(prev.x), METERS_TO_PIXELS(prev.y), METERS_TO_PIXELS(v.x), METERS_TO_PIXELS(v.y), 100, 255, 100);
					prev = v;
				}

				v = b->GetWorldPoint(shape->m_vertices[0]);
				App->renderer->DrawLine(METERS_TO_PIXELS(prev.x), METERS_TO_PIXELS(prev.y), METERS_TO_PIXELS(v.x), METERS_TO_PIXELS(v.y), 100, 255, 100);
			}
			break;

			// Draw a single segment(edge) ----------------------------------
			case b2Shape::e_edge:
			{
				b2EdgeShape* shape = (b2EdgeShape*)f->GetShape();
				b2Vec2 v1, v2;

				v1 = b->GetWorldPoint(shape->m_vertex0);
				v1 = b->GetWorldPoint(shape->m_vertex1);
				App->renderer->DrawLine(METERS_TO_PIXELS(v1.x), METERS_TO_PIXELS(v1.y), METERS_TO_PIXELS(v2.x), METERS_TO_PIXELS(v2.y), 100, 100, 255);
			}
			break;
			}

			//Mouse Joint
			if (App->input->GetMouseButton(SDL_BUTTON_LEFT) == KEY_DOWN) {

				int mouse_x = App->input->GetMouseX();
				int mouse_y = App->input->GetMouseY();

				b2Vec2 mouse_pos(PIXEL_TO_METERS(mouse_x), PIXEL_TO_METERS(mouse_y));
				if (f->TestPoint(mouse_pos)) {
					jointed_object = f->GetBody();
					break;
				}
			}
		}
	}

	//More on Mouse Joint
	if (App->input->GetMouseButton(SDL_BUTTON_LEFT) == KEY_DOWN && jointed_object != nullptr) {

		int mouse_x = App->input->GetMouseX();
		int mouse_y = App->input->GetMouseY();

		b2MouseJointDef def;
		def.bodyA = ground;
		def.bodyB = jointed_object;
		def.target = b2Vec2(PIXEL_TO_METERS(mouse_x), PIXEL_TO_METERS(mouse_y));
		def.dampingRatio = 0.5f;
		def.frequencyHz = 2.0f;
		def.maxForce = 100.0f * jointed_object->GetMass();

		mouse_joint = (b2MouseJoint*)world->CreateJoint(&def);
	}
	if (App->input->GetMouseButton(SDL_BUTTON_LEFT) == KEY_REPEAT && jointed_object != nullptr) {

		int mouse_x = App->input->GetMouseX();
		int mouse_y = App->input->GetMouseY(); //Now we get mouse X and Y in pixels

		b2Vec2 mouse_in_meters(PIXEL_TO_METERS(mouse_x), PIXEL_TO_METERS(mouse_y)); //Here we convert mouse_pos to meters

		b2Vec2 obj_pos = jointed_object->GetPosition(); //Getting the position of the object attached
		float32 obj_pos_x = METERS_TO_PIXELS(obj_pos.x);
		float32 obj_pos_y = METERS_TO_PIXELS(obj_pos.y); //Extracted X and Y of object attached and converted them into Pixels

		mouse_joint->SetTarget(mouse_in_meters); //Set target of the jointed object (to the mouse pos)
		App->renderer->DrawLine(mouse_x, mouse_y, obj_pos_x, obj_pos_y, 0, 0, 255, 100); //Drawing the attachment

	}

	//Release Mouse Joint
	if (App->input->GetMouseButton(SDL_BUTTON_LEFT) == KEY_UP && jointed_object != nullptr) {

		world->DestroyJoint(mouse_joint);
		mouse_joint = nullptr;
		jointed_object = nullptr;
		
	}

	return UPDATE_CONTINUE;
}



//CREATE BODIES
PhysBody* ModulePhysics::CreateCircle(int x, int y, int radius, b2BodyType type, bool playerball_)
{

	b2BodyDef body;
	body.type = type;
	body.position.Set(PIXEL_TO_METERS(x), PIXEL_TO_METERS(y));

	b2Body* b = world->CreateBody(&body);

	
	b2CircleShape shape;

	shape.m_radius = radius;
	shape.m_radius = PIXEL_TO_METERS(radius);

	b2FixtureDef fixture;
	fixture.shape = &shape;
	fixture.density = 100.0f;
	fixture.friction = 0;


	b->CreateFixture(&fixture);
	
	PhysBody* pbody = new PhysBody();
	pbody->body = b;
	if (playerball_) {
	pbody->Type = PLAYER_BALL;// WE SET THE CREATED CIRCLES TO BALL TYPE USED IN FUNCTION BEGINNCONTACT()
	}
	else if (!playerball_) {
		pbody->Type = GAME_CIRCLE;
		fixture.restitution = 1;
	}
	
	b->SetUserData(pbody);
	pbody->width = pbody->height = radius; //*SCREEN_SIZE
	//b->CacadeVaca(body.position.x, body.position.y);
	return pbody;
}

PhysBody* ModulePhysics::CreateRectangle(int x, int y, int width, int height, b2BodyType type,b2Button BUTTON)
{

	b2BodyDef body;
	body.type = type;
	body.position.Set(PIXEL_TO_METERS(x), PIXEL_TO_METERS(y));

	b2Body* b = world->CreateBody(&body);
	b2PolygonShape box;
	box.SetAsBox(PIXEL_TO_METERS(width) * 0.5f, PIXEL_TO_METERS(height) * 0.5f);

	b2FixtureDef fixture;
	fixture.shape = &box;
	fixture.density = 1.0f;

	b->CreateFixture(&fixture);

	PhysBody* pbody = new PhysBody();
	pbody->body = b;
	pbody->Button = BUTTON;
	b->SetUserData(pbody);
	pbody->width = width * 0.5f;
	pbody->height = height * 0.5f;

	return pbody;
}

PhysBody* ModulePhysics::CreateRectangleSensor(int x, int y, int width, int height, b2Button BUTTON)
{
	b2BodyDef body;
	body.type = b2_staticBody;
	body.position.Set(PIXEL_TO_METERS(x), PIXEL_TO_METERS(y));

	b2Body* b = world->CreateBody(&body);

	b2PolygonShape box;
	box.SetAsBox(PIXEL_TO_METERS(width) * 0.5f, PIXEL_TO_METERS(height) * 0.5f);

	b2FixtureDef fixture;
	fixture.shape = &box;
	fixture.density = 1.0f;
	fixture.isSensor = true;

	b->CreateFixture(&fixture);

	PhysBody* pbody = new PhysBody();
	pbody->body = b;
	b->SetUserData(pbody);
	pbody->width = width;
	pbody->height = height;
	
	return pbody;
}

//Chain from v2 vertex Program to create colliders You can close it or not with ARRIBA_ESPANA bool
PhysBody* ModulePhysics::CreateChain(int x, int y, b2Vec2 *vertices, int vertices_size, b2BodyType type, float restitution_, bool ARRIBA_ESPANA, b2Button BUTTON) //bool ARRIBA_ESPAÑA = closing or not closing the shape
{
	b2BodyDef body;
	body.type = type;
	body.position.Set(PIXEL_TO_METERS(x), PIXEL_TO_METERS(y));

	b2Body* b = world->CreateBody(&body);

	b2ChainShape shape;
	
	if (ARRIBA_ESPANA)
		shape.CreateLoop(vertices, vertices_size / 2);
	else
		shape.CreateChain(vertices, vertices_size / 2);

	b2FixtureDef fixture;
	fixture.shape = &shape;
	fixture.density = 1.0f;
	if (restitution_ != 0) {
		fixture.restitution = restitution_;
	}
	b->CreateFixture(&fixture);

	PhysBody* pbody = new PhysBody();
	pbody->body = b;
	pbody->Button = BUTTON;
	b->SetUserData(pbody);
	pbody->width = pbody->height = 0;

	return pbody;
}

//Transformations
void PhysBody::GetPosition(int& x, int &y) const
{
	b2Vec2 pos = body->GetPosition();
	x = METERS_TO_PIXELS(pos.x) - (width);
	y = METERS_TO_PIXELS(pos.y) - (height);
}

float PhysBody::GetRotation() const
{
	return RADTODEG * body->GetAngle();
}

//Collisions
bool PhysBody::Contains(int x, int y) const
{
	b2Vec2 p(PIXEL_TO_METERS(x), PIXEL_TO_METERS(y));

	const b2Fixture* fixture = body->GetFixtureList();

	while(fixture != NULL)
	{
		if(fixture->GetShape()->TestPoint(body->GetTransform(), p) == true)
			return true;
		fixture = fixture->GetNext();
	}

	return false;
}

int PhysBody::RayCast(int x1, int y1, int x2, int y2, float& normal_x, float& normal_y) const
{
	int ret = -1;

	b2RayCastInput input;
	b2RayCastOutput output;

	input.p1.Set(PIXEL_TO_METERS(x1), PIXEL_TO_METERS(y1));
	input.p2.Set(PIXEL_TO_METERS(x2), PIXEL_TO_METERS(y2));
	input.maxFraction = 1.0f;

	const b2Fixture* fixture = body->GetFixtureList();

	while(fixture != NULL)
	{
		if(fixture->GetShape()->RayCast(&output, input, body->GetTransform(), 0) == true)
		{
			// do we want the normal ?

			float fx = x2 - x1;
			float fy = y2 - y1;
			float dist = sqrtf((fx*fx) + (fy*fy));

			normal_x = output.normal.x;
			normal_y = output.normal.y;

			return output.fraction * dist;
		}
		fixture = fixture->GetNext();
	}

	return ret;
}

//Checks contact
void ModulePhysics::BeginContact(b2Contact* contact)
{
	PhysBody* physA = (PhysBody*)contact->GetFixtureA()->GetBody()->GetUserData();
	PhysBody* physB = (PhysBody*)contact->GetFixtureB()->GetBody()->GetUserData();

	if(physA && physA->listener != NULL)
		physA->listener->OnCollision(physA, physB);

	if(physB && physB->listener != NULL)
		physB->listener->OnCollision(physB, physA);

	//Light1
	if (physA->Button == Button1 && physB->Type == PLAYER_BALL) {
		App->scene_intro->Light1 = true;
		App->audio->PlayFx(soundfx,1);
	}
	if (physB->Button == Button1 && physA->Type == PLAYER_BALL) {
		App->scene_intro->Light1 = true;
		App->audio->PlayFx(soundfx, 1);
	}
	//Ligh2
	if (physA->Button == Button2 && physB->Type == PLAYER_BALL) {
		App->scene_intro->Light2 = true;
		App->audio->PlayFx(soundfx, 1);
	}
	if (physB->Button == Button2 && physA->Type == PLAYER_BALL) {
		App->scene_intro->Light2 = true;
		App->audio->PlayFx(soundfx, 1);
	}
	//Ligh3
	if (physA->Button == Button3 && physB->Type == PLAYER_BALL) {
		App->scene_intro->Light3 = true;
		App->audio->PlayFx(soundfx, 1);
	}
	if (physB->Button == Button3 && physA->Type == PLAYER_BALL) {
		App->scene_intro->Light3 = true;
		App->audio->PlayFx(soundfx, 1);
	}
	//Ligh4
	if (physA->Button == Button4 && physB->Type == PLAYER_BALL) {
		App->scene_intro->Light4 = true;
		App->audio->PlayFx(soundfx, 1);
	}
	if (physB->Button == Button4 && physA->Type == PLAYER_BALL) {
		App->scene_intro->Light4 = true;
		App->audio->PlayFx(soundfx, 1);
	}
	//Ligh5
	if (physA->Button == Button5 && physB->Type == PLAYER_BALL) {
		App->scene_intro->Light5 = true;
		App->audio->PlayFx(soundfx, 1);
	}
	if (physB->Button == Button5 && physA->Type == PLAYER_BALL) {
		App->scene_intro->Light5 = true;
		App->audio->PlayFx(soundfx, 1);
	}
	//Ligh6
	if (physA->Button == Button6 && physB->Type == PLAYER_BALL) {
		App->scene_intro->Light6 = true;
		App->audio->PlayFx(soundfx, 1);
	}
	if (physB->Button == Button6 && physA->Type == PLAYER_BALL) {
		App->scene_intro->Light6 = true;
		App->audio->PlayFx(soundfx, 1);
	}
	//Ligh7
	if (physA->Button == Button7 && physB->Type == PLAYER_BALL) {
		App->scene_intro->Light7 = true;
		App->audio->PlayFx(soundfx, 1);
	}
	if (physB->Button == Button7 && physA->Type == PLAYER_BALL) {
		App->scene_intro->Light7 = true;
		App->audio->PlayFx(soundfx, 1);
	}
	//Ligh8
	if (physA->Button == Button8 && physB->Type == PLAYER_BALL) {
		App->scene_intro->Light8 = true;
		App->audio->PlayFx(soundfx, 1);
	}
	if (physB->Button == Button8 && physA->Type == PLAYER_BALL) {
		App->scene_intro->Light8 = true;
		App->audio->PlayFx(soundfx, 1);
	}
	//Ligh24
	if (physA->Button == Button24 && physB->Type == PLAYER_BALL) {
		App->scene_intro->Light24 = true;
		App->audio->PlayFx(soundfx, 1);
	}
	if (physB->Button == Button24 && physA->Type == PLAYER_BALL) {
		App->scene_intro->Light24 = true;
		App->audio->PlayFx(soundfx, 1);
	}
	//Ligh25
	if (physA->Button == Button25 && physB->Type == PLAYER_BALL) {
		App->scene_intro->Light25 = true;
		App->audio->PlayFx(soundfx, 1);
	}
	if (physB->Button == Button25 && physA->Type == PLAYER_BALL) {
		App->scene_intro->Light25 = true;
		App->audio->PlayFx(soundfx, 1);
	}
	
	//Ligh26
	if (physA->Button == Button26 && physB->Type == PLAYER_BALL) {
		App->scene_intro->Light26 = true;
		App->audio->PlayFx(soundfx, 1);
	}
	if (physB->Button == Button26 && physA->Type == PLAYER_BALL) {
		App->scene_intro->Light26 = true;
		App->audio->PlayFx(soundfx, 1);
	}
	//Light27
	if (physA->Button == Button27 && physB->Type == PLAYER_BALL) {
		App->scene_intro->Light27 = true;
		App->audio->PlayFx(soundfx, 1);
	}
	if (physB->Button == Button27 && physA->Type == PLAYER_BALL) {
		App->scene_intro->Light27 = true;
		App->audio->PlayFx(soundfx, 1);
	}
	//BUTTON TURN OFF LIGHTS
	if (physA->Button == ButtonTurnOffLights && physB->Type == PLAYER_BALL) {
		App->scene_intro->TurnOffAll = true;
		App->audio->PlayFx(soundfx, 1);
	}
	if (physB->Button == ButtonTurnOffLights && physA->Type == PLAYER_BALL) {
		App->scene_intro->TurnOffAll = true;
		App->audio->PlayFx(soundfx, 1);
	}
	//Light12
	if (physA->Button == Button12 && physB->Type == PLAYER_BALL) {
		App->scene_intro->Light12 = true;
		App->audio->PlayFx(soundfx, 1);
	}
	if (physB->Button == Button12 && physA->Type == PLAYER_BALL) {
		App->scene_intro->Light12 = true;
		App->audio->PlayFx(soundfx, 1);
	}
	//Light13
	if (physA->Button == Button13 && physB->Type == PLAYER_BALL) {
		App->scene_intro->Light13 = true;
		App->audio->PlayFx(soundfx, 1);
	}
	if (physB->Button == Button13 && physA->Type == PLAYER_BALL) {
		App->scene_intro->Light13 = true;
		App->audio->PlayFx(soundfx, 1);
	}
	//Light14
	if (physA->Button == Button14 && physB->Type == PLAYER_BALL) {
		App->scene_intro->Light14 = true;
		App->audio->PlayFx(soundfx, 1);
	}
	if (physB->Button == Button14 && physA->Type == PLAYER_BALL) {
		App->scene_intro->Light14 = true;
		App->audio->PlayFx(soundfx, 1);
	}
	//Light15
	if (physA->Button == Button15 && physB->Type == PLAYER_BALL) {
		App->scene_intro->Light15 = true;
		App->audio->PlayFx(soundfx, 1);
	}
	if (physB->Button == Button15 && physA->Type == PLAYER_BALL) {
		App->scene_intro->Light15 = true;
		App->audio->PlayFx(soundfx, 1);
	}
	
}

//Converts an INT array to a Vector
b2Vec2* ModulePhysics::ConversionToVector(int* int_array, int size) {

	b2Vec2 *aux = new b2Vec2[size];
	for (uint i = 0; i < size; ++i) {

		aux[i].x = PIXEL_TO_METERS(int_array[i * 2]);
		aux[i].y = PIXEL_TO_METERS(int_array[i * 2 + 1]);
	}

	return aux;
}
