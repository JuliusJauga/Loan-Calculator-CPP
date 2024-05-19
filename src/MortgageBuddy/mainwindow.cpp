#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "customQTextEdit.h"
#include <QTreeWidget>
#include <QTreeWidgetItem>
// #include <QFileDialog>
#include <QPdfWriter>
#include <QPainter>
#include <QBrush>
#include <QFont>
#include <QColor>
#include "calculations.h"

QLineSeries *series;
QChart *chart;
QValueAxis *axisX;
QValueAxis *axisY;
QChartView *chartView;
bool clickedFlag = 0;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    //ui->endDateSlider->setVisible(false);
    is_linear = false;
    is_annuit = false;
    ui->setupUi(this);
    ui->month_list->setColumnCount(4);
    QStringList headers;
    headers << "Month" << "Monthly Payment" << "Interest Payment" << "Remaining Balance";
    ui->month_list->setHeaderLabels(headers);

    // Manually set the width for each column
    ui->month_list->setColumnWidth(0, 75); // Set width of column 0 to 100 pixels
    ui->month_list->setColumnWidth(1, 170); // Set width of column 1 to 200 pixels
    ui->month_list->setColumnWidth(2, 170); // Set width of column 2 to 200 pixels
    ui->month_list->setColumnWidth(3, 170); // Set width of column 3 to 200 pixels

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

    ui->month_list->header()->setDefaultAlignment(Qt::AlignCenter);

    createGraph();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_calculate_button_clicked()
{
    //clickedFlag = 1;
    if (!getData() || (is_annuit == false && is_linear == false)) {
        return;
    }
    Calculations newCalculations(loan_amount, annual_percent, years, months, delay_start, delay_end, is_annuit, is_linear);
    // getFilterData();
    fillView(newCalculations.getList());
    drawGraph(newCalculations.getList());
    //ui->endDateSlider->setVisible(true);
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

void MainWindow::on_exportToCSVButton_clicked()
{
    Calculations newCalculations(loan_amount, annual_percent, years, months, delay_start, delay_end, is_annuit, is_linear);
    exportToCSV(newCalculations.getList());
}

void MainWindow::on_importFromCSVButton_clicked()
{

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
    for (int i = 0; i <= (int)list.size() - 1; ++i) {
        if (i+1 < filter_start || i+1 > filter_end) continue;
        QStringList rowData;
        rowData << QString::number(list[i].getMonth());       // Month
        rowData << QString::number(list[i].getMonthlyPayment(), 'f', 2);  // Monthly Payment
        rowData << QString::number(list[i].getInterestPayment(), 'f', 2);   // Interest Payment
        rowData << QString::number(list[i].getRemainingBalance(), 'f', 2);  // Remaining Balance
        ui->month_list->addTopLevelItem(new QTreeWidgetItem(rowData));
    }

    for(int i = 0; i < ui->month_list->topLevelItemCount(); ++i) {
        QTreeWidgetItem *item = ui->month_list->topLevelItem(i);
        for(int j = 0; j < item->columnCount(); ++j) {
            item->setTextAlignment(j, Qt::AlignCenter);
        }
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
    series->setColor(QColor("#7b9d85"));
    QPen pen(QColor("#7b9d85"));
    pen.setWidth(3);
    series->setPen(pen);

    QColor chartBackgroundColor("#22232a");
    chart->setBackgroundBrush(QBrush(chartBackgroundColor));

    // Set the background color of the QChartView to be transparent
    chartView->setStyleSheet("background-color: transparent;");

    // Set the background color and border of the chartWidget
    ui->chartWidget->setStyleSheet("background-color: #22232a; border: 2px solid; border-color: #7b9d85; border-radius: 6px");

    QFont font;
    font.setBold(true);
    axisX->setTitleFont(font);
    axisX->setTitleBrush(QBrush(Qt::white));

    axisY->setTitleFont(font);
    axisY->setTitleBrush(QBrush(Qt::white));

    axisX->setTitleText("Month");           // X axis title
    axisY->setTitleText("Monthly Payment"); // Y axis title

    axisX->setLabelFormat("%.0f");          // Format month numeration
    axisY->setLabelFormat("%.2f");          // Format currency numeration

    // Set the color of the X axis labels to white
    axisX->setLabelsColor(Qt::white);

    // Set the color of the Y axis labels to white
    axisY->setLabelsColor(Qt::white);

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
    for (int i = 0; i < (int)list.size(); ++i) {
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

void MainWindow::exportToCSV(std::vector<MonthInfo> list) {
    QFile file("data.csv");
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        qDebug() << "Could not open file for writing:" << file.errorString();
        return;
    }

    QTextStream out(&file);

    // Write headers
    out << "Month,Monthly Payment,Interest Payment,Remaining Balance\n";

    // Write data
    for (const MonthInfo &info : list) {
        out << info.getMonth() << ","
            << info.getMonthlyPayment() << ","
            << info.getInterestPayment() << ","
            << info.getRemainingBalance() << "\n";
    }

    file.close();
}

