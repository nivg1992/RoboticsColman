#include "LocalizationManager.h"

namespace Managers {

LocalizationManager::LocalizationManager(Location currLocation,
		AnotherMap* currMap, double maxDistance, LaserProxy* laserProxy) {
	// add the location
	this->currLocation = Location(currLocation);
	this->particles = vector<Particle*>();

	// first particle
	Particle* fatherParticle = new Particle(this->currLocation.m_X,
			this->currLocation.m_Y, this->currLocation.m_Yaw, 1);

	// give the father particle the map	fatherParticle.SetMap(currMap);
	fatherParticle->SetMaxDistance(maxDistance);
	fatherParticle->SetMap(currMap);
	fatherParticle->SetLaserProxy(laserProxy);
	this->particles.push_back(fatherParticle);

	// rando all the particle list
	for (unsigned i = 0; i < NUMBER_OF_PARTICLE; i++) {
		this->particles.push_back(
				fatherParticle->CreateChild(PARTICALE_RADIOS_FROM_ROBOT,
						PARTICAL_DGREE_YAW_FROM_ROBOT));
	}

}

void LocalizationManager::update(float deltaX, float deltaY, float deltaYaw,
		float laserArr[], Cell* nextWaypoint) {
	vector<unsigned int> indexesToDelete;
	vector<Particle*> newParticles;
	unsigned int maxIndex = 0;
	unsigned int particleCount = this->particles.size();

	for (unsigned int i = 0; i < particleCount; i++) {
		Particle* particle = this->particles[i];
		particle->Update(deltaX, deltaY, deltaYaw, laserArr, nextWaypoint);
		if (this->particles[maxIndex]->belief < particle->belief) {
			maxIndex = i;
		}
		if (particle->belief >= TRASHHOLE) {
			newParticles.push_back(particle);
		}
	}

	if (newParticles.size() == 0) {
		newParticles.push_back(this->particles[maxIndex]);
	}

	Particle* bestParticle = this->particles[maxIndex];
	for (unsigned int i = newParticles.size(); i < particleCount; i++) {
		Particle* newParticle = bestParticle->CreateChild(
			Utils::MathUtil::cmToPx(PARTIACLE_CHILED_RADIOS_CM),
			PARTICAL_DGREE_YAW
		);
		newParticles.push_back(newParticle);
	}

	this->particles = newParticles;

}

Location LocalizationManager::BestLocation() {
	Particle* best = this->particles[0];
	for (Particle* p : this->particles) {
		if (best->belief < p->belief) {
			best = p;
		}
	}

	return (Location(best->x, best->y, best->yaw));
}

LocalizationManager::~LocalizationManager() {
	this->currLocation.~Location();
}
}
