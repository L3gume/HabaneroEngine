//
// Created by l3gume on 20/02/18.
//
#if EDITOR

#include <core/Engine.h>
#include <components/TransformComponent.h>
#include <components/CameraComponent.h>
#include "EditorController.h"

void EditorController::addNewEntity(std::string _name, ECS::Entity* _parent) {
    auto& ent = Core::Engine::getInstance().getEntityManager().addEntity(_name);
    ent.addComponent<TransformComponent>(glm::vec3(0.f, 0.f, 0.f), glm::vec3(0.f, 0.f, 0.f), glm::vec3(1.f, 1.f, 1.f));

    if (_parent) {
        ent.setParent(_parent);
        _parent->addChild(&ent);
    }
}

void EditorController::createNewScene() {
    Core::Engine::getInstance().reset();
    auto& cam = Core::Engine::getInstance().getEntityManager().addEntity("Camera");
    cam.addComponent<TransformComponent>(glm::vec3(0.f, 0.f, 0.f), glm::vec3(0.f, 0.f, 0.f), glm::vec3(1.f, 1.f, 1.f));
    cam.addComponent<CameraComponent>(90.f, 16.f, 9.f, 0.1f, 100.f);
}

#endif