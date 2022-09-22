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
	shootedCubes.push_back(obj);
}

void ObjectsManager::addTreeCoords(btVector3 vec) {
	treeCoords.push_back(vec);
}

void ObjectsManager::checkForCollisionUpdate() {
	std::set<CollisionPair> pairsThisUpdate;

	for (int i = 0; i < physics->getCollisionDispatcher()->getNumManifolds(); ++i){
		btPersistentManifold* pManifold = physics->getCollisionDispatcher()->getManifoldByIndexInternal(i);

		if (pManifold->getNumContacts() > 0) {
			const btRigidBody* pBody0 = static_cast<const btRigidBody*>(pManifold->getBody0());
			const btRigidBody* pBody1 = static_cast<const btRigidBody*>(pManifold->getBody1());

			bool const swapped = pBody0 > pBody1;
			const btRigidBody* pSortedBodyA = swapped ? pBody1 : pBody0;
			const btRigidBody* pSortedBodyB = swapped ? pBody0 : pBody1;

			CollisionPair thisPair = std::make_pair(pSortedBodyA, pSortedBodyB);

			pairsThisUpdate.insert(thisPair);

			if (collisionPairs.find(thisPair) == pairsThisUpdate.end()) {
				//CollisionEvent((btRigidBody*)pBody0, (btRigidBody*)pBody1);
			}
		}
	}

	std::set<CollisionPair> removedPairs;
	std::set_difference(collisionPairs.begin(), collisionPairs.end(),
		pairsThisUpdate.begin(), pairsThisUpdate.end(),
		std::inserter(removedPairs, removedPairs.begin()));

	for (std::set<CollisionPair>::const_iterator iter = removedPairs.begin(); iter != removedPairs.end(); ++iter) {
		//SeparationEvent((btRigidBody*)iter->first, (btRigidBody*)iter->second);
	}
	collisionPairs = pairsThisUpdate;
}


bool ObjectsManager::raycast(const btVector3& startPosition, const btVector3& direction, btVector3& output, btVector3& normal) {
	if (!physics->getDynamicsWorld())
		return false;

	btVector3 rayTo = direction;
	btVector3 rayFrom = startPosition;

	btCollisionWorld::ClosestRayResultCallback rayCallback(rayFrom, rayTo);

	physics->getDynamicsWorld()->rayTest(rayFrom, rayTo, rayCallback);

	if (rayCallback.hasHit())
	{
		output = rayCallback.m_hitPointWorld;
		normal = rayCallback.m_hitNormalWorld;
		return true;
	}
	return false;
}


std::vector<PhysicCube*>& ObjectsManager::getBuildings(){
	return buildings;
}

std::vector<PhysicCube*>& ObjectsManager::getShootedCubes() {
	return shootedCubes;
}

std::vector<btVector3>& ObjectsManager::getTreeCoords() {
	return treeCoords;
}