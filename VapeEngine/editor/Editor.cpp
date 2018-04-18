//
// Created by l3gume on 04/02/18.
//

#include <components/TransformComponent.h>
#include <core/SceneManager.h>
#include <components/ColliderComponent.h>
#include <components/RigidBodyComponent.h>
#include "Editor.h"
#include "EditorController.h"

/*
 * All of this code will only be compiled if in Editor mode.
 */
#if EDITOR

#define SORT_TIME 0x01
#define SORT_TAG 0x02
#define SORT_OCC 0x04
#define SORT_SEV 0x08
#define SORT_TYPE 0x16

using namespace VapeUI;

void Editor::init(GLFWwindow *_window) {
    m_window = _window;
    assert(m_window != nullptr);
    ImGui_ImplGlfwGL3_Init(m_window, true);

    clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);
    // Setup style
    ImGui::StyleColorsDark();
//    ImGui::StyleColorsClassic();
//    ImGui::StyleColorsLight();
    ImGuiIO &io = ImGui::GetIO();
    io.DisplaySize.x = x_res;
    io.DisplaySize.y = y_res;
    // TODO: Fill others settings of the io structure later.

    // Load texture atlas (there is a default font so you don't need to care about choosing a font yet)
    unsigned char *pixels;
    int width, height;
    io.Fonts->GetTexDataAsRGBA32(&pixels, &width, &height);
}

void Editor::render() {
    ImGui_ImplGlfwGL3_NewFrame();

    if (m_bShowMenuBar) showMainMenuBar();
    if (m_bShowLogWindow) showLogWindow();
    if (m_bShowObjTree) showObjTree();
    if (m_bShowInspector) showInspector();
    if (m_bShowOpenScene) showOpenDialog();
    if (m_bShowSaveScene) showSaveDialog();
    if (m_bShowNewEntWindow) showNewEntWindow();
    if (m_bShowAddComponent) showAddComponentWindow();

    int display_w, display_h;
    glfwGetFramebufferSize(m_window, &display_w, &display_h);
    glViewport(0, 0, display_w, display_h);
    glClearColor(0, 0, 0, 0);

    ImGui::Render();
}

void Editor::shutDown() {
    ImGui_ImplGlfwGL3_Shutdown();
}

void Editor::showMainMenuBar() {
    if (ImGui::BeginMainMenuBar()) {
        if (ImGui::BeginMenu("File")) {
            showMenuFile();
            ImGui::EndMenu();
        }
        if (ImGui::BeginMenu("Edit")) {
            if (ImGui::MenuItem("Undo", "CTRL+Z")) {}
            if (ImGui::MenuItem("Redo", "CTRL+Y", false, false)) {}  // Disabled item
            ImGui::Separator();
            if (ImGui::MenuItem("Cut", "CTRL+X")) {}
            if (ImGui::MenuItem("Copy", "CTRL+C")) {}
            if (ImGui::MenuItem("Paste", "CTRL+V")) {}
            ImGui::EndMenu();
        }
        if (ImGui::BeginMenu("View")) {
            if (ImGui::MenuItem("Log", "CTRL+L")) { m_bShowLogWindow = !m_bShowLogWindow; }
            if (ImGui::MenuItem("Scene Tree", "CTRL+T")) { m_bShowObjTree = !m_bShowObjTree; }
            if (ImGui::MenuItem("Inspector", "CTRL+I")) { m_bShowInspector = !m_bShowInspector; }
            // TODO
            ImGui::EndMenu();
        }
        if (ImGui::BeginMenu("Run")) {
            if (ImGui::MenuItem("Run Game", "CTRL+SHIFT+R")) {
                // TODO, run the game
                Core::Engine::getInstance().switchMode();
            }
            ImGui::EndMenu();
        }
        if (ImGui::BeginMenu("Scene")) {
            if (ImGui::MenuItem("New Scene", "CTRL+SHIFT+N")) {
                // TODO - Editor controller to handle this.
                EditorController::getInstance().createNewScene();
            }
            if (ImGui::MenuItem("Save Scene", "CTRL+SHIFT+S")) {
                m_bShowSaveScene = true;
            }
            if (ImGui::MenuItem("Open Scene", "CTRL+SHIFT+O")) {
                m_bShowOpenScene = true;
            }
            ImGui::EndMenu();
        }

        ImGui::EndMainMenuBar();
    }
}

