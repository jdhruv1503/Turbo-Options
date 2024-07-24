#include <iostream>
#include "option.h"

void testIntrinsicValue() {
    Option callOption("AAPL", 150, 1672531199, Option::Call);
    double callIntrinsicValue1 = callOption.getIntrinsicValue(160);
    double callIntrinsicValue2 = callOption.getIntrinsicValue(140);

    Option putOption("AAPL", 150, 1672531199, Option::Put);
    double putIntrinsicValue1 = putOption.getIntrinsicValue(140);
    double putIntrinsicValue2 = putOption.getIntrinsicValue(160);

    std::cout << "Testing Intrinsic Value:" << std::endl;
    std::cout << "Call Option (160): Expected 10, Got " << callIntrinsicValue1 << std::endl;
    std::cout << "Call Option (140): Expected 0, Got " << callIntrinsicValue2 << std::endl;
    std::cout << "Put Option (140): Expected 10, Got " << putIntrinsicValue1 << std::endl;
    std::cout << "Put Option (160): Expected 0, Got " << putIntrinsicValue2 << std::endl;
}

void testTimeValue() {
    Option callOption("AAPL", 150, 1672531199, Option::Call);
    callOption.setPrice(20);
    double callTimeValue = callOption.getTimeValue(160);

    Option putOption("AAPL", 150, 1672531199, Option::Put);
    putOption.setPrice(20);
    double putTimeValue = putOption.getTimeValue(140);

    std::cout << "Testing Time Value:" << std::endl;
    std::cout << "Call Option: Expected 10, Got " << callTimeValue << std::endl;
    std::cout << "Put Option: Expected 10, Got " << putTimeValue << std::endl;
}

int main() {
    testIntrinsicValue();
    testTimeValue();
    return 0;
}