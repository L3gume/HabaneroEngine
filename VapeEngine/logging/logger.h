//
// Created by notjustin on 12/24/17.
//

#ifndef VAPEENGINE_LOGGER_H
#define VAPEENGINE_LOGGER_H

#define BUTTON_WIDTH 80
#define BUTTON_HEIGHT 40

#include <QWidget>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QListView>

namespace VapeLog {

    class Logger : public QWidget {
    Q_OBJECT

    public:
        explicit Logger(QWidget* parent) : QWidget(parent) {

            /*
             * Hard-coded UI since it really won't change much and doing Qt outside of qtcreator is a pain in the butt.
             */

            this->setWindowTitle("VapeLog");

            m_sortTimeButton = new QPushButton("Sort by:\nTime", this);
            m_sortTimeButton->setGeometry(QRect(QPoint(0 * BUTTON_WIDTH, 0), QSize(BUTTON_WIDTH, BUTTON_HEIGHT)));
            connect(m_sortTimeButton, SIGNAL (released()), this, SLOT (handleSortTimeButton()));

            m_sortTagButton = new QPushButton("Sort by:\nTag", this);
            m_sortTagButton->setGeometry(QRect(QPoint(1 * BUTTON_WIDTH, 0), QSize(BUTTON_WIDTH, BUTTON_HEIGHT)));
            connect(m_sortTagButton, SIGNAL (released()), this, SLOT (handleSortTagButton()));

            m_sortOccurencesButton = new QPushButton("Sort by:\nOccurrences", this);
            m_sortOccurencesButton->setGeometry(QRect(QPoint(2 * BUTTON_WIDTH, 0), QSize(BUTTON_WIDTH, BUTTON_HEIGHT)));
            connect(m_sortOccurencesButton, SIGNAL (released()), this, SLOT (handleSortOccurencesButton()));

            m_sortSeverityButton = new QPushButton("Sort by:\nSeverity", this);
            m_sortSeverityButton->setGeometry(QRect(QPoint(3 * BUTTON_WIDTH, 0), QSize(BUTTON_WIDTH, BUTTON_HEIGHT)));
            connect(m_sortSeverityButton, SIGNAL (released()), this, SLOT (handleSortSeverityButton()));

            m_sortTypeButton = new QPushButton("Sort by:\nType", this);
            m_sortTypeButton->setGeometry(QRect(QPoint(4 * BUTTON_WIDTH, 0), QSize(BUTTON_WIDTH, BUTTON_HEIGHT)));
            connect(m_sortTypeButton, SIGNAL (released()), this, SLOT (handleSortTypeButton()));

            m_searchBox = new QLineEdit(this);
            m_searchBox->setGeometry(QRect(QPoint(5 * BUTTON_WIDTH, 0), QSize(3 * BUTTON_WIDTH, BUTTON_HEIGHT)));

            m_regexSearchButton = new QPushButton("Regex\nSearch", this);
            m_regexSearchButton->setGeometry(QRect(QPoint(8 * BUTTON_WIDTH, 0), QSize(BUTTON_WIDTH, BUTTON_HEIGHT)));
            connect(m_regexSearchButton, SIGNAL (released()), this, SLOT (handleRegexSearchButton()));

            m_clearSearchButton = new QPushButton("Clear\nSearch", this);
            m_clearSearchButton->setGeometry(QRect(QPoint(9 * BUTTON_WIDTH, 0), QSize(BUTTON_WIDTH, BUTTON_HEIGHT)));
            connect(m_clearSearchButton, SIGNAL (released()), this, SLOT (handleClearSearchButton()));

            m_logList = new QListView(this);
            m_logList->setGeometry(QRect(QPoint(0 * BUTTON_WIDTH, BUTTON_HEIGHT), QSize(10 * BUTTON_WIDTH, 10 * BUTTON_HEIGHT)));

            m_clearLogButton = new QPushButton("Clear\nLog", this);
            m_clearLogButton->setGeometry(QRect(QPoint(9 * BUTTON_WIDTH, 11 * BUTTON_HEIGHT), QSize(BUTTON_WIDTH, BUTTON_HEIGHT)));
            connect(m_clearLogButton, SIGNAL (released()), this, SLOT (handleClearLogButton()));
        }

        ~Logger() override {
            delete m_searchBox;
            delete m_logList;
            delete m_sortTimeButton;
            delete m_sortTagButton;
            delete m_sortOccurencesButton;
            delete m_sortSeverityButton;
            delete m_sortTypeButton;
            delete m_regexSearchButton;
            delete m_clearSearchButton;
            delete m_clearLogButton;
        }

        void printLog(); // TODO;
    private slots:
        void handleSortTimeButton();
        void handleSortTagButton();
        void handleSortOccurencesButton();
        void handleSortSeverityButton();
        void handleSortTypeButton();
        void handleRegexSearchButton();
        void handleClearSearchButton();
        void handleClearLogButton();
    private:
        QLineEdit* m_searchBox;
        QListView* m_logList;

        QPushButton* m_sortTimeButton;
        QPushButton* m_sortTagButton;
        QPushButton* m_sortOccurencesButton;
        QPushButton* m_sortSeverityButton;
        QPushButton* m_sortTypeButton;
        QPushButton* m_regexSearchButton;
        QPushButton* m_clearSearchButton;
        QPushButton* m_clearLogButton;
    };
}

namespace Ui {
    class VapeLog::Logger;
}
#endif //VAPEENGINE_LOGGER_H
