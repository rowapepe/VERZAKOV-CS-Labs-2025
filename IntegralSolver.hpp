#include <cstddef>

namespace {
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
}  // namespace

namespace IntegralSolver {
Results IntRect(double (*function)(double), double a, double b, double eps);
Results IntTrap(double (*function)(double), double a, double b, double eps);

void PrintTabl(I_print i_prn[], size_t k);

void ExecuteApp();
}  // namespace IntegralSolver
