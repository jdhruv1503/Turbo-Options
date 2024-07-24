#include "pricing_model.h"
#include <vector>
#include <cmath>
#include <algorithm>
#include <random>

double MonteCarloOption::price(const Option& option) const {
    const int num_sims = 100000; // Number of simulations
    const double S = 100.0; // Placeholder for underlying price
    const double K = option.getStrike();
    const double r = 0.05; // Placeholder for risk-free rate
    const double v = 0.2; // Placeholder for volatility
    const double T = 1.0; // Placeholder for time to expiration

    std::random_device rd;
    std::mt19937 gen(rd());
    std::normal_distribution<> d(0, 1);

    double payoff_sum = 0.0;

    for (int i = 0; i < num_sims; ++i) {
        double gauss_bm = d(gen);
        double S_cur = S * exp((r - 0.5 * v * v) * T + v * sqrt(T) * gauss_bm);
        if (option.getType() == Option::Call) {
            payoff_sum += std::max(S_cur - K, 0.0);
        } else {
            payoff_sum += std::max(K - S_cur, 0.0);
        }
    }

    return (payoff_sum / static_cast<double>(num_sims)) * exp(-r * T);
}

double FdmOption::price(const Option& option) const {
    const int M = 100; // Number of time steps
    const int N = 100; // Number of price steps
    const double S_max = 200.0; // Maximum price
    const double K = option.getStrike();
    const double r = 0.05; // Placeholder for risk-free rate
    const double v = 0.2; // Placeholder for volatility
    const double T = 1.0; // Placeholder for time to expiration

    double dt = T / M;
    double dS = S_max / N;

    std::vector<double> prices(N + 1);
    std::vector<double> values(N + 1);

    for (int i = 0; i <= N; ++i) {
        prices[i] = i * dS;
        if (option.getType() == Option::Call) {
            values[i] = std::max(0.0, prices[i] - K);
        } else {
            values[i] = std::max(0.0, K - prices[i]);
        }
    }

    for (int j = M - 1; j >= 0; --j) {
        for (int i = 1; i < N; ++i) {
            double delta = (values[i + 1] - values[i - 1]) / (2 * dS);
            double gamma = (values[i + 1] - 2 * values[i] + values[i - 1]) / (dS * dS);
            double theta = -0.5 * v * v * prices[i] * prices[i] * gamma - r * prices[i] * delta + r * values[i];
            values[i] += theta * dt;
        }
    }

    return values[N / 2]; // Return the option price at S = S_max / 2
}

double BlackScholesPDE::solve(const Option& option) const {
    const int M = 100; // Number of time steps
    const int N = 100; // Number of price steps
    const double S_max = 200.0; // Maximum price
    const double K = option.getStrike();
    const double r = 0.05; // Placeholder for risk-free rate
    const double v = 0.2; // Placeholder for volatility
    const double T = 1.0; // Placeholder for time to expiration

    double dt = T / M;
    double dS = S_max / N;

    std::vector<double> prices(N + 1);
    std::vector<double> values(N + 1);

    for (int i = 0; i <= N; ++i) {
        prices[i] = i * dS;
        if (option.getType() == Option::Call) {
            values[i] = std::max(0.0, prices[i] - K);
        } else {
            values[i] = std::max(0.0, K - prices[i]);
        }
    }

    for (int j = M - 1; j >= 0; --j) {
        for (int i = 1; i < N; ++i) {
            double delta = (values[i + 1] - values[i - 1]) / (2 * dS);
            double gamma = (values[i + 1] - 2 * values[i] + values[i - 1]) / (dS * dS);
            double theta = -0.5 * v * v * prices[i] * prices[i] * gamma - r * prices[i] * delta + r * values[i];
            values[i] += theta * dt;
        }
    }

    return values[N / 2]; // Return the option price at S = S_max / 2
}