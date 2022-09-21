#ifndef OBJECTSMANAGER_H
#define OBJECTSMANAGER_H

#include <iostream>
#include <vector>
#include <memory>
#include <set>
#include <algorithm>
#include <bullet/btBulletDynamicsCommon.h>


#include "Physics.h"
#include "PhysicCube.h"


typedef std::pair<const btRigidBody*, const btRigidBody*> CollisionPair;

class ObjectsManager {
private:
	std::set<CollisionPair> collisionPairs;

	std::vector<PhysicCube*> buildings;
	std::vector<PhysicCube*> shootedCubes;

	std::shared_ptr<Physics> physics;
	
public:
	ObjectsManager();
	~ObjectsManager();

	void initializeObjectsManager(Physics& physics);

	void addBuilding(btVector3 size, const float& mass, const btVector3& color, const btVector3& initialPosition, const btQuaternion& initialRotation);
	void addShootedCube(btVector3 size, const float& mass, const btVector3& color, const btVector3& initialPosition, const btQuaternion& initialRotation, btVector3 vel);

	void checkForCollisionUpdate();

	bool raycast(const btVector3& startPosition, const btVector3& direction, btVector3& output, btVector3& normal);


	std::vector<PhysicCube*>& getBuildings();
	std::vector<PhysicCube*>& getShootedCubes();

};



#endif