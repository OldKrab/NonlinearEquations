#ifndef NONLINEAREQUATIONS_NONLINEARSOLVER_H
#define NONLINEAREQUATIONS_NONLINEARSOLVER_H

#include <functional>
#include "matrix.h"

typedef std::function<db(db)> y_x;


class NonLinearSolver {
public:
    NonLinearSolver(y_x f, y_x der_f, y_x der2_f);

    dvector FindRoots(db a, db b, db eps, int splitNumber);

    vector<int> GetIterCounts();
private:

    db FindRoot(db a, db fa, db b, db fb, db eps);

    db FindApproximation(db xn, db fxn, db xn_, db fxn_);

    db ChordMethod(db xn, db fxn, db xn_, db fxn_);

    db TangentMethod(db xn, db fxn);

    y_x f, der_f, der2_f;
    vector<int> iterCnts;
};


#endif //NONLINEAREQUATIONS_NONLINEARSOLVER_H
