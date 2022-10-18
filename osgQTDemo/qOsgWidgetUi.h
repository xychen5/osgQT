#ifndef QOSGWIDGETUI_H
#define QOSGWIDGETUI_H

#include <QWidget>
#include "qOsgWidget.h"

namespace Ui {
class QOsgWidgetUi;
}

class QOsgWidgetUi : public QWidget
{
    Q_OBJECT

public:
    explicit QOsgWidgetUi(QWidget *parent = nullptr);
    explicit QOsgWidgetUi(QWidget *parent = nullptr, std::string modelPath = "");

    /**
     * @brief initQOsgWidget: attach the qosgWidget to this ui class
     * @param modelPath: moddel needed to show and edit
     */
    void initQOsgWidget(std::string modelPath);

    ///< the qOsgWidget to embedded into this ui
    QOsgWidget *modelInterface = nullptr;

    ~QOsgWidgetUi();

private:
    Ui::QOsgWidgetUi *ui;
};

#endif // QOSGWIDGETUI_H
