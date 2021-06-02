#include "../headers/NonLinearSolver.h"

NonLinearSolver::NonLinearSolver(y_x f, y_x der_f, y_x der2_f) : f(f), der_f(der_f), der2_f(der2_f) {}

dvector NonLinearSolver::FindRoots(db a, db b, db eps, int splitNumber) {
    auto res = dvector();
    iterCnts.clear();
    auto xs = dbRange(a, b, splitNumber);
    auto fxi = f(xs[0]);
    for (int i = 0; i < xs.size() - 1; i++) {
        auto fxi1 = f(xs[i + 1]);

        if (abs(fxi) < 1e-12) {
            res.push_back(xs[i]);
            iterCnts.push_back(1);
        } else if (fxi * fxi1 + 1e-12 < 0) {
            if(der2_f(xs[i])*der2_f(xs[i+1]) + 1e-12 < 0 ||der_f(xs[i])*der_f(xs[i+1]) + 1e-12 < 0  )
                cout << "We need more splits!\n";
            res.push_back(FindRoot(xs[i], fxi, xs[i + 1], fxi1, eps));
        }
        fxi = fxi1;
    }
    return res;
}

db NonLinearSolver::FindRoot(db a, db fa, db b, db fb, db eps) {
    int iterCnt = 0;
    while (abs(a - b) > eps) {
        db temp_a = FindApproximation(a, fa, b, fb);
        b = FindApproximation(b, fb, a, fa);
        a = temp_a;
        fa = f(a);
        fb = f(b);
        iterCnt++;
    }
    iterCnts.push_back(iterCnt);
    return (a + b) / 2;
}

db NonLinearSolver::FindApproximation(db xn,  db fxn, db xn_, db fxn_) {
    if (fxn * der2_f(xn) < -1e-12)
        return ChordMethod(xn, fxn, xn_, fxn_);
    else
        return TangentMethod(xn, fxn);
}

db NonLinearSolver::ChordMethod(db xn,  db fxn, db xn_, db fxn_) {
    return xn - fxn / (fxn_ - fxn) * (xn_ - xn);
}

db NonLinearSolver::TangentMethod(db xn,  db fxn) {
    return xn - fxn / der_f(xn);
}

vector<int> NonLinearSolver::GetIterCounts() {
    return iterCnts;
}

