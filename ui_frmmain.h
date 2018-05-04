/********************************************************************************
** Form generated from reading UI file 'frmmain.ui'
**
** Created by: Qt User Interface Compiler version 5.8.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_FRMMAIN_H
#define UI_FRMMAIN_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_frmMain
{
public:
    QWidget *centralWidget;
    QGridLayout *gridLayout;
    QHBoxLayout *horizontalLayout;
    QPushButton *btnOpenFile;
    QLabel *lblChosenFile;
    QHBoxLayout *horizontalLayout_2;
    QLabel *lblOriginal;
    QLabel *lblCanny;

    void setupUi(QMainWindow *frmMain)
    {
        if (frmMain->objectName().isEmpty())
            frmMain->setObjectName(QStringLiteral("frmMain"));
        frmMain->resize(400, 300);
        centralWidget = new QWidget(frmMain);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        gridLayout = new QGridLayout(centralWidget);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(6);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        btnOpenFile = new QPushButton(centralWidget);
        btnOpenFile->setObjectName(QStringLiteral("btnOpenFile"));
        QFont font;
        font.setPointSize(12);
        btnOpenFile->setFont(font);

        horizontalLayout->addWidget(btnOpenFile);

        lblChosenFile = new QLabel(centralWidget);
        lblChosenFile->setObjectName(QStringLiteral("lblChosenFile"));

        horizontalLayout->addWidget(lblChosenFile);

        horizontalLayout->setStretch(1, 1);

        gridLayout->addLayout(horizontalLayout, 0, 0, 1, 1);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setSpacing(6);
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        lblOriginal = new QLabel(centralWidget);
        lblOriginal->setObjectName(QStringLiteral("lblOriginal"));
        lblOriginal->setFrameShape(QFrame::Box);
        lblOriginal->setAlignment(Qt::AlignCenter);

        horizontalLayout_2->addWidget(lblOriginal);

        lblCanny = new QLabel(centralWidget);
        lblCanny->setObjectName(QStringLiteral("lblCanny"));
        lblCanny->setFrameShape(QFrame::Box);
        lblCanny->setScaledContents(false);
        lblCanny->setAlignment(Qt::AlignCenter);

        horizontalLayout_2->addWidget(lblCanny);


        gridLayout->addLayout(horizontalLayout_2, 1, 0, 1, 1);

        gridLayout->setRowStretch(1, 1);
        frmMain->setCentralWidget(centralWidget);
        btnOpenFile->raise();
        lblChosenFile->raise();
        lblOriginal->raise();
        lblCanny->raise();
        btnOpenFile->raise();
        lblChosenFile->raise();

        retranslateUi(frmMain);

        QMetaObject::connectSlotsByName(frmMain);
    } // setupUi

    void retranslateUi(QMainWindow *frmMain)
    {
        frmMain->setWindowTitle(QApplication::translate("frmMain", "frmMain", Q_NULLPTR));
        btnOpenFile->setText(QApplication::translate("frmMain", "Open File", Q_NULLPTR));
        lblChosenFile->setText(QApplication::translate("frmMain", "TextLabel", Q_NULLPTR));
        lblOriginal->setText(QApplication::translate("frmMain", "TextLabel", Q_NULLPTR));
        lblCanny->setText(QApplication::translate("frmMain", "TextLabel", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class frmMain: public Ui_frmMain {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_FRMMAIN_H
