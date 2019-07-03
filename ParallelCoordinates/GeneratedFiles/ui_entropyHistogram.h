/********************************************************************************
** Form generated from reading UI file 'entropyHistogram.ui'
**
** Created by: Qt User Interface Compiler version 5.8.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_ENTROPYHISTOGRAM_H
#define UI_ENTROPYHISTOGRAM_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_EntropyForm
{
public:
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout;
    QPushButton *pushButton;
    QPushButton *pushButton_2;
    QTableWidget *tableWidget;

    void setupUi(QWidget *EntropyForm)
    {
        if (EntropyForm->objectName().isEmpty())
            EntropyForm->setObjectName(QStringLiteral("EntropyForm"));
        EntropyForm->resize(400, 300);
        EntropyForm->setAcceptDrops(true);
        verticalLayout = new QVBoxLayout(EntropyForm);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        pushButton = new QPushButton(EntropyForm);
        pushButton->setObjectName(QStringLiteral("pushButton"));

        horizontalLayout->addWidget(pushButton);

        pushButton_2 = new QPushButton(EntropyForm);
        pushButton_2->setObjectName(QStringLiteral("pushButton_2"));

        horizontalLayout->addWidget(pushButton_2);


        verticalLayout->addLayout(horizontalLayout);

        tableWidget = new QTableWidget(EntropyForm);
        tableWidget->setObjectName(QStringLiteral("tableWidget"));

        verticalLayout->addWidget(tableWidget);


        retranslateUi(EntropyForm);

        QMetaObject::connectSlotsByName(EntropyForm);
    } // setupUi

    void retranslateUi(QWidget *EntropyForm)
    {
        EntropyForm->setWindowTitle(QApplication::translate("EntropyForm", "Entropy View", Q_NULLPTR));
        pushButton->setText(QApplication::translate("EntropyForm", "Load Volumes...", Q_NULLPTR));
        pushButton_2->setText(QApplication::translate("EntropyForm", "Update", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class EntropyForm: public Ui_EntropyForm {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_ENTROPYHISTOGRAM_H
