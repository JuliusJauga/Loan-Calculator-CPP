#ifndef CALCULATIONS_H
#define CALCULATIONS_H

#include "monthinfo.h"
#include <vector>

class Calculations;

/**
 * @brief Classes used for calling Annuit and Linear calculations for monthly payments.
 * 
 * @author Aurelijus Lukšas
*/

class ListCreationStrategy {
    protected:
        Calculations* calculations;
    public:
        ListCreationStrategy() {};
        ListCreationStrategy(Calculations* calc) : calculations(calc) {}
        virtual void createList() = 0;
};

class AnnuitListCreationStrategy : public ListCreationStrategy {
    protected:
        Calculations* calculations;
    public:
        AnnuitListCreationStrategy(Calculations* calc) : calculations(calc) {}
        void createList() override;
};

class LinearListCreationStrategy : public ListCreationStrategy {
    protected:
        Calculations* calculations;
    public:
        LinearListCreationStrategy(Calculations* calc) : calculations(calc) {}
        void createList() override;
};


class Calculations
{
public:
    Calculations();
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
    void createList();
    void createAnnuitList();
    void createLinearList();
    void setStrategy(ListCreationStrategy* newStrategy);
private:
    ListCreationStrategy* strategy;
    double loan_amount;
    double annual_percentage;
    int years;
    int months;
    bool is_annuit;
    bool is_linear;
    int delay_start;
    int delay_end;
    std::vector<MonthInfo> month_list;
};

#endif // CALCULATIONS_H
