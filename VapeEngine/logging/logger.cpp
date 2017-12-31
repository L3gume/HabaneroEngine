//
// Created by notjustin on 12/24/17.
//

#include <QtCore/QStringListModel>
#include <QtGui/QStandardItemModel>
#include "logger.h"
#include "LogMessage.h"
#include "LogManager.h"

using namespace VapeLog;

void Logger::notify() {
    m_log->clear();
    std::vector<LogMessage>* out = LogManager::getInstance().getOutputMessages();

    for (const auto& item : *out) {
        m_log->appendPlainText(QString::fromStdString(item.toString()));
    }
}

void Logger::handleSortTimeButton() {
    m_log->clear();
#if DEBUG
    VapeLog::LogManager::getInstance().printMessage(VapeLog::LogMessage(
            VapeLog::LogTag::LOG, VapeLog::LogType::MESSAGE,
            VapeLog::LogSeverity::LOW, "Sorting log by time"));
#endif

    VapeLog::LogManager::getInstance().setSortFlags(SORT_TIME);
}

void Logger::handleSortTagButton() {
    m_log->clear();
#if DEBUG
    VapeLog::LogManager::getInstance().printMessage(VapeLog::LogMessage(
            VapeLog::LogTag::LOG, VapeLog::LogType::MESSAGE,
            VapeLog::LogSeverity::LOW, "Sorting log by tag"));
#endif
    VapeLog::LogManager::getInstance().setSortFlags(SORT_TAG);
}

void Logger::handleSortOccurencesButton() {
    m_log->clear();
#if DEBUG
    VapeLog::LogManager::getInstance().printMessage(VapeLog::LogMessage(
            VapeLog::LogTag::LOG, VapeLog::LogType::MESSAGE,
            VapeLog::LogSeverity::LOW, "Sorting log by occurences"));
#endif
    VapeLog::LogManager::getInstance().setSortFlags(SORT_OCC);
}

void Logger::handleSortSeverityButton() {
    m_log->clear();
#if DEBUG
    VapeLog::LogManager::getInstance().printMessage(VapeLog::LogMessage(
            VapeLog::LogTag::LOG, VapeLog::LogType::MESSAGE,
            VapeLog::LogSeverity::LOW, "Sorting log by severity"));
#endif
    VapeLog::LogManager::getInstance().setSortFlags(SORT_SEV);
}

void Logger::handleSortTypeButton() {
    m_log->clear();
#if DEBUG
    VapeLog::LogManager::getInstance().printMessage(VapeLog::LogMessage(
            VapeLog::LogTag::LOG, VapeLog::LogType::MESSAGE,
            VapeLog::LogSeverity::LOW, "Sorting log by type"));
#endif
    VapeLog::LogManager::getInstance().setSortFlags(SORT_TYPE);
}

void Logger::handleRegexSearchButton() {
    m_log->clear();
#if DEBUG
    VapeLog::LogManager::getInstance().printMessage(VapeLog::LogMessage(
            VapeLog::LogTag::LOG, VapeLog::LogType::MESSAGE,
            VapeLog::LogSeverity::LOW, "Performing Regex search"));
#endif
    VapeLog::LogManager::getInstance().setSearchString(m_searchBox->text().toUtf8().constData());
}

void Logger::handleClearSearchButton() {
    m_log->clear();
#if DEBUG
    VapeLog::LogManager::getInstance().printMessage(VapeLog::LogMessage(
            VapeLog::LogTag::LOG, VapeLog::LogType::MESSAGE,
            VapeLog::LogSeverity::LOW, "Clear Regex search"));
#endif
    m_searchBox->clear();
    VapeLog::LogManager::getInstance().setSearchString("");
}

void Logger::handleClearLogButton() {
    m_log->clear();
    VapeLog::LogManager::getInstance().clearLog();
}