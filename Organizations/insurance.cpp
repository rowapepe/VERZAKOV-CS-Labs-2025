#include "insurance.hpp"

InsuranceCompany::InsuranceCompany(const char* name, int year, double assets) : Organization(name, year), totalAssets(assets) {
    std::cout << "InsuranceCompany()" << std::endl;
}

InsuranceCompany::~InsuranceCompany() {
    std::cout << "~InsuranceCompany()" << std::endl;
}

void InsuranceCompany::show() const {
    std::cout << "Страховая компания: " << name << ", основана в " << year << " году, общая сумма активов: " << totalAssets << "₽"<< std::endl;
}