void Editor::showMenuFile() {
    ImGui::MenuItem("(dummy menu)", nullptr, false, false);
    if (ImGui::MenuItem("New")) {}
    if (ImGui::MenuItem("Open", "Ctrl+O")) {}
    if (ImGui::BeginMenu("Open Recent")) {
        ImGui::MenuItem("fish_hat.c");
        ImGui::MenuItem("fish_hat.inl");
        ImGui::MenuItem("fish_hat.h");
        if (ImGui::BeginMenu("More..")) {
            ImGui::MenuItem("Hello");
            ImGui::MenuItem("Sailor");
            if (ImGui::BeginMenu("Recurse..")) {
                showMenuFile();
                ImGui::EndMenu();
            }
            ImGui::EndMenu();
        }
        ImGui::EndMenu();
    }
    if (ImGui::MenuItem("Save", "Ctrl+S")) {}
    if (ImGui::MenuItem("Save As..")) {}
    ImGui::Separator();
    if (ImGui::BeginMenu("Options")) {
        static bool enabled = true;
        ImGui::MenuItem("Enabled", "", &enabled);
        ImGui::BeginChild("child", ImVec2(0, 60), true);
        for (int i = 0; i < 10; i++)
            ImGui::Text("Scrolling Text %d", i);
        ImGui::EndChild();
        static float f = 0.5f;
        static int n = 0;
        static bool b = true;
        ImGui::SliderFloat("Value", &f, 0.0f, 1.0f);
        ImGui::InputFloat("Input", &f, 0.1f);
        ImGui::Combo("Combo", &n, "Yes\0No\0Maybe\0\0");
        ImGui::Checkbox("Check", &b);
        ImGui::EndMenu();
    }
    if (ImGui::BeginMenu("Colors")) {
        ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, ImVec2(0, 0));
        for (int i = 0; i < ImGuiCol_COUNT; i++) {
            const char *name = ImGui::GetStyleColorName((ImGuiCol) i);
            ImGui::ColorButton(name, ImGui::GetStyleColorVec4((ImGuiCol) i));
            ImGui::SameLine();
            ImGui::MenuItem(name);
        }
        ImGui::PopStyleVar();
        ImGui::EndMenu();
    }
    if (ImGui::BeginMenu("Disabled", false)) // Disabled
    {
        IM_ASSERT(0);
    }
    if (ImGui::MenuItem("Checked", NULL, true)) {}
    if (ImGui::MenuItem("Quit", "Alt+F4")) {
        Core::Engine::getInstance().shutDown();
    }
}

struct LogWindow {
    ImGuiTextBuffer Buf;
    ImGuiTextFilter Filter;
    ImVector<int> LineOffsets;        // Index to lines offset
    bool ScrollToBottom;

    void Clear() {
        Buf.clear();
        LineOffsets.clear();
    }

    void AddLog(const char *fmt, ...) IM_FMTARGS(2) {
        int old_size = Buf.size();
        va_list args;
        va_start(args, fmt);
        Buf.appendfv(fmt, args);
        va_end(args);
        for (int new_size = Buf.size(); old_size < new_size; old_size++)
            if (Buf[old_size] == '\n')
                LineOffsets.push_back(old_size);
        ScrollToBottom = true;
    }

