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

        real c = 0.9 * pow(eps / error.normMax(), 1.0 / (1 + rk_p));

        if (c < 0.1) {
            h_ *= 0.1;
        } else if (c > 5) {
            h_ *= 5;
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
}

int main() {
    for (int i = 1; i <= 1; i++) {
        getExample(i, mass, f, yBeg, tBeg, tEnd, h0, doDraw, doOutput);
        rk_beta_trans.redim(rk_beta.getRows(), rk_beta.getCols());
        rk_beta_trans = rk_beta;
        rk_beta_trans.trans();
        if (mass.getLength() == 1) {
            /* with f */
            real tCheck = tBeg, t = tBeg, h = h0;
            Vector yCheck = yBeg, y = yBeg;

            while (t <= tEnd) {
                tCheck = t;
                yCheck = y;
                RKStep(f, t, y, h);
                checkStep(t, y, doDraw, doOutput);
            }
            checkSolution(tCheck, yCheck);
        } else {
            /* without f */
        }
        getchar();
    }
    return 0;
}
