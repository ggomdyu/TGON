#pragma once

namespace tgon
{


struct Vertex
{
	float x, y, z;
};

struct TexVertex
{
	float x, y, z;			// Element
	float nx, ny, nz;		// Normal vector
	float u, v;			// TexCoord
};


}