/**
 * @class Calculations
 * @brief Implementation file for the Calculations class.
 * 
 * This file contains the implementation of the Calculations class, which is responsible for performing loan calculations.
 * The class provides methods to set and get loan parameters, recalculate the loan, and create a list of monthly payment information.
 * The calculations can be done using either annuity or linear repayment methods. Also able to set the strategy of calculations.
 * 
 * @authors Julius Jauga, Aurelijus Lukšas
 */
#include "calculations.h"
#include <vector>
#include <cmath>

/**
 * @brief Constructs a Calculations object with the specified parameters.
 * 
 * @param loan_amount The loan amount.
 * @param annual_percentage The annual interest rate as a percentage.
 * @param years The number of years for the loan.
 * @param months The number of months for the loan.
 * @param start The start delay in months.
 * @param end The end delay in months.
 * @param is_annuit A boolean indicating whether the loan is annuity-based.
 * @param is_linear A boolean indicating whether the loan is linear-based.
 * 
 * @author Julius Jauga
 */
Calculations::Calculations(double loan_amount, double annual_percentage, int years, int months, int start, int end, bool is_annuit, bool is_linear) {
    this->loan_amount = loan_amount;
    this->annual_percentage = annual_percentage;
    this->years = years;
    this->months = months;
    this->is_annuit = is_annuit;
    this->is_linear = is_linear;
    this->strategy = strategy;
    delay_start = start;
    delay_end = end;

    createList();
}

/**
 * @brief Sets the strategy for creating the list of monthly payment information.
 * 
 * @param newStrategy The new strategy to be used.
 * 
 * @author Julius Jauga
 */
void Calculations::setStrategy(ListCreationStrategy* newStrategy) {
    strategy = newStrategy;
}

/**
 * @brief Sets the loan amount.
 * 
 * @param loan_amount The new loan amount.
 * 
 * @author Julius Jauga
 */
void Calculations::setLoanAmount(double loan_amount) {
    this->loan_amount = loan_amount;
}

/**
 * @brief Sets the annual interest rate as a percentage.
 * 
 * @param annual_percentage The new annual interest rate.
 * 
 * @author Julius Jauga
 */
void Calculations::setAnnualPercentage(double annual_percentage) {
    this->annual_percentage = annual_percentage;
}
/**
 * @brief Sets the number of years for the loan.
 * 
 * @param years The new number of years.
 * 
 * @author Julius Jauga
 */
void Calculations::setYears(int years) {
    this->years = years;
}
/**
 * @brief Sets the number of months for the loan.
 * 
 * @param months The new number of months.
 * 
 * @author Julius Jauga
 */
void Calculations::setMonths(int months) {
    this->months = months;
}
/**
 * @brief Sets whether the loan is annuity-based.
 * 
 * @param is_annuit A boolean indicating whether the loan is annuity-based.
 * 
 * @author Julius Jauga
 */
void Calculations::setIsAnnuit(bool is_annuit) {
    this->is_annuit = is_annuit;
}
/**
 * @brief Sets whether the loan is linear-based.
 * 
 * @param is_linear A boolean indicating whether the loan is linear-based.
 * 
 * @author Julius Jauga
 */
void Calculations::setIsLinear(bool is_linear) {
    this->is_linear = is_linear;
}
/**
 * @brief Gets the loan amount.
 * 
 * @return The loan amount.
 * 
 * @author Julius Jauga
 */
double Calculations::getLoanAmount() const {
    return loan_amount;
}
/**
 * @brief Gets the annual interest rate as a percentage.
 * 
 * @return The annual interest rate.
 * 
 * @author Julius Jauga
 */
double Calculations::getAnnualPercentage() const {
    return annual_percentage;
}
/**
 * @brief Gets the number of years for the loan.
 * 
 * @return The number of years.
 * 
 * @author Julius Jauga
 */
int Calculations::getYears() const {
    return years;
}
/**
 * @brief Gets the number of months for the loan.
 * 
 * @return The number of months.
 * 
 * @author Julius Jauga
 */
int Calculations::getMonths() const {
    return months;
}
/**
 * @brief Gets whether the loan is annuity-based.
 * 
 * @return A boolean indicating whether the loan is annuity-based.
 * 
 * @author Julius Jauga
 */
bool Calculations::getIsAnnuit() const {
    return is_annuit;
}
/**
 * @brief Gets whether the loan is linear-based.
 * 
 * @return A boolean indicating whether the loan is linear-based.
 * 
 * @author Julius Jauga
 */
bool Calculations::getIsLinear() const {
    return is_linear;
}
/**
 * @brief Gets the list of monthly payment information.
 * 
 * @return The list of monthly payment information.
 * 
 * @author Julius Jauga
 */
std::vector<MonthInfo> Calculations::getList() const {
    return month_list;
}
/**
 * @brief Recalculates the list of monthly payment information.
 * 
 * @author Julius Jauga
 */
