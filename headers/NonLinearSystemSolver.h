#ifndef NONLINEAREQUATIONS_NONLINEARSYSTEMSOLVER_H
#define NONLINEAREQUATIONS_NONLINEARSYSTEMSOLVER_H

#include <functional>
#include "matrix.h"

typedef function<db(dvector)> y_xn;

class NonLinearSystemSolver {
public:
    dvector Solve(db eps, dvector x0);
    NonLinearSystemSolver(vector<y_xn> funcSystem, vector<vector<y_xn>> jacobiMatrix);
private:
    dvector CalcSystem(vector<y_xn> system, dvector xs);
    dmatrix CalcFuncMatrix(vector<vector<y_xn>> matrix, dvector xs);

    vector<vector<y_xn>> jacobiMatrix;
    vector<y_xn> funcSystem;
};


#endif //NONLINEAREQUATIONS_NONLINEARSYSTEMSOLVER_H
