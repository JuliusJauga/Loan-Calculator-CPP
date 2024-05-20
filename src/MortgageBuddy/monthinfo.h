#ifndef MONTHINFO_H
#define MONTHINFO_H

/**
 * @file monthinfo.h
 * @class MonthInfo
 * @brief Represents information about a specific month in a loan calculation.
 * 
 * @author Julius Jauga
 */
class MonthInfo {
public:
    /**
     * @brief Constructs a MonthInfo object with the given parameters.
     * @param month The month number.
     * @param monthly_payment The monthly payment amount.
     * @param interest_payment The interest payment amount.
     * @param remaining_balance The remaining balance amount.
     */
    MonthInfo(int month, double monthly_payment, double interest_payment, double remaining_balance);

    /**
     * @brief Copy constructor.
     * @param other The MonthInfo object to be copied.
     */
    MonthInfo(const MonthInfo &other);

    /**
     * @brief Assignment operator.
     * @param other The MonthInfo object to be assigned.
     * @return A reference to the assigned MonthInfo object.
     */
    MonthInfo& operator=(const MonthInfo &other);

    /**
     * @brief Sets the month number.
     * @param month The month number.
     */
    void setMonth(int month);

    /**
     * @brief Sets the monthly payment amount.
     * @param monthly_payment The monthly payment amount.
     */
    void setMonthlyPayment(double monthly_payment);

    /**
     * @brief Sets the interest payment amount.
     * @param interest_payment The interest payment amount.
     */
    void setInterestPayment(double interest_payment);

    /**
     * @brief Sets the remaining balance amount.
     * @param remaining_balance The remaining balance amount.
     */
    void setRemainingBalance(double remaining_balance);

    /**
     * @brief Returns the month number.
     * @return The month number.
     */
    int getMonth() const;

    /**
     * @brief Returns the monthly payment amount.
     * @return The monthly payment amount.
     */
    double getMonthlyPayment() const;

    /**
     * @brief Returns the interest payment amount.
     * @return The interest payment amount.
     */
    double getInterestPayment() const;

    /**
     * @brief Returns the remaining balance amount.
     * @return The remaining balance amount.
     */
    double getRemainingBalance() const;

private:
    int month;                  ///< The month number.
    double monthly_payment;     ///< The monthly payment amount.
    double interest_payment;    ///< The interest payment amount.
    double remaining_balance;   ///< The remaining balance amount.
};

#endif
