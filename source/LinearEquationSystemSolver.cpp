#include "LinearEquationSystemSolver.h"

dvector LinearEquationSystemSolver::Solve() {
    if (!converted_to_triangular)
        ConvertToTriangular();
    return SolveByTriangular(_a, _b);
}

LinearEquationSystemSolver::LinearEquationSystemSolver(dmatrix a, dvector b) : _a(a), _b(b), _m(a.size()) {
    rows_order.resize(_m);
    for (int i = 0; i < _m; i++)
        rows_order[i] = i;
}

dvector LinearEquationSystemSolver::SolveByTriangular(const dmatrix &a, const dvector &b) const {
    dvector x(_m, 0);
    for (int k = _m - 1; k >= 0; k--) {
        db ax = 0;
        for (int j = k + 1; j < _m; j++)
            ax += a[k][j] * x[j];
        x[k] = (b[k] - ax) / a[k][k];
    }
    return x;
}

dvector LinearEquationSystemSolver::ConvertB(const dvector &b) {
    dvector tb(_m);
    for (int i = 0; i < _m; i++)
        tb[i] = b[rows_order[i]];
    for (int k = 0; k < _m; k++) {
        for (int p = k + 1; p < _m; p++)
            tb[p] -= _a[p][k] * tb[k];
    }
    return tb;
}

void LinearEquationSystemSolver::ConvertToTriangular() {
    for (int k = 0; k < _m; k++) {
        HandleMainElem(k);
        for (int p = k + 1; p < _m; p++) {
            db c = _a[p][k] / _a[k][k];
            for (int l = k + 1; l < _m; l++)
                _a[p][l] -= c * _a[k][l];
            _a[p][k] = c;
        }
    }
    _b = ConvertB(_b);
    converted_to_triangular = true;
}

void LinearEquationSystemSolver::HandleMainElem(int k) {
    int row = SelectMaxElem(k);
    if (abs(_a[row][k]) < eps) {
        ;//throw invalid_argument("Матрица вырожденная");
    }
    if (row == k)
        return;
    swap(_a[k], _a[row]);
    swap(rows_order[k], rows_order[row]);
}

int LinearEquationSystemSolver::SelectMaxElem(int k) {
    int max_elem = _a[k][k];
    int max_row = k;
    for (int i = k + 1; i < _m; i++)
        if (abs(_a[i][k]) > abs(max_elem)) {
            max_elem = _a[i][k];
            max_row = i;
        }
    return max_row;
}
