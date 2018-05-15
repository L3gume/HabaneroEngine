//
// Created by l3gume on 20/02/18.
//

#ifndef HABANERO_SCENEMANAGER_H
#define HABANERO_SCENEMANAGER_H

#include <string>
#include "../ecs/EntityConstructor.h"

/*
 * There won't be a "Scene" class this time around, a scene is essentially only going to be a collection of entities
 * that we load into the entity manager.
 */
class SceneManager {
public:
    static SceneManager &getInstance() {
        static SceneManager instance;
        return instance;
    }

    SceneManager(SceneManager const &) = delete;
    void operator=(SceneManager const &) = delete;

    // -----------------------------------------------------------------------------------------------------------------
    //                                      Scene functions
    // -----------------------------------------------------------------------------------------------------------------

    void saveScene(std::string _name); // Saves the currently loaded scene.
    void loadScene(const std::string& _path); // Loads a file and puts everything in the entityManager

    void backupScene(); // Backs up the active scene and keeps the path in mem
    void restoreScene(); // Reloads the backed up scene.

    // -----------------------------------------------------------------------------------------------------------------
    //                                      Entity functions
    // -----------------------------------------------------------------------------------------------------------------

    // TODO ?
private:
    SceneManager() = default;

    /*
     * When we switch between play and editor mode, we will save the scene, enter play mode, do our stuff, exit play mode,
     * and reload the scene from the file, we will keep the path of the file in memory.
     */
    std::string m_sActiveScene = "";
    std::string m_sBackedUpScene;
};


#endif //HABANERO_SCENEMANAGER_H
