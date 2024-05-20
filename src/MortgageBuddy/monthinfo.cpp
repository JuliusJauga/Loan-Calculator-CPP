/**
 * @file monthinfo.cpp
 * @class MonthInfo
 * @brief Represents information about a specific month in a loan calculation.
 * 
 * The MonthInfo class stores information such as the month number, monthly payment,
 * interest payment, and remaining balance for a specific month in a loan calculation.
 * 
 * @author Julius Jauga
 */
#include "monthinfo.h"
/**
 * @brief Constructs a MonthInfo object with default values.
 * 
 * @param month The month number.
 * @param monthly_payment The monthly payment amount.
 * @param interest_payment The interest payment amount.
 * @param remaining_balance The remaining balance amount.
 */
MonthInfo::MonthInfo(int month, double monthly_payment, double interest_payment, double remaining_balance) {
    this->month = month;
    this->monthly_payment = monthly_payment;
    this->interest_payment = interest_payment;
    this->remaining_balance = remaining_balance;
};

/**
 * @brief Constructs a MonthInfo object by copying another MonthInfo object.
 * 
 * @param other The MonthInfo object to be copied.
 */
MonthInfo::MonthInfo(const MonthInfo &other) {
    this->month = other.month;
    this->monthly_payment = other.monthly_payment;
    this->interest_payment = other.interest_payment;
    this->remaining_balance = other.remaining_balance;
}

/**
 * @brief Assigns the values of another MonthInfo object to this object.
 * 
 * @param other The MonthInfo object to be assigned.
 * @return A reference to this MonthInfo object.
 */
MonthInfo& MonthInfo::operator=(const MonthInfo &other) {
    if (this != &other) {
        this->month = other.month;
        this->monthly_payment = other.monthly_payment;
        this->interest_payment = other.interest_payment;
        this->remaining_balance = other.remaining_balance;
    }
    return *this;
}

/**
 * @brief Gets the month number.
 * 
 * @return The month number.
 */
int MonthInfo::getMonth() const {
    return month;
}

/**
 * @brief Sets the month number.
 * 
 * @param newMonth The new month number.
 */
void MonthInfo::setMonth(int newMonth) {
    month = newMonth;
}

/**
 * @brief Gets the monthly payment amount.
 * 
 * @return The monthly payment amount.
 */
double MonthInfo::getMonthlyPayment() const {
    return monthly_payment;
}

/**
 * @brief Sets the monthly payment amount.
 * 
 * @param newMonthlyPayment The new monthly payment amount.
 */
void MonthInfo::setMonthlyPayment(double newMonthlyPayment) {
    monthly_payment = newMonthlyPayment;
}

/**
 * @brief Gets the interest payment amount.
 * 
 * @return The interest payment amount.
 */
double MonthInfo::getInterestPayment() const {
    return interest_payment;
}

/**
 * @brief Sets the interest payment amount.
 * 
 * @param newInterestPayment The new interest payment amount.
 */
void MonthInfo::setInterestPayment(double newInterestPayment) {
    interest_payment = newInterestPayment;
}

/**
 * @brief Gets the remaining balance amount.
 * 
 * @return The remaining balance amount.
 */
double MonthInfo::getRemainingBalance() const {
    return remaining_balance;
}

/**
 * @brief Sets the remaining balance amount.
 * 
 * @param newRemainingBalance The new remaining balance amount.
 */
void MonthInfo::setRemainingBalance(double newRemainingBalance) {
    remaining_balance = newRemainingBalance;
}
