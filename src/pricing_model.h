#pragma once

#include "option.h"

class PricingModel {
public:
    virtual double price(const Option& option) const = 0;
};

class MonteCarloOption : public PricingModel {
public:
    double price(const Option& option) const override;
};

class FdmOption : public PricingModel {
public:
    double price(const Option& option) const override;
};

class BlackScholesPDE {
public:
    double solve(const Option& option) const;
};