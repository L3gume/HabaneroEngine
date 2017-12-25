//
// Created by notjustin on 12/25/17.
//

#ifndef VAPEENGINE_LOGMESSAGE_H
#define VAPEENGINE_LOGMESSAGE_H

#include <string>
#include <GLFW/glfw3.h>

namespace VapeLog {

    enum LogTag {
        COMMON,
        INPUT,
        LOG,
        RENDER,
        PHYSICS,
        GAME
        // Add stuff to this
    };

    enum LogType {
        BUG,
        ISSUE,
        MESSAGE,
        // Add stuff to this
    };

    enum LogSeverity : unsigned short {
        CRITICAL = 0,
        SEVERE = 1,
        HIGH = 2,
        MODERATE = 3,
        LOW = 4
        // Can add levels
    };

    struct LogMessage {
        LogMessage(LogTag _tag, LogType _type, LogSeverity _severity, std::string _str) :
                m_tag(_tag), m_type(_type), m_severity(_severity), m_str(std::move(_str)), m_occurences(0) {
            m_time = glfwGetTime();
        }

        // Compares their content
        bool operator==(LogMessage& other) {
            return (m_tag == other.m_tag) && (m_type == other.m_type) &&
                   (m_severity == other.m_severity) && (m_str == other.m_str);
        }

        LogTag m_tag;
        LogType m_type;
        LogSeverity m_severity;

        std::string m_str;

        double m_time;
        int m_occurences;
    };
}
#endif //VAPEENGINE_LOGMESSAGE_H
