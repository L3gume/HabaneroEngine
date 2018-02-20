//
// Created by l3gume on 20/02/18.
//

#include "SceneManager.h"

void SceneManager::saveScene(std::string _name) {
    auto& entities = Core::Engine::getInstance().getEntityManager().getEntities();

    std::sort(std::begin(entities), std::end(entities), [](std::shared_ptr<ECS::Entity>& A, std::shared_ptr<ECS::Entity>& B){
        return A->getParent() == nullptr && B->getParent() != nullptr;
    });

    std::ofstream os(_name + ".scn"); // TODO: validation of the file name
    std::ostringstream oss;
    ECS::EntityConstructor ec;
    oss << "SCENE:" << _name << "\n{\n";
    for (auto& e : entities) {
        if (!e->getParent())
            ec.saveEntity(*e, &oss);
    }
    oss << "}\n";
    os << oss.str();
    os.close();
}

void SceneManager::loadScene(const std::string& _path) {
    ECS::EntityConstructor ec;
    std::ifstream ifs(_path);
    std::string line;
    std::vector<std::string> args;
    while (std::getline(ifs, line)) {
       args.emplace_back(line);
    }
    ifs.close();

    for (int i = 0; i < args.size(); i++) {
        if (i == 0) {
            std::string pref("SCENE:");
            if (boost::starts_with(args[i], pref)) {
                m_sActiveScene = args[i].substr(pref.size());
            } else {
                fprintf(stderr, "Invalid scene file\n");
            }
        } else if (boost::starts_with(args[i], "ENTITY:")) {
            int max_tries = 500;
            std::vector<std::string> entityArgs;
            entityArgs.emplace_back(args[i]);
            while (true) {
                entityArgs.emplace_back(args[++i]);
                if (args[i] == "}") break;
                if (max_tries-- <= 0) {
                    fprintf(stderr, "Bad formatting of file\n");
                    break;
                }
            }
            ec.constructEntity(entityArgs, nullptr);
        }
    }
}
