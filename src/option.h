#pragma once

#include <string>
#include <ctime>

class Option {
public:
    enum OptionType { Call, Put };

    Option(const std::string& underlying, double strike, std::time_t expiration, OptionType type);

    double getIntrinsicValue(double underlyingPrice) const;
    double getTimeValue(double marketPrice) const;

    // Getters
    const std::string& getUnderlying() const;
    double getStrike() const;
    std::time_t getExpiration() const;
    OptionType getType() const;
    double getPrice() const;

    // Setters
    void setPrice(double price);

private:
    std::string underlying;
    double strike;
    std::time_t expiration;
    OptionType type;
    double price;
};