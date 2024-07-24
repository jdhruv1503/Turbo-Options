#include "market_data.h"
#include <fstream>
#include <sstream>
#include <stdexcept>

MarketData::MarketData(const std::string& dataFile) {
    loadData(dataFile);
}

void MarketData::loadData(const std::string& dataFile) {
    std::ifstream file(dataFile);
    std::string line;

    while (std::getline(file, line)) {
        std::istringstream iss(line);
        std::string key;
        double value;

        if (iss >> key >> value) {
            if (key == "interestRate") {
                interestRate = value;
            } else if (key == "dividendYield") {
                dividendYield = value;
            } else if (key.find("volatility_") == 0) {
                std::string underlying = key.substr(11); // Remove "volatility_" prefix
                impliedVolatilities[underlying] = value;
            } else {
                underlyingPrices[key] = value;
            }
        }
    }
}

double MarketData::getUnderlyingPrice(const std::string& underlying) const {
    auto it = underlyingPrices.find(underlying);
    if (it != underlyingPrices.end()) {
        return it->second;
    }
    throw std::runtime_error("Underlying price not found");
}

double MarketData::getInterestRate() const {
    return interestRate;
}

double MarketData::getDividendYield() const {
    return dividendYield;
}

double MarketData::getImpliedVolatility(const std::string& underlying) const {
    auto it = impliedVolatilities.find(underlying);
    if (it != impliedVolatilities.end()) {
        return it->second;
    }
    throw std::runtime_error("Implied volatility not found");
}