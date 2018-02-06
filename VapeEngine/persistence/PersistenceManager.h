//
// Created by notjustin on 2/6/18.
//

#ifndef VAPEENGINE_PERSISTENCEMANAGER_H
#define VAPEENGINE_PERSISTENCEMANAGER_H

class PersistenceManager {
public:
    static PersistenceManager& getInstance() {
        static PersistenceManager instance;
        return instance;
    }

    PersistenceManager(PersistenceManager const &) = delete;
    void operator=(PersistenceManager const &) = delete;

    /*
     * TODO:
     *
     * implement prefabs: serialize gameObject with all of its components and children
     * implement scenes: serialize the scene and all the objects and/or prefabs within it
     * project files: global settings and stuff.
     *
     * use either xml or json for simplicity.
     */

private:
    PersistenceManager() = default;
};


#endif //VAPEENGINE_PERSISTENCEMANAGER_H
