/**
 * @file mainwindow.cpp
 * @brief Implementation of the MainWindow class.
 *
 * This file contains the implementation of the MainWindow class, which is the main window of the application.
 * The class is responsible for handling user input, displaying the loan payment information, and drawing the monthly payment line graph.
 * The class also provides functionality for exporting the loan payment information to a CSV file and importing it back from a CSV file.
 * The class is part of the Loan Calculator application.
 *
 * @version 1.0
 * @date 2021-05-23
 *
 * @see MainWindow
 * @see mainwindow.h
 * @see calculations.h
 * @see customQTextEdit.h
 * @see main.cpp
 * @see calculations.cpp
 * @see customQTextEdit.cpp
 * 
 * @authors Julius Jauga, Rokas Baliutavičius, Aurelijus Lukšas
 */
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "customQTextEdit.h"
#include <QTreeWidget>
#include <QTreeWidgetItem>
#include <QtWidgets>
#include <QtCharts>
// #include <QFileDialog>
#include <QPdfWriter>
#include <QPainter>
#include <QBrush>
#include <QFont>
#include <QColor>
#include <algorithm>
#include "calculations.h"

QLineSeries *series; ///< Line series for the graph
QChart *chart;     ///< Chart for the graph
QValueAxis *axisX; ///< X axis for the graph
QValueAxis *axisY; ///< Y axis for the graph
QChartView *chartView; ///< Chart view for the graph

bool clickedFlag = 0; ///< Flag to check if the calculate button was clicked

/**
 * @brief Constructor for the MainWindow class.
 * @param parent The parent widget of the MainWindow.
 * @authors Julius Jauga, Rokas Baliutavičius
*/
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    //ui->endDateSlider->setVisible(false);
    is_linear = false;
    is_annuit = false;
    ui->setupUi(this);
    ui->month_list->setColumnCount(4);
    ui->paid_month_list->setColumnCount(4);
    QStringList headers;
    headers << "Month" << "Monthly Payment" << "Interest Payment" << "Remaining Balance";
    ui->month_list->setHeaderLabels(headers);
    ui->startDateSlider->setMaximum(0);
    ui->endDateSlider->setMaximum(0);
    ui->paid_month_list->setHeaderLabels(headers);
    // Manually set the width for each column
    ui->month_list->setColumnWidth(0, 75); // Set width of column 0 to 100 pixels
    ui->month_list->setColumnWidth(1, 170); // Set width of column 1 to 200 pixels
    ui->month_list->setColumnWidth(2, 170); // Set width of column 2 to 200 pixels
    ui->month_list->setColumnWidth(3, 170); // Set width of column 3 to 200 pixels
    ui->paid_month_list->setColumnWidth(0, 75); // Set width of column 0 to 100 pixels
    ui->paid_month_list->setColumnWidth(1, 170); // Set width of column 1 to 200 pixels
    ui->paid_month_list->setColumnWidth(2, 170); // Set width of column 2 to 200 pixels
    ui->paid_month_list->setColumnWidth(3, 170); // Set width of column 3 to 200 pixels

    // Is always checking if startDateSlider is moved.
    connect(ui->startDateSlider, &QSlider::valueChanged, [this](int value) {
        ui->filterStartLabel->setText(QString::number(value));
        if (value > filter_end) ui->endDateSlider->setValue(value);
        filter_start = value;

        filterData();
    });


    // Is always checking if endDateSlider is moved. 
    connect(ui->endDateSlider, &QSlider::valueChanged, [this](int value) {
        ui->filterEndLabel->setText(QString::number(value));
        if (value < filter_start) ui->startDateSlider->setValue(value);
        filter_end = value;
        
        filterData();
    });

    ui->month_list->header()->setDefaultAlignment(Qt::AlignCenter);
    ui->paid_month_list->header()->setDefaultAlignment(Qt::AlignCenter);
    ui->tabWidget->setTabText(0, "Month list");
    ui->tabWidget->setTabText(1, "Paid month list");
    createGraph();
}

/**
 * @brief Destructor for the MainWindow class.
*/
MainWindow::~MainWindow()
{
    delete ui;
}
/**
 * @brief Clears the items in a QTreeWidget.
 *
 * This function removes all items from the specified QTreeWidget.
 *
 * @param treeWidget The QTreeWidget to be cleared.
 * 
 * @author Julius Jauga
 */
void clearTreeWidget(QTreeWidget* treeWidget) {
    while (treeWidget->topLevelItemCount() > 0) {
        delete treeWidget->takeTopLevelItem(0);
    }
}

