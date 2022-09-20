#pragma once

#include "OBJ_Loader.h"
#include "PhysBody3D.h"
#include "Application.h"
#include "Primitive.h"
#include "ModulePhysics3D.h"

class Model
{
public:
	Model();
	~Model() {}


	void RenderModel();
	

	objl::Loader model;
	float x, y, z;
	float colR;
	float colG;
	float colB;
	float alpha;
	float scale;
	bool wireframe;

	btQuaternion orientation;


private:
	void RotateVertex(objl::Vertex &v);
	btQuaternion HamiltonProduct(btQuaternion& q, btQuaternion& p);
};