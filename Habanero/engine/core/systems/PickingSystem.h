#pragma once
#include "engine/core/ecs/system.h"
#include "engine/core/input/InputMessage.h"
#include "engine/core/input/InputListener.h"

class PickingSystem : public ecs::System, public input::InputListener {
    friend class ecs::SystemManager;
public:
    void onKeyPressed(const input::KeyboardInputMessage& _kbdMsg) override {}
    void onMouseMoved(const input::MouseMovedInputMessage& _msMsg) override {};
    void onMousePressed(const input::MouseClickedInputMessage& _msMsg) override;
    void onMouseScrolled(const input::MouseScrolledInputMessage& _msMsg) override {};

    void pick(int screenX, int screenY);

private:
    PickingSystem() : input::InputListener(false, false, true, false, false) {}
    virtual ~PickingSystem() {}
};