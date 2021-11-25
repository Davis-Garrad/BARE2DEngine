#include "Body.hpp"

Body::Body(glm::vec2 position, glm::vec2 velocity, double m, double r) : pos(position), vel(velocity), mass(m), radius(r)
{
}

Body::~Body()
{
}

void Body::update(std::vector<Body*> others) {
	pos += vel;
	
	for(unsigned int i = 0; i < others.size(); i++) {
		if(others[i] == this)
			continue;
			
		pos += glm::vec2(radius);
		others[i]->pos += glm::vec2(others[i]->radius);
			
		double r = glm::distance(others[i]->pos, pos);
		
		if(r < (others[i]->radius + radius)) {
			
			glm::vec2 adjustment = glm::normalize(pos - others[i]->pos) * (float)((others[i]->radius + radius) - r);
			
			others[i]->pos -= (adjustment)/2.0f;
			pos -= (-adjustment)/2.0f;
			
		}
		
		double force = mass * others[i]->mass / (std::pow(r, 2.0)) * 1.0e-11;
		
		vel += glm::normalize(others[i]->pos - pos) * glm::vec2(force/mass);
		
		
			
		pos -= glm::vec2(radius);
		others[i]->pos -= glm::vec2(others[i]->radius);
	}
}
