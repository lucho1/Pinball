#pragma once
#include "Module.h"
#include "Globals.h"
#include "ModuleTextures.h"
#include "p2Point.h"
#include "Box2D/Box2D/Box2D.h"

#define GRAVITY_X 0.0f
#define GRAVITY_Y -7.0f

#define PIXELS_PER_METER 50.0f // if touched change METER_PER_PIXEL too
#define METER_PER_PIXEL 0.02f // this is 1 / PIXELS_PER_METER !

#define METERS_TO_PIXELS(m) ((int) floor(PIXELS_PER_METER * m))
#define PIXEL_TO_METERS(p)  ((float) METER_PER_PIXEL * p)

// Small class to return to other modules to track position and rotation of physics bodies
class PhysBody
{
public:
	PhysBody() : listener(NULL), body(NULL)
	{}

	void GetPosition(int& x, int &y) const;
	float GetRotation() const;
	bool Contains(int x, int y) const;
	int RayCast(int x1, int y1, int x2, int y2, float& normal_x, float& normal_y) const;

public:
	int width, height;
	b2Body* body;
	Module* listener;
};

// Module --------------------------------------
class ModulePhysics : public Module, public b2ContactListener
{
public:
	ModulePhysics(Application* app, bool start_enabled = true);
	~ModulePhysics();

	bool Start();
	update_status PreUpdate();
	update_status PostUpdate();
	bool CleanUp();

	PhysBody* CreateCircle(int x, int y, int radius, b2BodyType type = b2_dynamicBody);
	PhysBody* CreateRectangle(int x, int y, int width, int height, b2BodyType type = b2_dynamicBody);
	PhysBody* CreateRectangleSensor(int x, int y, int width, int height);
	PhysBody* CreateChain(int x, int y, b2Vec2 *vertices, int vertices_size, b2BodyType type, bool ARRIBA_ESPANA = true); //bool ARRIBA_ESPA�A = closing or not closing the shape

	// b2ContactListener ---
	void BeginContact(b2Contact* contact);

	//To pass INT array to a p2Vec2 array
	b2Vec2* ConversionToVector(int* int_array, int size);
	
	b2RevoluteJointDef LFlipperJoint;
	b2RevoluteJointDef RFlipperJoint;

private:

	bool debug;
	b2World* world;
	b2MouseJoint* mouse_joint;
	b2Body *jointed_object;
	b2Body* ground;
	PhysBody* RFlipper = nullptr;
	PhysBody* RMotor = nullptr;
};