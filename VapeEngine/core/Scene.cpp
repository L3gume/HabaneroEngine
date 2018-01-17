//
// Created by notjustin on 1/15/18.
//

#include "Scene.h"

using namespace Core;

void Scene::addObject(Core::GameObject* _gameObject) {
    if (_gameObject) {
        m_objects.emplace_back(_gameObject);
    }
}

void Scene::removeObject(std::string _tag) {
    auto found = std::find_if(m_objects.begin(), m_objects.end(), [_tag] (const GameObject* _gameObject) {
        return _gameObject->getTag() == _tag;
    });

    if (found != m_objects.end()) {
        delete *found;
        m_objects.erase(found);
    }
}

void Scene::removeObject(const int _id) {
    auto found = std::find_if(m_objects.begin(), m_objects.end(), [_id] (const GameObject* _gameObject) {
        return _gameObject->getID() == _id;
    });

    if (found != m_objects.end()) {
        delete *found;
        m_objects.erase(found);
    }
}

Core::GameObject* Scene::findObjectByTag(std::string _tag) {
    auto found = std::find_if(m_objects.begin(), m_objects.end(), [_tag] (const GameObject* _gameObject) {
        return _gameObject->getTag() == _tag;
    });

    return found != m_objects.end() ? *found : nullptr;
}

Core::GameObject* Scene::findObjectByID(int _id) {
    auto found = std::find_if(m_objects.begin(), m_objects.end(), [_id] (const GameObject* _gameObject) {
        return _gameObject->getID() == _id;
    });

    return found != m_objects.end() ? *found : nullptr;
}

void Scene::update() {
    // Update all of the GameObjects in the scene (include physics or not?)
    for (const auto it : m_objects) {
        it->update();
    }
}




