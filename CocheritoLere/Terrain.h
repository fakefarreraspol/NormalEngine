#pragma once
#include "Bullet/include/btBulletDynamicsCommon.h"
#include "Bullet/include/BulletCollision/CollisionShapes/btHeightfieldTerrainShape.h"
#include "Bullet/include/Utils/b3BulletDefaultFileIO.h"
#include "Bullet/include/BulletCommon/b3AlignedObjectArray.h"
#include "Bullet/include/stb_image/stb_image.h"

//https://github.com/bulletphysics/bullet3/blob/master/examples/Heightfield/HeightfieldExample.cpp

typedef unsigned char byte_t;

class Terrain
{
public :
	int						upAxis;
	PHY_ScalarType			type;
	byte_t*					rawHeightfieldData;
	btScalar				minHeight;
	btScalar				maxHeight;
	btScalar				gridHeightScale;
	btScalar				gridSpacing = 0.5;
	int						gridSize = 16 + 1;  // must be (2^N) + 1
	btHeightfieldTerrainShape* heightfieldShape;

	byte_t*  GetRawHeightfieldData(PHY_ScalarType type,btScalar& minHeight,btScalar& maxHeight);
	
	int getByteSize(PHY_ScalarType type)
	{
		int size = 0;

		switch (type) {
		case PHY_FLOAT:
			size = sizeof(btScalar);
			break;

		case PHY_UCHAR:
			size = sizeof(unsigned char);
			break;

		case PHY_SHORT:
			size = sizeof(short);
			break;

		default:
			//btAssert(!"Bad heightfield data type");
			break;
		}

		return size;
	}
	btScalar convertToFloat(const byte_t* p, PHY_ScalarType type);
	void	convertFromFloat(byte_t* p, btScalar value, PHY_ScalarType type);



};

