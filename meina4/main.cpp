#include <math.h>

#include <vector>

#include "tmatrix.h"
#include "tvector.h"
#include "unit.h"

static Vector mass;
static Vector yBeg;
static real tBeg;
static real tEnd;
static real h0;
static VFFunction f;
static bool doDraw = true, doOutput = true;
static Matrix rk_beta_trans;
Vector fkt(real t, const Vector x) {
    size_t len = x.getLength();
    Vector result(len);
    size_t bias = len / 2;
    size_t num = len / 4;
    for (size_t i = 0; i < num; i++) {
        result(i * 2) = x(bias + i * 2);
        result(i * 2 + 1) = x(bias + i * 2 + 1);
        Vector sum(2);
        Vector x_i(2);
        x_i(0) = x(i * 2);
        x_i(1) = x(i * 2 + 1);
        for (size_t j = 0; j < num; j++) {
            if (j != i) {
                Vector x_j(2);
                x_j(0) = x(j * 2);
                x_j(1) = x(j * 2 + 1);
                sum += kGrav * mass(j) * (x_j - x_i) /
                       (powl((x_j - x_i).norm2(), 3));
            }
        }
        result(bias + i * 2) = sum(0);
        result(bias + i * 2 + 1) = sum(1);
    }
    return result;
}
void RKStep(VFFunction f, real &t, Vector &y, real &h) {
    size_t m = rk_alpha.getLength();
    real h_ = h;
    while (1) {
        Vector sumK_gamma(y.getLength()), error(y.getLength()),
            yNext(y.getLength());
        std::vector<Vector> vecK;
        for (size_t j = 1; j <= m; j++) {
            Vector sumK(y.getLength());
            for (size_t l = 0; l < vecK.size(); l++) {
                sumK += rk_beta_trans(j - 1, l) * vecK[l];
            }
            Vector K_j = f(t + rk_alpha(j - 1) * h_, y + h_ * sumK);
            sumK_gamma += K_j * rk_gamma(j - 1);

            error += rk_delta(j - 1) * K_j * h_;
            vecK.push_back(K_j);
        }
        yNext = y + h_ * sumK_gamma;
        real tNext = t + h_;
        real errorNorm = error.normMax();

        real c = 0.9 * powl(eps / error.normMax(), 1.0 / (1 + rk_p));

        if (c < 0.1) {
            h_ *= 0.1;
        } else if (c > 5.0) {
            h_ *= 5.0;
        } else {
            h_ *= c;
        }

        if (errorNorm < eps) {
            y = yNext;
            t = tNext;
            h = h_;
            break;
        }
    }
    if (t + h > tEnd) {
        h = tEnd - t;
    }
}

int main(int argc, char **argv) {
    if (argc == 2) {
        int i = std::stoi(argv[1]);
        getExample(i, mass, f, yBeg, tBeg, tEnd, h0, doDraw, doOutput);
        rk_beta_trans.redim(rk_beta.getRows(), rk_beta.getCols());
        rk_beta_trans = rk_beta;
        rk_beta_trans.trans();
        real t = tBeg, h = h0;
        Vector y = yBeg;
        checkStep(t, y, doDraw, doOutput);
        if (mass.getLength() == 1) {
            /* with f */
            while (t < tEnd) {
                RKStep(f, t, y, h);
                checkStep(t, y, doDraw, doOutput);
            }
        } else {
            /* without f */

            while (t < tEnd) {
                RKStep(fkt, t, y, h);
                checkStep(t, y, doDraw, doOutput);
            }
        }
        checkSolution(t, y);
    }
    return 0;
}