    void Draw(const char *title, bool *p_open = nullptr) {
        ImGui::SetNextWindowSize(ImVec2(1200, 300), ImGuiCond_Once);
        ImGui::SetNextWindowPos(ImVec2(0, 750), ImGuiCond_Once);
        ImGui::Begin(title, p_open);
        if (ImGui::Button("Sort by: Time")) {
            Clear();
#if DEBUG
            VapeLog::LogManager::getInstance().printMessage(VapeLog::LogMessage(
                    VapeLog::LogTag::LOG, VapeLog::LogType::MESSAGE,
                    VapeLog::LogSeverity::LOW, "Sorting log by time"));
#endif

            VapeLog::LogManager::getInstance().setSortFlags(SORT_TIME);
        }
        ImGui::SameLine();
        if (ImGui::Button("Sort by: Tag")) {
            Clear();
#if DEBUG
            VapeLog::LogManager::getInstance().printMessage(VapeLog::LogMessage(
                    VapeLog::LogTag::LOG, VapeLog::LogType::MESSAGE,
                    VapeLog::LogSeverity::LOW, "Sorting log by tag"));
#endif
            VapeLog::LogManager::getInstance().setSortFlags(SORT_TAG);
        }
        ImGui::SameLine();
        if (ImGui::Button("Sort by: Occurences")) {
            Clear();
#if DEBUG
            VapeLog::LogManager::getInstance().printMessage(VapeLog::LogMessage(
                    VapeLog::LogTag::LOG, VapeLog::LogType::MESSAGE,
                    VapeLog::LogSeverity::LOW, "Sorting log by occurences"));
#endif
            VapeLog::LogManager::getInstance().setSortFlags(SORT_OCC);
        }
        ImGui::SameLine();
        if (ImGui::Button("Sort by: Severity")) {
            Clear();
#if DEBUG
            VapeLog::LogManager::getInstance().printMessage(VapeLog::LogMessage(
                    VapeLog::LogTag::LOG, VapeLog::LogType::MESSAGE,
                    VapeLog::LogSeverity::LOW, "Sorting log by severity"));
#endif
            VapeLog::LogManager::getInstance().setSortFlags(SORT_SEV);
        }
        ImGui::SameLine();
        if (ImGui::Button("Sort by: type")) {
            Clear();
#if DEBUG
            VapeLog::LogManager::getInstance().printMessage(VapeLog::LogMessage(
                    VapeLog::LogTag::LOG, VapeLog::LogType::MESSAGE,
                    VapeLog::LogSeverity::LOW, "Sorting log by type"));
#endif
            VapeLog::LogManager::getInstance().setSortFlags(SORT_TYPE);
        }
        ImGui::SameLine();
        bool copy = ImGui::Button("Copy");
        ImGui::SameLine();
        Filter.Draw("", -100.0f);
        ImGui::SameLine();
        if (ImGui::Button("Clear")) {
            Clear();
            VapeLog::LogManager::getInstance().clearLog();
        }
        ImGui::BeginChild("scrolling", ImVec2(0, 0), false, ImGuiWindowFlags_HorizontalScrollbar);
        if (copy) ImGui::LogToClipboard();

        if (Filter.IsActive()) {
            const char *buf_begin = Buf.begin();
            const char *line = buf_begin;
            for (int line_no = 0; line != NULL; line_no++) {
                const char *line_end = (line_no < LineOffsets.Size) ? buf_begin + LineOffsets[line_no] : NULL;
                if (Filter.PassFilter(line, line_end))
                    ImGui::TextUnformatted(line, line_end);
                line = line_end && line_end[1] ? line_end + 1 : NULL;
            }
        } else {
            ImGui::TextUnformatted(Buf.begin());
        }

        if (ScrollToBottom)
            ImGui::SetScrollHere(1.0f);
        ScrollToBottom = false;
        ImGui::EndChild();
        ImGui::End();
    }
};

void Editor::showLogWindow() {
    static LogWindow log;

    log.Clear();
    for (const auto &message : *(VapeLog::LogManager::getInstance().getOutputMessages())) {
        log.AddLog(message.toString().c_str());
        log.AddLog("\n");
    }

    bool open = true;
    log.Draw("VapeLog", &open);
    m_bShowLogWindow = open;
}

