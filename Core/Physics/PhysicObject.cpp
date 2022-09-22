#include "PhysicObject.h"

PhysicObject::PhysicObject(btCollisionShape* pShape, float mass, const btVector3& color, const btVector3& initialPosition, const btQuaternion& initialRotation) {
	this->shape = pShape;
	this->color = color;

	btTransform transform;
	transform.setIdentity();
	transform.setOrigin(initialPosition);
	transform.setRotation(initialRotation);

	motionState = new OpenGLMotionState(transform);

	btVector3 localInertia(0, 0, 0);

	if (mass != 0.0f) {
		pShape->calculateLocalInertia(mass, localInertia);
	}

	btRigidBody::btRigidBodyConstructionInfo cInfo(mass, motionState, pShape, localInertia);
	body = new btRigidBody(cInfo);
}


PhysicObject::~PhysicObject() {
	delete shape;
	delete motionState;
	delete body;
}
