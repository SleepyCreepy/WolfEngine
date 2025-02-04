#include "Billboard.h"
#include "Application.h"
#include "ModuleRender.h"
#include "Color.h"
#include "ModuleTextures.h"
#include "OpenGL.h"


Billboard::Billboard(aiString & texture, float3 position, float up, float right) : position(position), up(up), right(right)
{
	this->texture = App->textures->LoadTexture(texture);
}

Billboard::~Billboard()
{
}

void Billboard::ComputeQuad(float3 camera)
{
	float3 right_vector =  (position - camera).Cross(up_vector);
	right_vector.Normalize();
	vertices[0] = position + (up * up_vector) + (right * right_vector);
	vertices[1] = position - (up * up_vector) + (right * right_vector);
	vertices[2] = position + (up * up_vector) - (right * right_vector);
	vertices[3] = position - (up * up_vector) - (right * right_vector);
}

void Billboard::Draw(float3 scale, float2 texture_scale)
{
	glEnable(GL_COLOR_MATERIAL);
	glBindTexture(GL_TEXTURE_2D, texture);

	App->renderer->debug_drawer->SetColor(Colors::White);

	glPushMatrix();
	glScalef(scale.x, scale.y, scale.z);

	glBegin(GL_TRIANGLES);

	glTexCoord2f(1.0f * texture_scale.x, 1.0f * texture_scale.y);
	glVertex3f(vertices[0].x, vertices[0].y, vertices[0].z);
	glTexCoord2f(0.0f, 1.0f * texture_scale.y);
	glVertex3f(vertices[2].x, vertices[2].y, vertices[2].z);
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(vertices[3].x, vertices[3].y, vertices[3].z);
	glTexCoord2f(1.0f * texture_scale.x, 1.0f * texture_scale.y);
	glVertex3f(vertices[0].x, vertices[0].y, vertices[0].z);
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(vertices[3].x, vertices[3].y, vertices[3].z);
	glTexCoord2f(1.0f * texture_scale.x, 0.0f);
	glVertex3f(vertices[1].x, vertices[1].y, vertices[1].z); 

	glEnd();
	glPopMatrix();

	App->renderer->debug_drawer->SetColor(Colors::Black);
	glBindTexture(GL_TEXTURE_2D, 0);
	glDisable(GL_COLOR_MATERIAL);
}
