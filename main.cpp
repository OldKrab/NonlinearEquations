#include <iostream>
#include <valarray>
#include "headers/NonLinearSolver.h"

int fCallCnt = 0;

db f(db x) {
    fCallCnt++;
    return 4 * pow(x, 4) - 4 * pow(x, 3) - x - 1;
}

int derFCallCnt = 0;

db der_f(db x) {
    derFCallCnt++;
    return 16 * pow(x, 3) - 12* pow(x, 2) -  1;
}

int der2FCallCnt = 0;

db der2_f(db x) {
    der2FCallCnt++;
    return 48 * pow(x, 2) - 24* x;
}

int main() {
    auto solver = NonLinearSolver(f, der_f, der2_f);
    auto xs = solver.FindRoots(-1, 2, 1e-15, 5);
    auto residual = dvector(xs.size());

    cout << "Roots: " << xs << endl
         << "Number of function calls: f(x) - " << fCallCnt << ", f'(x) - " <<
         derFCallCnt << ", f''(x) - " << der2FCallCnt << endl;
    for (int i = 0; i < xs.size(); i++)
        residual[i] = f(xs[i]);
    cout << "Residual: " << residual << endl <<
         "Iterations: " << solver.GetIterCounts();
}
