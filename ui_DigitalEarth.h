/********************************************************************************
** Form generated from reading UI file 'DigitalEarth.ui'
**
** Created by: Qt User Interface Compiler version 5.15.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DIGITALEARTH_H
#define UI_DIGITALEARTH_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_DigitalEarth
{
public:
    QWidget *centralwidget;
    QGridLayout *mainLayout;

    void setupUi(QMainWindow *DigitalEarth)
    {
        if (DigitalEarth->objectName().isEmpty())
            DigitalEarth->setObjectName(QString::fromUtf8("DigitalEarth"));
        DigitalEarth->resize(800, 600);
        centralwidget = new QWidget(DigitalEarth);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        mainLayout = new QGridLayout(centralwidget);
        mainLayout->setSpacing(0);
        mainLayout->setObjectName(QString::fromUtf8("mainLayout"));
        mainLayout->setContentsMargins(3, 3, 3, 3);
        DigitalEarth->setCentralWidget(centralwidget);

        retranslateUi(DigitalEarth);

        QMetaObject::connectSlotsByName(DigitalEarth);
    } // setupUi

    void retranslateUi(QMainWindow *DigitalEarth)
    {
        DigitalEarth->setWindowTitle(QCoreApplication::translate("DigitalEarth", "DigitalEarth", nullptr));
    } // retranslateUi

};

namespace Ui {
    class DigitalEarth: public Ui_DigitalEarth {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DIGITALEARTH_H
