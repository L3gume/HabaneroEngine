//
// Created by l3gume on 20/02/18.
//

#ifndef VAPEENGINE_EDITORCONTROLLER_H
#define VAPEENGINE_EDITORCONTROLLER_H

#if EDITOR

class EditorController {
public:
    static EditorController &getInstance() {
        static EditorController instance; // Guaranteed to be destroyed.
        return instance;
    }

    EditorController(EditorController const &) = delete;
    void operator=(EditorController const &) = delete;

    void addNewEntity(std::string _name);
    void createNewScene();

private:
    EditorController() = default;
};

#endif

#endif //VAPEENGINE_EDITORCONTROLLER_H
