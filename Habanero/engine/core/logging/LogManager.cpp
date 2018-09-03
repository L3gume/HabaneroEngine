//
// Created by notjustin on 12/25/17.
//

#include "../logging/LogManager.h"

using namespace HabaneroLog;

void LogManager::printMessage(LogMessage _message) {
    // First try to see if the message already exists:
    auto found = std::find_if(m_messages.begin(), m_messages.end(), [&_message](const LogMessage& logMessage) {
        return logMessage.isEqual(_message);
    });

    if (found != m_messages.end()) {
        (*found).m_occurences++; // It already exists in the system, increment the occurrences
    } else {
        m_messages.emplace_back(_message);
    }
}

void LogManager::setSortFlags(unsigned char _flags) {
    m_sortFlags.m_sFlags = _flags;
}

void LogManager::setSearchString(const std::string& _regex) {
    m_sRegex = _regex;
}

std::vector<HabaneroLog::LogMessage>* LogManager::getOutputMessages() {
    if (!m_sRegex.empty()) {
        m_outputMessages.clear();
        std::smatch match;
        for (const auto& it : m_messages) {
            /*
             * I know I said no exception handling, but we have no choice here.
             * I guess its acceptable on UI code.
             */
            try {
                if (std::regex_search(it.m_str, std::regex(m_sRegex))) {
                    m_outputMessages.emplace_back(it); // matches, add it to output
                }
            } catch (std::regex_error& e) {
                // DO NOT PRINT TO LOG HERE, CAUSES INFINITE RECURSION AND SEGFAULT
#if DEBUG
                fprintf(stderr, "Regex syntax error.\n");
#endif
            }
        }
    } else {
        resetOutput();
    }

    if (m_sortFlags.m_sFlags) {
        if (m_sortFlags.m_flags.m_bSortTime) {
            std::sort(m_outputMessages.begin(), m_outputMessages.end(), [](const LogMessage& l1, const LogMessage& l2) {
                return l1.m_time > l2.m_time;
            });
        } else if (m_sortFlags.m_flags.m_bSortTag) {
            std::sort(m_outputMessages.begin(), m_outputMessages.end(), [](const LogMessage& l1, const LogMessage& l2) {
                return l1.m_tag < l2.m_tag;
            });
        } else if (m_sortFlags.m_flags.m_bSortOccurrences) {
            std::sort(m_outputMessages.begin(), m_outputMessages.end(), [](const LogMessage& l1, const LogMessage& l2) {
                return l1.m_occurences > l2.m_occurences;
            });
        } else if (m_sortFlags.m_flags.m_bSortSeverity) {
            std::sort(m_outputMessages.begin(), m_outputMessages.end(), [](const LogMessage& l1, const LogMessage& l2) {
                return l1.m_severity < l2.m_severity;
            });
        } else if (m_sortFlags.m_flags.m_bSortType) {
            std::sort(m_outputMessages.begin(), m_outputMessages.end(), [](const LogMessage& l1, const LogMessage& l2) {
                return l1.m_type < l2.m_type;
            });
        }
    }
    return &m_outputMessages;
}

void LogManager::clearLog() {
    m_messages.clear();
    m_outputMessages.clear();
}