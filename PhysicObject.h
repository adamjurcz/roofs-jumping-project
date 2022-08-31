#ifndef PHYSICOBJECT_H
#define PHYSICOBJECT_H

#include <memory>
#include <bullet/btBulletDynamicsCommon.h>

#include "OpenGLMotionState.h"

class PhysicObject {
private:

protected:
	btCollisionShape* shape;
	btRigidBody* body;
	OpenGLMotionState* motionState;
	btVector3 color;

public:
	PhysicObject(btCollisionShape* pShape, float mass, const btVector3& color, const btVector3& initialPosition = btVector3(0, 0, 0), const btQuaternion& initialRotation = btQuaternion(0, 0, 1, 1));
	virtual ~PhysicObject();

	btCollisionShape* GetShape() { return shape; }
	btRigidBody* GetRigidBody() { return body; }
	OpenGLMotionState* GetMotionState() { return motionState; }

	void GetTransform(btScalar* transform) {
		if (motionState) motionState->GetWorldTransform(transform);
	}

	btVector3 GetColor() { return color; }
};



#endif