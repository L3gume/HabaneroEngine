//
// Created by notjustin on 12/25/17.
//

#ifndef HABANERO_LOGMESSAGE_H
#define HABANERO_LOGMESSAGE_H

#include <string>
#include <sstream>

namespace VapeLog {

    enum LogTag {
        COMMON,
        INPUT,
        LOG,
        RENDER,
        PHYSICS,
        GAME,
        SCENEMANAGER
        // Add stuff to this
    };

    enum LogType {
        BUG,
        ISSUE,
        MESSAGE,
        WARNING
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
                m_tag(_tag), m_type(_type), m_severity(_severity), m_str(std::move(_str)), m_occurences(1) {
            m_time = 0;
        }

        // Compares their content
        bool isEqual(LogMessage& other) const {
            return (m_tag == other.m_tag) && (m_type == other.m_type) &&
                   (m_severity == other.m_severity) && (m_str == other.m_str);
        }

        std::string toString() const {
            std::string ret;
            std::string time;
            std::string tag;
            std::string type;
            std::string severity;
            std::string occurrences;

            switch (m_tag) {
                case COMMON: tag = "COMMON"; break;
                case INPUT: tag = "INPUT"; break;
                case LOG: tag = "LOG"; break;
                case RENDER: tag = "RENDER"; break;
                case PHYSICS: tag = "PHYSICS"; break;
                case GAME: tag = "GAME"; break;
                default: tag = "UNKNOWN"; break;
            }

            switch (m_type) {
                case BUG: type = "BUG"; break;
                case ISSUE: type = "ISSUE"; break;
                case MESSAGE: type = "MESSAGE"; break;
                default: type = "UNKNOWN"; break;
            }

            switch (m_severity) {
                case CRITICAL: severity = "CRITICAL"; break;
                case SEVERE: severity = "SEVERE"; break;
                case HIGH: severity = "HIGH"; break;
                case MODERATE: severity = "MODERATE"; break;
                case LOW: severity = "LOW"; break;
                default: severity = "UNKNOWN"; break;
            }

            std::ostringstream strs;
            strs << m_time;
            time = strs.str();

            std::ostringstream strss;
            strss << m_occurences;
            occurrences = strss.str();

            return time + "\t" + tag + "\t" + severity + "\t" + m_str + "\t" + type + "\t" + occurrences;
        }

        LogTag m_tag;
        LogType m_type;
        LogSeverity m_severity;

        std::string m_str;

        double m_time;
        int m_occurences;
    };
}
#endif //HABANERO_LOGMESSAGE_H
