#include <cstddef>

namespace {}  // namespace

namespace IntegralSolver {
struct I_print {
    const char* name;
    double i_sum;
    double i_toch;
    int n;
};

struct Results {
    double sum;
    int n;
};

Results IntRect(double (*function)(double), double a, double b, double eps);
Results IntTrap(double (*function)(double), double a, double b, double eps);

void ExecuteApp();
}  // namespace IntegralSolver
