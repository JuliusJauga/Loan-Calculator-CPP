/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.6.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QTreeWidget>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QLabel *label;
    QLabel *label_2;
    QLabel *label_3;
    QLabel *label_4;
    QPushButton *calculate_button;
    QCheckBox *annuit_box;
    QCheckBox *linear_box;
    QLabel *label_5;
    QLabel *label_6;
    QTreeWidget *month_list;
    QLabel *label_7;
    QLabel *label_8;
    QLabel *label_9;
    QLabel *label_10;
    QLabel *label_11;
    QLabel *label_12;
    QLabel *label_13;
    QTextEdit *loan_amount_line;
    QTextEdit *annual_percent_line;
    QTextEdit *year_line;
    QTextEdit *month_line;
    QTextEdit *start_year_line;
    QTextEdit *start_month_line;
    QTextEdit *end_year_line;
    QTextEdit *end_month_line;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName("MainWindow");
        MainWindow->resize(800, 600);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName("centralwidget");
        label = new QLabel(centralwidget);
        label->setObjectName("label");
        label->setGeometry(QRect(102, 130, 91, 20));
        label_2 = new QLabel(centralwidget);
        label_2->setObjectName("label_2");
        label_2->setGeometry(QRect(102, 170, 101, 20));
        label_3 = new QLabel(centralwidget);
        label_3->setObjectName("label_3");
        label_3->setGeometry(QRect(102, 210, 91, 20));
        label_4 = new QLabel(centralwidget);
        label_4->setObjectName("label_4");
        label_4->setGeometry(QRect(230, 210, 91, 20));
        calculate_button = new QPushButton(centralwidget);
        calculate_button->setObjectName("calculate_button");
        calculate_button->setGeometry(QRect(300, 310, 93, 29));
        annuit_box = new QCheckBox(centralwidget);
        annuit_box->setObjectName("annuit_box");
        annuit_box->setGeometry(QRect(380, 130, 91, 24));
        linear_box = new QCheckBox(centralwidget);
        linear_box->setObjectName("linear_box");
        linear_box->setGeometry(QRect(380, 160, 91, 24));
        label_5 = new QLabel(centralwidget);
        label_5->setObjectName("label_5");
        label_5->setGeometry(QRect(400, 90, 63, 20));
        label_6 = new QLabel(centralwidget);
        label_6->setObjectName("label_6");
        label_6->setGeometry(QRect(360, 210, 91, 20));
        month_list = new QTreeWidget(centralwidget);
        QTreeWidgetItem *__qtreewidgetitem = new QTreeWidgetItem();
        __qtreewidgetitem->setText(0, QString::fromUtf8("1"));
        month_list->setHeaderItem(__qtreewidgetitem);
        month_list->setObjectName("month_list");
        month_list->setGeometry(QRect(340, 350, 451, 192));
        label_7 = new QLabel(centralwidget);
        label_7->setObjectName("label_7");
        label_7->setGeometry(QRect(120, 420, 91, 20));
        label_8 = new QLabel(centralwidget);
        label_8->setObjectName("label_8");
        label_8->setGeometry(QRect(250, 420, 91, 20));
        label_9 = new QLabel(centralwidget);
        label_9->setObjectName("label_9");
        label_9->setGeometry(QRect(250, 480, 91, 20));
        label_10 = new QLabel(centralwidget);
        label_10->setObjectName("label_10");
        label_10->setGeometry(QRect(120, 480, 91, 20));
        label_11 = new QLabel(centralwidget);
        label_11->setObjectName("label_11");
        label_11->setGeometry(QRect(40, 450, 63, 20));
        label_12 = new QLabel(centralwidget);
        label_12->setObjectName("label_12");
        label_12->setGeometry(QRect(40, 510, 63, 20));
        label_13 = new QLabel(centralwidget);
        label_13->setObjectName("label_13");
        label_13->setGeometry(QRect(180, 380, 141, 20));
        loan_amount_line = new QTextEdit(centralwidget);
        loan_amount_line->setObjectName("loan_amount_line");
        loan_amount_line->setGeometry(QRect(220, 130, 104, 21));
        annual_percent_line = new QTextEdit(centralwidget);
        annual_percent_line->setObjectName("annual_percent_line");
        annual_percent_line->setGeometry(QRect(220, 170, 104, 21));
        year_line = new QTextEdit(centralwidget);
        year_line->setObjectName("year_line");
        year_line->setGeometry(QRect(200, 240, 104, 21));
        month_line = new QTextEdit(centralwidget);
        month_line->setObjectName("month_line");
        month_line->setGeometry(QRect(350, 240, 104, 21));
        start_year_line = new QTextEdit(centralwidget);
        start_year_line->setObjectName("start_year_line");
        start_year_line->setGeometry(QRect(90, 450, 104, 21));
        start_month_line = new QTextEdit(centralwidget);
        start_month_line->setObjectName("start_month_line");
        start_month_line->setGeometry(QRect(230, 450, 104, 21));
        end_year_line = new QTextEdit(centralwidget);
        end_year_line->setObjectName("end_year_line");
        end_year_line->setGeometry(QRect(90, 510, 104, 21));
        end_month_line = new QTextEdit(centralwidget);
        end_month_line->setObjectName("end_month_line");
        end_month_line->setGeometry(QRect(230, 510, 104, 21));
        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName("menubar");
        menubar->setGeometry(QRect(0, 0, 800, 26));
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName("statusbar");
        MainWindow->setStatusBar(statusbar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
        label->setText(QCoreApplication::translate("MainWindow", "Loan amount", nullptr));
        label_2->setText(QCoreApplication::translate("MainWindow", "Annual percent", nullptr));
        label_3->setText(QCoreApplication::translate("MainWindow", "Term", nullptr));
        label_4->setText(QCoreApplication::translate("MainWindow", "Years", nullptr));
        calculate_button->setText(QCoreApplication::translate("MainWindow", "Calculate", nullptr));
        annuit_box->setText(QCoreApplication::translate("MainWindow", "Annuit", nullptr));
        linear_box->setText(QCoreApplication::translate("MainWindow", "Linear", nullptr));
        label_5->setText(QCoreApplication::translate("MainWindow", "Schedule", nullptr));
        label_6->setText(QCoreApplication::translate("MainWindow", "Months", nullptr));
        label_7->setText(QCoreApplication::translate("MainWindow", "Years", nullptr));
        label_8->setText(QCoreApplication::translate("MainWindow", "Months", nullptr));
        label_9->setText(QCoreApplication::translate("MainWindow", "Months", nullptr));
        label_10->setText(QCoreApplication::translate("MainWindow", "Years", nullptr));
        label_11->setText(QCoreApplication::translate("MainWindow", "Start", nullptr));
        label_12->setText(QCoreApplication::translate("MainWindow", "End", nullptr));
        label_13->setText(QCoreApplication::translate("MainWindow", "Postponement", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
