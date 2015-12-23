/********************************************************************************
** Form generated from reading UI file 'kmyengineeditor.ui'
**
** Created by: Qt User Interface Compiler version 5.2.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_KMYENGINEEDITOR_H
#define UI_KMYENGINEEDITOR_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QSlider>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_KMyEngineEditorClass
{
public:
    QAction *actionXinjianchangjing;
    QAction *actionChangjingbaocun;
    QWidget *centralWidget;
    QHBoxLayout *horizontalLayout;
    QVBoxLayout *verticalLayout;
    QListWidget *listWidget;
    QVBoxLayout *verticalLayout_4;
    QHBoxLayout *EngineGridLayout;
    QHBoxLayout *horizontalLayout_2;
    QTabWidget *tabWidget;
    QWidget *tab;
    QGroupBox *groupBox;
    QLabel *label;
    QRadioButton *RBTN_2048;
    QRadioButton *RBTN_1024;
    QRadioButton *RBTN_64;
    QLabel *label_3;
    QTextEdit *TEXT_CellSpacing;
    QRadioButton *RBTN_512;
    QGroupBox *groupBox_2;
    QRadioButton *RBTN_QuadTreeLod1;
    QRadioButton *RBTN_QuadTreeLod2;
    QRadioButton *RBTN_QuadTreeLOD3;
    QRadioButton *RBTN_QuadTreeLOD4;
    QRadioButton *RBTN_DX11Tesslation;
    QPushButton *BTN_CreateTerrain;
    QPushButton *BTN_LoadHeightMap;
    QWidget *tab_2;
    QPushButton *pushButton_15;
    QPushButton *pushButton_16;
    QPushButton *pushButton_17;
    QSlider *horizontalSlider_5;
    QLabel *label_5;
    QLabel *label_2;
    QLabel *label_6;
    QSlider *horizontalSlider_6;
    QPushButton *pushButton_20;
    QPushButton *pushButton_21;
    QSlider *horizontalSlider_2;
    QPushButton *pushButton_22;
    QWidget *tab_7;
    QMenuBar *menuBar;
    QMenu *menu;
    QMenu *menu_2;
    QMenu *menu_3;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *KMyEngineEditorClass)
    {
        if (KMyEngineEditorClass->objectName().isEmpty())
            KMyEngineEditorClass->setObjectName(QStringLiteral("KMyEngineEditorClass"));
        KMyEngineEditorClass->resize(1340, 858);
        actionXinjianchangjing = new QAction(KMyEngineEditorClass);
        actionXinjianchangjing->setObjectName(QStringLiteral("actionXinjianchangjing"));
        actionChangjingbaocun = new QAction(KMyEngineEditorClass);
        actionChangjingbaocun->setObjectName(QStringLiteral("actionChangjingbaocun"));
        centralWidget = new QWidget(KMyEngineEditorClass);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(centralWidget->sizePolicy().hasHeightForWidth());
        centralWidget->setSizePolicy(sizePolicy);
        horizontalLayout = new QHBoxLayout(centralWidget);
        horizontalLayout->setSpacing(6);
        horizontalLayout->setContentsMargins(11, 11, 11, 11);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        verticalLayout = new QVBoxLayout();
        verticalLayout->setSpacing(6);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        listWidget = new QListWidget(centralWidget);
        new QListWidgetItem(listWidget);
        listWidget->setObjectName(QStringLiteral("listWidget"));

        verticalLayout->addWidget(listWidget);


        horizontalLayout->addLayout(verticalLayout);

        verticalLayout_4 = new QVBoxLayout();
        verticalLayout_4->setSpacing(6);
        verticalLayout_4->setObjectName(QStringLiteral("verticalLayout_4"));
        EngineGridLayout = new QHBoxLayout();
        EngineGridLayout->setSpacing(6);
        EngineGridLayout->setObjectName(QStringLiteral("EngineGridLayout"));

        verticalLayout_4->addLayout(EngineGridLayout);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setSpacing(6);
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        tabWidget = new QTabWidget(centralWidget);
        tabWidget->setObjectName(QStringLiteral("tabWidget"));
        tab = new QWidget();
        tab->setObjectName(QStringLiteral("tab"));
        groupBox = new QGroupBox(tab);
        groupBox->setObjectName(QStringLiteral("groupBox"));
        groupBox->setGeometry(QRect(20, 10, 411, 81));
        label = new QLabel(groupBox);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(30, 20, 71, 16));
        RBTN_2048 = new QRadioButton(groupBox);
        RBTN_2048->setObjectName(QStringLiteral("RBTN_2048"));
        RBTN_2048->setGeometry(QRect(50, 40, 89, 16));
        RBTN_1024 = new QRadioButton(groupBox);
        RBTN_1024->setObjectName(QStringLiteral("RBTN_1024"));
        RBTN_1024->setGeometry(QRect(140, 40, 89, 16));
        RBTN_64 = new QRadioButton(groupBox);
        RBTN_64->setObjectName(QStringLiteral("RBTN_64"));
        RBTN_64->setGeometry(QRect(140, 60, 89, 16));
        label_3 = new QLabel(groupBox);
        label_3->setObjectName(QStringLiteral("label_3"));
        label_3->setGeometry(QRect(230, 20, 71, 16));
        TEXT_CellSpacing = new QTextEdit(groupBox);
        TEXT_CellSpacing->setObjectName(QStringLiteral("TEXT_CellSpacing"));
        TEXT_CellSpacing->setGeometry(QRect(260, 40, 104, 31));
        TEXT_CellSpacing->setTabStopWidth(60);
        RBTN_512 = new QRadioButton(groupBox);
        RBTN_512->setObjectName(QStringLiteral("RBTN_512"));
        RBTN_512->setGeometry(QRect(50, 60, 89, 16));
        groupBox_2 = new QGroupBox(tab);
        groupBox_2->setObjectName(QStringLiteral("groupBox_2"));
        groupBox_2->setGeometry(QRect(440, 10, 511, 80));
        RBTN_QuadTreeLod1 = new QRadioButton(groupBox_2);
        RBTN_QuadTreeLod1->setObjectName(QStringLiteral("RBTN_QuadTreeLod1"));
        RBTN_QuadTreeLod1->setGeometry(QRect(30, 30, 171, 16));
        RBTN_QuadTreeLod2 = new QRadioButton(groupBox_2);
        RBTN_QuadTreeLod2->setObjectName(QStringLiteral("RBTN_QuadTreeLod2"));
        RBTN_QuadTreeLod2->setGeometry(QRect(30, 60, 161, 16));
        RBTN_QuadTreeLOD3 = new QRadioButton(groupBox_2);
        RBTN_QuadTreeLOD3->setObjectName(QStringLiteral("RBTN_QuadTreeLOD3"));
        RBTN_QuadTreeLOD3->setGeometry(QRect(200, 30, 171, 16));
        RBTN_QuadTreeLOD4 = new QRadioButton(groupBox_2);
        RBTN_QuadTreeLOD4->setObjectName(QStringLiteral("RBTN_QuadTreeLOD4"));
        RBTN_QuadTreeLOD4->setGeometry(QRect(200, 60, 171, 16));
        RBTN_DX11Tesslation = new QRadioButton(groupBox_2);
        RBTN_DX11Tesslation->setObjectName(QStringLiteral("RBTN_DX11Tesslation"));
        RBTN_DX11Tesslation->setGeometry(QRect(370, 30, 171, 16));
        BTN_CreateTerrain = new QPushButton(tab);
        BTN_CreateTerrain->setObjectName(QStringLiteral("BTN_CreateTerrain"));
        BTN_CreateTerrain->setGeometry(QRect(960, 60, 101, 31));
        BTN_LoadHeightMap = new QPushButton(tab);
        BTN_LoadHeightMap->setObjectName(QStringLiteral("BTN_LoadHeightMap"));
        BTN_LoadHeightMap->setGeometry(QRect(960, 20, 101, 31));
        tabWidget->addTab(tab, QString());
        tab_2 = new QWidget();
        tab_2->setObjectName(QStringLiteral("tab_2"));
        pushButton_15 = new QPushButton(tab_2);
        pushButton_15->setObjectName(QStringLiteral("pushButton_15"));
        pushButton_15->setGeometry(QRect(560, 10, 111, 31));
        pushButton_16 = new QPushButton(tab_2);
        pushButton_16->setObjectName(QStringLiteral("pushButton_16"));
        pushButton_16->setGeometry(QRect(680, 10, 101, 31));
        pushButton_17 = new QPushButton(tab_2);
        pushButton_17->setObjectName(QStringLiteral("pushButton_17"));
        pushButton_17->setGeometry(QRect(200, 10, 171, 31));
        horizontalSlider_5 = new QSlider(tab_2);
        horizontalSlider_5->setObjectName(QStringLiteral("horizontalSlider_5"));
        horizontalSlider_5->setGeometry(QRect(410, 60, 131, 19));
        horizontalSlider_5->setOrientation(Qt::Horizontal);
        label_5 = new QLabel(tab_2);
        label_5->setObjectName(QStringLiteral("label_5"));
        label_5->setGeometry(QRect(380, 60, 54, 12));
        label_2 = new QLabel(tab_2);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setGeometry(QRect(210, 60, 54, 12));
        label_6 = new QLabel(tab_2);
        label_6->setObjectName(QStringLiteral("label_6"));
        label_6->setGeometry(QRect(10, 60, 54, 12));
        horizontalSlider_6 = new QSlider(tab_2);
        horizontalSlider_6->setObjectName(QStringLiteral("horizontalSlider_6"));
        horizontalSlider_6->setGeometry(QRect(60, 60, 121, 19));
        horizontalSlider_6->setOrientation(Qt::Horizontal);
        pushButton_20 = new QPushButton(tab_2);
        pushButton_20->setObjectName(QStringLiteral("pushButton_20"));
        pushButton_20->setGeometry(QRect(10, 10, 181, 31));
        pushButton_21 = new QPushButton(tab_2);
        pushButton_21->setObjectName(QStringLiteral("pushButton_21"));
        pushButton_21->setGeometry(QRect(380, 10, 161, 31));
        horizontalSlider_2 = new QSlider(tab_2);
        horizontalSlider_2->setObjectName(QStringLiteral("horizontalSlider_2"));
        horizontalSlider_2->setGeometry(QRect(249, 60, 121, 20));
        horizontalSlider_2->setOrientation(Qt::Horizontal);
        pushButton_22 = new QPushButton(tab_2);
        pushButton_22->setObjectName(QStringLiteral("pushButton_22"));
        pushButton_22->setGeometry(QRect(560, 50, 111, 31));
        tabWidget->addTab(tab_2, QString());
        tab_7 = new QWidget();
        tab_7->setObjectName(QStringLiteral("tab_7"));
        tabWidget->addTab(tab_7, QString());

        horizontalLayout_2->addWidget(tabWidget);


        verticalLayout_4->addLayout(horizontalLayout_2);

        verticalLayout_4->setStretch(0, 5);
        verticalLayout_4->setStretch(1, 1);

        horizontalLayout->addLayout(verticalLayout_4);

        horizontalLayout->setStretch(0, 1);
        horizontalLayout->setStretch(1, 5);
        KMyEngineEditorClass->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(KMyEngineEditorClass);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 1340, 23));
        menu = new QMenu(menuBar);
        menu->setObjectName(QStringLiteral("menu"));
        menu_2 = new QMenu(menuBar);
        menu_2->setObjectName(QStringLiteral("menu_2"));
        menu_3 = new QMenu(menuBar);
        menu_3->setObjectName(QStringLiteral("menu_3"));
        KMyEngineEditorClass->setMenuBar(menuBar);
        mainToolBar = new QToolBar(KMyEngineEditorClass);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        KMyEngineEditorClass->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(KMyEngineEditorClass);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        KMyEngineEditorClass->setStatusBar(statusBar);

        menuBar->addAction(menu->menuAction());
        menuBar->addAction(menu_2->menuAction());
        menuBar->addAction(menu_3->menuAction());
        menu->addAction(actionXinjianchangjing);
        menu->addAction(actionChangjingbaocun);

        retranslateUi(KMyEngineEditorClass);

        tabWidget->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(KMyEngineEditorClass);
    } // setupUi

    void retranslateUi(QMainWindow *KMyEngineEditorClass)
    {
        KMyEngineEditorClass->setWindowTitle(QApplication::translate("KMyEngineEditorClass", "KMyEngineEditor", 0));
        actionXinjianchangjing->setText(QApplication::translate("KMyEngineEditorClass", "\346\226\260\345\273\272\345\234\272\346\231\257", 0));
        actionChangjingbaocun->setText(QApplication::translate("KMyEngineEditorClass", "\344\277\235\345\255\230\345\234\272\346\231\257", 0));

        const bool __sortingEnabled = listWidget->isSortingEnabled();
        listWidget->setSortingEnabled(false);
        QListWidgetItem *___qlistwidgetitem = listWidget->item(0);
        ___qlistwidgetitem->setText(QApplication::translate("KMyEngineEditorClass", "\345\261\202\346\254\241\351\235\242\346\235\277", 0));
        listWidget->setSortingEnabled(__sortingEnabled);

        groupBox->setTitle(QApplication::translate("KMyEngineEditorClass", "\351\200\232\347\224\250\345\217\202\346\225\260", 0));
        label->setText(QApplication::translate("KMyEngineEditorClass", "\345\234\260\345\275\242\345\210\206\350\276\250\347\216\207", 0));
        RBTN_2048->setText(QApplication::translate("KMyEngineEditorClass", "2048*2048", 0));
        RBTN_1024->setText(QApplication::translate("KMyEngineEditorClass", "1024*1024", 0));
        RBTN_64->setText(QApplication::translate("KMyEngineEditorClass", "64*64", 0));
        label_3->setText(QApplication::translate("KMyEngineEditorClass", "CellSpacing", 0));
        RBTN_512->setText(QApplication::translate("KMyEngineEditorClass", "512*512", 0));
        groupBox_2->setTitle(QApplication::translate("KMyEngineEditorClass", "\347\256\227\346\263\225\351\200\211\346\213\251", 0));
        RBTN_QuadTreeLod1->setText(QApplication::translate("KMyEngineEditorClass", "\345\233\233\345\217\211\346\240\221+Section IB\345\217\230VB\345\256\232", 0));
        RBTN_QuadTreeLod2->setText(QApplication::translate("KMyEngineEditorClass", "\347\275\221\347\273\234\345\255\246\344\271\240\345\233\233\345\217\211\346\240\221LOD\345\234\260\345\275\242", 0));
        RBTN_QuadTreeLOD3->setText(QApplication::translate("KMyEngineEditorClass", "\345\233\233\345\217\211\346\240\221+Section IB\345\217\230VB\345\256\232", 0));
        RBTN_QuadTreeLOD4->setText(QApplication::translate("KMyEngineEditorClass", "\345\233\233\345\217\211\346\240\221+Section IB\345\217\230VB\345\256\232", 0));
        RBTN_DX11Tesslation->setText(QApplication::translate("KMyEngineEditorClass", "DX11\346\233\262\351\235\242\347\273\206\345\210\206", 0));
        BTN_CreateTerrain->setText(QApplication::translate("KMyEngineEditorClass", "\347\224\237\346\210\220\345\234\260\345\275\242", 0));
        BTN_LoadHeightMap->setText(QApplication::translate("KMyEngineEditorClass", "\345\212\240\350\275\275\351\253\230\345\272\246\345\233\276", 0));
        tabWidget->setTabText(tabWidget->indexOf(tab), QApplication::translate("KMyEngineEditorClass", "\345\234\260\345\275\242\347\224\237\346\210\220\347\256\227\346\263\225", 0));
        pushButton_15->setText(QApplication::translate("KMyEngineEditorClass", "\346\267\273\345\212\240\351\235\231\346\200\201\344\272\221", 0));
        pushButton_16->setText(QApplication::translate("KMyEngineEditorClass", "\345\274\200\345\220\257\345\244\251\347\251\272\347\233\222", 0));
        pushButton_17->setText(QApplication::translate("KMyEngineEditorClass", "\344\272\224\345\261\202\347\272\271\347\220\206\346\267\267\345\220\210", 0));
        label_5->setText(QApplication::translate("KMyEngineEditorClass", "\346\267\261\345\272\246", 0));
        label_2->setText(QApplication::translate("KMyEngineEditorClass", "offset", 0));
        label_6->setText(QApplication::translate("KMyEngineEditorClass", "tiling", 0));
        pushButton_20->setText(QApplication::translate("KMyEngineEditorClass", "\344\270\200\345\261\202\347\272\271\347\220\206\346\265\213\350\257\225", 0));
        pushButton_21->setText(QApplication::translate("KMyEngineEditorClass", "DetailMap\347\273\206\350\212\202\347\272\271\347\220\206", 0));
        pushButton_22->setText(QApplication::translate("KMyEngineEditorClass", "\346\267\273\345\212\240\345\212\250\346\200\201\344\272\221", 0));
        tabWidget->setTabText(tabWidget->indexOf(tab_2), QApplication::translate("KMyEngineEditorClass", "\345\234\260\345\275\242\347\273\206\350\212\202\351\200\211\351\241\271", 0));
        tabWidget->setTabText(tabWidget->indexOf(tab_7), QApplication::translate("KMyEngineEditorClass", "\345\234\260\345\275\242\351\253\230\345\272\246\347\274\226\350\276\221", 0));
        menu->setTitle(QApplication::translate("KMyEngineEditorClass", "\345\234\272\346\231\257\346\226\207\344\273\266", 0));
        menu_2->setTitle(QApplication::translate("KMyEngineEditorClass", "\346\250\241\345\236\213\347\274\226\350\276\221\345\231\250", 0));
        menu_3->setTitle(QApplication::translate("KMyEngineEditorClass", "\347\201\257\345\205\211", 0));
    } // retranslateUi

};

namespace Ui {
    class KMyEngineEditorClass: public Ui_KMyEngineEditorClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_KMYENGINEEDITOR_H
