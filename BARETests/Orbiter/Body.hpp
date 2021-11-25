#pragma once

#include <glm/glm.hpp>
#include <vector>

class Body
{
public:
	Body(glm::vec2 position, glm::vec2 velocity, double m, double r);
	~Body();
	
	void update(std::vector<Body*> others);
	
	glm::vec2 pos;
	glm::vec2 vel;
	double mass;
	double radius;

};

