#pragma once

#include <glm/glm.hpp>
#include <vector>

class Boid
{
public:
	Boid(float X, float Y, float Size);
	~Boid();
	
	void update(std::vector<Boid*>& others);
	
	float x, y, size;
	float speed = 1.0f;
	glm::vec2 direction;
	
	float separationWeight = 3.0f;
	float alignmentWeight = 3.0f;
	float cohesionWeight = 2.0f;
	float smoothness = 20.0f;
	float threshold = 100.0f;
	float viewCone = 1.5f; // 1.0f corresponds to pi/2 radians each side of the "head", so 1.5 is 3pi/4

};

