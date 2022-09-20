// OBJ_Loader.h - A Single Header OBJ Model Loader

#pragma once

// Iostream - STD I/O Library
#include <iostream>

// Vector - STD Vector/Array Library
#include <vector>

// String - STD String Library
#include <string>

// fStream - STD File I/O Library
#include <fstream>

// Math.h - STD math Library
#include <math.h>

#include "p2List.h"

// Print progress to console while loading (large models)
#define OBJL_CONSOLE_OUTPUT

// Namespace: OBJL
//
// Description: The namespace that holds eveyrthing that
//	is needed and used for the OBJ Model Loader
namespace objl
{
	// Structure: OBJ_Vector2
	//
	// Description: A 2D Vector that Holds Positional Data
	struct OBJ_Vector2
	{
		// Default Constructor
		OBJ_Vector2()
		{
			X = 0.0f;
			Y = 0.0f;
		}
		// Variable Set Constructor
		OBJ_Vector2(float X_, float Y_)
		{
			X = X_;
			Y = Y_;
		}
		// Bool Equals Operator Overload
		bool operator==(const OBJ_Vector2& other) const
		{
			return (this->X == other.X && this->Y == other.Y);
		}
		// Bool Not Equals Operator Overload
		bool operator!=(const OBJ_Vector2& other) const
		{
			return !(this->X == other.X && this->Y == other.Y);
		}
		// Addition Operator Overload
		OBJ_Vector2 operator+(const OBJ_Vector2& right) const
		{
			return OBJ_Vector2(this->X + right.X, this->Y + right.Y);
		}
		// Subtraction Operator Overload
		OBJ_Vector2 operator-(const OBJ_Vector2& right) const
		{
			return OBJ_Vector2(this->X - right.X, this->Y - right.Y);
		}
		// Float Multiplication Operator Overload
		OBJ_Vector2 operator*(const float& other) const
		{
			return OBJ_Vector2(this->X *other, this->Y * other);
		}

		// Positional Variables
		float X;
		float Y;
	};

	// Structure: OBJ_Vector3
	//
	// Description: A 3D Vector that Holds Positional Data
	struct OBJ_Vector3
	{
		// Default Constructor
		OBJ_Vector3()
		{
			X = 0.0f;
			Y = 0.0f;
			Z = 0.0f;
		}
		// Variable Set Constructor
		OBJ_Vector3(float X_, float Y_, float Z_)
		{
			X = X_;
			Y = Y_;
			Z = Z_;
		}
		// Bool Equals Operator Overload
		bool operator==(const OBJ_Vector3& other) const;
		// Bool Not Equals Operator Overload
		bool operator!=(const OBJ_Vector3& other) const;
		// Addition Operator Overload
		OBJ_Vector3 operator+(const OBJ_Vector3& right) const;
		// Subtraction Operator Overload
		OBJ_Vector3 operator-(const OBJ_Vector3& right) const;
		// Float Multiplication Operator Overload
		OBJ_Vector3 operator*(const float& other) const;
		// Float Division Operator Overload
		OBJ_Vector3 operator/(const float& other) const;

		// Positional Variables
		float X;
		float Y;
		float Z;
	};

	// Structure: Vertex
	//
	// Description: Model Vertex object that holds
	//	a Position, Normal, and Texture Coordinate
	struct Vertex
	{
		// Position Vector
		OBJ_Vector3 Position;

		// Normal Vector
		OBJ_Vector3 Normal;

		// Texture Coordinate Vector
		OBJ_Vector2 TextureCoordinate;
	};

	struct Material
	{
		Material()
		{
			name;
			Ns = 0.0f;
			Ni = 0.0f;
			d = 0.0f;
			illum = 0;
		}

		// Material Name
		std::string name;
		// Ambient Color
		OBJ_Vector3 Ka;
		// Diffuse Color
		OBJ_Vector3 Kd;
		// Specular Color
		OBJ_Vector3 Ks;
		// Specular Exponent
		float Ns;
		// Optical Density
		float Ni;
		// Dissolve
		float d;
		// Illumination
		int illum;
		// Ambient Texture Map
		std::string map_Ka;
		// Diffuse Texture Map
		std::string map_Kd;
		// Specular Texture Map
		std::string map_Ks;
		// Specular Hightlight Map
		std::string map_Ns;
		// Alpha Texture Map
		std::string map_d;
		// Bump Map
		std::string map_bump;
	};

