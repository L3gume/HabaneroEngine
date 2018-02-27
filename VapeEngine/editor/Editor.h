//
// Created by l3gume on 04/02/18.
//

#ifndef VAPEENGINE_EDITOR_H
#define VAPEENGINE_EDITOR_H

#if EDITOR

#include <common/VapeGL.h>
#include <imgui/imgui.h>
#include <imgui/imgui_impl_glfw_gl3.h>
#include <common/util.h>
#include <core/GameObject.h>
#include <logging/LogManager.h>
#include <logging/LogMessage.h>
#include <input/InputListener.h>
#include <core/Engine.h>
#include <imgui/ImguiWindowsFileIO.hpp>
#include <fstream>
#include <ecs/ecs.h>


namespace VapeUI {

    /*
     * Singleton class, since the UI is dynamic we only really need one class to render it.
     */
    class Editor : public VapeInput::InputListener {
    public:
        static Editor &getInstance() {
            static Editor instance; // Guaranteed to be destroyed.
            return instance;
        }

        Editor(Editor const &) = delete;
        void operator=(Editor const &) = delete;

        void init(GLFWwindow *_window);
        void render(); // Renders the UI, called every frame.
        void shutDown();
        void reset() { m_selectedEntity = nullptr; }

        void onKeyPressed(const VapeInput::KeyboardInputMessage &_kbdMsg) override;
        void onMouseMoved(const VapeInput::MouseMovedInputMessage &_msMsg) {}
        void onMousePressed(const VapeInput::MouseClickedInputMessage &_msMsg) {}
        void onMouseScrolled(const VapeInput::MouseScrolledInputMessage &_msMsg) {}
    private:
        Editor() : InputListener(true, false, true, false, false) {
            m_bShowMenuBar = true;
            m_bShowLogWindow = true;
            m_bShowInspector = true;
            m_bShowObjTree = true;
            m_bShowSaveScene = false;
            m_bShowOpenScene = false;
            m_bScrollDownParent = false;
            m_selectedEntity = nullptr;
        };

        void showMainMenuBar();
        void showMenuFile();
        void showLogWindow();
        void showInspector();
        void showObjTree();
        void showFileBrowser(); // maybe?
        void showNewEntWindow();
        void showAddComponentWindow();

        void showOpenDialog();
        void showSaveDialog();

        void addObjTreeNode(ECS::Entity* obj);
        void renderTransformInspector();
        void renderRenderableInspector();
        void renderScriptInspector();
        void renderCameraInspector();
        void renderBoxColliderInspector();

        GLFWwindow *m_window = nullptr;
        ECS::Entity* m_selectedEntity = nullptr;
        ECS::Entity* m_newEntParent = nullptr;
        ImVec4 clear_color;
        std::vector<ECS::Entity*> m_treeNodes;
        std::vector<std::string> m_sRecentFiles;

        // stuff that is on by default:
        bool m_bShowMenuBar         : 1;
        bool m_bShowLogWindow       : 1;
        bool m_bShowInspector       : 1;
        bool m_bShowObjTree         : 1;
        // Stuff that isn't
        bool m_bShowSaveScene       : 1;
        bool m_bShowOpenScene       : 1;
        bool m_bShowNewEntWindow    : 1;
        bool m_bShowAddComponent    : 1;
        bool m_bScrollDownParent    : 1;
        /* TODO */

        char buf[50];
    };

}

#endif

#endif //VAPEENGINE_EDITOR_H
