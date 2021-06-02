#include "NonLinearSystemSolver.h"
#include "LinearEquationSystemSolver.h"

NonLinearSystemSolver::NonLinearSystemSolver(vector<y_xn> funcSystem, vector<vector<y_xn>> jacobiMatrix)
        : funcSystem(funcSystem), jacobiMatrix(jacobiMatrix) {}


dvector NonLinearSystemSolver::Solve(db eps, dvector x0) {
    auto xSubs = dvector{};
    do {
        auto b = CalcSystem(funcSystem, x0) * -1;
        auto a = CalcFuncMatrix(jacobiMatrix, x0);
        LinearEquationSystemSolver le(a, b);
        xSubs = le.Solve();
        x0 = xSubs + x0;
    } while (MaxAbsElement(xSubs) > eps);
    return x0;
}

dvector NonLinearSystemSolver::CalcSystem(vector<y_xn> system, dvector xs) {
    auto res = dvector(xs.size());
    for (int i = 0; i < system.size(); ++i)
        res[i] = system[i](xs);
    return res;
}

dmatrix NonLinearSystemSolver::CalcFuncMatrix(vector<vector<y_xn>> matrix, dvector xs) {
    auto res = dmatrix(matrix.size());
    for (int i = 0; i < matrix.size(); i++)
        res[i] = CalcSystem(matrix[i], xs);
    return res;
}


