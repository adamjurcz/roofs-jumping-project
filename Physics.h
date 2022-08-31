#ifndef PHYSICS_H
#define PHYSICS_H
#include <bullet/btBulletDynamicsCommon.h>
#include <iostream>


class Physics {
private:
	btBroadphaseInterface* m_pBroadphase;
	btCollisionConfiguration* m_pCollisionConfiguration;
	btCollisionDispatcher* m_pDispatcher;
	btConstraintSolver* m_pSolver;
	btDynamicsWorld* m_pWorld;

public:
	Physics();
	~Physics();

	void initializePhysics();
	void shutdownPhysics();

	void updatePhysicScene(float dt);

	btBroadphaseInterface* getBroadphaseInterface() {
		return m_pBroadphase;
	}

	btCollisionConfiguration* getCollisionConfiguration() {
		return m_pCollisionConfiguration;
	}

	btCollisionDispatcher* getCollisionDispatcher() {
		return m_pDispatcher;
	}

	btConstraintSolver* getConstraintSolver() {
		return m_pSolver;
	}

	btDynamicsWorld* getDynamicsWorld() {
		return m_pWorld;
	}

};



#endif
