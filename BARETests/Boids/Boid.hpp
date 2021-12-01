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
	float speed = 2.0f;
	glm::vec2 direction;
	
	float separationWeight = 1.8f;
	float alignmentWeight = 1.5f;
	float cohesionWeight = 1.0f;
	float herdCohesionWeight = 0.6f;
	float herdOrbitRadius = 1000.0f;
	float smoothness = 30.0f/speed;
	float threshold = 40.0f;
	float maxThreshold = 50.0f;
	float viewCone = 1.5f; // 1.0f corresponds to pi/2 radians each side of the "head", so 1.5 is 3pi/4

};