void Editor::onKeyPressed(const VapeInput::KeyboardInputMessage &_kbdMsg) {
    static unsigned int ctr = 0;
    if ((_kbdMsg.KEY_LEFT_CONTROL || _kbdMsg.KEY_RIGHT_CONTROL) && _kbdMsg.KEY_L) {
        if (ctr++ == 0) {
            m_bShowLogWindow = !m_bShowLogWindow;
        }
    } else if ((_kbdMsg.KEY_LEFT_CONTROL || _kbdMsg.KEY_RIGHT_CONTROL) && _kbdMsg.KEY_T) {
        if (ctr++ == 0) {
            m_bShowObjTree = !m_bShowObjTree;
        }
    } else if ((_kbdMsg.KEY_LEFT_CONTROL || _kbdMsg.KEY_RIGHT_CONTROL) && _kbdMsg.KEY_I) {
        if (ctr++ == 0) {
            m_bShowInspector = !m_bShowInspector;
        }
    } else if ((_kbdMsg.KEY_LEFT_CONTROL || _kbdMsg.KEY_RIGHT_CONTROL) &&
               (_kbdMsg.KEY_LEFT_SHIFT || _kbdMsg.KEY_RIGHT_SHIFT) && _kbdMsg.KEY_R) {
        if (ctr++ == 0) {
            Core::Engine::getInstance().signalRunGame();
        }
    } else if ((_kbdMsg.KEY_LEFT_CONTROL || _kbdMsg.KEY_RIGHT_CONTROL) &&
               (_kbdMsg.KEY_LEFT_SHIFT || _kbdMsg.KEY_RIGHT_SHIFT) && _kbdMsg.KEY_O) {
        if (ctr++ == 0) {
            m_bShowOpenScene = true;
        }
    } else if ((_kbdMsg.KEY_LEFT_CONTROL || _kbdMsg.KEY_RIGHT_CONTROL) &&
               (_kbdMsg.KEY_LEFT_SHIFT || _kbdMsg.KEY_RIGHT_SHIFT) && _kbdMsg.KEY_S) {
        if (ctr++ == 0) {
            m_bShowSaveScene = true;
        }
    } else if ((_kbdMsg.KEY_LEFT_CONTROL || _kbdMsg.KEY_RIGHT_CONTROL) &&
               (_kbdMsg.KEY_LEFT_SHIFT || _kbdMsg.KEY_RIGHT_SHIFT) && _kbdMsg.KEY_N) {
        if (ctr++ == 0) {
            EditorController::getInstance().createNewScene();
        }
    } else {
        ctr = 0;
    }

}

/*
 * Show a tree view of all the gameobjects in the scene.
 * Make children objects subnodes of their parents
 *
 * When node selected, single click updates inspector, double click opens it if closed
 *
 * Inspector constains separated sections for each of the object's components
 */
void Editor::showObjTree() {
    m_treeNodes.clear();

    auto &entities = Core::Engine::getInstance().getEntityManager().getEntities();
    bool open = true;
    ImGui::SetNextWindowSize(ImVec2(250, 680), ImGuiCond_Once);
    ImGui::SetNextWindowPos(ImVec2(x_res - 600, 15), ImGuiCond_Once);
    if (!ImGui::Begin("Scene", &open)) {
        // Early out if the window is collapsed, as an optimization.
        ImGui::End();
        return;
    }
    if (ImGui::Button("New Entity")) {
        m_bShowNewEntWindow = true;
    }
    for (auto &ent : entities) {
        // Show top level objects only, children are going to be recursively shown.
        if (!ent->getParent())
            addObjTreeNode(ent.get()); // pass the raw pointer
    }
    ImGui::End();
    m_bShowObjTree = open;
}