void Calculations::recalculate() {
    strategy->createList();
}
/**
 * @brief This method selects strategy and calls method the creates a list of monthly payment information using the annuity or linear repayment method.
 * 
 * @authors Julius Jauga, Aurelijus Lukšas
*/
void Calculations::createList() {
    if (is_annuit) {
        strategy = new AnnuitListCreationStrategy(this);
    }
    else if (is_linear) {
        strategy = new LinearListCreationStrategy(this);
    }
    strategy->createList();
}
// This method creates a list of monthly payment information using the annuity repayment method. Probably needs testing and debugging.
// 1. Crashes when total_months == 0;

/**
 * @brief This method creates a list of monthly payment information using the annuity repayment method.
 * 
 * @authors Julius Jauga
 */
void Calculations::createAnnuitList() {
    month_list.clear();
    double monthly_interest_rate = annual_percentage / 12 / 100;
    int total_months = years * 12 + months;
    double monthly_payment;
    if ((1 - std::pow((1+monthly_interest_rate), -total_months)) == 0) {
        monthly_payment = loan_amount / total_months;
    }
    else monthly_payment = loan_amount * monthly_interest_rate / (1 - std::pow(1 + monthly_interest_rate, -total_months));
    int counter = 1;
    double remainingBalance = monthly_payment * total_months;
    double principal = loan_amount;
    double percent;
    for (int month = 1; month <= total_months; month++) {
        remainingBalance -= monthly_payment;
        if (month >= delay_start && month < delay_end && delay_end < total_months) {
            monthly_payment = 0;
            counter++;
        }
        if (delay_end == month && month > 1 && delay_end < total_months) {
            remainingBalance += remainingBalance * counter * monthly_interest_rate;
            monthly_payment = remainingBalance / (total_months - month);
            principal += principal * monthly_interest_rate;
        }
        if (principal <= 0) principal = 0;
        percent = principal * monthly_interest_rate;
        principal -= percent;
        month_list.push_back(MonthInfo(month, monthly_payment, percent, std::abs(remainingBalance)));
    }
}
// This method creates a list of monthly payment information using the linear repayment method. Probably needs testing and debugging.
// 1. Crashes when total_months == 0;


/**
 * @brief This method creates a list of monthly payment information using the linear repayment method.
 * 
 * @authors Julius Jauga
 */
void Calculations::createLinearList() {
    int totalMonths = years * 12 + months;
    int counter = 1;
    double remaining_mortgage = loan_amount;
    double monthly_reduction = loan_amount / totalMonths;
    double monthly_interest_rate = annual_percentage / 12 / 100;
    double monthly_payment;
    double total_to_pay = 0;
    month_list.clear();
    for (int month = 1; month <= totalMonths; month++) {
        monthly_payment = monthly_reduction + monthly_interest_rate * remaining_mortgage;
        if (month >= delay_start && month < delay_end && delay_end < totalMonths) {
            monthly_payment = 0;
            counter++;
        }
        else if (delay_end == month && month > 1 && delay_end < totalMonths) {
            remaining_mortgage += remaining_mortgage * counter * monthly_interest_rate;
            monthly_reduction = remaining_mortgage / (totalMonths - months);
            monthly_payment = monthly_reduction + remaining_mortgage * monthly_interest_rate;
        }
        else {
            remaining_mortgage -= monthly_reduction;
        }
        if (remaining_mortgage < 0) remaining_mortgage = 0;
        total_to_pay += monthly_payment;
    }
    monthly_reduction = loan_amount / totalMonths;
    remaining_mortgage = loan_amount;
    counter = 1;
    double percent;
    for (int month = 1; month <= totalMonths; month++) {
        monthly_payment = monthly_reduction + monthly_interest_rate * remaining_mortgage;
        if (month >= delay_start && month < delay_end && delay_end < totalMonths) {
            monthly_payment = 0;
            counter++;
            percent = remaining_mortgage * monthly_interest_rate;
        }
        else if (delay_end == month && month > 1 && delay_end < totalMonths) {
            remaining_mortgage += remaining_mortgage * counter * monthly_interest_rate;
            monthly_reduction = remaining_mortgage / (totalMonths - months);
            monthly_payment = monthly_reduction + remaining_mortgage * monthly_interest_rate;
            percent = remaining_mortgage * monthly_interest_rate;
        }
        else {
            percent = remaining_mortgage * monthly_interest_rate;
            remaining_mortgage -= monthly_reduction;
        }
        if (remaining_mortgage < 0) remaining_mortgage = 0;
        total_to_pay -= monthly_payment;
        month_list.push_back(MonthInfo(month, monthly_payment, percent, std::abs(total_to_pay)));
    }
}

/**
 * @brief This method creates a list of monthly payment information using the linear repayment method.
 * 
 * @author Aurelijus Lukšas
 */
void AnnuitListCreationStrategy::createList() {
    calculations->createAnnuitList();
}

/**
 * @brief This method creates a list of monthly payment information using the linear repayment method.
 * 
 * @author Aurelijus Lukšas
 */
void LinearListCreationStrategy::createList() {
    calculations->createLinearList();
}



