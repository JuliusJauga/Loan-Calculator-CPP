/**
 * @file mainwindow.h
 * @brief This file contains the declaration of the MainWindow class.
 * 
 * @authors Julius Jauga, Rokas Baliutavičius, Aurelijus Lukšas
**/
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

/**
 * @brief The MainWindow class represents the main window of the Mortgage Buddy application.
 * 
 * This class inherits from QMainWindow and provides functionality for creating and managing the user interface,
 * as well as performing various calculations and operations related to mortgage calculations.
 */
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    /**
     * @brief Constructs a MainWindow object.
     * 
     * @param parent The parent widget.
     */
    MainWindow(QWidget *parent = nullptr);

    /**
     * @brief Destroys the MainWindow object.
     */
    ~MainWindow();

    /**
     * @brief Creates the graph view for displaying mortgage data.
     */
    void createGraph();

    /**
     * @brief Fills the graph view with data.
     * 
     * @param list The list of MonthInfo objects representing the mortgage data.
     */
    void fillView(std::vector<MonthInfo> list);

    /**
     * @brief Sets the filter limits for the mortgage data.
     * 
     * @param years The number of years to include in the filter.
     * @param months The number of months to include in the filter.
     */
    void setFilterLimits(int years, int months);

    /**
     * @brief Draws the graph based on the mortgage data.
     * 
     * @param list The list of MonthInfo objects representing the mortgage data.
     */
    void drawGraph(std::vector<MonthInfo> list);

    /**
     * @brief Prints the graph as a PDF file.
     */
    void printGraphAsPDF();

    /**
     * @brief Exports the mortgage data to a CSV file.
     * 
     * @param list The list of MonthInfo objects representing the mortgage data.
     */
    void exportToCSV(std::vector<MonthInfo> list);

    /**
     * @brief Filters the mortgage data based on the set filter limits.
     */
    void filterData();

    /**
     * @brief Imports mortgage data from a CSV file.
     */
    void importFromCSV();

private slots:
    /**
     * @brief Slot function called when the calculate button is clicked.
     */
    void on_calculate_button_clicked();

    /**
     * @brief Slot function called when the annuit box state is changed.
     */
    void on_annuit_box_stateChanged();

    /**
     * @brief Slot function called when the linear box state is changed.
     */
    void on_linear_box_stateChanged();

    /**
     * @brief Slot function called when the saveChartPDF button is clicked.
     */
    void on_saveChartPDF_clicked();

    /**
     * @brief Slot function called when the exportToCSVButton is clicked.
     */
    void on_exportToCSVButton_clicked();

    /**
     * @brief Slot function called when the importFromCSVButton is clicked.
     */
    void on_importFromCSVButton_clicked();

    /**
     * @brief Slot function called when an item in the month_list is double-clicked.
     * 
     * @param item The double-clicked item.
     * @param column The column index of the double-clicked item.
     */
    void on_month_list_itemDoubleClicked(QTreeWidgetItem *item, int column);

private:
    ListCreationStrategy* strategy; ///< The strategy for creating the mortgage data list.
    AnnuitListCreationStrategy* annuitStrategy; ///< The strategy for creating the mortgage data list using annuity payments.
    LinearListCreationStrategy* linearStrategy; ///< The strategy for creating the mortgage data list using linear payments.
    Ui::MainWindow *ui; ///< The user interface object.
    std::vector<int> addedMonths; ///< The list of paid months.
    double loan_amount; ///< The loan amount.
    double annual_percent; ///< The annual interest rate.
    int years; ///< The number of years for which the mortgage data is calculated.
    int months; ///< The number of months for which the mortgage data is calculated.
    int delay_start; ///< The start month for the delay period.
    int delay_end; ///< The end month for the delay period.
    int filter_start; ///< The start month for the filter period.
    int filter_end; ///< The end month for the filter period.
    bool is_annuit; ///< A flag indicating whether annuity payments are used.
    bool is_linear; ///< A flag indicating whether linear payments are used.

    /**
     * @brief Gets the mortgage data from the user input fields.
     * 
     * @return The number of months for which the mortgage data is calculated.
     */
    int getData();
};

#endif // MAINWINDOW_H
