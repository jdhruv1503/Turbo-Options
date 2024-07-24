#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <ctime>
#include <sstream>
#include "option.h"
#include "pricing_model.h"
#include "market_data.h"

int main(int argc, char* argv[]) {
    if (argc != 2) {
        std::cerr << "Usage: " << argv[0] << " <options_file>" << std::endl;
        return 1;
    }

    std::ifstream optionsFile(argv[1]);
    if (!optionsFile) {
        std::cerr << "Error opening options file: " << argv[1] << std::endl;
        return 1;
    }

    MarketData marketData("data/market_data.txt");
    MonteCarloOption mcModel;
    FdmOption fdmModel;
    BlackScholesPDE bsPDE;

    std::string line;
    while (std::getline(optionsFile, line)) {
        std::istringstream iss(line);
        std::string underlying;
        double strike;
        std::time_t expiration;
        std::string typeStr;
        Option::OptionType type;

        if (!(iss >> underlying >> strike >> expiration >> typeStr)) {
            std::cerr << "Error reading option data from line: " << line << std::endl;
            continue;
        }

        if (typeStr == "call") {
            type = Option::Call;
        } else if (typeStr == "put") {
            type = Option::Put;
        } else {
            std::cerr << "Invalid option type: " << typeStr << std::endl;
            continue;
        }

        Option option(underlying, strike, expiration, type);
        double mcPrice = mcModel.price(option);
        double fdmPrice = fdmModel.price(option);
        double bsPrice = bsPDE.solve(option);

        std::cout << "Option: " << underlying << ", Strike=" << strike << ", Expiry=" << expiration << std::endl;
        std::cout << "Monte Carlo price: $" << mcPrice << std::endl;
        std::cout << "FDM price: $" << fdmPrice << std::endl;
        std::cout << "Black-Scholes PDE price: $" << bsPrice << std::endl;
    }

    return 0;
}