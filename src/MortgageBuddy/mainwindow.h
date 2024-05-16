#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTCharts>
#include <QChartView>
#include <QLineSeries>
#include "monthinfo.h"
#include "calculations.h"
#include <vector>
QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void createGraph();
    void fillView(std::vector<MonthInfo> list);
    void setFilterLimits(int years, int months);
    void drawGraph(std::vector<MonthInfo> list);
    void printGraphAsPDF();
    void exportToCSV(std::vector<MonthInfo> list);

private slots:
    void on_calculate_button_clicked();

    void on_annuit_box_stateChanged();

    void on_linear_box_stateChanged();

    void on_saveChartPDF_clicked();

    void on_exportToCSVButton_clicked();

    void on_importFromCSVButton_clicked();

private:
    ListCreationStrategy* strategy; 
    AnnuitListCreationStrategy* annuitStrategy;
    LinearListCreationStrategy* linearStrategy;
    Ui::MainWindow *ui;
    double loan_amount;
    double annual_percent;
    int years;
    int months;
    int delay_start;
    int delay_end;
    int filter_start;
    int filter_end;
    bool is_annuit;
    bool is_linear;
    int getData();
};
#endif // MAINWINDOW_H
