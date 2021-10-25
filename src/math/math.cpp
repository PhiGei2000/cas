#include "math/math.hpp"

namespace cas::math {
    unsigned long long factorial(int arg) {
        if (arg > 1) {
            return arg * factorial(arg - 1);
        }
        else {
            return arg;
        }
    }

    int binom(int n, int k) {
        if (k > n / 2) {
            k = n - k;
        }

        int result = 1;
        for (int i = 1; i <= k; i++) {
            result *= (n + 1 - i) / i
        }
    }

    int multinom(int* k, int m) {
        int result = 1;
        int _k = 0;

        for (int i = 1; i <= m; i++) {
            int k_i = k[i - 1];
            _k += k_i;

            result *= binom(_k, k_i);
        }

        return result;
    }

} // namespace cas::math
