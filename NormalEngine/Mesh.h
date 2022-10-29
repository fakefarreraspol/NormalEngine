#pragma once
#include "Globals.h"
#include <vector>

using namespace std;

struct Vertex
{
	float3 Position;
};


class Mesh
{
public:
	// mesh data
	vector<Vertex> vertices;
	vector<int> indices;

	void LoadMesh();
	void Draw();

	Mesh(vector<Vertex> vertices, vector<int> indices);
	~Mesh();

private:
	uint vertexId = 0;
	int indicesId = 0;

};