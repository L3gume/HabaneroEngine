//
// Created by notjustin on 12/25/17.
//

#ifndef VAPEENGINE_LOGMANAGER_H
#define VAPEENGINE_LOGMANAGER_H

namespace VapeLog {

    class LogManager {
    public:
        static LogManager &getInstance() {
            static LogManager instance; // Guaranteed to be destroyed.
            return instance;
        }

        LogManager(LogManager const &) = delete;
        void operator=(LogManager const &) = delete;

    private:
        LogManager() = default;
    };
}

#endif //VAPEENGINE_LOGMANAGER_H
