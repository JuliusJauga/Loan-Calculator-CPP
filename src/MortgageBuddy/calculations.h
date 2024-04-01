#ifndef CALCULATIONS_H
#define CALCULATIONS_H

#include "monthinfo.h"
#include <vector>
class Calculations
{
public:
    Calculations(double loan_amount, double annual_percentage, int years, int months, int start, int end, bool is_annuit, bool is_linear);
    void recalculate();
    void setLoanAmount(double amount);
    void setAnnualPercentage(double percentage);
    void setYears(int years);
    void setMonths(int months);
    void setIsAnnuit(bool isAnnuit);
    void setIsLinear(bool isLinear);
    double getLoanAmount() const;
    double getAnnualPercentage() const;
    int getYears() const;
    int getMonths() const;
    bool getIsAnnuit() const;
    bool getIsLinear() const;
    std::vector<MonthInfo> getList() const;
private:
    double loan_amount;
    double annual_percentage;
    int years;
    int months;
    bool is_annuit;
    bool is_linear;
    int delay_start;
    int delay_end;
    std::vector<MonthInfo> month_list;
    void createList();
    void createAnnuitList();
    void createLinearList();
};

#endif // CALCULATIONS_H
