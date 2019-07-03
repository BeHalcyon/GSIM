/********************************************************************************
** Form generated from reading UI file 'renderproperties.ui'
**
** Created by: Qt User Interface Compiler version 5.8.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_RENDERPROPERTIES_H
#define UI_RENDERPROPERTIES_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSlider>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include <mydoublespinbox.h>

QT_BEGIN_NAMESPACE

class Ui_RenderProperties
{
public:
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout;
    QLabel *label;
    QSlider *horizontalSlider;
    MyDoubleSpinBox *doubleSpinBox;
    QHBoxLayout *horizontalLayout_2;
    QLabel *label_2;
    QSlider *horizontalSlider_2;
    MyDoubleSpinBox *doubleSpinBox_2;
    QHBoxLayout *horizontalLayout_3;
    QLabel *label_3;
    QSlider *horizontalSlider_3;
    MyDoubleSpinBox *doubleSpinBox_3;
    QHBoxLayout *horizontalLayout_4;
    QLabel *label_4;
    QSlider *horizontalSlider_4;
    MyDoubleSpinBox *doubleSpinBox_4;
    QHBoxLayout *horizontalLayout_9;
    QHBoxLayout *horizontalLayout_5;
    QLabel *label_5;
    QPushButton *pushButton;
    QSlider *horizontalSlider_5;
    QHBoxLayout *horizontalLayout_10;
    QHBoxLayout *horizontalLayout_6;
    QLabel *label_6;
    QPushButton *pushButton_2;
    QSlider *horizontalSlider_6;
    QHBoxLayout *horizontalLayout_11;
    QHBoxLayout *horizontalLayout_7;
    QLabel *label_7;
    QPushButton *pushButton_3;
    QSlider *horizontalSlider_7;
    QHBoxLayout *horizontalLayout_12;
    QHBoxLayout *horizontalLayout_8;
    QLabel *label_8;
    QPushButton *pushButton_4;
    QSlider *horizontalSlider_8;
    QSpacerItem *verticalSpacer;

    void setupUi(QWidget *RenderProperties)
    {
        if (RenderProperties->objectName().isEmpty())
            RenderProperties->setObjectName(QStringLiteral("RenderProperties"));
        RenderProperties->resize(400, 300);
        verticalLayout = new QVBoxLayout(RenderProperties);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        label = new QLabel(RenderProperties);
        label->setObjectName(QStringLiteral("label"));

        horizontalLayout->addWidget(label);

        horizontalSlider = new QSlider(RenderProperties);
        horizontalSlider->setObjectName(QStringLiteral("horizontalSlider"));
        horizontalSlider->setMaximum(100);
        horizontalSlider->setSingleStep(1);
        horizontalSlider->setValue(73);
        horizontalSlider->setOrientation(Qt::Horizontal);

        horizontalLayout->addWidget(horizontalSlider);

        doubleSpinBox = new MyDoubleSpinBox(RenderProperties);
        doubleSpinBox->setObjectName(QStringLiteral("doubleSpinBox"));
        doubleSpinBox->setMaximum(1);
        doubleSpinBox->setSingleStep(0.01);
        doubleSpinBox->setValue(0.73);

        horizontalLayout->addWidget(doubleSpinBox);


        verticalLayout->addLayout(horizontalLayout);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        label_2 = new QLabel(RenderProperties);
        label_2->setObjectName(QStringLiteral("label_2"));

        horizontalLayout_2->addWidget(label_2);

        horizontalSlider_2 = new QSlider(RenderProperties);
        horizontalSlider_2->setObjectName(QStringLiteral("horizontalSlider_2"));
        horizontalSlider_2->setMaximum(100);
        horizontalSlider_2->setValue(50);
        horizontalSlider_2->setOrientation(Qt::Horizontal);

        horizontalLayout_2->addWidget(horizontalSlider_2);

        doubleSpinBox_2 = new MyDoubleSpinBox(RenderProperties);
        doubleSpinBox_2->setObjectName(QStringLiteral("doubleSpinBox_2"));
        doubleSpinBox_2->setMaximum(1);
        doubleSpinBox_2->setSingleStep(0.01);
        doubleSpinBox_2->setValue(0.5);

        horizontalLayout_2->addWidget(doubleSpinBox_2);


        verticalLayout->addLayout(horizontalLayout_2);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName(QStringLiteral("horizontalLayout_3"));
        label_3 = new QLabel(RenderProperties);
        label_3->setObjectName(QStringLiteral("label_3"));

        horizontalLayout_3->addWidget(label_3);

        horizontalSlider_3 = new QSlider(RenderProperties);
        horizontalSlider_3->setObjectName(QStringLiteral("horizontalSlider_3"));
        horizontalSlider_3->setMaximum(100);
        horizontalSlider_3->setValue(10);
        horizontalSlider_3->setOrientation(Qt::Horizontal);

        horizontalLayout_3->addWidget(horizontalSlider_3);

        doubleSpinBox_3 = new MyDoubleSpinBox(RenderProperties);
        doubleSpinBox_3->setObjectName(QStringLiteral("doubleSpinBox_3"));
        doubleSpinBox_3->setMaximum(1);
        doubleSpinBox_3->setSingleStep(0.01);
        doubleSpinBox_3->setValue(0.1);

        horizontalLayout_3->addWidget(doubleSpinBox_3);


        verticalLayout->addLayout(horizontalLayout_3);

        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setObjectName(QStringLiteral("horizontalLayout_4"));
        label_4 = new QLabel(RenderProperties);
        label_4->setObjectName(QStringLiteral("label_4"));

        horizontalLayout_4->addWidget(label_4);

        horizontalSlider_4 = new QSlider(RenderProperties);
        horizontalSlider_4->setObjectName(QStringLiteral("horizontalSlider_4"));
        horizontalSlider_4->setMinimum(1);
        horizontalSlider_4->setMaximum(100);
        horizontalSlider_4->setValue(7);
        horizontalSlider_4->setOrientation(Qt::Horizontal);

        horizontalLayout_4->addWidget(horizontalSlider_4);

        doubleSpinBox_4 = new MyDoubleSpinBox(RenderProperties);
        doubleSpinBox_4->setObjectName(QStringLiteral("doubleSpinBox_4"));
        doubleSpinBox_4->setMaximum(1);
        doubleSpinBox_4->setSingleStep(0.01);
        doubleSpinBox_4->setValue(0.07);

        horizontalLayout_4->addWidget(doubleSpinBox_4);


        verticalLayout->addLayout(horizontalLayout_4);

        horizontalLayout_9 = new QHBoxLayout();
        horizontalLayout_9->setObjectName(QStringLiteral("horizontalLayout_9"));
        horizontalLayout_5 = new QHBoxLayout();
        horizontalLayout_5->setObjectName(QStringLiteral("horizontalLayout_5"));
        label_5 = new QLabel(RenderProperties);
        label_5->setObjectName(QStringLiteral("label_5"));

        horizontalLayout_5->addWidget(label_5);

        pushButton = new QPushButton(RenderProperties);
        pushButton->setObjectName(QStringLiteral("pushButton"));
        pushButton->setMinimumSize(QSize(25, 25));
        pushButton->setMaximumSize(QSize(25, 25));
        QIcon icon;
        icon.addFile(QStringLiteral(":/color/color.png"), QSize(), QIcon::Normal, QIcon::Off);
        pushButton->setIcon(icon);

        horizontalLayout_5->addWidget(pushButton);


        horizontalLayout_9->addLayout(horizontalLayout_5);

        horizontalSlider_5 = new QSlider(RenderProperties);
        horizontalSlider_5->setObjectName(QStringLiteral("horizontalSlider_5"));
        horizontalSlider_5->setMaximum(100);
        horizontalSlider_5->setValue(100);
        horizontalSlider_5->setOrientation(Qt::Horizontal);

        horizontalLayout_9->addWidget(horizontalSlider_5);


        verticalLayout->addLayout(horizontalLayout_9);

        horizontalLayout_10 = new QHBoxLayout();
        horizontalLayout_10->setObjectName(QStringLiteral("horizontalLayout_10"));
        horizontalLayout_6 = new QHBoxLayout();
        horizontalLayout_6->setObjectName(QStringLiteral("horizontalLayout_6"));
        label_6 = new QLabel(RenderProperties);
        label_6->setObjectName(QStringLiteral("label_6"));

        horizontalLayout_6->addWidget(label_6);

        pushButton_2 = new QPushButton(RenderProperties);
        pushButton_2->setObjectName(QStringLiteral("pushButton_2"));
        pushButton_2->setMinimumSize(QSize(25, 25));
        pushButton_2->setMaximumSize(QSize(25, 25));
        pushButton_2->setIcon(icon);

        horizontalLayout_6->addWidget(pushButton_2);


        horizontalLayout_10->addLayout(horizontalLayout_6);

        horizontalSlider_6 = new QSlider(RenderProperties);
        horizontalSlider_6->setObjectName(QStringLiteral("horizontalSlider_6"));
        horizontalSlider_6->setMaximum(100);
        horizontalSlider_6->setValue(100);
        horizontalSlider_6->setOrientation(Qt::Horizontal);

        horizontalLayout_10->addWidget(horizontalSlider_6);


        verticalLayout->addLayout(horizontalLayout_10);

        horizontalLayout_11 = new QHBoxLayout();
        horizontalLayout_11->setObjectName(QStringLiteral("horizontalLayout_11"));
        horizontalLayout_7 = new QHBoxLayout();
        horizontalLayout_7->setObjectName(QStringLiteral("horizontalLayout_7"));
        label_7 = new QLabel(RenderProperties);
        label_7->setObjectName(QStringLiteral("label_7"));

        horizontalLayout_7->addWidget(label_7);

        pushButton_3 = new QPushButton(RenderProperties);
        pushButton_3->setObjectName(QStringLiteral("pushButton_3"));
        pushButton_3->setMinimumSize(QSize(25, 25));
        pushButton_3->setMaximumSize(QSize(25, 25));
        pushButton_3->setIcon(icon);

        horizontalLayout_7->addWidget(pushButton_3);


        horizontalLayout_11->addLayout(horizontalLayout_7);

        horizontalSlider_7 = new QSlider(RenderProperties);
        horizontalSlider_7->setObjectName(QStringLiteral("horizontalSlider_7"));
        horizontalSlider_7->setMaximum(100);
        horizontalSlider_7->setValue(99);
        horizontalSlider_7->setOrientation(Qt::Horizontal);

        horizontalLayout_11->addWidget(horizontalSlider_7);


        verticalLayout->addLayout(horizontalLayout_11);

        horizontalLayout_12 = new QHBoxLayout();
        horizontalLayout_12->setObjectName(QStringLiteral("horizontalLayout_12"));
        horizontalLayout_8 = new QHBoxLayout();
        horizontalLayout_8->setObjectName(QStringLiteral("horizontalLayout_8"));
        label_8 = new QLabel(RenderProperties);
        label_8->setObjectName(QStringLiteral("label_8"));

        horizontalLayout_8->addWidget(label_8);

        pushButton_4 = new QPushButton(RenderProperties);
        pushButton_4->setObjectName(QStringLiteral("pushButton_4"));
        pushButton_4->setMinimumSize(QSize(25, 25));
        pushButton_4->setMaximumSize(QSize(25, 25));
        pushButton_4->setIcon(icon);

        horizontalLayout_8->addWidget(pushButton_4);


        horizontalLayout_12->addLayout(horizontalLayout_8);

        horizontalSlider_8 = new QSlider(RenderProperties);
        horizontalSlider_8->setObjectName(QStringLiteral("horizontalSlider_8"));
        horizontalSlider_8->setMaximum(100);
        horizontalSlider_8->setValue(100);
        horizontalSlider_8->setOrientation(Qt::Horizontal);

        horizontalLayout_12->addWidget(horizontalSlider_8);


        verticalLayout->addLayout(horizontalLayout_12);

        verticalSpacer = new QSpacerItem(20, 89, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout->addItem(verticalSpacer);


        retranslateUi(RenderProperties);

        QMetaObject::connectSlotsByName(RenderProperties);
    } // setupUi

    void retranslateUi(QWidget *RenderProperties)
    {
        RenderProperties->setWindowTitle(QApplication::translate("RenderProperties", "Form", Q_NULLPTR));
        label->setText(QApplication::translate("RenderProperties", "Ambient", Q_NULLPTR));
        label_2->setText(QApplication::translate("RenderProperties", "Diffuse", Q_NULLPTR));
        label_3->setText(QApplication::translate("RenderProperties", "Specular", Q_NULLPTR));
        label_4->setText(QApplication::translate("RenderProperties", "Opacity", Q_NULLPTR));
        label_5->setText(QApplication::translate("RenderProperties", "Feature1 Color", Q_NULLPTR));
        pushButton->setText(QString());
        label_6->setText(QApplication::translate("RenderProperties", "Feature2 Color", Q_NULLPTR));
        pushButton_2->setText(QString());
        label_7->setText(QApplication::translate("RenderProperties", "Feature3 Color", Q_NULLPTR));
        pushButton_3->setText(QString());
        label_8->setText(QApplication::translate("RenderProperties", "Feature4 Color", Q_NULLPTR));
        pushButton_4->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class RenderProperties: public Ui_RenderProperties {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_RENDERPROPERTIES_H