void Editor::addObjTreeNode(ECS::Entity *obj) {
    const char *tag = strlen(obj->getName().c_str()) > 0 ? obj->getName().c_str() : "no name";
    auto found = std::find_if(m_treeNodes.begin(), m_treeNodes.end(), [obj](ECS::Entity *_obj) {
        return _obj->getID() == obj->getID();
    });
    if (found == m_treeNodes.end()) {
        m_treeNodes.emplace_back(obj);
        bool opened = ImGui::TreeNode(tag);
        if (ImGui::IsItemClicked()) {
#if DEBUG
            VapeLog::LogManager::getInstance().printMessage(VapeLog::LogMessage(
                    VapeLog::LogTag::LOG, VapeLog::LogType::MESSAGE,
                    VapeLog::LogSeverity::LOW, "Tree item clicked. " + obj->getName()));
#endif
            // TODO
            m_selectedEntity = obj;
        }
        if (opened) {
            for (auto &_child : obj->getChildren()) {
                addObjTreeNode(_child);
            }
            ImGui::TreePop();
        }
    }
}

void Editor::showInspector() {
    bool open = true;
    ImGui::SetNextWindowSize(ImVec2(350, 680), ImGuiCond_Once);
    ImGui::SetNextWindowPos(ImVec2(x_res - 350, 15), ImGuiCond_Once);
    if (!ImGui::Begin("Inspector", &open)) {
        ImGui::End();
    } else {
        if (m_selectedEntity) {
            // do stuff
            ImGui::Text("Tag:");
            ImGui::SameLine();
            ImGui::Text(m_selectedEntity->getName().c_str());
            ImGui::Text("ID:");
            std::string s = std::to_string(m_selectedEntity->getID());
            char const *pchar = s.c_str();
            ImGui::SameLine();
            ImGui::Text(pchar);

            ImGui::Separator();
            renderTransformInspector();
            if (m_selectedEntity->hasComponent<RenderableComponent>()) {
                ImGui::Separator();
                renderRenderableInspector();
            }
            if (m_selectedEntity->hasComponent<ScriptComponent>()) {
                ImGui::Separator();
                renderScriptInspector();
            }
            if (m_selectedEntity->hasComponent<CameraComponent>()) {
                ImGui::Separator();
                renderCameraInspector();
            }
            if (m_selectedEntity->hasComponent<ColliderComponent>()) {
                ImGui::Separator();
                renderColliderInspector();
            }
            if (m_selectedEntity->hasComponent<RigidBodyComponent>()) {
                ImGui::Separator();
                renderRigidBodyInspector();
            }
            ImGui::Separator();
            if (ImGui::Button("Add Component")) {
                m_bShowAddComponent = true;
            }
            if (ImGui::Button("Delete")) {
                if (auto p = m_selectedEntity->getParent(); p) {
                    auto &v = p->getChildren();
                    v.erase(std::remove_if(std::begin(v), std::end(v), [this](ECS::Entity *_ent) {
                        return m_selectedEntity->getID() == _ent->getID();
                    }), std::end(v));
                }  
                m_selectedEntity->destroy();
                Core::Engine::getInstance().getEntityManager().refresh();
                m_selectedEntity = nullptr;
            }
        }
        ImGui::End();
    }
    m_bShowInspector = open;
}

void Editor::renderTransformInspector() {
    /*
     * Transform
     */
    ImGui::Text("Transform:");
    ImGui::Text(" ");
    if (m_selectedEntity && m_selectedEntity->hasComponent<TransformComponent>()) {
        /*
         * If the representation of the rotation seems, weird, it is perfectly normal, euler angles are represented that way.
         */
        float pos[3], rot[3], scl[3];
        auto &t = m_selectedEntity->getComponent<TransformComponent>();
        pos[0] = t.position.x;
        pos[1] = t.position.y;
        pos[2] = t.position.z;
        rot[0] = glm::degrees(t.rotation.x);
        rot[1] = glm::degrees(t.rotation.y);
        rot[2] = glm::degrees(t.rotation.z);
        scl[0] = t.scale.x;
        scl[1] = t.scale.y;
        scl[2] = t.scale.z;
        ImGui::InputFloat3("Position", pos, 3);
        ImGui::InputFloat3("Rotation", rot, 3);
        ImGui::InputFloat3("Scale", scl, 3);
        t.position.x = pos[0];
        t.position.y = pos[1];
        t.position.z = pos[2];
        t.rotation.x = glm::radians(rot[0]);
        t.rotation.y = glm::radians(rot[1]);
        t.rotation.z = glm::radians(rot[2]);
        t.scale.x = scl[0];
        t.scale.y = scl[1];
        t.scale.z = scl[2];
    }
}

