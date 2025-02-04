#ifndef PANEL_H
#define PANEL_H

#include "Interface.h"
#include <string>

class Panel
{
public:
	Panel(const char* name, bool active = true) : name(name), active(active) {}
	virtual ~Panel() {};

	virtual void Draw() {};

public:
	bool active;
	int w, h, x, y;

	ImVec4 yellow = ImVec4(255, 255, 0, 255);
	std::string name;
};

#endif