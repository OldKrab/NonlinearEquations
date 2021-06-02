#ifndef NONLINEAREQUATIONS_LINEAREQUATIONSYSTEMSOLVER_H
#define NONLINEAREQUATIONS_LINEAREQUATIONSYSTEMSOLVER_H

#include <algorithm>
#include <cassert>
#include "matrix.h"

class LinearEquationSystemSolver {
public:
    dvector Solve();

    LinearEquationSystemSolver(dmatrix a, dvector b);

private:
    dvector SolveByTriangular(const dmatrix &a, const dvector &b) const;

    dvector ConvertB(const dvector &b);

    void ConvertToTriangular();

    void HandleMainElem(int k);

    int SelectMaxElem(int k);

    dmatrix _a;
    dvector _b;
    vector<int> rows_order;
    int _m;
    bool converted_to_triangular = false;
    db eps = 1e-8;
};


#endif //NONLINEAREQUATIONS_LINEAREQUATIONSYSTEMSOLVER_H
