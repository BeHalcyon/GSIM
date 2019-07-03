/********************************************************************************
** Form generated from reading UI file 'controlPanel.ui'
**
** Created by: Qt User Interface Compiler version 5.8.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CONTROLPANEL_H
#define UI_CONTROLPANEL_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDoubleSpinBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_ControlPanel
{
public:
    QVBoxLayout *verticalLayout;
    QLabel *label;
    QComboBox *comboBox;
    QLabel *label_2;
    QComboBox *comboBox_2;
    QLabel *label_3;
    QLabel *label_4;
    QLineEdit *lineEdit;
    QLabel *label_5;
    QLineEdit *lineEdit_2;
    QLabel *label_11;
    QLineEdit *lineEdit_3;
    QPushButton *pushButton;
    QLabel *label_6;
    QLabel *label_7;
    QHBoxLayout *horizontalLayout;
    QDoubleSpinBox *doubleSpinBox;
    QLabel *label_9;
    QLabel *label_8;
    QHBoxLayout *horizontalLayout_2;
    QDoubleSpinBox *doubleSpinBox_2;
    QLabel *label_10;
    QCheckBox *checkBox;
    QCheckBox *checkBox_2;
    QCheckBox *isJaccardUsed;
    QSpacerItem *verticalSpacer;

    void setupUi(QWidget *ControlPanel)
    {
        if (ControlPanel->objectName().isEmpty())
            ControlPanel->setObjectName(QStringLiteral("ControlPanel"));
        ControlPanel->resize(150, 438);
        verticalLayout = new QVBoxLayout(ControlPanel);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        label = new QLabel(ControlPanel);
        label->setObjectName(QStringLiteral("label"));
        label->setTextFormat(Qt::AutoText);

        verticalLayout->addWidget(label);

        comboBox = new QComboBox(ControlPanel);
        comboBox->setObjectName(QStringLiteral("comboBox"));

        verticalLayout->addWidget(comboBox);

        label_2 = new QLabel(ControlPanel);
        label_2->setObjectName(QStringLiteral("label_2"));

        verticalLayout->addWidget(label_2);

        comboBox_2 = new QComboBox(ControlPanel);
        comboBox_2->setObjectName(QStringLiteral("comboBox_2"));

        verticalLayout->addWidget(comboBox_2);

        label_3 = new QLabel(ControlPanel);
        label_3->setObjectName(QStringLiteral("label_3"));

        verticalLayout->addWidget(label_3);

        label_4 = new QLabel(ControlPanel);
        label_4->setObjectName(QStringLiteral("label_4"));

        verticalLayout->addWidget(label_4);

        lineEdit = new QLineEdit(ControlPanel);
        lineEdit->setObjectName(QStringLiteral("lineEdit"));
        lineEdit->setMaximumSize(QSize(30, 16777215));

        verticalLayout->addWidget(lineEdit);

        label_5 = new QLabel(ControlPanel);
        label_5->setObjectName(QStringLiteral("label_5"));

        verticalLayout->addWidget(label_5);

        lineEdit_2 = new QLineEdit(ControlPanel);
        lineEdit_2->setObjectName(QStringLiteral("lineEdit_2"));
        lineEdit_2->setMaximumSize(QSize(30, 16777215));

        verticalLayout->addWidget(lineEdit_2);

        label_11 = new QLabel(ControlPanel);
        label_11->setObjectName(QStringLiteral("label_11"));
        label_11->setMaximumSize(QSize(50, 16777215));

        verticalLayout->addWidget(label_11);

        lineEdit_3 = new QLineEdit(ControlPanel);
        lineEdit_3->setObjectName(QStringLiteral("lineEdit_3"));
        lineEdit_3->setMaximumSize(QSize(30, 16777215));

        verticalLayout->addWidget(lineEdit_3);

        pushButton = new QPushButton(ControlPanel);
        pushButton->setObjectName(QStringLiteral("pushButton"));

        verticalLayout->addWidget(pushButton);

        label_6 = new QLabel(ControlPanel);
        label_6->setObjectName(QStringLiteral("label_6"));

        verticalLayout->addWidget(label_6);

        label_7 = new QLabel(ControlPanel);
        label_7->setObjectName(QStringLiteral("label_7"));

        verticalLayout->addWidget(label_7);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        doubleSpinBox = new QDoubleSpinBox(ControlPanel);
        doubleSpinBox->setObjectName(QStringLiteral("doubleSpinBox"));
        doubleSpinBox->setMaximumSize(QSize(50, 16777215));
        doubleSpinBox->setMaximum(50.99);
        doubleSpinBox->setSingleStep(0.1);
        doubleSpinBox->setValue(0.2);

        horizontalLayout->addWidget(doubleSpinBox);

        label_9 = new QLabel(ControlPanel);
        label_9->setObjectName(QStringLiteral("label_9"));

        horizontalLayout->addWidget(label_9);


        verticalLayout->addLayout(horizontalLayout);

        label_8 = new QLabel(ControlPanel);
        label_8->setObjectName(QStringLiteral("label_8"));

        verticalLayout->addWidget(label_8);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        doubleSpinBox_2 = new QDoubleSpinBox(ControlPanel);
        doubleSpinBox_2->setObjectName(QStringLiteral("doubleSpinBox_2"));
        doubleSpinBox_2->setMaximumSize(QSize(50, 16777215));
        doubleSpinBox_2->setMaximum(50.99);
        doubleSpinBox_2->setSingleStep(0.1);
        doubleSpinBox_2->setValue(10);

        horizontalLayout_2->addWidget(doubleSpinBox_2);

        label_10 = new QLabel(ControlPanel);
        label_10->setObjectName(QStringLiteral("label_10"));

        horizontalLayout_2->addWidget(label_10);


        verticalLayout->addLayout(horizontalLayout_2);

        checkBox = new QCheckBox(ControlPanel);
        checkBox->setObjectName(QStringLiteral("checkBox"));
        checkBox->setChecked(true);

        verticalLayout->addWidget(checkBox);

        checkBox_2 = new QCheckBox(ControlPanel);
        checkBox_2->setObjectName(QStringLiteral("checkBox_2"));

        verticalLayout->addWidget(checkBox_2);

        isJaccardUsed = new QCheckBox(ControlPanel);
        isJaccardUsed->setObjectName(QStringLiteral("isJaccardUsed"));

        verticalLayout->addWidget(isJaccardUsed);

        verticalSpacer = new QSpacerItem(20, 63, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout->addItem(verticalSpacer);


        retranslateUi(ControlPanel);

        QMetaObject::connectSlotsByName(ControlPanel);
    } // setupUi

    void retranslateUi(QWidget *ControlPanel)
    {
        ControlPanel->setWindowTitle(QApplication::translate("ControlPanel", "Form", Q_NULLPTR));
        label->setText(QApplication::translate("ControlPanel", "First, sort by", Q_NULLPTR));
        comboBox->clear();
        comboBox->insertItems(0, QStringList()
         << QApplication::translate("ControlPanel", "Degree", Q_NULLPTR)
         << QApplication::translate("ControlPanel", "Amount", Q_NULLPTR)
         << QApplication::translate("ControlPanel", "Mutual Info", Q_NULLPTR)
         << QApplication::translate("ControlPanel", "Coherent", Q_NULLPTR)
         << QApplication::translate("ControlPanel", "Pearson", Q_NULLPTR)
        );
        label_2->setText(QApplication::translate("ControlPanel", "Then, sort by", Q_NULLPTR));
        comboBox_2->clear();
        comboBox_2->insertItems(0, QStringList()
         << QApplication::translate("ControlPanel", "Degree", Q_NULLPTR)
         << QApplication::translate("ControlPanel", "Amount", Q_NULLPTR)
         << QApplication::translate("ControlPanel", "Mutual Info", Q_NULLPTR)
         << QApplication::translate("ControlPanel", "Coherent", Q_NULLPTR)
         << QApplication::translate("ControlPanel", "Pearson", Q_NULLPTR)
        );
        label_3->setText(QApplication::translate("ControlPanel", "Variate Set", Q_NULLPTR));
        label_4->setText(QApplication::translate("ControlPanel", "Min Degree", Q_NULLPTR));
        label_5->setText(QApplication::translate("ControlPanel", "Max Degree", Q_NULLPTR));
        label_11->setText(QApplication::translate("ControlPanel", "GSIM", Q_NULLPTR));
        lineEdit_3->setText(QApplication::translate("ControlPanel", "0.9", Q_NULLPTR));
        pushButton->setText(QApplication::translate("ControlPanel", "Submit", Q_NULLPTR));
        label_6->setText(QApplication::translate("ControlPanel", "Feature Subspace", Q_NULLPTR));
        label_7->setText(QApplication::translate("ControlPanel", "Min Size", Q_NULLPTR));
        label_9->setText(QApplication::translate("ControlPanel", "% Vol.", Q_NULLPTR));
        label_8->setText(QApplication::translate("ControlPanel", "Max Size", Q_NULLPTR));
        label_10->setText(QApplication::translate("ControlPanel", "% Vol.", Q_NULLPTR));
        checkBox->setText(QApplication::translate("ControlPanel", "Hide Empty", Q_NULLPTR));
        checkBox_2->setText(QApplication::translate("ControlPanel", "Subsets", Q_NULLPTR));
        isJaccardUsed->setText(QApplication::translate("ControlPanel", "Jaccard distance", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class ControlPanel: public Ui_ControlPanel {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CONTROLPANEL_H
