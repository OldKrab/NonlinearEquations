#include <iostream>
#include <valarray>
#include "headers/NonLinearSystemSolver.h"


int main() {
    auto solver = NonLinearSystemSolver(
            {
                    [](dvector x) { return x[0] * x[0] + x[1] * x[1] / 3 - 3; },
                    [](dvector x) { return pow(x[0] - 3, 2) + x[1] * x[1] - 4; }
            },
            {
                    {[](dvector x) { return 2 * x[0]; },     [](dvector x) { return 2 * x[1] / 3; }},
                    {[](dvector x) { return 2 * x[0] - 6; }, [](dvector x) { return 2 * x[1]; }}
            });
    cout << solver.Solve(1e-3, {1, -1});
}
