
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

/**
 * @brief The AnnuitListCreationStrategy class represents a strategy for creating a list of month information for an annuity-based loan.
 * 
 * @author Aurelijus Lukšas
 */
class AnnuitListCreationStrategy : public ListCreationStrategy {
    protected:
        Calculations* calculations;
    public:
        AnnuitListCreationStrategy(Calculations* calc) : calculations(calc) {}
        void createList() override;
};
/**
 * @brief The LinearListCreationStrategy class represents a strategy for creating a list of month information for a linear-based loan.
 * @author Aurelijus Lukšas
 */
class LinearListCreationStrategy : public ListCreationStrategy {
    protected:
        Calculations* calculations;
    public:
        LinearListCreationStrategy(Calculations* calc) : calculations(calc) {}
        void createList() override;
};


/**
 * @brief The Calculations class represents a loan calculator that performs various calculations related to a loan.
 */
class Calculations
{
public:
    /**
     * @brief Constructs a Calculations object with default values.
     */
    Calculations();

    /**
     * @brief Constructs a Calculations object with the specified parameters.
     * @param loan_amount The loan amount.
     * @param annual_percentage The annual interest rate percentage.
     * @param years The number of years for the loan.
     * @param months The number of months for the loan.
     * @param start The starting month for the loan calculations.
     * @param end The ending month for the loan calculations.
     * @param is_annuit A flag indicating whether the loan is annuity-based.
     * @param is_linear A flag indicating whether the loan is linear-based.
     */
    Calculations(double loan_amount, double annual_percentage, int years, int months, int start, int end, bool is_annuit, bool is_linear);

    /**
     * @brief Recalculates the loan based on the current parameters.
     */
    void recalculate();

    /**
     * @brief Sets the loan amount.
     * @param amount The loan amount.
     */
    void setLoanAmount(double amount);

    /**
     * @brief Sets the annual interest rate percentage.
     * @param percentage The annual interest rate percentage.
     */
    void setAnnualPercentage(double percentage);

    /**
     * @brief Sets the number of years for the loan.
     * @param years The number of years for the loan.
     */
    void setYears(int years);

    /**
     * @brief Sets the number of months for the loan.
     * @param months The number of months for the loan.
     */
    void setMonths(int months);

    /**
     * @brief Sets whether the loan is annuity-based.
     * @param isAnnuit A flag indicating whether the loan is annuity-based.
     */
    void setIsAnnuit(bool isAnnuit);

    /**
     * @brief Sets whether the loan is linear-based.
     * @param isLinear A flag indicating whether the loan is linear-based.
     */
    void setIsLinear(bool isLinear);

    /**
     * @brief Gets the loan amount.
     * @return The loan amount.
     */
    double getLoanAmount() const;

    /**
     * @brief Gets the annual interest rate percentage.
     * @return The annual interest rate percentage.
     */
    double getAnnualPercentage() const;

    /**
     * @brief Gets the number of years for the loan.
     * @return The number of years for the loan.
     */
    int getYears() const;

    /**
     * @brief Gets the number of months for the loan.
     * @return The number of months for the loan.
     */
    int getMonths() const;

    /**
     * @brief Gets whether the loan is annuity-based.
     * @return A flag indicating whether the loan is annuity-based.
     */
    bool getIsAnnuit() const;

    /**
     * @brief Gets whether the loan is linear-based.
     * @return A flag indicating whether the loan is linear-based.
     */
    bool getIsLinear() const;

    /**
     * @brief Gets the list of month information for the loan.
     * @return The list of month information.
     */
    std::vector<MonthInfo> getList() const;

    /**
     * @brief Creates the list of month information for the loan.
     */
    void createList();

    /**
     * @brief Creates the list of month information for the annuity-based loan.
     */
    void createAnnuitList();

    /**
     * @brief Creates the list of month information for the linear-based loan.
     */
    void createLinearList();

    /**
     * @brief Sets the strategy for creating the list of month information.
     * @param newStrategy The new strategy for creating the list.
     */
    void setStrategy(ListCreationStrategy* newStrategy);

private:
    ListCreationStrategy* strategy; /**< The strategy for creating the list of month information. */
    double loan_amount; /**< The loan amount. */
    double annual_percentage; /**< The annual interest rate percentage. */
    int years; /**< The number of years for the loan. */
    int months; /**< The number of months for the loan. */
    bool is_annuit; /**< A flag indicating whether the loan is annuity-based. */
    bool is_linear; /**< A flag indicating whether the loan is linear-based. */
    int delay_start; /**< The starting month for the loan calculations. */
    int delay_end; /**< The ending month for the loan calculations. */
    std::vector<MonthInfo> month_list; /**< The list of month information for the loan. */
};

#endif // CALCULATIONS_H
