//
// Created by notjustin on 12/25/17.
//

#ifndef VAPEENGINE_LOGMANAGER_H
#define VAPEENGINE_LOGMANAGER_H

#include <vector>
#include <regex>
#include "LogMessage.h"

namespace VapeLog {

    // -----------------------------------------------------------------------------------------------------------------
    // The next struct + union are quite fun! They use the concept of overlapping memory to update multiple flags with a
    // single argument.
    // -----------------------------------------------------------------------------------------------------------------
    struct Flags {
        bool m_bSortTime        : 1;
        bool m_bSortTag         : 1;
        bool m_bSortOccurrences : 1;
        bool m_bSortSeverity    : 1;
        bool m_bSortType        : 1;
        //
        // There's room for 3 more bit flags
        //
    };

    /*
     * The Flags data structure is composed of a bitfield of multiple bools aligned in memory, it is then put in union
     * with an unsigned character, which is 8 bits. That makes it so updating that char also updates the flags. We can
     * then use that to update multiple flags with only one arguments. I also makes it very easy to support one-hot
     * encoding so that only one flag is set at a time!
     */
    union SortFlags {
        unsigned char m_sFlags = 0x00;
        Flags m_flags;
    };

    class LogManager {

    public:
        static LogManager &getInstance() {
            static LogManager instance; // Guaranteed to be destroyed.
            return instance;
        }

        LogManager(LogManager const &) = delete;
        void operator=(LogManager const &) = delete;

        void printMessage(LogMessage _message); // Called by the user, adds a message to the logging system
        void setSortFlags(unsigned char _flags);
        void setSearchString(const std::string &_regex); // Gets the messages the match the regex search

        void clearLog();

        std::vector<VapeLog::LogMessage>* getOutputMessages();

    private:
        LogManager() = default;

        inline void resetOutput() { m_outputMessages = m_messages; }
        
        SortFlags m_sortFlags;
        std::string m_sRegex;

        std::vector<VapeLog::LogMessage> m_messages; // holds ALL the messages
        std::vector<VapeLog::LogMessage> m_outputMessages; // Holds the message to pass to the UI
    };
}

#endif //VAPEENGINE_LOGMANAGER_H
