#ifndef OBJECTSMANAGER_H
#define OBJECTSMANAGER_H

#include <iostream>
#include <vector>
#include <memory>
#include <bullet/btBulletDynamicsCommon.h>

#include "Physics.h"
#include "PhysicCube.h"

class ObjectsManager {
private:
	std::vector<PhysicCube*> buildings;
	std::vector<PhysicCube*> shootedCubes;

	std::shared_ptr<Physics> physics;
	
public:
	ObjectsManager();
	~ObjectsManager();

	void initializeObjectsManager(Physics& physics);

	void addBuilding(btVector3 size, const float& mass, const btVector3& color, const btVector3& initialPosition, const btQuaternion& initialRotation);
	void addShootedCube(btVector3 size, const float& mass, const btVector3& color, const btVector3& initialPosition, const btQuaternion& initialRotation, btVector3 vel);

	std::vector<PhysicCube*>& getBuildings();
	std::vector<PhysicCube*>& getShootedCubes();

};



#endif