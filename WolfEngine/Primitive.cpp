#include "Primitive.h"
#include "Globals.h"
#include "OpenGL.h"
#include "Application.h"
#include "ModuleRender.h"

Primitive::Primitive()
{
}

Primitive::Primitive(const float3& size, const Color& color) : size(size), color(color)
{
}

Primitive::Primitive(const float3& position, const float3& size, const Color& color) : size(size), position(position), color(color)
{
}

Primitive::~Primitive()
{
}

PrimitivePlane::PrimitivePlane() : Primitive()
{
}

PrimitivePlane::PrimitivePlane(float width, float position_y, float distance, const Color& color) : Primitive(float3(0.0f, 0.0f, position_y), float3(width, 0.0f, width), color), lines_distance(distance)
{
	num_lines = ((int)((width) / lines_distance)) + 1;
	edges = width * 0.5f;
}

void PrimitivePlane::Draw() const
{
	glLineWidth(2.0f);
	App->renderer->DrawColor(color);

	glBegin(GL_LINES);
	for (int i = 0; i < num_lines; i++)
	{
		glVertex3f(-edges + i*lines_distance, 0.0, -edges);
		glVertex3f(-edges + i*lines_distance, 0.0, edges);
		glVertex3f(-edges, 0.0, -edges + i*lines_distance);
		glVertex3f(edges, 0.0, -edges + i*lines_distance);
	}
	glEnd();
}

PrimitiveCube::PrimitiveCube() : Primitive()
{
	type = Primitive::Type::CUBE;
	num_vertices = 12;
	num_indices = 36;
}

PrimitiveCube::PrimitiveCube(const float3& size) : Primitive(size)
{
	type = Primitive::Type::CUBE;
	num_vertices = 12;
	num_indices = 36;
}

PrimitiveCube::PrimitiveCube(const float3& position, const float3& size) : Primitive(position, size)
{
	type = Primitive::Type::CUBE;
	num_vertices = 12;
	num_indices = 36;
}

void PrimitiveCube::LoadMesh(float3* vertices, float2* tex_coord, float3* normals, unsigned* indices) const
{
	float3 half = size * 0.5f;

	float3 A = { -half.x, -half.y, half.z };
	float3 B = { half.x, -half.y, half.z };
	float3 C = { -half.x, half.y, half.z };
	float3 D = { half.x, half.y, half.z };
	float3 E = { -half.x, -half.y, -half.z };
	float3 F = { half.x, -half.y, -half.z };
	float3 G = { -half.x, half.y, -half.z };
	float3 H = { half.x, half.y, -half.z };

	float vert[] = { A.x, A.y, A.z,  B.x, B.y, B.z,  C.x, C.y, C.z,  D.x, D.y, D.z, E.x, E.y, E.z, F.x, F.y, F.z, G.x, G.y, G.z, H.x, H.y, H.z, A.x, A.y, A.z,  B.x, B.y, B.z, G.x, G.y, G.z, H.x, H.y, H.z };
	float texture_coord[] = { 0,0, 1,0, 0,1, 1,1, 1,0, 0,0, 1,1, 0,1, 1,1, 0,1, 0,0, 1,0 };
	float norm[] = { -1,-1,1, 1,-1,1, -1,1,1, 1,1,1, -1,-1,-1, 1,-1,-1, -1,1,-1, 1,1,-1, -1,-1,1, 1,-1,1, -1,1,-1, 1,1,-1 };
	unsigned triangles_indices[] = { 0, 1, 2,  2, 1, 3,  3, 9, 5,  3, 5, 11,  10, 4, 8,  10, 8, 2,  2, 3, 10,  10, 3, 11,  6, 7, 4,  4, 7, 5,  4, 5, 8,  8, 5, 9 };

	memcpy(vertices, vert, 3 * num_vertices * sizeof(float));
	memcpy(tex_coord, texture_coord, 2 * num_vertices * sizeof(float));
	memcpy(normals, norm, 3 * num_vertices * sizeof(float));
	memcpy(indices, triangles_indices, num_indices * sizeof(unsigned));
}