#include "Body.hpp"

Body::Body(glm::vec2 position, glm::vec2 velocity, double m, double r) : pos(position), vel(velocity), mass(m), radius(r)
{
}

Body::~Body()
{
}

void Body::update(std::vector<Body*> others) {
	pos += vel;
	
	if(mass < 0.1) return;
	
	for(unsigned int i = 0; i < others.size(); i++) {
		if(others[i] == this)
			continue;
			
		pos += glm::vec2(radius);
		others[i]->pos += glm::vec2(others[i]->radius);
			
		double r = glm::distance(others[i]->pos, pos);
		
		double force = mass * others[i]->mass / (std::pow(r, 2.0)) * 1.0e-11;
		
		if(r < (others[i]->radius + radius)) {
			if(others[i]->mass <= mass) {
				// Inherit all of mass + inertia
				glm::vec2 totalInertia = glm::vec2(mass) * vel + others[i]->vel * glm::vec2(others[i]->mass);// Conservation of inertia
				vel = totalInertia / glm::vec2(mass + others[i]->mass);
				mass += others[i]->mass;
				
				radius += std::pow(others[i]->radius, 2.0) / radius;
				
				pos -= glm::vec2(radius);
				others[i]->pos -= glm::vec2(others[i]->radius);
				
				others[i]->mass = 0.0;
				others[i]->radius = 0.0;
				
				continue;
			}
		}
		
		vel += glm::normalize(others[i]->pos - pos) * glm::vec2(force/mass);
		
		pos -= glm::vec2(radius);
		others[i]->pos -= glm::vec2(others[i]->radius);
	}
}