void Editor::renderRenderableInspector() {
    ImGui::Text("RenderableComponent");
    ImGui::Text(" ");
    int shape = m_selectedEntity->getComponent<RenderableComponent>().m_shape;
    ImGui::InputInt("Shape", &shape);
}

void Editor::renderScriptInspector() {
    ImGui::Text("ScriptComponent");
    ImGui::Text(" ");
    // that's pretty hacky, TODO: find a better solution
    char* buf = const_cast<char*>(m_selectedEntity->getComponent<ScriptComponent>().m_script->m_sName.c_str()); 
    ImGui::InputText("Script", buf, 20);
    m_selectedEntity->getComponent<ScriptComponent>().m_script->m_sName = buf;
}

void Editor::renderCameraInspector() {
    ImGui::Text("CameraComponent");
    ImGui::Text(" ");
    auto &cam = m_selectedEntity->getComponent<CameraComponent>();
    float fov = cam.m_fov;
    float hRes = cam.m_hRes;
    float vRes = cam.m_vRes;
    float zNear = cam.m_zNear;
    float zFar = cam.m_zFar;

    ImGui::InputFloat("FoV", &fov, 0, 0, 3);
    ImGui::InputFloat("hRes", &hRes, 0, 0, 3);
    ImGui::InputFloat("vRes", &vRes, 0, 0, 3);
    ImGui::InputFloat("zNear", &zNear, 0, 0, 3);
    ImGui::InputFloat("zFar", &zFar, 0, 0, 3);

    cam.m_fov = fov;
    cam.m_hRes = hRes;
    cam.m_vRes = vRes;
    cam.m_zNear = zNear;
    cam.m_zFar = zFar;
}

void Editor::renderColliderInspector() {
    ImGui::Text("ColliderComponent");
    ImGui::Text(" ");
    auto &col = m_selectedEntity->getComponent<ColliderComponent>();
    auto &parentTransform = m_selectedEntity->getComponent<TransformComponent>();
    if (col.type == BOX) {
        ImGui::Text("Type: BOX");
        auto &aabb = col.collider.boxCollider;
        float c[3] = {aabb.c.x - parentTransform.abs_position.x, aabb.c.y - parentTransform.abs_position.y, aabb.c.z - parentTransform.abs_position.z};
        float h[3] = {aabb.r.x, aabb.r.y, aabb.r.z};
        bool t = col.isTrigger;
        bool s = col.isStatic;
        ImGui::InputFloat3("Center", c, 3);
        ImGui::InputFloat3("HalfWidths", h, 3);
        ImGui::Checkbox("isTrigger", &t);
        ImGui::Checkbox("isStatic", &s);
        col.isTrigger = t;
        col.isStatic = s;
        aabb.c.x = c[0] + parentTransform.abs_position.x;
        aabb.c.y = c[1] + parentTransform.abs_position.y;
        aabb.c.z = c[2] + parentTransform.abs_position.z;
        aabb.r.x = h[0];
        aabb.r.y = h[1];
        aabb.r.z = h[2];
    } else if (col.type == SPHERE) {
        ImGui::Text("Type: SPHERE");
        auto& sphere = col.collider.sphereCollider;
        float c[3] = {sphere.c.x - parentTransform.abs_position.x, sphere.c.y - parentTransform.abs_position.y, sphere.c.z - parentTransform.abs_position.z};
        float rad = sphere.r;
        bool t = col.isTrigger;
        bool s = col.isStatic;
        ImGui::InputFloat3("Center", c, 3);
        ImGui::InputFloat("Radius", &rad, 3);
        ImGui::Checkbox("isTrigger", &t);
        ImGui::Checkbox("isStatic", &s);
        sphere.c.x = c[0] + parentTransform.abs_position.x;
        sphere.c.y = c[1] + parentTransform.abs_position.y;
        sphere.c.z = c[2] + parentTransform.abs_position.z;
        sphere.r = rad;
        col.isTrigger = t;
        col.isStatic = s;
    }
}

