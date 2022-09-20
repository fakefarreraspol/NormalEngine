#include "Terrain.h"

byte_t* Terrain::GetRawHeightfieldData(PHY_ScalarType type, btScalar& minHeight, btScalar& maxHeight)
{
    //b3BulletDefaultFileIO fileIO;
    //char relativeFileName[1024];
    //int found = fileIO.findFile("heightmaps/wm_height_out.png", relativeFileName, 1024);


    //b3AlignedObjectArray<char> buffer;
    //buffer.reserve(1024);
    //int fileId = fileIO.fileOpen(relativeFileName, "rb");
    //if (fileId >= 0)
    //{
    //    int size = fileIO.getFileSize(fileId);
    //    if (size > 0)
    //    {
    //        buffer.resize(size);
    //        int actual = fileIO.fileRead(fileId, &buffer[0], size);
    //        if (actual != size)
    //        {
    //            b3Warning("STL filesize mismatch!\n");
    //            buffer.resize(0);
    //        }
    //    }
    //    fileIO.fileClose(fileId);
    //}

    //if (buffer.size())
    //{
    //    int width, height, n;

    //    unsigned char* image = stbi_load_from_memory((const unsigned char*)&buffer[0], buffer.size(), &width, &height, &n, 3);
    //    if (image)
    //    {
    //        printf("width=%d, height=%d at %d channels\n", width, height, n);
    //        gridSize = width;
    //        gridSpacing = 0.2;
    //        gridHeightScale = 0.2;
    //        fileIO.fileClose(fileId);
    //        long nElements = ((long)gridSize) * gridSize;
    //        //	std::cerr << "  nElements = " << nElements << "\n";

    //        int bytesPerElement = getByteSize(type);
    //        //	std::cerr << "  bytesPerElement = " << bytesPerElement << "\n";
    //       // btAssert(bytesPerElement > 0 && "bad bytes per element");

    //        long nBytes = nElements * bytesPerElement;
    //        //	std::cerr << "  nBytes = " << nBytes << "\n";
    //        byte_t* raw = new byte_t[nBytes];
    //      //  btAssert(raw && "out of memory");

    //        byte_t* p = raw;

    //        for (int j = 0; j < width; ++j)
    //        {

    //            for (int i = 0; i < width; ++i)
    //            {
    //                float x = i * gridSpacing;
    //                float y = j * gridSpacing;
    //                float heightScaling = (14. / 256.);
    //                float z = double(image[(width - 1 - i) * 3 + width * j * 3]) * heightScaling;
    //                convertFromFloat(p, z, type);
    //                // update min/max
    //                if (!i && !j) {
    //                    minHeight = z;
    //                    maxHeight = z;
    //                }
    //                else {
    //                    if (z < minHeight) {
    //                        minHeight = z;
    //                    }
    //                    if (z > maxHeight) {
    //                        maxHeight = z;
    //                    }
    //                }

    //                p += bytesPerElement;
    //            }
    //        }
    //        return raw;

    //    }

    //}
    return nullptr;
}

btScalar Terrain::convertToFloat(const byte_t* p, PHY_ScalarType type)
{
 
       // btAssert(p);

        switch (type) {
        case PHY_FLOAT:
        {
            btScalar* pf = (btScalar*)p;
            return *pf;
        }

        case PHY_UCHAR:
        {
            unsigned char* pu = (unsigned char*)p;
            return ((*pu) * gridHeightScale);
        }

        case PHY_SHORT:
        {
            short* ps = (short*)p;
            return ((*ps) * gridHeightScale);
        }

        default:
        //    btAssert(!"bad type");
            break;
        }

        return 0;

}

void Terrain::convertFromFloat(byte_t* p, btScalar value, PHY_ScalarType type)
{
  //  btAssert(p && "null");

    switch (type) {
    case PHY_FLOAT:
    {
        btScalar* pf = (btScalar*)p;
        *pf = value;
    }
    break;

    case PHY_UCHAR:
    {
        unsigned char* pu = (unsigned char*)p;
        *pu = (unsigned char)(value / gridHeightScale);
    }
    break;

    case PHY_SHORT:
    {
        short* ps = (short*)p;
        *ps = (short)(value / gridHeightScale);
    }
    break;

    default:
  //      btAssert(!"bad type");
        break;
    }
}
