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

void RKStep(VFFunction f, real &t, Vector &y, real &h) {
    Matrix rk_beta_trans = rk_beta.trans();
    size_t m = rk_alpha.getLength();
    real errorNorm = 100;
    while (1) {
        Vector sumK_gamma(y.getLength()), error(y.getLength());
        std::vector<Vector> vecK;
        for (size_t j = 1; j <= m; j++) {
            Vector sumK(y.getLength());
            for (size_t l = 0; l < vecK.size(); l++) {
                sumK += rk_beta_trans(j - 1, l) * vecK[l];
            }
            Vector K_j = f(t + rk_alpha(j - 1) * h, y + h * sumK);
            sumK_gamma += K_j * rk_gamma(j - 1);
            error += rk_delta(j - 1) * K_j * h;
            vecK.push_back(K_j);
        }

        errorNorm = error.normMax();
        real c = 0.9 * pow(eps / error.normMax(), 1.0 / (1 + rk_p));

        if (c < 0.1) {
            h *= 0.1;
        } else if (c > 5) {
            h *= 5;
        } else {
            h *= c;
        }

        if (errorNorm < eps) {
            y += h * sumK_gamma;
            t = t + h;
            break;
        }
    }
}

int main() {
    for (int i = 1; i <= 1; i++) {
        getExample(i, mass, f, yBeg, tBeg, tEnd, h0, doDraw, doOutput);
        Matrix rk_beta_trans = rk_beta.trans();
        if (mass.getLength() == 1) {
            /* with f */
            real tCheck = tBeg, t = tBeg, h = h0;
            Vector yCheck = yBeg, y = yBeg;

            while (t <= tEnd) {
                tCheck = t;
                yCheck = y;
                RKStep(f, t, y, h);
                std::cout << t << ":" << tEnd << std::endl;
                checkStep(t, y, doDraw, doOutput);
            }
            checkSolution(tCheck, yCheck);
        } else {
            /* without f */
        }
    }
    return 0;
}
