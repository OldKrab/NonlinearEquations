#ifndef NONLINEAREQUATIONS_NONLINEARSYSTEMSOLVER_H
#define NONLINEAREQUATIONS_NONLINEARSYSTEMSOLVER_H

#include <functional>
#include "matrix.h"

typedef function<db(dvector)> y_xn;

class NonLinearSystemSolver {
public:
    dvector Solve(db eps, dvector x0);
    int GetIterCount() const;
    NonLinearSystemSolver(vector<y_xn> funcSystem, vector<vector<y_xn>> jacobiMatrix);
    dvector CalcSystem(vector<y_xn> system, dvector xs);
private:
    dmatrix CalcFuncMatrix(vector<vector<y_xn>> matrix, dvector xs);

    vector<vector<y_xn>> jacobiMatrix;
    vector<y_xn> funcSystem;
    int iterCount = 0;
};


#endif //NONLINEAREQUATIONS_NONLINEARSYSTEMSOLVER_H
