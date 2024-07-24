## Project Structure

The project is structured into the following files and folders:

- `src/`: Contains the C++ source code files 
  - `main.cpp`: Main entry point, handles input and runs the pricing engine
  - `option.h` and `option.cpp`: Define the `Option` class representing an option contract
  - `pricing_model.h` and `pricing_model.cpp`: Implement the pricing models (Monte Carlo, finite difference)
  - `market_data.h` and `market_data.cpp`: Handle fetching and updating market data 
  - `math_utils.h` and `math_utils.cpp`: Math utility functions
- `include/`: External library headers (Eigen, Boost)
- `data/`: Market and options data files
- `tests/`: Unit tests
- `Makefile`: Makefile to build the project

## Option Class

The `Option` class (`option.h`) represents an options contract with the following key properties:

- Underlying asset
- Strike price  
- Expiration date
- Option type (call/put)
- Price (calculated by the pricing engine)

It also contains methods to calculate the option's intrinsic value and time value.

## Pricing Models

The pricing engine (`pricing_model.h/cpp`) implements two models:

1. Monte Carlo simulation
   - Simulates many random paths for the underlying asset price
   - Calculates the option payoff for each path and takes the average
   - Discounts the average payoff to the present value

2. Finite difference methods (FDM)  
   - Converts the Black-Scholes PDE to a set of finite difference equations
   - Solves the equations numerically to get the option price at each point in a grid
   - Interpolates to get the price for the desired strike and expiration

Both models use the Eigen library for efficient matrix math and Boost.Math for statistical distributions. Key functions:

- `MonteCarloOption::price()`: Runs the Monte Carlo simulation to price the option
- `FdmOption::price()`: Runs the finite difference method to price the option
- `BlackScholesPDE::solve()`: Solves the Black-Scholes PDE using FDM

## Parallel Processing

To accelerate the calculations, the pricing engine uses:

- OpenMP to run the Monte Carlo simulations in parallel across multiple CPU cores
- CUDA to run the finite difference calculations on a GPU

The Monte Carlo simulation is _embarrassingly_ parallel, so splitting the paths across threads provides a big speedup. Using a GPU for the finite difference grid calculations is also much faster than a CPU.

## Market Data

The `MarketData` class (`market_data.h/cpp`) is responsible for fetching, storing and updating the market data needed for pricing, including:

- Current underlying price 
- Interest rates
- Dividend yield
- Implied volatility surface

It reads data from files in the `data` directory and provides methods to access it.

## Building and Running        

To build the project, simply run `make` in the project directory. This will compile the source code, link against the Eigen and Boost libraries, and produce an executable called `pricer`.

To run the pricer, pass it a file containing the options to be priced (one per line):

```shell
./pricer options.txt
```

This will price each option using both Monte Carlo and finite difference, and output the results.

## Example

Here's an example of pricing a European call option on a stock:

- Underlying price: $100
- Strike price: $105
- Time to expiration: 30 days  
- Risk-free rate: 2%
- Dividend yield: 0%
- Implied volatility: 30%

Running the pricer on this option might produce the following output:

```
Option: European call on XYZ, Strike=105, Expiry=2024-08-22
Monte Carlo price: $4.12
FDM price: $4.09 
```

This indicates both models agree the fair price for this option is around $4.10.