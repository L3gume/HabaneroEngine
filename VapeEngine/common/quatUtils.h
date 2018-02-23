//
// Created by notjustin on 1/19/18.
//

#ifndef VAPEENGINE_QUATUTILS_H
#define VAPEENGINE_QUATUTILS_H

#include <glm/glm.hpp>
#include <glm/gtc/quaternion.hpp>
#include <glm/gtx/quaternion.hpp>
#include <glm/gtx/euler_angles.hpp>
#include <glm/gtx/norm.hpp>

using namespace glm;

static quat rotationBetweenVectors(vec3 _start, vec3 _dest){
	_start = normalize(_start);
	_dest = normalize(_dest);

	float cosTheta = dot(_start, _dest);
	vec3 rotationAxis;

	if (cosTheta < -1 + 0.001f){
		// special case when vectors in opposite directions:
		// there is no "ideal" rotation axis
		// So guess one; any will do as long as it's perpendicular to _start
		rotationAxis = cross(vec3(0.0f, 0.0f, 1.0f), _start);
		if (length2(rotationAxis) < 0.01 ) // bad luck, they were parallel, try again!
			rotationAxis = cross(vec3(1.0f, 0.0f, 0.0f), _start);

		rotationAxis = normalize(rotationAxis);
		return angleAxis(glm::radians(180.0f), rotationAxis);
	}

	rotationAxis = cross(_start, _dest);

	float s = sqrt( (1+cosTheta)*2 );
	float invs = 1 / s;

	return quat(
		s * 0.5f,
		rotationAxis.x * invs,
		rotationAxis.y * invs,
		rotationAxis.z * invs
	);

}

static quat lookAt(vec3 _direction, vec3 _desiredUp){

	if (length2(_direction) < 0.0001f )
		return quat();

	// Recompute _desiredUp so that it's perpendicular to the _direction
	// You can skip that part if you really want to force _desiredUp
	vec3 right = cross(_direction, _desiredUp);
	_desiredUp = cross(right, _direction);

	// Find the rotation between the front of the object (that we assume towards +Z,
	// but this depends on your model) and the desired _direction
	quat rot1 = rotationBetweenVectors(vec3(0.0f, 0.0f, 1.0f), _direction);
	// Because of the 1rst rotation, the up is probably completely screwed up.
	// Find the rotation between the "up" of the rotated object, and the desired up
	vec3 newUp = rot1 * vec3(0.0f, 1.0f, 0.0f);
	quat rot2 = rotationBetweenVectors(newUp, _desiredUp);

	// Apply them
	return rot2 * rot1; // remember, in reverse order.
}



// Like SLERP, but forbids rotation greater than maxAngle (in radians)
// In conjunction to LookAt, can make your characters
static quat rotateTowards(quat _q1, quat _q2, float _maxAngle) {

	if( _maxAngle < 0.001f ){
		// No rotation allowed. Prevent dividing by 0 later.
		return _q1;
	}

	float cosTheta = dot(_q1, _q2);

	// q1 and q2 are already equal.
	// Force q2 just to be sure
	if(cosTheta > 0.9999f){
		return _q2;
	}

	// Avoid taking the long path around the sphere
	if (cosTheta < 0){
		_q1 = _q1*-1.0f;
		cosTheta *= -1.0f;
	}

	float angle = acos(cosTheta);

	// If there is only a 2° difference, and we are allowed 5°,
	// then we arrived.
	if (angle < _maxAngle){
		return _q2;
	}

	// This is just like slerp(), but with a custom t
	float t = _maxAngle / angle;
	angle = _maxAngle;

	quat res = (sin((1.0f - t) * angle) * _q1 + sin(t * angle) * _q2) / sin(angle);
	res = normalize(res);
	return res;
}

#endif //VAPEENGINE_QUATUTILS_H
