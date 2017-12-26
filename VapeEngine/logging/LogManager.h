//
// Created by notjustin on 12/25/17.
//

#ifndef VAPEENGINE_LOGMANAGER_H
#define VAPEENGINE_LOGMANAGER_H

#include <vector>
#include <regex>
#include "LogMessage.h"
#include "logger.h"

namespace VapeLog {

    struct Flags {
        bool m_bSortTime        : 1;
        bool m_bSortTag         : 1;
        bool m_bSortOccurences  : 1;
        bool m_bSortSeverity    : 1;
        bool m_bSortType        : 1;
    };

    union SortFlags {
        unsigned short m_sFlags = 0x00;
        Flags m_flags;
    };

    class LogManager : public QObject {
    Q_OBJECT

    public:
        static LogManager &getInstance() {
            static LogManager instance; // Guaranteed to be destroyed.
            return instance;
        }

        LogManager(LogManager const &) = delete;
        void operator=(LogManager const &) = delete;

        void setLogger(Logger* _logger) { _logger->connect(this, &LogManager::notifyLogger, _logger, &Logger::notify); }

        void printMessage(LogMessage _message); // Called by the user, adds a message to the logging system
        void setSortFlags(unsigned short _flags);
        void setSearchString(const std::string &_regex); // Gets the messages the match the regex search

        void clearLog();

        std::vector<VapeLog::LogMessage>* getOutputMessages();

    signals:
        void notifyLogger();
    private:
        LogManager() = default;

        inline void resetOutput() { m_outputMessages = m_messages; }

        Logger* m_logger = nullptr;

        SortFlags m_sortFlags;
        std::string m_sRegex;

        std::vector<VapeLog::LogMessage> m_messages; // holds ALL the messages
        std::vector<VapeLog::LogMessage> m_outputMessages; // Holds the message to pass to the UI
    };
}

#endif //VAPEENGINE_LOGMANAGER_H
