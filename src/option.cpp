#include "option.h"
#include <algorithm>

Option::Option(const std::string& underlying, double strike, std::time_t expiration, OptionType type)
    : underlying(underlying), strike(strike), expiration(expiration), type(type), price(0.0) {}

double Option::getIntrinsicValue(double underlyingPrice) const {
    if (type == Call) {
        return std::max(0.0, underlyingPrice - strike);
    } else {
        return std::max(0.0, strike - underlyingPrice);
    }
}

double Option::getTimeValue(double marketPrice) const {
    return marketPrice - getIntrinsicValue(marketPrice);
}

const std::string& Option::getUnderlying() const {
    return underlying;
}

double Option::getStrike() const {
    return strike;
}

std::time_t Option::getExpiration() const {
    return expiration;
}

Option::OptionType Option::getType() const {
    return type;
}

double Option::getPrice() const {
    return price;
}

void Option::setPrice(double price) {
    this->price = price;
}