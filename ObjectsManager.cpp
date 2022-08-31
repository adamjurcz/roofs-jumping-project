#include "ObjectsManager.h"

ObjectsManager::ObjectsManager() {
}

ObjectsManager::~ObjectsManager() {
	for (auto obj : buildings) {
		delete obj;
	}
	buildings.clear();
	for (auto obj : shootedCubes) {
		delete obj;
	}
	shootedCubes.clear();
}

void ObjectsManager::initializeObjectsManager(Physics& physics) {
	this->physics.reset(&physics);
}


void ObjectsManager::addBuilding(btVector3 size, const float& mass, const btVector3& color, const btVector3& initialPosition, const btQuaternion& initialRotation) {
	PhysicCube* obj = PhysicCube::createPhysicCube(size, mass, color, initialPosition, initialRotation);
	if (physics->getDynamicsWorld()) {
		physics->getDynamicsWorld()->addRigidBody(obj->GetRigidBody());
	}
	buildings.push_back(obj);
}

void ObjectsManager::addShootedCube(btVector3 size, const float& mass, const btVector3& color, const btVector3& initialPosition, const btQuaternion& initialRotation, btVector3 vel) {
	PhysicCube* obj = PhysicCube::createPhysicCube(size, mass, color, initialPosition, initialRotation);
	obj->GetRigidBody()->setLinearVelocity(vel);
	if (physics->getDynamicsWorld()) {
		physics->getDynamicsWorld()->addRigidBody(obj->GetRigidBody());
	}
	buildings.push_back(obj);
}

std::vector<PhysicCube*>& ObjectsManager::getBuildings(){
	return buildings;
}

std::vector<PhysicCube*>& ObjectsManager::getShootedCubes() {
	return shootedCubes;
}