#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QTreeWidget>
#include <QTreeWidgetItem>
#include "calculations.h"

QLineSeries *series;
QChart *chart;
QValueAxis *axisX;
QValueAxis *axisY;
QChartView *chartView;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    is_linear = false;
    is_annuit = false;
    ui->setupUi(this);
    ui->month_list->setColumnCount(4);
    QStringList headers;
    headers << "Month" << "Monthly Payment" << "Interest Payment" << "Remaining Balance";
    ui->month_list->setHeaderLabels(headers);
    createGraph();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_calculate_button_clicked()
{
    if (!getData() || (is_annuit == false && is_linear == false)) {
        return;
    }
    Calculations newCalculations(loan_amount, annual_percent, years, months, delay_start, delay_end, is_annuit, is_linear);
    fillView(newCalculations.getList());
    drawGraph(newCalculations.getList());
}


void MainWindow::on_annuit_box_stateChanged()
{
    if(ui->annuit_box->isChecked()) {
        is_linear = false;
        is_annuit = true;
        ui->linear_box->setChecked(false);
    }
}


void MainWindow::on_linear_box_stateChanged()
{
    if(ui->linear_box->isChecked()) {
        is_linear = true;
        is_annuit = false;
        ui->annuit_box->setChecked(false);
    }
}

/**
 * @brief Retrieves data from the user interface and stores it in member variables.
 * 
 * @return true if the data retrieval is successful, false otherwise.
 * 
 * @author Julius Jauga
 */
int MainWindow::getData() {
    years = 0;
    months = 0;
    delay_start = 0;
    delay_end = 0;
    bool ok = 1;
    bool ok2 = 1;
    loan_amount = ui->loan_amount_line->toPlainText().toDouble(&ok);
    if (!ok) return ok;
    annual_percent = ui->annual_percent_line->toPlainText().toDouble(&ok);
    if (!ok) return ok;
    years = ui->year_line->toPlainText().toInt(&ok);
    months = ui->month_line->toPlainText().toInt(&ok2);
    if (!ok && !ok2) return ok;
    delay_start = ui->start_year_line->toPlainText().toInt() * 12 + ui->start_month_line->toPlainText().toInt();
    delay_end = ui->end_year_line->toPlainText().toInt() * 12 + ui->end_month_line->toPlainText().toInt();
    return true;
}
/**
 * @brief Fills the view with data from a vector of MonthInfo objects.
 * 
 * This method clears the month_list widget and populates it with data from the provided vector.
 * Each MonthInfo object in the vector represents a month's worth of information for a loan payment.
 * The data includes the month number, monthly payment, interest payment, and remaining balance.
 * 
 * @param list The vector of MonthInfo objects containing the loan payment information.
 *
 * @author Julius Jauga
 */
void MainWindow::fillView(std::vector<MonthInfo> list) {
    ui->month_list->clear();
    for (size_t i = 0; i <= list.size() - 1; ++i) {
        QStringList rowData;
        rowData << QString::number(list[i].getMonth());       // Month
        rowData << QString::number(list[i].getMonthlyPayment(), 'f', 2);  // Monthly Payment
        rowData << QString::number(list[i].getInterestPayment(), 'f', 2);   // Interest Payment
        rowData << QString::number(list[i].getRemainingBalance(), 'f', 2);  // Remaining Balance
        ui->month_list->addTopLevelItem(new QTreeWidgetItem(rowData));
    }
}
void MainWindow::createGraph() {
    series = new QLineSeries();
    chart = new QChart;
    axisX = new QValueAxis();
    axisY = new QValueAxis();
    chart->addSeries(series);
    chartView = new QChartView(chart);
     ui->verticalLayout->addWidget(chartView);
    chart->addAxis(axisX, Qt::AlignBottom);
    chart->addAxis(axisY, Qt::AlignLeft);

    // Attach the series to the axes
    series->attachAxis(axisX);
    series->attachAxis(axisY);

    axisX->setTitleText("Month");
    axisY->setTitleText("Monthly Payment");

    axisX->setLabelFormat("%.0f");
    axisY->setLabelFormat("%.2f");

    chart->legend()->hide();
    // chart->createDefaultAxes();
}
void MainWindow::drawGraph(std::vector<MonthInfo> list) {
    series->clear();

    double biggestPayment = 0;
    for (size_t i = 0; i < list.size(); ++i) {
        series->append(list[i].getMonth(), list[i].getMonthlyPayment());
        if (list[i].getMonthlyPayment() > biggestPayment) biggestPayment = list[i].getMonthlyPayment();
    }

    // Set range of X and Y axes
    axisX->setRange(0, list.size() + 1);
    axisY->setRange(0, biggestPayment + biggestPayment * 0.1);
}



