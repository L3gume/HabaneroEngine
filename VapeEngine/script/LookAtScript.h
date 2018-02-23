//
// Created by notjustin on 2/22/18.
//

#ifndef VAPEENGINE_LOOKATSCRIPT_H
#define VAPEENGINE_LOOKATSCRIPT_H


#include <components/ScriptComponent.h>
#include <components/TransformComponent.h>

class LookAtScript : public Script {
public:
    LookAtScript() {
        m_sName = "PlayerMovementScript";
    }

    TransformComponent* transform = nullptr;
    TransformComponent* parentTransform = nullptr;

    void init() override;
    void update(float _deltaTime) override;
};


#endif //VAPEENGINE_LOOKATSCRIPT_H
