//
// Created by notjustin on 12/24/17.
//

#ifndef VAPEENGINE_LOGGER_H
#define VAPEENGINE_LOGGER_H
#include <QWidget>
#include "ui_logger.h"

namespace VapeLog {

    class Logger : public QWidget {
    Q_OBJECT

    public:
        explicit Logger(QWidget* parent) : QWidget(parent), ui(new Ui::Logger) {
            ui->setupUi(this);
        }

        ~Logger() override {
            delete ui;
        }

    private:
        Ui::Logger *ui;
    };
}

namespace Ui {
    class VapeLog::Logger;
}
#endif //VAPEENGINE_LOGGER_H
