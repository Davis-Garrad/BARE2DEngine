#include "Boid.hpp"

#include <random>

Boid::Boid(float X, float Y, float Size) : x(X), y(Y), size(Size)
{
	int xDir = (std::rand() % 200) - 100;
	int yDir = (std::rand() % 200) - 100;
	
	direction = glm::vec2(xDir, yDir);
	
	direction = glm::normalize(direction);
}

Boid::~Boid()
{
}

void Boid::update(std::vector<Boid*>& others) {
	x += direction.x * speed;
	y += direction.y * speed;
	
	// For alignment
	glm::vec2 avgDirection(0.0f);
	
	// For cohesion
	glm::vec2 centreMass(0.0f);
	
	// For separation
	glm::vec2 avgNeighbours(0.0f);
	
	unsigned int numNeighbours = 0;
	
	for(unsigned int i = 0; i < others.size(); i++) {
		if(others[i] == this) continue; // Don't want to do this to ourself!
		
		glm::vec2 other = glm::vec2(others[i]->x, others[i]->y);
		glm::vec2 self = glm::vec2(x, y);
		float distance = glm::distance(other, self);
		
		glm::vec2 dirToOther = glm::normalize(other-self);
		
		float agreeance = glm::dot(dirToOther, direction);
		
		if(distance < threshold && agreeance > (1.0f - viewCone)) {
			numNeighbours++;
			
			avgDirection += others[i]->direction / std::pow(distance/threshold, 2.0f);
			centreMass += other - self;
			avgNeighbours += (other - self) / std::pow(distance/(threshold/2.0f), 1.0f); // 1/Distance weighted position.
		}
	}
	
	if(numNeighbours > 0) {
		avgDirection /= numNeighbours;
		centreMass /= numNeighbours;
		avgNeighbours /= numNeighbours;
		
		glm::vec2 newDirection = (avgDirection * alignmentWeight + centreMass * cohesionWeight - avgNeighbours * separationWeight) / (alignmentWeight + cohesionWeight + separationWeight);

		direction += glm::normalize(newDirection) / smoothness;
		direction = glm::normalize(direction);
	}
}