void Editor::renderRigidBodyInspector() {
    ImGui::Text("RigidBodyComponent");
    ImGui::Text(" ");
    auto &rb = m_selectedEntity->getComponent<RigidBodyComponent>();
    float grav_scl = rb.gravityScale;
    float ms = rb.mass;
    float fric = rb.friction;
    bool lckPosx = rb.lockPos_x;
    bool lckPosy = rb.lockPos_y;
    bool lckPosz = rb.lockPos_z;
    bool lckRotx = rb.lockRot_x;
    bool lckRoty = rb.lockRot_y;
    bool lckRotz = rb.lockRot_z;
    bool kin = rb.isKinematic;
    ImGui::InputFloat("Gravity Scale", &grav_scl, 3);
    ImGui::InputFloat("Mass", &ms, 3);
    ImGui::InputFloat("Friction", &fric, 3);
    ImGui::Text("Lock Position:");
    ImGui::Checkbox("x", &lckPosx);
    ImGui::SameLine();
    ImGui::Checkbox("y", &lckPosy);
    ImGui::SameLine();
    ImGui::Checkbox("z", &lckPosz);
    ImGui::Text("Lock Rotation:");
    ImGui::Checkbox("x", &lckRotx);
    ImGui::SameLine();
    ImGui::Checkbox("y", &lckRoty);
    ImGui::SameLine();
    ImGui::Checkbox("z", &lckRotz);
    ImGui::Checkbox("IsKinematic", &kin);
    rb.gravityScale = grav_scl;
    rb.mass = ms;
    rb.friction = fric;
    rb.lockPos_x = lckPosx;
    rb.lockPos_y = lckPosy;
    rb.lockPos_z = lckPosz;
    rb.lockRot_x = lckRotx;
    rb.lockRot_y = lckRoty;
    rb.lockRot_z = lckRotz;
    rb.isKinematic = kin;
}

void Editor::showOpenDialog() {
    std::string open_file;
    if (fileIOWindow(open_file, m_sRecentFiles, "Open", {"*.scn"}, true)) {
        m_bShowOpenScene = false;
        if (!open_file.empty()) {
            m_sRecentFiles.push_back(open_file);
            Core::Engine::getInstance().reset();
            SceneManager::getInstance().loadScene(open_file);
        }
    }
}

void Editor::showSaveDialog() {
    std::string save_file;
    if (fileIOWindow(save_file, m_sRecentFiles, "Save", {"*.scn"})) {
        m_bShowSaveScene = false;
        if (!save_file.empty()) {
            m_sRecentFiles.push_back(save_file);

            SceneManager::getInstance().saveScene(save_file);
        }
    }
}

