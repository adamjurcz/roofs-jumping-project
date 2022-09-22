#include "Physics.h"

Physics::Physics() : 
m_pBroadphase(0),
m_pCollisionConfiguration(0),
m_pDispatcher(0),
m_pSolver(0),
m_pWorld(0)
{}

Physics::~Physics() {
	shutdownPhysics();
}

void Physics::initializePhysics() {
	//
	m_pCollisionConfiguration = new btDefaultCollisionConfiguration();
	// 
	m_pDispatcher = new btCollisionDispatcher(m_pCollisionConfiguration);
	// 
	m_pBroadphase = new btDbvtBroadphase();
	// 
	m_pSolver = new btSequentialImpulseConstraintSolver();
	// 
	m_pWorld = new btDiscreteDynamicsWorld(m_pDispatcher, m_pBroadphase, m_pSolver, m_pCollisionConfiguration);
}

void Physics::shutdownPhysics() {
	delete m_pWorld;
	delete m_pSolver;
	delete m_pBroadphase;
	delete m_pDispatcher;
	delete m_pCollisionConfiguration;
}

void Physics::updatePhysicScene(float dt) {
	if (m_pWorld) {
		m_pWorld->stepSimulation(dt);
		m_pWorld->performDiscreteCollisionDetection();
	}
}

