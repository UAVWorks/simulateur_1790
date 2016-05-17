/********************************************************************************
** Form generated from reading UI file 'maindialog.ui'
**
** Created by: Qt User Interface Compiler version 5.5.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINDIALOG_H
#define UI_MAINDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QTreeView>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainDialog
{
public:
    QGridLayout *gridLayout;
    QSpacerItem *horizontalSpacer;
    QPushButton *pbuQuit;
    QTabWidget *tabWidget;
    QWidget *tab;
    QTreeView *treeView;
    QWidget *tab_2;
    QTreeView *treeView_2;
    QWidget *tab_3;
    QTreeView *treeView_3;
    QWidget *tab_4;
    QTreeView *treeView_4;
    QLabel *label;

    void setupUi(QDialog *MainDialog)
    {
        if (MainDialog->objectName().isEmpty())
            MainDialog->setObjectName(QStringLiteral("MainDialog"));
        MainDialog->resize(651, 479);
        gridLayout = new QGridLayout(MainDialog);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        horizontalSpacer = new QSpacerItem(145, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer, 0, 1, 1, 1);

        pbuQuit = new QPushButton(MainDialog);
        pbuQuit->setObjectName(QStringLiteral("pbuQuit"));

        gridLayout->addWidget(pbuQuit, 0, 2, 1, 1);

        tabWidget = new QTabWidget(MainDialog);
        tabWidget->setObjectName(QStringLiteral("tabWidget"));
        tab = new QWidget();
        tab->setObjectName(QStringLiteral("tab"));
        treeView = new QTreeView(tab);
        treeView->setObjectName(QStringLiteral("treeView"));
        treeView->setGeometry(QRect(10, 10, 611, 381));
        tabWidget->addTab(tab, QString());
        tab_2 = new QWidget();
        tab_2->setObjectName(QStringLiteral("tab_2"));
        treeView_2 = new QTreeView(tab_2);
        treeView_2->setObjectName(QStringLiteral("treeView_2"));
        treeView_2->setGeometry(QRect(10, 10, 611, 381));
        QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(treeView_2->sizePolicy().hasHeightForWidth());
        treeView_2->setSizePolicy(sizePolicy);
        treeView_2->setAutoFillBackground(false);
        tabWidget->addTab(tab_2, QString());
        tab_3 = new QWidget();
        tab_3->setObjectName(QStringLiteral("tab_3"));
        treeView_3 = new QTreeView(tab_3);
        treeView_3->setObjectName(QStringLiteral("treeView_3"));
        treeView_3->setGeometry(QRect(10, 10, 611, 381));
        tabWidget->addTab(tab_3, QString());
        tab_4 = new QWidget();
        tab_4->setObjectName(QStringLiteral("tab_4"));
        treeView_4 = new QTreeView(tab_4);
        treeView_4->setObjectName(QStringLiteral("treeView_4"));
        treeView_4->setGeometry(QRect(10, 10, 611, 381));
        tabWidget->addTab(tab_4, QString());

        gridLayout->addWidget(tabWidget, 1, 0, 1, 3);

        label = new QLabel(MainDialog);
        label->setObjectName(QStringLiteral("label"));

        gridLayout->addWidget(label, 0, 0, 1, 1);


        retranslateUi(MainDialog);

        tabWidget->setCurrentIndex(3);


        QMetaObject::connectSlotsByName(MainDialog);
    } // setupUi

    void retranslateUi(QDialog *MainDialog)
    {
        MainDialog->setWindowTitle(QApplication::translate("MainDialog", "Dialog", 0));
        pbuQuit->setText(QApplication::translate("MainDialog", "Quitter", 0));
        tabWidget->setTabText(tabWidget->indexOf(tab), QApplication::translate("MainDialog", "Arduino 1", 0));
        tabWidget->setTabText(tabWidget->indexOf(tab_2), QApplication::translate("MainDialog", "Arduino 2", 0));
        tabWidget->setTabText(tabWidget->indexOf(tab_3), QApplication::translate("MainDialog", "Arduino 3", 0));
        tabWidget->setTabText(tabWidget->indexOf(tab_4), QApplication::translate("MainDialog", "Arduino 4", 0));
        label->setText(QApplication::translate("MainDialog", "Vue arborescente des communications logiciel / Arduinos", 0));
    } // retranslateUi

};

namespace Ui {
    class MainDialog: public Ui_MainDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINDIALOG_H
