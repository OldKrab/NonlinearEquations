#include <iostream>
#include <fstream>
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
    cout << "Result: " << solver.Solve(1e-5, {1, -2});

    ofstream fout(R"(D:\GoogleDrive\sync\source\clion\NonlinearEquations\out.txt)");
    dvector iters{}, xs{}, ys{}, resx{}, resy{};

    for (db x = -1.3; x < 10; x += 1.1)
        for (db y = -21; y < 20; y += 1.01) {
            auto res = solver.Solve(1e-5, {x, y});
            resx.push_back(res[0]);
            resy.push_back(res[1]);
            xs.push_back(x);
            ys.push_back(y);
            iters.push_back(solver.GetIterCount());
        }
    fout << xs << endl << ys << endl << iters << endl << resx << endl << resy;
    fout.close();
    system(R"(python D:\GoogleDrive\sync\source\clion\NonlinearEquations\graph.py)");
}
