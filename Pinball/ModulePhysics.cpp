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
	

	// needed to create joints like mouse joint
	b2BodyDef bd;
	ground = world->CreateBody(&bd);

	int x = SCREEN_WIDTH / 2;
	int y = SCREEN_HEIGHT / 1.5f;

	//Colliders & Body creations
	//Game Main Colliders
	CreateChain(0, 0, mons, GetArraySize(Monster), b2_staticBody); //1
	CreateChain(0, 0, rightred, GetArraySize(RightRed), b2_staticBody); //2
	CreateChain(0, 0, leftred, GetArraySize(LeftRed), b2_staticBody); //3
	CreateChain(0, 0, mons_met, GetArraySize(MonsterMetalic), b2_staticBody); //4
	CreateChain(0, 0, jackpot, GetArraySize(Jackpot), b2_staticBody); //6


	//Pills
	CreateChain(0, 0, pill1, GetArraySize(Pill1), b2_staticBody); //16
	CreateChain(0, 0, pill2, GetArraySize(Pill2), b2_staticBody); //7
	CreateChain(0, 0, pill3, GetArraySize(Pill3), b2_staticBody); //17
	CreateChain(0, 0, pill4, GetArraySize(Pill4), b2_staticBody); //18

	

	//Walls
	CreateChain(0, 0, wall_right, GetArraySize(WallRight), b2_staticBody); //12
	CreateChain(0, 0, wall_left, GetArraySize(WallLeft), b2_staticBody); //13

	//Create Flickers, Holders and their joints
	CreateChain(0, 0, holder_right, GetArraySize(HolderRight), b2_staticBody); //11

	//Right Joint Holder-Flicker
	RFlipper = CreateChain(0, 0, flicker_right, GetArraySize(FlickerRight), b2_dynamicBody); //14
	/*b2BodyDef FlipBody;
	FlipBody.type = b2_dynamicBody;
	b2FixtureDef FlipFixture;
	FlipFixture.density = 1.0f;

	b2PolygonShape Flipper;
	Flipper.Set(flicker_right, GetArraySize(FlickerRight));
	FlipFixture.shape = &Flipper;
	b2Body *FB = world->CreateBody(&FlipBody);
	FB->CreateFixture(&FlipFixture);*/

	RMotor = CreateCircle(258, 620, 10, b2_staticBody);

	RFlipperJoint.Initialize(RFlipper->body, RMotor->body, RMotor->body->GetWorldCenter());
	RFlipperJoint.collideConnected = false;

	RFlipper->listener = this;

	App->physics->RFlipperJoint.enableMotor = true;
	App->physics->RFlipperJoint.maxMotorTorque = 10.0f;
	App->physics->RFlipperJoint.motorSpeed = 90 * DEGTORAD; //90 degrees per second

	//Set Anchorage Point
	(b2RevoluteJoint*)world->CreateJoint(&RFlipperJoint); //Create Joint in the world

	App->physics->RFlipperJoint.enableMotor = true;
	App->physics->RFlipperJoint.maxMotorTorque = 10.0f;
	App->physics->RFlipperJoint.motorSpeed = 90 * DEGTORAD;//90 degrees per second

	//RFlickerJoint.enableLimit = true;
	//RFlickerJoint.lowerAngle = -45 * DEGTORAD;
	//RFlickerJoint.upperAngle = 45 * DEGTORAD;


	float trans = 1 - SCREEN_SIZE;

	//trampoline 

	PhysBody* TrampolineRocket = CreateChain(0, 0, TrampolineChainVec, GetArraySize(TrampolineChain), b2_staticBody);
	App->scene_intro->boxes.add(TrampolineRocket);
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
	
	if (App->input->GetKey(SDL_SCANCODE_F1) == KEY_DOWN)
		debug = !debug;

	if (!debug)
		return UPDATE_CONTINUE;

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

				//for (b2Fixture* fl = RFlipper->body->GetFixtureList(); fl; fl = fl->GetNext())
				//{
				//	if (fl->TestPoint(mouse_pos)) {
				//		jointed_object = RFlipper->body;
				//		break;
				//	}
				//}
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

	
	b->CreateFixture(&fixture);
	
	PhysBody* pbody = new PhysBody();
	pbody->body = b;
	if (playerball_) {
	pbody->Type = PLAYER_BALL;// WE SET THE CREATED CIRCLES TO BALL TYPE USED IN FUNCTION BEGINNCONTACT()
	
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
	fixture.density = 100.0f;

	b->CreateFixture(&fixture);

	PhysBody* pbody = new PhysBody();
	pbody->body = b;
	pbody->Button = BUTTON;
	b->SetUserData(pbody);
	pbody->width = width * 0.5f;
	pbody->height = height * 0.5f;

	return pbody;
}

PhysBody* ModulePhysics::CreateRectangleSensor(int x, int y, int width, int height)
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
PhysBody* ModulePhysics::CreateChain(int x, int y, b2Vec2 *vertices, int vertices_size, b2BodyType type, bool ARRIBA_ESPANA, b2Button BUTTON) //bool ARRIBA_ESPAÑA = closing or not closing the shape
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

	/*if (physA->Type == PLAYER_BALL && physB->Type == GAME_RECTANGLE)  {
		EffectiveCollision = true;
	
	}
	else if (physA->Type == GAME_RECTANGLE && physB->Type == PLAYER_BALL) {
		EffectiveCollision = true;
		
	}else if()
		EffectiveCollision = false;*/
	if (physA->Button == Button0 || physB->Button == Button0) {

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