/**
 * @brief Slot function called when the clear_button is clicked.
 * @author Julius Jauga
*/
void MainWindow::on_calculate_button_clicked()
{
    //clickedFlag = 1;
    clearTreeWidget(ui->paid_month_list);
    if (!getData() || (is_annuit == false && is_linear == false)) {
        return;
    }
    Calculations newCalculations(loan_amount, annual_percent, years, months, delay_start, delay_end, is_annuit, is_linear);

    setFilterLimits(years, months);
    fillView(newCalculations.getList());
    drawGraph(newCalculations.getList());
    
}

/**
 * @brief Slot function called when the annuit_box checkbox is checked or unchecked.
 * @author Julius Jauga
*/
void MainWindow::on_annuit_box_stateChanged()
{
    if(ui->annuit_box->isChecked()) {
        is_linear = false;
        is_annuit = true;

        ui->linear_box->setChecked(false);
    }
}



/**
 * @brief Slot function called when the linear_box checkbox is checked or unchecked.
 * @author Julius Jauga
*/
void MainWindow::on_linear_box_stateChanged()
{
    if(ui->linear_box->isChecked()) {
        is_linear = true;
        is_annuit = false;
        ui->annuit_box->setChecked(false);
    }
}

/**
 * @brief Slot function called when the saveChartPDF button is clicked.
 * @author Rokas Baliutavičius
*/
void MainWindow::on_saveChartPDF_clicked()
{
    printGraphAsPDF();
}

/**
 * @authors Rokas Baliutavičius, Aurelijus Lukšas
 * @brief Slot function called when the exportToCSVButton is clicked.
*/

void MainWindow::on_exportToCSVButton_clicked()
{
    if (!getData() || (is_annuit == false && is_linear == false)) {
        return;
    }

    QString filename = ui->fileNameInput->toPlainText();
    if (filename == "") {
        filename = "data.csv";
    }

    importFromCSV(filename);

    Calculations newCalculations(loan_amount, annual_percent, years, months, delay_start, delay_end, is_annuit, is_linear);
    exportToCSV(newCalculations.getList(), filename);
}


/**
 * @authors Rokas Baliutavičius, Aurelijus Lukšas
 * @brief Slot function called when the importFromCSVButton is clicked.
*/
void MainWindow::on_importFromCSVButton_clicked()
{

    QString filename = ui->fileNameInput->toPlainText();
    if (filename == "") {
        filename = "data.csv";
    }
    importFromCSV(filename);
}

/**
 * @author Aurelijus Lukšas
 * @brief Filters the data for use in graph and table.
*/