void Editor::showNewEntWindow() {
    ImGui::SetNextWindowSize(ImVec2(200, 400), ImGuiCond_Once);
    ImGui::SetNextWindowPos(ImVec2(x_res - 600, 20), ImGuiCond_Once);
//    m_bShowNewEntWindow = true;
    bool open = m_bShowNewEntWindow;
    ImGui::Begin("New Entity", &open);
    std::string name;
    ImGui::InputText("Name", buf, IM_ARRAYSIZE(buf));
    ImGui::Text(m_newEntParent ? m_newEntParent->getName().c_str() : "None");
    bool scrolldown = m_bScrollDownParent;
    if (ImGui::CollapsingHeader("Parent")) {
        if (ImGui::Button("None", ImVec2(ImGui::GetContentRegionAvailWidth() * 0.99f, 20.f)))m_newEntParent = nullptr;
        for (auto &e : Core::Engine::getInstance().getEntityManager().getEntities()) {
            if (ImGui::Button(e->getName().c_str(), ImVec2(ImGui::GetContentRegionAvailWidth() * 0.99f, 20.f))) {
                m_newEntParent = e.get();
                scrolldown = false;
            }
        }
    }
    if (ImGui::Button("Confirm")) {
        name = std::string(buf);
        if (!name.empty()) EditorController::getInstance().addNewEntity(name, m_newEntParent);
        open = false;
    }
    ImGui::SameLine();
    if (ImGui::Button("cancel")) open = false;
    ImGui::End();
    m_bShowNewEntWindow = open;
    m_bScrollDownParent = scrolldown;
    if (!m_bShowNewEntWindow) m_newEntParent = nullptr;
}

void Editor::showAddComponentWindow() {
    ImGui::SetNextWindowSize(ImVec2(200, 200), ImGuiCond_Once);
    ImGui::SetNextWindowPos(ImVec2(x_res - 300, 20), ImGuiCond_Once);
    bool open = m_bShowAddComponent;
    ImGui::Begin("Add Component", &open);

    // Renderable
    if (ImGui::Button("RenderableComponent(CUBE)")) {
        if (!m_selectedEntity->hasComponent<RenderableComponent>()) {
            m_selectedEntity->addComponent<RenderableComponent>(VapeRenderer::PrimitiveShapes::CUBE);
            open = false;
        }
    }
    if (ImGui::Button("RenderableComponent(PLANE)")) {
        if (!m_selectedEntity->hasComponent<RenderableComponent>()) {
            m_selectedEntity->addComponent<RenderableComponent>(VapeRenderer::PrimitiveShapes::PLANE);
            open = false;
        }
    }
    if (ImGui::Button("RenderableComponent(PYRAMID)")) {
        if (!m_selectedEntity->hasComponent<RenderableComponent>()) {
            m_selectedEntity->addComponent<RenderableComponent>(VapeRenderer::PrimitiveShapes::PYRAMID);
            open = false;
        }
    }
    if (ImGui::Button("ScriptComponent(PlayerMovement)")) {
        if (!m_selectedEntity->hasComponent<ScriptComponent>()) {
            m_selectedEntity->addComponent<ScriptComponent>(new PlayerMovementScript());
            open = false;
        }
    }
    if (ImGui::Button("CameraComponent")) {
        if (!m_selectedEntity->hasComponent<CameraComponent>()) {
            m_selectedEntity->addComponent<CameraComponent>(90.f, 16.f, 9.f, 0.1f, 100.f);
            open = false;
        }
    }
    if (ImGui::Button("ColliderComponent(AABB)")) {
        if (!m_selectedEntity->hasComponent<ColliderComponent>()) {
            m_selectedEntity->addComponent<ColliderComponent>(glm::vec3(0.f, 0.f, 0.f), glm::vec3(0.f, 0.f, 0.f));
            open = false;
        }
    }
    if (ImGui::Button("ColliderComponent(SPHERE)")) {
        if (!m_selectedEntity->hasComponent<ColliderComponent>()) {
            m_selectedEntity->addComponent<ColliderComponent>(glm::vec3(0.f, 0.f, 0.f), 0.f);
            open = false;
        }
    } 
    if (ImGui::Button("RigidBodyComponent")) {
        if (!m_selectedEntity->hasComponent<RigidBodyComponent>()) {
            m_selectedEntity->addComponent<RigidBodyComponent>();
            open = false;
        }
    } 
    // Script
    ImGui::End();
    m_bShowAddComponent = open;
}


#endif
