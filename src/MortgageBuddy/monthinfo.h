#ifndef MONTHINFO_H
#define MONTHINFO_H

class MonthInfo
{
public:
    MonthInfo(int month, double monthly_payment, double interest_payment, double remaining_balance);
    MonthInfo(const MonthInfo &other);
    MonthInfo& operator=(const MonthInfo &other);
    void setMonth(int month);
    void setMonthlyPayment(double monthly_payment);
    void setInterestPayment(double interest_payment);
    void setRemainingBalance(double remaining_balance);

    int getMonth() const;
    double getMonthlyPayment() const;
    double getInterestPayment() const;
    double getRemainingBalance() const;

private:
    int month;
    double monthly_payment;
    double interest_payment;
    double remaining_balance;
};

#endif // MONTHINFO_H
