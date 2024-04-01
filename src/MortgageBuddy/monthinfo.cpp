/**
 * @class MonthInfo
 * @brief Represents information about a specific month in a loan calculation.
 * 
 * The MonthInfo class stores information such as the month number, monthly payment,
 * interest payment, and remaining balance for a specific month in a loan calculation.
 * 
 * @author Julius Jauga
 */
#include "monthinfo.h"

MonthInfo::MonthInfo(int month = 0, double monthly_payment = 0, double interest_payment = 0, double remaining_balance = 0) {
    this->month = month;
    this->monthly_payment = monthly_payment;
    this->interest_payment = interest_payment;
    this->remaining_balance = remaining_balance;
};
MonthInfo::MonthInfo(const MonthInfo &other) {
    this->month = other.month;
    this->monthly_payment = other.monthly_payment;
    this->interest_payment = other.interest_payment;
    this->remaining_balance = other.remaining_balance;
}

MonthInfo& MonthInfo::operator=(const MonthInfo &other) {
    if (this != &other) {
        this->month = other.month;
        this->monthly_payment = other.monthly_payment;
        this->interest_payment = other.interest_payment;
        this->remaining_balance = other.remaining_balance;
    }
    return *this;
}
int MonthInfo::getMonth() const {
    return month;
}
void MonthInfo::setMonth(int newMonth) {
    month = newMonth;
}

double MonthInfo::getMonthlyPayment() const {
    return monthly_payment;
}

void MonthInfo::setMonthlyPayment(double newMonthlyPayment) {
    monthly_payment = newMonthlyPayment;
}

double MonthInfo::getInterestPayment() const {
    return interest_payment;
}

void MonthInfo::setInterestPayment(double newInterestPayment) {
    interest_payment = newInterestPayment;
}

double MonthInfo::getRemainingBalance() const {
    return remaining_balance;
}

void MonthInfo::setRemainingBalance(double newRemainingBalance) {
    remaining_balance = newRemainingBalance;
}
