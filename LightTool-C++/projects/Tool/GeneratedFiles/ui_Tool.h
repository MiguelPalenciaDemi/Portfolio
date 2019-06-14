/********************************************************************************
** Form generated from reading UI file 'Tool.ui'
**
** Created by: Qt User Interface Compiler version 5.12.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_TOOL_H
#define UI_TOOL_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDoubleSpinBox>
#include <QtWidgets/QFrame>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_ToolClass
{
public:
    QWidget *centralWidget;
    QVBoxLayout *verticalLayout_4;
    QVBoxLayout *verticalLayout_3;
    QLabel *label_26;
    QVBoxLayout *verticalLayout_2;
    QHBoxLayout *horizontalLayout_5;
    QVBoxLayout *Ambient_L_2;
    QLabel *label_14;
    QDoubleSpinBox *directional_ambient;
    QVBoxLayout *Intensity_L_2;
    QLabel *label_15;
    QDoubleSpinBox *directional_intensity;
    QVBoxLayout *Specular_L_2;
    QLabel *label_16;
    QDoubleSpinBox *directional_specular;
    QHBoxLayout *horizontalLayout_6;
    QVBoxLayout *Position_L_2;
    QLabel *label_18;
    QHBoxLayout *horizontalLayout_7;
    QLabel *label_19;
    QDoubleSpinBox *directional_x;
    QLabel *label_20;
    QDoubleSpinBox *directional_y;
    QLabel *label_21;
    QDoubleSpinBox *directional_z;
    QFrame *line;
    QVBoxLayout *Color_L_2;
    QLabel *label_22;
    QHBoxLayout *horizontalLayout_8;
    QLabel *label_23;
    QDoubleSpinBox *directional_r;
    QLabel *label_24;
    QDoubleSpinBox *directional_g;
    QLabel *label_25;
    QDoubleSpinBox *directional_b;
    QPushButton *DeleteDirectionalLight_Button;
    QPushButton *CreateDirectionalLight_Button;
    QVBoxLayout *PointLight;
    QLabel *label;
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout_3;
    QVBoxLayout *Ambient_L;
    QLabel *label_2;
    QDoubleSpinBox *point_ambient;
    QVBoxLayout *Intensity_L;
    QLabel *label_3;
    QDoubleSpinBox *point_intensity;
    QVBoxLayout *Specular_L;
    QLabel *label_4;
    QDoubleSpinBox *point_specular;
    QVBoxLayout *Range_L;
    QLabel *label_5;
    QDoubleSpinBox *point_range;
    QHBoxLayout *horizontalLayout_4;
    QVBoxLayout *Position_L;
    QLabel *label_6;
    QHBoxLayout *horizontalLayout;
    QLabel *label_7;
    QDoubleSpinBox *point_x;
    QLabel *label_10;
    QDoubleSpinBox *point_y;
    QLabel *label_11;
    QDoubleSpinBox *point_z;
    QFrame *line_2;
    QVBoxLayout *Color_L;
    QLabel *label_8;
    QHBoxLayout *horizontalLayout_2;
    QLabel *label_9;
    QDoubleSpinBox *point_r;
    QLabel *label_12;
    QDoubleSpinBox *point_g;
    QLabel *label_13;
    QDoubleSpinBox *point_b;
    QPushButton *DeletePointLight_Button;
    QPushButton *CreatePointLight_Button;
    QVBoxLayout *Position_L_3;
    QHBoxLayout *horizontalLayout_9;
    QLabel *label_27;
    QLabel *label_28;
    QLabel *camera_x;
    QLabel *label_29;
    QLabel *camera_y;
    QLabel *label_30;
    QLabel *camera_z;
    QHBoxLayout *horizontalLayout_10;
    QVBoxLayout *verticalLayout_5;
    QLineEdit *LoadPath;
    QPushButton *LoadButton;
    QVBoxLayout *verticalLayout_9;
    QLineEdit *SavePath;
    QPushButton *SaveButton;
    QVBoxLayout *verticalLayout_8;
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *ToolClass)
    {
        if (ToolClass->objectName().isEmpty())
            ToolClass->setObjectName(QString::fromUtf8("ToolClass"));
        ToolClass->resize(729, 651);
        centralWidget = new QWidget(ToolClass);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        verticalLayout_4 = new QVBoxLayout(centralWidget);
        verticalLayout_4->setSpacing(6);
        verticalLayout_4->setContentsMargins(11, 11, 11, 11);
        verticalLayout_4->setObjectName(QString::fromUtf8("verticalLayout_4"));
        verticalLayout_3 = new QVBoxLayout();
        verticalLayout_3->setSpacing(6);
        verticalLayout_3->setObjectName(QString::fromUtf8("verticalLayout_3"));
        label_26 = new QLabel(centralWidget);
        label_26->setObjectName(QString::fromUtf8("label_26"));
        QFont font;
        font.setFamily(QString::fromUtf8("Microsoft JhengHei"));
        font.setPointSize(18);
        font.setBold(true);
        font.setWeight(75);
        label_26->setFont(font);
        label_26->setAlignment(Qt::AlignCenter);

        verticalLayout_3->addWidget(label_26);

        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setSpacing(6);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        horizontalLayout_5 = new QHBoxLayout();
        horizontalLayout_5->setSpacing(6);
        horizontalLayout_5->setObjectName(QString::fromUtf8("horizontalLayout_5"));
        Ambient_L_2 = new QVBoxLayout();
        Ambient_L_2->setSpacing(6);
        Ambient_L_2->setObjectName(QString::fromUtf8("Ambient_L_2"));
        label_14 = new QLabel(centralWidget);
        label_14->setObjectName(QString::fromUtf8("label_14"));

        Ambient_L_2->addWidget(label_14);

        directional_ambient = new QDoubleSpinBox(centralWidget);
        directional_ambient->setObjectName(QString::fromUtf8("directional_ambient"));
        directional_ambient->setMaximumSize(QSize(100, 20));
        directional_ambient->setMinimum(-200000.000000000000000);
        directional_ambient->setMaximum(200000.000000000000000);

        Ambient_L_2->addWidget(directional_ambient);


        horizontalLayout_5->addLayout(Ambient_L_2);

        Intensity_L_2 = new QVBoxLayout();
        Intensity_L_2->setSpacing(6);
        Intensity_L_2->setObjectName(QString::fromUtf8("Intensity_L_2"));
        label_15 = new QLabel(centralWidget);
        label_15->setObjectName(QString::fromUtf8("label_15"));

        Intensity_L_2->addWidget(label_15);

        directional_intensity = new QDoubleSpinBox(centralWidget);
        directional_intensity->setObjectName(QString::fromUtf8("directional_intensity"));
        directional_intensity->setMaximumSize(QSize(100, 20));
        directional_intensity->setMinimum(-200000.000000000000000);
        directional_intensity->setMaximum(200000.000000000000000);

        Intensity_L_2->addWidget(directional_intensity);


        horizontalLayout_5->addLayout(Intensity_L_2);

        Specular_L_2 = new QVBoxLayout();
        Specular_L_2->setSpacing(6);
        Specular_L_2->setObjectName(QString::fromUtf8("Specular_L_2"));
        label_16 = new QLabel(centralWidget);
        label_16->setObjectName(QString::fromUtf8("label_16"));

        Specular_L_2->addWidget(label_16);

        directional_specular = new QDoubleSpinBox(centralWidget);
        directional_specular->setObjectName(QString::fromUtf8("directional_specular"));
        directional_specular->setMaximumSize(QSize(100, 20));
        directional_specular->setMinimum(-200000.000000000000000);
        directional_specular->setMaximum(200000.000000000000000);

        Specular_L_2->addWidget(directional_specular);


        horizontalLayout_5->addLayout(Specular_L_2);


        verticalLayout_2->addLayout(horizontalLayout_5);

        horizontalLayout_6 = new QHBoxLayout();
        horizontalLayout_6->setSpacing(6);
        horizontalLayout_6->setObjectName(QString::fromUtf8("horizontalLayout_6"));
        Position_L_2 = new QVBoxLayout();
        Position_L_2->setSpacing(6);
        Position_L_2->setObjectName(QString::fromUtf8("Position_L_2"));
        label_18 = new QLabel(centralWidget);
        label_18->setObjectName(QString::fromUtf8("label_18"));

        Position_L_2->addWidget(label_18);

        horizontalLayout_7 = new QHBoxLayout();
        horizontalLayout_7->setSpacing(6);
        horizontalLayout_7->setObjectName(QString::fromUtf8("horizontalLayout_7"));
        label_19 = new QLabel(centralWidget);
        label_19->setObjectName(QString::fromUtf8("label_19"));
        label_19->setMinimumSize(QSize(10, 24));

        horizontalLayout_7->addWidget(label_19, 0, Qt::AlignRight);

        directional_x = new QDoubleSpinBox(centralWidget);
        directional_x->setObjectName(QString::fromUtf8("directional_x"));
        directional_x->setMinimum(-200000.000000000000000);
        directional_x->setMaximum(200000.000000000000000);

        horizontalLayout_7->addWidget(directional_x);

        label_20 = new QLabel(centralWidget);
        label_20->setObjectName(QString::fromUtf8("label_20"));
        label_20->setMinimumSize(QSize(10, 24));

        horizontalLayout_7->addWidget(label_20, 0, Qt::AlignRight);

        directional_y = new QDoubleSpinBox(centralWidget);
        directional_y->setObjectName(QString::fromUtf8("directional_y"));
        directional_y->setMinimum(-200000.000000000000000);
        directional_y->setMaximum(200000.000000000000000);

        horizontalLayout_7->addWidget(directional_y);

        label_21 = new QLabel(centralWidget);
        label_21->setObjectName(QString::fromUtf8("label_21"));
        label_21->setMinimumSize(QSize(10, 24));

        horizontalLayout_7->addWidget(label_21, 0, Qt::AlignRight);

        directional_z = new QDoubleSpinBox(centralWidget);
        directional_z->setObjectName(QString::fromUtf8("directional_z"));
        directional_z->setMinimum(-200000.000000000000000);
        directional_z->setMaximum(200000.000000000000000);

        horizontalLayout_7->addWidget(directional_z);


        Position_L_2->addLayout(horizontalLayout_7);


        horizontalLayout_6->addLayout(Position_L_2);

        line = new QFrame(centralWidget);
        line->setObjectName(QString::fromUtf8("line"));
        line->setFrameShape(QFrame::VLine);
        line->setFrameShadow(QFrame::Sunken);

        horizontalLayout_6->addWidget(line);

        Color_L_2 = new QVBoxLayout();
        Color_L_2->setSpacing(6);
        Color_L_2->setObjectName(QString::fromUtf8("Color_L_2"));
        label_22 = new QLabel(centralWidget);
        label_22->setObjectName(QString::fromUtf8("label_22"));

        Color_L_2->addWidget(label_22);

        horizontalLayout_8 = new QHBoxLayout();
        horizontalLayout_8->setSpacing(6);
        horizontalLayout_8->setObjectName(QString::fromUtf8("horizontalLayout_8"));
        label_23 = new QLabel(centralWidget);
        label_23->setObjectName(QString::fromUtf8("label_23"));
        label_23->setMinimumSize(QSize(10, 24));

        horizontalLayout_8->addWidget(label_23, 0, Qt::AlignRight);

        directional_r = new QDoubleSpinBox(centralWidget);
        directional_r->setObjectName(QString::fromUtf8("directional_r"));
        directional_r->setMinimum(-200000.000000000000000);
        directional_r->setMaximum(200000.000000000000000);

        horizontalLayout_8->addWidget(directional_r);

        label_24 = new QLabel(centralWidget);
        label_24->setObjectName(QString::fromUtf8("label_24"));
        label_24->setMinimumSize(QSize(10, 24));

        horizontalLayout_8->addWidget(label_24, 0, Qt::AlignRight);

        directional_g = new QDoubleSpinBox(centralWidget);
        directional_g->setObjectName(QString::fromUtf8("directional_g"));
        directional_g->setMinimum(-200000.000000000000000);
        directional_g->setMaximum(200000.000000000000000);

        horizontalLayout_8->addWidget(directional_g);

        label_25 = new QLabel(centralWidget);
        label_25->setObjectName(QString::fromUtf8("label_25"));
        label_25->setMinimumSize(QSize(10, 24));

        horizontalLayout_8->addWidget(label_25, 0, Qt::AlignRight);

        directional_b = new QDoubleSpinBox(centralWidget);
        directional_b->setObjectName(QString::fromUtf8("directional_b"));
        directional_b->setMinimum(-200000.000000000000000);
        directional_b->setMaximum(200000.000000000000000);

        horizontalLayout_8->addWidget(directional_b);


        Color_L_2->addLayout(horizontalLayout_8);


        horizontalLayout_6->addLayout(Color_L_2);


        verticalLayout_2->addLayout(horizontalLayout_6);

        DeleteDirectionalLight_Button = new QPushButton(centralWidget);
        DeleteDirectionalLight_Button->setObjectName(QString::fromUtf8("DeleteDirectionalLight_Button"));

        verticalLayout_2->addWidget(DeleteDirectionalLight_Button);

        CreateDirectionalLight_Button = new QPushButton(centralWidget);
        CreateDirectionalLight_Button->setObjectName(QString::fromUtf8("CreateDirectionalLight_Button"));

        verticalLayout_2->addWidget(CreateDirectionalLight_Button);


        verticalLayout_3->addLayout(verticalLayout_2);


        verticalLayout_4->addLayout(verticalLayout_3);

        PointLight = new QVBoxLayout();
        PointLight->setSpacing(6);
        PointLight->setObjectName(QString::fromUtf8("PointLight"));
        label = new QLabel(centralWidget);
        label->setObjectName(QString::fromUtf8("label"));
        label->setFont(font);
        label->setAlignment(Qt::AlignCenter);

        PointLight->addWidget(label);

        verticalLayout = new QVBoxLayout();
        verticalLayout->setSpacing(6);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setSpacing(6);
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        Ambient_L = new QVBoxLayout();
        Ambient_L->setSpacing(6);
        Ambient_L->setObjectName(QString::fromUtf8("Ambient_L"));
        label_2 = new QLabel(centralWidget);
        label_2->setObjectName(QString::fromUtf8("label_2"));

        Ambient_L->addWidget(label_2);

        point_ambient = new QDoubleSpinBox(centralWidget);
        point_ambient->setObjectName(QString::fromUtf8("point_ambient"));
        point_ambient->setMaximumSize(QSize(100, 20));
        point_ambient->setMinimum(-200000.000000000000000);
        point_ambient->setMaximum(200000.000000000000000);

        Ambient_L->addWidget(point_ambient);


        horizontalLayout_3->addLayout(Ambient_L);

        Intensity_L = new QVBoxLayout();
        Intensity_L->setSpacing(6);
        Intensity_L->setObjectName(QString::fromUtf8("Intensity_L"));
        label_3 = new QLabel(centralWidget);
        label_3->setObjectName(QString::fromUtf8("label_3"));

        Intensity_L->addWidget(label_3);

        point_intensity = new QDoubleSpinBox(centralWidget);
        point_intensity->setObjectName(QString::fromUtf8("point_intensity"));
        point_intensity->setMaximumSize(QSize(100, 20));
        point_intensity->setMinimum(-200000.000000000000000);
        point_intensity->setMaximum(200000.000000000000000);

        Intensity_L->addWidget(point_intensity);


        horizontalLayout_3->addLayout(Intensity_L);

        Specular_L = new QVBoxLayout();
        Specular_L->setSpacing(6);
        Specular_L->setObjectName(QString::fromUtf8("Specular_L"));
        label_4 = new QLabel(centralWidget);
        label_4->setObjectName(QString::fromUtf8("label_4"));

        Specular_L->addWidget(label_4);

        point_specular = new QDoubleSpinBox(centralWidget);
        point_specular->setObjectName(QString::fromUtf8("point_specular"));
        point_specular->setMaximumSize(QSize(100, 20));
        point_specular->setMinimum(-200000.000000000000000);
        point_specular->setMaximum(200000.000000000000000);

        Specular_L->addWidget(point_specular);


        horizontalLayout_3->addLayout(Specular_L);

        Range_L = new QVBoxLayout();
        Range_L->setSpacing(6);
        Range_L->setObjectName(QString::fromUtf8("Range_L"));
        label_5 = new QLabel(centralWidget);
        label_5->setObjectName(QString::fromUtf8("label_5"));

        Range_L->addWidget(label_5);

        point_range = new QDoubleSpinBox(centralWidget);
        point_range->setObjectName(QString::fromUtf8("point_range"));
        point_range->setMaximumSize(QSize(100, 20));
        point_range->setMinimum(-200000.000000000000000);
        point_range->setMaximum(200000.000000000000000);

        Range_L->addWidget(point_range);


        horizontalLayout_3->addLayout(Range_L);


        verticalLayout->addLayout(horizontalLayout_3);

        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setSpacing(6);
        horizontalLayout_4->setObjectName(QString::fromUtf8("horizontalLayout_4"));
        Position_L = new QVBoxLayout();
        Position_L->setSpacing(6);
        Position_L->setObjectName(QString::fromUtf8("Position_L"));
        label_6 = new QLabel(centralWidget);
        label_6->setObjectName(QString::fromUtf8("label_6"));

        Position_L->addWidget(label_6);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(6);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        label_7 = new QLabel(centralWidget);
        label_7->setObjectName(QString::fromUtf8("label_7"));
        label_7->setMinimumSize(QSize(10, 24));

        horizontalLayout->addWidget(label_7, 0, Qt::AlignRight);

        point_x = new QDoubleSpinBox(centralWidget);
        point_x->setObjectName(QString::fromUtf8("point_x"));
        point_x->setMinimum(-200000.000000000000000);
        point_x->setMaximum(200000.000000000000000);

        horizontalLayout->addWidget(point_x);

        label_10 = new QLabel(centralWidget);
        label_10->setObjectName(QString::fromUtf8("label_10"));
        label_10->setMinimumSize(QSize(10, 24));

        horizontalLayout->addWidget(label_10, 0, Qt::AlignRight);

        point_y = new QDoubleSpinBox(centralWidget);
        point_y->setObjectName(QString::fromUtf8("point_y"));
        point_y->setMinimum(-200000.000000000000000);
        point_y->setMaximum(200000.000000000000000);

        horizontalLayout->addWidget(point_y);

        label_11 = new QLabel(centralWidget);
        label_11->setObjectName(QString::fromUtf8("label_11"));
        label_11->setMinimumSize(QSize(10, 24));

        horizontalLayout->addWidget(label_11, 0, Qt::AlignRight);

        point_z = new QDoubleSpinBox(centralWidget);
        point_z->setObjectName(QString::fromUtf8("point_z"));
        point_z->setMinimum(-200000.000000000000000);
        point_z->setMaximum(200000.000000000000000);

        horizontalLayout->addWidget(point_z);


        Position_L->addLayout(horizontalLayout);


        horizontalLayout_4->addLayout(Position_L);

        line_2 = new QFrame(centralWidget);
        line_2->setObjectName(QString::fromUtf8("line_2"));
        line_2->setFrameShape(QFrame::VLine);
        line_2->setFrameShadow(QFrame::Sunken);

        horizontalLayout_4->addWidget(line_2);

        Color_L = new QVBoxLayout();
        Color_L->setSpacing(6);
        Color_L->setObjectName(QString::fromUtf8("Color_L"));
        label_8 = new QLabel(centralWidget);
        label_8->setObjectName(QString::fromUtf8("label_8"));

        Color_L->addWidget(label_8);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setSpacing(6);
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        label_9 = new QLabel(centralWidget);
        label_9->setObjectName(QString::fromUtf8("label_9"));
        label_9->setMinimumSize(QSize(10, 24));

        horizontalLayout_2->addWidget(label_9, 0, Qt::AlignRight);

        point_r = new QDoubleSpinBox(centralWidget);
        point_r->setObjectName(QString::fromUtf8("point_r"));
        point_r->setMinimum(-200000.000000000000000);
        point_r->setMaximum(200000.000000000000000);

        horizontalLayout_2->addWidget(point_r);

        label_12 = new QLabel(centralWidget);
        label_12->setObjectName(QString::fromUtf8("label_12"));
        label_12->setMinimumSize(QSize(10, 24));

        horizontalLayout_2->addWidget(label_12, 0, Qt::AlignRight);

        point_g = new QDoubleSpinBox(centralWidget);
        point_g->setObjectName(QString::fromUtf8("point_g"));
        point_g->setMinimum(-200000.000000000000000);
        point_g->setMaximum(200000.000000000000000);

        horizontalLayout_2->addWidget(point_g);

        label_13 = new QLabel(centralWidget);
        label_13->setObjectName(QString::fromUtf8("label_13"));
        label_13->setMinimumSize(QSize(10, 24));

        horizontalLayout_2->addWidget(label_13, 0, Qt::AlignRight);

        point_b = new QDoubleSpinBox(centralWidget);
        point_b->setObjectName(QString::fromUtf8("point_b"));
        point_b->setMinimum(-200000.000000000000000);
        point_b->setMaximum(200000.000000000000000);

        horizontalLayout_2->addWidget(point_b);


        Color_L->addLayout(horizontalLayout_2);


        horizontalLayout_4->addLayout(Color_L);


        verticalLayout->addLayout(horizontalLayout_4);


        PointLight->addLayout(verticalLayout);

        DeletePointLight_Button = new QPushButton(centralWidget);
        DeletePointLight_Button->setObjectName(QString::fromUtf8("DeletePointLight_Button"));

        PointLight->addWidget(DeletePointLight_Button);

        CreatePointLight_Button = new QPushButton(centralWidget);
        CreatePointLight_Button->setObjectName(QString::fromUtf8("CreatePointLight_Button"));

        PointLight->addWidget(CreatePointLight_Button);


        verticalLayout_4->addLayout(PointLight);

        Position_L_3 = new QVBoxLayout();
        Position_L_3->setSpacing(6);
        Position_L_3->setObjectName(QString::fromUtf8("Position_L_3"));
        Position_L_3->setSizeConstraint(QLayout::SetFixedSize);
        horizontalLayout_9 = new QHBoxLayout();
        horizontalLayout_9->setSpacing(6);
        horizontalLayout_9->setObjectName(QString::fromUtf8("horizontalLayout_9"));
        label_27 = new QLabel(centralWidget);
        label_27->setObjectName(QString::fromUtf8("label_27"));

        horizontalLayout_9->addWidget(label_27);

        label_28 = new QLabel(centralWidget);
        label_28->setObjectName(QString::fromUtf8("label_28"));
        label_28->setMinimumSize(QSize(10, 24));

        horizontalLayout_9->addWidget(label_28, 0, Qt::AlignRight);

        camera_x = new QLabel(centralWidget);
        camera_x->setObjectName(QString::fromUtf8("camera_x"));

        horizontalLayout_9->addWidget(camera_x);

        label_29 = new QLabel(centralWidget);
        label_29->setObjectName(QString::fromUtf8("label_29"));
        label_29->setMinimumSize(QSize(10, 24));

        horizontalLayout_9->addWidget(label_29, 0, Qt::AlignRight);

        camera_y = new QLabel(centralWidget);
        camera_y->setObjectName(QString::fromUtf8("camera_y"));

        horizontalLayout_9->addWidget(camera_y);

        label_30 = new QLabel(centralWidget);
        label_30->setObjectName(QString::fromUtf8("label_30"));
        label_30->setMinimumSize(QSize(10, 24));

        horizontalLayout_9->addWidget(label_30, 0, Qt::AlignRight);

        camera_z = new QLabel(centralWidget);
        camera_z->setObjectName(QString::fromUtf8("camera_z"));

        horizontalLayout_9->addWidget(camera_z);


        Position_L_3->addLayout(horizontalLayout_9);


        verticalLayout_4->addLayout(Position_L_3);

        horizontalLayout_10 = new QHBoxLayout();
        horizontalLayout_10->setSpacing(6);
        horizontalLayout_10->setObjectName(QString::fromUtf8("horizontalLayout_10"));
        verticalLayout_5 = new QVBoxLayout();
        verticalLayout_5->setSpacing(6);
        verticalLayout_5->setObjectName(QString::fromUtf8("verticalLayout_5"));
        LoadPath = new QLineEdit(centralWidget);
        LoadPath->setObjectName(QString::fromUtf8("LoadPath"));

        verticalLayout_5->addWidget(LoadPath);

        LoadButton = new QPushButton(centralWidget);
        LoadButton->setObjectName(QString::fromUtf8("LoadButton"));

        verticalLayout_5->addWidget(LoadButton);


        horizontalLayout_10->addLayout(verticalLayout_5);

        verticalLayout_9 = new QVBoxLayout();
        verticalLayout_9->setSpacing(6);
        verticalLayout_9->setObjectName(QString::fromUtf8("verticalLayout_9"));
        SavePath = new QLineEdit(centralWidget);
        SavePath->setObjectName(QString::fromUtf8("SavePath"));

        verticalLayout_9->addWidget(SavePath);

        SaveButton = new QPushButton(centralWidget);
        SaveButton->setObjectName(QString::fromUtf8("SaveButton"));

        verticalLayout_9->addWidget(SaveButton);


        horizontalLayout_10->addLayout(verticalLayout_9);

        verticalLayout_8 = new QVBoxLayout();
        verticalLayout_8->setSpacing(6);
        verticalLayout_8->setObjectName(QString::fromUtf8("verticalLayout_8"));

        horizontalLayout_10->addLayout(verticalLayout_8);


        verticalLayout_4->addLayout(horizontalLayout_10);

        ToolClass->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(ToolClass);
        menuBar->setObjectName(QString::fromUtf8("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 729, 26));
        ToolClass->setMenuBar(menuBar);
        mainToolBar = new QToolBar(ToolClass);
        mainToolBar->setObjectName(QString::fromUtf8("mainToolBar"));
        ToolClass->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(ToolClass);
        statusBar->setObjectName(QString::fromUtf8("statusBar"));
        ToolClass->setStatusBar(statusBar);

        retranslateUi(ToolClass);

        QMetaObject::connectSlotsByName(ToolClass);
    } // setupUi

    void retranslateUi(QMainWindow *ToolClass)
    {
        ToolClass->setWindowTitle(QApplication::translate("ToolClass", "Tool", nullptr));
        label_26->setText(QApplication::translate("ToolClass", "Directional Light", nullptr));
        label_14->setText(QApplication::translate("ToolClass", "Ambient", nullptr));
        label_15->setText(QApplication::translate("ToolClass", "Intensity", nullptr));
        label_16->setText(QApplication::translate("ToolClass", "Specular", nullptr));
        label_18->setText(QApplication::translate("ToolClass", "Rotation", nullptr));
        label_19->setText(QApplication::translate("ToolClass", "X", nullptr));
        label_20->setText(QApplication::translate("ToolClass", "Y", nullptr));
        label_21->setText(QApplication::translate("ToolClass", "Z", nullptr));
        label_22->setText(QApplication::translate("ToolClass", "Color", nullptr));
        label_23->setText(QApplication::translate("ToolClass", "R", nullptr));
        label_24->setText(QApplication::translate("ToolClass", "G", nullptr));
        label_25->setText(QApplication::translate("ToolClass", "B", nullptr));
        DeleteDirectionalLight_Button->setText(QApplication::translate("ToolClass", "Delete ALL", nullptr));
        CreateDirectionalLight_Button->setText(QApplication::translate("ToolClass", "Create", nullptr));
        label->setText(QApplication::translate("ToolClass", "Point Light", nullptr));
        label_2->setText(QApplication::translate("ToolClass", "Ambient", nullptr));
        label_3->setText(QApplication::translate("ToolClass", "Intensity", nullptr));
        label_4->setText(QApplication::translate("ToolClass", "Specular", nullptr));
        label_5->setText(QApplication::translate("ToolClass", "Range", nullptr));
        label_6->setText(QApplication::translate("ToolClass", "Position", nullptr));
        label_7->setText(QApplication::translate("ToolClass", "X", nullptr));
        label_10->setText(QApplication::translate("ToolClass", "Y", nullptr));
        label_11->setText(QApplication::translate("ToolClass", "Z", nullptr));
        label_8->setText(QApplication::translate("ToolClass", "Color", nullptr));
        label_9->setText(QApplication::translate("ToolClass", "R", nullptr));
        label_12->setText(QApplication::translate("ToolClass", "G", nullptr));
        label_13->setText(QApplication::translate("ToolClass", "B", nullptr));
        DeletePointLight_Button->setText(QApplication::translate("ToolClass", "Delete ALL", nullptr));
        CreatePointLight_Button->setText(QApplication::translate("ToolClass", "Create", nullptr));
        label_27->setText(QApplication::translate("ToolClass", "Position Camera", nullptr));
        label_28->setText(QApplication::translate("ToolClass", "X:", nullptr));
        camera_x->setText(QApplication::translate("ToolClass", "0", nullptr));
        label_29->setText(QApplication::translate("ToolClass", "Y:", nullptr));
        camera_y->setText(QApplication::translate("ToolClass", "0", nullptr));
        label_30->setText(QApplication::translate("ToolClass", "Z:", nullptr));
        camera_z->setText(QApplication::translate("ToolClass", "0", nullptr));
        LoadPath->setText(QApplication::translate("ToolClass", "Path Load XML", nullptr));
        LoadButton->setText(QApplication::translate("ToolClass", "Load XML", nullptr));
        SavePath->setText(QApplication::translate("ToolClass", "Path Save XML", nullptr));
        SaveButton->setText(QApplication::translate("ToolClass", "Save XML", nullptr));
    } // retranslateUi

};

namespace Ui {
    class ToolClass: public Ui_ToolClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_TOOL_H