void MainWindow::filterData() {

    if (!getData() || (is_annuit == false && is_linear == false)) {
        return;
    }
    fillView(Calculations(loan_amount, annual_percent, years, months, delay_start, delay_end, is_annuit, is_linear).getList());
    drawGraph(Calculations(loan_amount, annual_percent, years, months, delay_start, delay_end, is_annuit, is_linear).getList());
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
    series->setMarkerSize(1);
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

/**
 * @author Aurelijus Lukšas
 * @brief Exports the mortgage data to a CSV file.
 * @param list The list of MonthInfo objects representing the mortgage data.
 * @param filename The name of the file to export data to.
*/

void MainWindow::exportToCSV(std::vector<MonthInfo> list, QString filename) {
    QFile file(filename);
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

    QFile file2(filename + "_info.csv");
    if (!file2.open(QIODevice::WriteOnly | QIODevice::Text)) {
        qDebug() << "Could not open file for writing:" << file.errorString();
        return;
    }

    QTextStream out2(&file2);

    out2 << "Loan amount,Interest rate,Years,Months,Is Annuit,Is Linear,Start Year, Start Month, End Year, End Month\n";

    out2 << loan_amount << ","
        << annual_percent << ","
        << years << ","
        << months << ","
        << is_annuit << ","
        << is_linear << ","
        << ui->start_year_line->toPlainText().toInt() << ","
        << ui->start_month_line->toPlainText().toInt() << ","
        << ui->end_year_line->toPlainText().toInt() << ","
        << ui->end_month_line->toPlainText().toInt() << "\n";

    file2.close();    

}

/**
 * @author Aurelijus Lukšas
 * @brief Imports mortgage data from a CSV file.
 * @param filename The name of the file to import data from.
*/

void MainWindow::importFromCSV(QString filename) {

    QFile file2(filename + "_info.csv");
    if (!file2.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qDebug() << "Could not open file for reading:" << file2.errorString();
        return;
    }

    QTextStream in2(&file2);
    in2.readLine();

    QString line2 = in2.readLine();
    QStringList fields2 = line2.split(",");
    if (fields2.size() != 10) {
        qDebug() << "Invalid line:" << line2;
        return;
    }

    ui->loan_amount_line->setText(fields2[0]);
    ui->annual_percent_line->setText(fields2[1]);
    ui->year_line->setText(fields2[2]);
    ui->month_line->setText(fields2[3]);
    if (fields2[4] == "1") {
        ui->annuit_box->setChecked(true);
    }
    else {
        ui->linear_box->setChecked(true);
    }
    if (fields2[6] != "0") {
        ui->start_year_line->setText(fields2[6]);
    }

    if (fields2[7] != "0") {
        ui->start_month_line->setText(fields2[7]);
    }

    if (fields2[8] != "0") {
        ui->end_year_line->setText(fields2[8]);
    }

    if (fields2[9] != "0") {
        ui->end_month_line->setText(fields2[9]);
    }




    QFile file(filename);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qDebug() << "Could not open file for reading:" << file.errorString();
        return;
    }

    QTextStream in(&file);
    std::vector<MonthInfo> importedList;
    // Skip headers
    in.readLine();

    // Read data
    while (!in.atEnd()) {
        QString line = in.readLine();
        QStringList fields = line.split(",");
        if (fields.size() != 4) {
            qDebug() << "Invalid line:" << line;
            continue;
        }

        int month = fields[0].toInt();
        double monthlyPayment = fields[1].toDouble();
        double interestPayment = fields[2].toDouble();
        double remainingBalance = fields[3].toDouble();
        importedList.push_back(MonthInfo(month, monthlyPayment, interestPayment, remainingBalance));
        
    }

    fillView(importedList);
    drawGraph(importedList);
    on_calculate_button_clicked();

    file.close();
}

/**
 * @brief Swaps the items at the specified indices in a QTreeWidget.
 * 
 * This function swaps the items at the given indices in the specified QTreeWidget.
 * If both indices are valid and the items exist, the function removes the items from their original positions
 * and inserts them at each other's positions.
 * 
 * @param treeWidget The QTreeWidget in which the items are to be swapped.
 * @param firstIndex The index of the first item to be swapped.
 * @param secondIndex The index of the second item to be swapped.
 * 
 * @author Julius Jauga
 */
void swapWidgetItems(QTreeWidget* treeWidget, int firstIndex, int secondIndex) {
    QTreeWidgetItem* firstItem = treeWidget->topLevelItem(firstIndex);
    QTreeWidgetItem* secondItem = treeWidget->topLevelItem(secondIndex);

    if (firstItem && secondItem) {
        treeWidget->takeTopLevelItem(firstIndex);
        treeWidget->takeTopLevelItem(secondIndex);

        treeWidget->insertTopLevelItem(secondIndex, firstItem);
        treeWidget->insertTopLevelItem(firstIndex, secondItem);
    }
}


/**
 * @brief Slot function triggered when an item in the month_list QTreeWidget is double-clicked.
 * 
 * This function handles the logic for adding the selected item to the paid_month_list QTreeWidget.
 * It checks if the item has already been added and if not, clones the item and adds it to the paid_month_list.
 * The addedMonths vector keeps track of the added items' indices for sorting purposes.
 * 
 * @param item The selected item in the month_list QTreeWidget.
 * @param column The column index of the selected item.
 * 
 * @author Julius Jauga
 */
void MainWindow::on_month_list_itemDoubleClicked(QTreeWidgetItem *item, int column)
{
    QTreeWidget *treeWidget = ui->month_list;

    int rowIndex = treeWidget->indexOfTopLevelItem(item);

    if (rowIndex != -1) {
        if (std::find(addedMonths.begin(), addedMonths.end(), rowIndex) != addedMonths.end()) {
            return;
        }
        QTreeWidgetItem *item = treeWidget->topLevelItem(rowIndex);
        if (item) {
            ui->paid_month_list->addTopLevelItem(item->clone());
            addedMonths.push_back(rowIndex);
            for(size_t i = addedMonths.size() - 1; i > 0; i--) {
                if (addedMonths[i] < addedMonths[i-1]) {
                    std::swap(addedMonths[i], addedMonths[i-1]);
                    swapWidgetItems(ui->paid_month_list, i, i-1);
                }
            }
        }
        else return;
    }
    else return;
}

