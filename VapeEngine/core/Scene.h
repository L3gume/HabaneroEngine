//
// Created by notjustin on 1/15/18.
//

#ifndef VAPEENGINE_SCENE_H
#define VAPEENGINE_SCENE_H

#include "GameObject.h"

namespace Core {

    class Scene {
    public:
        explicit Scene(std::string _name) : m_sName(_name) {}

        inline std::string getName() { return m_sName; }
        inline std::string setName(std::string _name) { m_sName = _name; }

        void addObject(GameObject* _gameObject);

        // The remove methods will delete the object
        void removeObject(std::string _tag);
        void removeObject(int _id);

        GameObject* findObjectByTag(std::string _tag); // returns nullptr if it fails
        GameObject* findObjectByID(int _id); // returns nullptr if it fails

        inline std::vector<GameObject*> getObjects() { return m_objects; }

        void update(); // updates all of the objects stored in the scene
    private:
        std::string m_sName;
        std::vector<GameObject*> m_objects;
    };

}

#endif //VAPEENGINE_SCENE_H