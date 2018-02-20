//
// Created by l3gume on 04/02/18.
//

#include "Editor.h"

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
//    ImGui::StyleColorsDark();
    ImGui::StyleColorsClassic();
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

    int display_w, display_h;
    glfwGetFramebufferSize(m_window, &display_w, &display_h);
    glViewport(0, 0, display_w, display_h);
    glClearColor(clear_color.x, clear_color.y, clear_color.z, clear_color.w);

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
                Core::Engine::getInstance().signalRunGame();
            }
            ImGui::EndMenu();
        }
        if (ImGui::BeginMenu("Scene")) {
            if (ImGui::MenuItem("New Scene", "CTRL+SHIFT+N")) {
                // TODO - Editor controller to handle this.
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
    static unsigned int ctr2 = 0;
    static unsigned int ctr3 = 0;
    static unsigned int ctr4 = 0;


    if ((_kbdMsg.KEY_LEFT_CONTROL || _kbdMsg.KEY_RIGHT_CONTROL) && _kbdMsg.KEY_L) {
        if (ctr++ == 0) {
            m_bShowLogWindow = !m_bShowLogWindow;
        }
    } else {
        ctr = 0;
    }
    if ((_kbdMsg.KEY_LEFT_CONTROL || _kbdMsg.KEY_RIGHT_CONTROL) && _kbdMsg.KEY_T) {
        if (ctr2++ == 0) {
            m_bShowObjTree = !m_bShowObjTree;
        }
    } else {
        ctr2 = 0;
    }
    if ((_kbdMsg.KEY_LEFT_CONTROL || _kbdMsg.KEY_RIGHT_CONTROL) && _kbdMsg.KEY_I) {
        if (ctr3++ == 0) {
            m_bShowInspector = !m_bShowInspector;
        }
    } else {
        ctr3 = 0;
    }
    if ((_kbdMsg.KEY_LEFT_CONTROL || _kbdMsg.KEY_RIGHT_CONTROL) &&
        (_kbdMsg.KEY_LEFT_SHIFT || _kbdMsg.KEY_RIGHT_SHIFT) && _kbdMsg.KEY_R) {
        if (ctr4++ == 0) {
            Core::Engine::getInstance().signalRunGame();
        }
    } else {
        ctr4 = 0;
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

    auto& entities = Core::Engine::getInstance().getEntityManager().getEntities();
    bool open = true;
    ImGui::SetNextWindowSize(ImVec2(250, 680), ImGuiCond_Once);
    ImGui::SetNextWindowPos(ImVec2(x_res - 600, 15), ImGuiCond_Once);
    if (!ImGui::Begin("Scene", &open)) {
        // Early out if the window is collapsed, as an optimization.
        ImGui::End();
        return;
    }
    for (auto& ent : entities) {
            // Show top level objects only, children are going to be recursively shown.
        if (!ent->getParent())
            addObjTreeNode(ent.get()); // pass the raw pointer
    }
    ImGui::End();
    m_bShowObjTree = open;
}

void Editor::addObjTreeNode(ECS::Entity* obj) {
    const char *tag = strlen(obj->getName().c_str()) > 0 ? obj->getName().c_str() : "no name";
    auto found = std::find_if(m_treeNodes.begin(), m_treeNodes.end(), [obj](ECS::Entity* _obj) {
        return _obj->getID() == obj->getID();
    });
    if (found == m_treeNodes.end()) {
        m_treeNodes.emplace_back(obj);
        if (ImGui::TreeNode(tag)) {
            if (ImGui::IsItemClicked()) {
#if DEBUG
                VapeLog::LogManager::getInstance().printMessage(VapeLog::LogMessage(
                        VapeLog::LogTag::LOG, VapeLog::LogType::MESSAGE,
                        VapeLog::LogSeverity::LOW, "Tree item clicked. " + obj->getName()));
#endif
                // TODO
                m_selectedEntity = obj;
            }
            for (auto& _child : obj->getChildren()) {
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
    }
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
//        renderTransformInspector();
        ImGui::Separator();
//        for (deprecatedComponent *comp : *m_selectedEntity->) {
//            // TODO: Render a section for each component
//            comp->renderInspectorSection();
//        }
    }
    ImGui::End();
    m_bShowInspector = open;
}
//
//void Editor::renderTransformInspector() {
//    /*
//     * Transform
//     */
//    ImGui::Text("Transform:");
//    ImGui::Text(" ");
//    if (m_selectedEntity) {
//        Core::Transform *t = m_selectedEntity->getTransform();
//        glm::vec3 pos = t->position;
//        glm::vec3 rot = t->euler_rotation;
//        glm::vec3 scl = t->scale;
//
//        ImGui::PushItemWidth(40);
//        ImGui::Text("Position: ");
//        ImGui::SameLine();
//        ImGui::InputFloat("xpos", &(pos.x), 0.f, 0.f, 2);
//        ImGui::SameLine();
//        ImGui::InputFloat("ypos", &(pos.y), 0.f, 0.f, 2);
//        ImGui::SameLine();
//        ImGui::InputFloat("zpos", &(pos.z), 0.f, 0.f, 2);
//        ImGui::Text("Rotation: ");
//        ImGui::SameLine();
//        ImGui::InputFloat("xrot", &(rot.x), 0.f, 0.f, 2);
//        ImGui::SameLine();
//        ImGui::InputFloat("yrot", &(rot.y), 0.f, 0.f, 2);
//        ImGui::SameLine();
//        ImGui::InputFloat("zrot", &(rot.z), 0.f, 0.f, 2);
//        ImGui::Text("Scale:    ");
//        ImGui::SameLine();
//        ImGui::InputFloat("xscl", &(scl.x), 0.f, 0.f, 2);
//        ImGui::SameLine();
//        ImGui::InputFloat("yscl", &(scl.y), 0.f, 0.f, 2);
//        ImGui::SameLine();
//        ImGui::InputFloat("zscl", &(scl.z), 0.f, 0.f, 2);
//        ImGui::PopItemWidth();
//
//        t->position = pos;
//        t->euler_rotation = rot;
//        t->scale = scl;
//    }
//}

void Editor::showOpenDialog() {
    std::string open_file;
    if (fileIOWindow(open_file, m_sRecentFiles, "Open", {"*.usr", "*.*"}, true)) {
        m_bShowOpenScene = false;
        if (!open_file.empty()) {
            m_sRecentFiles.push_back(open_file);
            // TODO
        }
    }
}

void Editor::showSaveDialog() {
    std::string save_file;
    if (fileIOWindow(save_file, m_sRecentFiles, "Save", {"*.usr", "*.*"})) {
        m_bShowSaveScene = false;
        if (!save_file.empty()) {
            m_sRecentFiles.push_back(save_file);

            std::ofstream out_file;
            out_file.open(save_file, std::ios_base::trunc);

            // TODO

            out_file.close();
        }
    }
}

#endif
