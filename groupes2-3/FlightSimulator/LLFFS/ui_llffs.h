/********************************************************************************
** Form generated from reading UI file 'llffs.ui'
**
** Created by: Qt User Interface Compiler version 5.5.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_LLFFS_H
#define UI_LLFFS_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_LLFFS
{
public:

    void setupUi(QWidget *LLFFS)
    {
        if (LLFFS->objectName().isEmpty())
            LLFFS->setObjectName(QStringLiteral("LLFFS"));
        LLFFS->resize(400, 300);

        retranslateUi(LLFFS);

        QMetaObject::connectSlotsByName(LLFFS);
    } // setupUi

    void retranslateUi(QWidget *LLFFS)
    {
        LLFFS->setWindowTitle(QApplication::translate("LLFFS", "Form", 0));
    } // retranslateUi

};

namespace Ui {
    class LLFFS: public Ui_LLFFS {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_LLFFS_H
