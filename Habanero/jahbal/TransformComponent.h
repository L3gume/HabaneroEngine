#pragma once

#include "Component.h"

class TransformComponent : public Component
{
public:
	TransformComponent(BaseEntity* owner);
	~TransformComponent();
};

