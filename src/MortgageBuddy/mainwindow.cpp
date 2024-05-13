#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QTreeWidget>
#include <QTreeWidgetItem>
// #include <QFileDialog>
#include <QPdfWriter>
#include <QPainter>
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

    connect(ui->startDateSlider, &QSlider::valueChanged, [this](int value) {
        ui->filterStartLabel->setText(QString::number(value));
        filter_start = value;
        fillView(Calculations(loan_amount, annual_percent, years, months, delay_start, delay_end, is_annuit, is_linear).getList());
        drawGraph(Calculations(loan_amount, annual_percent, years, months, delay_start, delay_end, is_annuit, is_linear).getList());
    });

    connect(ui->endDateSlider, &QSlider::valueChanged, [this](int value) {
        ui->filterEndLabel->setText(QString::number(value));
        filter_end = value;
        fillView(Calculations(loan_amount, annual_percent, years, months, delay_start, delay_end, is_annuit, is_linear).getList());
        drawGraph(Calculations(loan_amount, annual_percent, years, months, delay_start, delay_end, is_annuit, is_linear).getList());
    });


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
    // getFilterData();
    fillView(newCalculations.getList());
    drawGraph(newCalculations.getList());
}


void MainWindow::on_annuit_box_stateChanged()
{
    if(ui->annuit_box->isChecked()) {
        is_linear = false;
        is_annuit = true;
        // strategy = annuitStrategy;
        // Calculations.setStrategy(strategy);

        ui->linear_box->setChecked(false);
    }
}


void MainWindow::on_linear_box_stateChanged()
{
    if(ui->linear_box->isChecked()) {
        is_linear = true;
        is_annuit = false;
        // strategy = linearStrategy;
        // Calculations.setStrategy(strategy);
        ui->annuit_box->setChecked(false);
    }
}

void MainWindow::on_saveChartPDF_clicked()
{
    printGraphAsPDF();
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
    setFilterLimits(years, months);
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
    ui->month_list->isEnabled();
    ui->month_list->clear();
    for (size_t i = 0; i <= list.size() - 1; ++i) {
        if (i+1 < filter_start || i+1 > filter_end) continue;
        QStringList rowData;
        rowData << QString::number(list[i].getMonth());       // Month
        rowData << QString::number(list[i].getMonthlyPayment(), 'f', 2);  // Monthly Payment
        rowData << QString::number(list[i].getInterestPayment(), 'f', 2);   // Interest Payment
        rowData << QString::number(list[i].getRemainingBalance(), 'f', 2);  // Remaining Balance
        ui->month_list->addTopLevelItem(new QTreeWidgetItem(rowData));
    }
}



/**
 * @brief Sets the limits of the filter sliders.
 * 
 * @author Aurelijus Lukšas
*/

void MainWindow::setFilterLimits(int years, int months) {
    ui->startDateSlider->setMinimum(1);
    ui->startDateSlider->setMaximum(years * 12 + months);
    ui->startDateSlider->setValue(1);
    ui->endDateSlider->setMinimum(1);
    ui->endDateSlider->setMaximum(years * 12 + months);
    ui->endDateSlider->setValue(years * 12 + months);
}

/**
 * @brief Creates line graph for later use.
 *
 * This method initializes components needed for displaying the monthly payment line graph.
 * This includes adding X and Y axes to the graph, setting their titles and numeration format.
 *
 * @author Rokas Baliutavičius
 */

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

    axisX->setTitleText("Month");           // X axis title
    axisY->setTitleText("Monthly Payment"); // Y axis title

    axisX->setLabelFormat("%.0f");          // Format month numeration
    axisY->setLabelFormat("%.2f");          // Format currency numeration

    chart->legend()->hide();
}

/**
 * @brief Re-draws the line graph with calculated data.
 *
 * This method is used for re-drawing the monthly payment line graph upon pressing "Calculate" button.
 * The process includes adding new data to the series as well as adjusting the scale of the axes based on the new data.
 *
 * @param list The vector of MonthInfo objects containing the loan payment information.
 *
 * @author Rokas Baliutavičius
 */

void MainWindow::drawGraph(std::vector<MonthInfo> list) {
    series->clear();

    double biggestPayment = 0;
    for (size_t i = 0; i < list.size(); ++i) {
        if (i+1 < filter_start || i+1 > filter_end) continue;
        series->append(list[i].getMonth(), list[i].getMonthlyPayment());
        if (list[i].getMonthlyPayment() > biggestPayment) biggestPayment = list[i].getMonthlyPayment(); // Getting the biggest monthly payment for Y axis scale
    }

    // Set range of X and Y axes
    axisX->setRange(0, list.size() + 1);
    axisY->setRange(0, biggestPayment + biggestPayment * 0.1);
}

/**
 * @brief Saves the line graph to a PDF file
 *
 * @author Rokas Baliutavičius
 */

void MainWindow::printGraphAsPDF() {
    QPdfWriter writer("chart.pdf");

    // Replace with size in UI if changed
    int graphWidth = 651;
    int graphHeight = 381;

    QSizeF customPageSizeMM(graphWidth, graphHeight);
    qreal widthPoints = customPageSizeMM.width() * 72.0 / 25.4;
    qreal heightPoints = customPageSizeMM.height() * 72.0 / 25.4;
    QPageSize customPageSize(QSize(widthPoints, heightPoints), QPageSize::Point);
    writer.setPageSize(customPageSize);

    QPainter painter(&writer);

    QSizeF size = chartView->size();

    float widthScaleFactor = writer.width() / size.width();
    float heightScaleFactor = writer.height() / size.height();
    float scaleFactor = qMin(widthScaleFactor, heightScaleFactor);

    size *= scaleFactor;
    QPointF pos = chartView->pos() * scaleFactor;

    chartView->render(&painter, QRectF(pos, size), chartView->rect());

    painter.end();
}

