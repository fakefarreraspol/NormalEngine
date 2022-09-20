#include "OBJ_Model.h"
#include <gl/GL.h>
#include <gl/GLU.h>


Model::Model()
{
	x = y = z = 0;
	colR = 1;
	colG = 1;
	colB = 1;
	alpha = 1;
	scale = 1;
	wireframe = false;
	
}

void Model::RenderModel()
{
	
	
	for (int i = 0; i < model.LoadedMeshes.size(); i++)
	{
		
		objl::Mesh currMesh = model.LoadedMeshes.at(i);
	
		for (int j = 0; j < currMesh.Indices.size(); j += 3)
		{
			int currIndex = currMesh.Indices[j];


			objl::Vertex v1 = currMesh.Vertices[currIndex];
			objl::Vertex v2 = currMesh.Vertices[currIndex + 1];
			objl::Vertex v3 = currMesh.Vertices[currIndex + 2];

			glDisable(GL_CULL_FACE);
			if (wireframe)
			{
				glBegin(GL_LINE_STRIP);

			}
			else
			{
				glBegin(GL_TRIANGLES);
			}

			glColor4f(colR, colG, colB, alpha);


			RotateVertex(v1);
			RotateVertex(v2);
			RotateVertex(v3);

			glNormal3f(v1.Normal.X, v1.Normal.Y, v1.Normal.Z);
			glVertex3f(
				x + METERS_TO_UNITS(v1.Position.X) * scale,
				y + METERS_TO_UNITS(v1.Position.Y) * scale,
				z + METERS_TO_UNITS(v1.Position.Z) * scale
				);
			
			glNormal3f(v2.Normal.X, v2.Normal.Y, v2.Normal.Z);
			glVertex3f(
				x + METERS_TO_UNITS(v2.Position.X) * scale,
				y + METERS_TO_UNITS(v2.Position.Y) * scale,
				z + METERS_TO_UNITS(v2.Position.Z) * scale
			);
			
			glNormal3f(v3.Normal.X, v3.Normal.Y, v3.Normal.Z);
			glVertex3f(
				x + METERS_TO_UNITS(v3.Position.X) * scale ,
				y + METERS_TO_UNITS(v3.Position.Y) * scale ,
				z + METERS_TO_UNITS(v3.Position.Z) * scale 
			);
			
			
			glEnd();
		}
	}
}
void Model::RotateVertex(objl::Vertex &v)
{
	btQuaternion p;
	btQuaternion inv;
	orientation.normalize();
	inv = orientation;
	inv.setX(-inv.getX());
	inv.setY(-inv.getY());
	inv.setZ(-inv.getZ());

		
	p.setValue((btScalar)v.Position.X, (btScalar)v.Position.Y, (btScalar)v.Position.Z);
	
	
	p = HamiltonProduct(orientation, p);
	p = HamiltonProduct(p, inv);

	v.Position.X = -p.getX();
	v.Position.Y = p.getY();
	v.Position.Z = p.getZ();
	

}
btQuaternion Model::HamiltonProduct(btQuaternion &q, btQuaternion &p)
{
	btQuaternion result;

	result[0] = q[0] * p[0] - q[1] * p[1] - q[2] * p[2] - q[3] * p[3];
	result[1] = q[0] * p[1] + q[1] * p[0] + q[2] * p[3] - q[3] * p[2];
	result[2] = q[0] * p[2] - q[1] * p[3] + q[2] * p[0] + q[3] * p[1];
	result[3] = q[0] * p[3] + q[1] * p[2] - q[2] * p[1] + q[3] * p[0];

	return result;
}

