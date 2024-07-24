#pragma once

#include <string>
#include <unordered_map>

class MarketData {
public:
    MarketData(const std::string& dataFile);

    double getUnderlyingPrice(const std::string& underlying) const;
    double getInterestRate() const;
    double getDividendYield() const;
    double getImpliedVolatility(const std::string& underlying) const;

private:
    void loadData(const std::string& dataFile);

    std::unordered_map<std::string, double> underlyingPrices;
    double interestRate;
    double dividendYield;
    std::unordered_map<std::string, double> impliedVolatilities;
};