	// Structure: Mesh
	//
	// Description: A Simple Mesh Object that holds
	//	a name, a vertex list, and an index list
	struct Mesh
	{
		// Default Constructor
		Mesh()
		{

		}
		// Variable Set Constructor
		Mesh(std::vector<Vertex>& _Vertices, std::vector<unsigned int>& _Indices)
		{
			Vertices = _Vertices;
			Indices = _Indices;
		}
		// Mesh Name
		std::string MeshName;
		// Vertex List
		std::vector<Vertex> Vertices;
		// Index List
		std::vector<unsigned int> Indices;

		// Material
		Material MeshMaterial;
	};

	// Namespace: Math
	//
	// Description: The namespace that holds all of the math
	//	functions need for OBJL
	namespace math
	{
		// OBJ_Vector3 Cross Product
		OBJ_Vector3 CrossV3(const OBJ_Vector3 a, const OBJ_Vector3 b);
		
		// OBJ_Vector3 Magnitude Calculation
		float MagnitudeV3(const OBJ_Vector3 in);

		// OBJ_Vector3 DotProduct
		float DotV3(const OBJ_Vector3 a, const OBJ_Vector3 b);

		// Angle between 2 OBJ_Vector3 Objects
		float AngleBetweenV3(const OBJ_Vector3 a, const OBJ_Vector3 b);

		// Projection Calculation of a onto b
		OBJ_Vector3 ProjV3(const OBJ_Vector3 a, const OBJ_Vector3 b);
	}

	// Namespace: Algorithm
	//
	// Description: The namespace that holds all of the
	// Algorithms needed for OBJL
	namespace algorithm
	{
		// OBJ_Vector3 Multiplication Opertor Overload
		OBJ_Vector3 operator*(const float& left, const OBJ_Vector3& right);

		// A test to see if P1 is on the same side as P2 of a line segment ab
		bool SameSide(OBJ_Vector3 p1, OBJ_Vector3 p2, OBJ_Vector3 a, OBJ_Vector3 b);

		// Generate a cross produect normal for a triangle
		OBJ_Vector3 GenTriNormal(OBJ_Vector3 t1, OBJ_Vector3 t2, OBJ_Vector3 t3);

		// Check to see if a OBJ_Vector3 Point is within a 3 OBJ_Vector3 Triangle
		bool inTriangle(OBJ_Vector3 point, OBJ_Vector3 tri1, OBJ_Vector3 tri2, OBJ_Vector3 tri3);

		// Split a String into a string array at a given token
		inline void split(const std::string& in,
			std::vector<std::string>& out,
			std::string token);

		// Get tail of string after first token and possibly following spaces
		inline std::string tail(const std::string& in);

		// Get first token of string
		inline std::string firstToken(const std::string& in);

		// Get element at given index position
		template <class T>
		inline const T & getElement(const std::vector<T> &elements, std::string &index)
		{
			int idx = std::stoi(index);
			if (idx < 0)
				idx = int(elements.size()) + idx;
			else
				idx--;
			return elements[idx];
		}
	}

	// Class: Loader
	//
	// Description: The OBJ Model Loader
	class Loader
	{
	public:
		// Default Constructor
		Loader()
		{

		}
		~Loader()
		{
			LoadedMeshes.clear();
		}

		// Load a file into the loader
		//
		// If file is loaded return true
		//
		// If the file is unable to be found
		// or unable to be loaded return false
		bool LoadFile(std::string Path);

		objl::Loader LoadModel(std::string path);
		// Loaded Mesh Objects
		std::vector<Mesh> LoadedMeshes;
		// Loaded Vertex Objects
		std::vector<Vertex> LoadedVertices;
		// Loaded Index Positions
		std::vector<unsigned int> LoadedIndices;
		// Loaded Material Objects
		std::vector<Material> LoadedMaterials;

		p2List<objl::Loader> modelsList;

	private:
		// Generate vertices from a list of positions, 
		//	tcoords, normals and a face line
		void GenVerticesFromRawOBJ(std::vector<Vertex>& oVerts,
			const std::vector<OBJ_Vector3>& iPositions,
			const std::vector<OBJ_Vector2>& iTCoords,
			const std::vector<OBJ_Vector3>& iNormals,
			std::string icurline);

		// Triangulate a list of vertices into a face by printing
		//	inducies corresponding with triangles within it
		void VertexTriangluation(std::vector<unsigned int>& oIndices,
			const std::vector<Vertex>& iVerts);

		// Load Materials from .mtl file
		bool LoadMaterials(std::string path);
	};
}
