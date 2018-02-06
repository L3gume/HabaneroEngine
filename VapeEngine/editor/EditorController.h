//
// Created by l3gume on 05/02/18.
//

#ifndef VAPEENGINE_EDITORCONTROLLER_H
#define VAPEENGINE_EDITORCONTROLLER_H

#if EDITOR

/*
 * MVC pattern, controls some UI featurese
 */
class EditorController {
public:
    static EditorController &getInstance() {
        static EditorController instance; // Guaranteed to be destroyed.
        return instance;
    }

    EditorController(EditorController const &) = delete;
    void operator=(EditorController const &) = delete;

    void openScene();
    void saveScene();
private:
    EditorController() = default;
};

#endif

#endif //VAPEENGINE_EDITORCONTROLLER_H
