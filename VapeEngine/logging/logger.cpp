//
// Created by notjustin on 12/24/17.
//

#include "logger.h"
//#include "ui_logger.h"

using namespace VapeLog;

//Logger::Logger(QWidget *parent) :
//        QWidget(parent)
//{
//    //    ui->setupUi(this);
//}

void Logger::printLog() {

}
void Logger::handleSortTimeButton() {
#ifdef DEBUG
    fprintf(stderr, "Sort by time not implemented.\n");
#endif
}
void Logger::handleSortTagButton() {
#ifdef DEBUG
    fprintf(stderr, "Sort by Tag not implemented.\n");
#endif
}
void Logger::handleSortOccurencesButton() {
#ifdef DEBUG
    fprintf(stderr, "Sort by occurrences not implemented.\n");
#endif
}
void Logger::handleSortSeverityButton() {
#ifdef DEBUG
    fprintf(stderr, "Sort by severity not implemented.\n");
#endif
}
void Logger::handleSortTypeButton() {
#ifdef DEBUG
    fprintf(stderr, "Sort by type not implemented.\n");
#endif
}
void Logger::handleRegexSearchButton() {
#ifdef DEBUG
    fprintf(stderr, "regex search not implemented.\n");
#endif
}
void Logger::handleClearSearchButton() {
#ifdef DEBUG
    fprintf(stderr, "clear search not implemented.\n");
#endif
}
void Logger::handleClearLogButton() {
#ifdef DEBUG
    fprintf(stderr, "clear log not implemented.\n");
#endif
}