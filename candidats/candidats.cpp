#include "candidats.hpp"
#include <cstring>
#include <fstream>
#include <iostream>

namespace {
const int kBuffSize = 100;

int BinarySearch(Candidats::Candidat* candidats, int size, const char* target) {
    int left = 0;
    int right = size - 1;

    while (left <= right) {
        int mid = left + (right - left) / 2;

        if (candidats[mid] == target) {
            return mid;
        } else if (candidats[mid] < target) {
            left = mid + 1;
        } else {
            right = mid - 1;
        }
    }
    return -1;
}
}  // namespace

namespace Candidats {
Candidat::Candidat(const char* n, bool m, const char* r, int vn) {
    name = new char[strlen(n) + 1];
    strcpy(name, n);

    male = m;

    region = new char[strlen(r) + 1];
    strcpy(region, r);

    votesNumber = vn;
}

Candidat::Candidat(const Candidat& other) {
    name = new char[strlen(other.name) + 1];
    strcpy(name, other.name);

    male = other.male;

    region = new char[strlen(other.region) + 1];
    strcpy(region, other.region);

    votesNumber = other.votesNumber;
}

Candidat::~Candidat() {
    delete[] name;
}

void Candidat::SetName(const char* n) {
    if (name) {
        delete[] name;
    }

    name = new char[strlen(n) + 1];
    strcpy(name, n);
}

void Candidat::SetMale(bool m) {
    male = m;
}
void Candidat::SetRegion(const char* r) {
    if (region) {
        delete[] region;
    }

    region = new char[strlen(r) + 1];
    strcpy(region, r);
}
void Candidat::SetVotesNumber(int vn) {
    votesNumber = vn;
}

char* Candidat::GetName() {
    return name;
}

bool Candidat::GetMale() {
    return male;
}

char* Candidat::GetRegion() {
    return region;
}

int Candidat::GetVotesNumber() {
    return votesNumber;
}

Candidat& Candidat::operator=(const Candidat& other) {
    if (this == &other)
        return *this;

    delete[] name;
    delete[] region;

    name = new char[strlen(other.name) + 1];
    strcpy(name, other.name);

    male = other.male;

    region = new char[strlen(other.region) + 1];
    strcpy(region, other.region);

    votesNumber = other.votesNumber;

    return *this;
}

std::ofstream& operator<<(std::ofstream& file, Candidat& candidat) {
    file << candidat.GetName() << " " << candidat.GetMale() << " " << candidat.GetRegion() << " " << candidat.GetVotesNumber() << std::endl;
    return file;
}

std::ifstream& operator>>(std::ifstream& file, Candidat& candidat) {
    char n[kBuffSize]{};
    bool m{};
    char r[kBuffSize]{};
    int vn{};

    file >> n >> m >> r >> vn;
    candidat.SetName(n);
    candidat.SetMale(m);
    candidat.SetRegion(r);
    candidat.SetVotesNumber(vn);

    return file;
}

bool Candidat::operator==(const char* n) {
    if (strcmp(this->GetName(), n) == 0) {
        return true;
    } else {
        return false;
    }
}

bool Candidat::operator<(Candidat& сandidat2) {
    if (strcmp(this->GetName(), сandidat2.GetName()) < 0) {
        return true;
    } else {
        return false;
    }
}

bool Candidat::operator<(const char* n) {
    if (strcmp(this->GetName(), n) < 0) {
        return true;
    } else {
        return false;
    }
}

void Candidat::Resize(Candidat*& candidats, int& size) {
    Candidat* newCandidats = new Candidat[size + 1];

    for (int i = 0; i < size; ++i) {
        newCandidats[i] = candidats[i];
    }

    DeleteDB(candidats, size);
    candidats = newCandidats;
    ++size;
}

void Candidat::DeleteDB(Candidat*& candidats, int size) {
    if (!candidats) {
        return;
    }

    delete[] candidats;
    candidats = nullptr;
}

void Candidat::ReadDB(Candidat*& candidats, int& size) {
    std::ifstream file("Candidats.txt");
    if (!file) {
        std::cout << "Ошибка открытия файла!" << std::endl;
        return;
    }

    Candidat temp;

    while (file >> temp) {
        if (size == 1 && candidats[0] == "\0") {
            candidats[0] = temp;
        } else {
            Resize(candidats, size);
            candidats[size - 1] = temp;
        }
    }

    file.close();
}

void Candidat::WriteDB(Candidat*& candidats, int size) {
    if (!candidats) {
        return;
    }

    std::ofstream file("Candidats.txt");
    if (!file) {
        std::cout << "Ошибка открытия файла!" << std::endl;
        return;
    }

    for (int i = 0; i < size; ++i) {
        file << candidats[i];
    }

    file.close();
}

void Candidat::SortDB(Candidat*& candidats, int left, int right) {
    if (!candidats || left >= right) {
        return;
    }

    Candidat pivot = candidats[right];
    int partitionIndex = left;

    for (int i = left; i < right; ++i) {
        if (candidats[i] < pivot) {
            std::swap(candidats[i], candidats[partitionIndex]);
            ++partitionIndex;
        }
    }
    std::swap(candidats[right], candidats[partitionIndex]);

    SortDB(candidats, left, partitionIndex - 1);
    SortDB(candidats, partitionIndex + 1, right);
}

void Candidat::AddElement(Candidat*& candidats, int& size) {
    if (!candidats) {
        return;
    }

    Resize(candidats, size);

    char n[kBuffSize]{};
    bool m{};
    char r[kBuffSize]{};
    int vn{};

    std::cout << "Введите имя кандидата, пол (мужской - 1, женский - 0), регион, количество голосов: ";
    std::cin >> n >> m >> r >> vn;
    std::cout << std::endl;

    candidats[size - 1].SetName(n);
    candidats[size - 1].SetMale(m);
    candidats[size - 1].SetRegion(r);
    candidats[size - 1].SetVotesNumber(vn);
}

void Candidat::DeleteElement(Candidat*& candidats, int& size) {
    if (!candidats) {
        return;
    }

    char n[kBuffSize]{};
    std::cout << "Введите имя кандидата для удаления: ";
    std::cin >> n;
    std::cout << std::endl;

    SortDB(candidats, 0, size - 1);
    int point = BinarySearch(candidats, size, n);

    if (point == -1) {
        std::cout << "Кандидат не найден." << std::endl;
        return;
    }

    Candidat* newCandidats = new Candidat[size - 1]();

    for (int i = 0, j = 0; i < size; ++i) {
        if (i == point) {
            continue;
        }
        newCandidats[j++] = candidats[i];
    }

    DeleteDB(candidats, size);
    candidats = newCandidats;
    --size;
}

void Candidat::EditDB(Candidat*& сandidats, int size) {
    if (!сandidats) {
        return;
    }

    char nameToEdit[kBuffSize]{};
    std::cout << "Введите имя кандидата, которого хотите изменить: ";
    std::cin >> nameToEdit;
    std::cout << std::endl;

    SortDB(сandidats, 0, size - 1);

    int point = BinarySearch(сandidats, size, nameToEdit);

    if (point == -1) {
        std::cout << "Кандидат не найден." << std::endl;
        return;
    }

    char n[kBuffSize]{};
    bool m{};
    char r[kBuffSize]{};
    int vn{};

    std::cout << "Введите измененные имя кандидата, пол (мужской - 1, женский - 0), регион, количество голосов: ";
    std::cin >> n >> m >> r >> vn;
    std::cout << std::endl;
    сandidats[point].SetName(n);
    сandidats[point].SetMale(m);
    сandidats[point].SetRegion(r);
    сandidats[point].SetVotesNumber(vn);
}

void Candidat::PrintDB(Candidat*& candidats, int size) {
    if (!candidats) {
        return;
    }

    const char* m{};

    for (int i = 0; i < size; ++i) {
        m = "женский";

        if (candidats[i].GetMale()) {
            m = "мужской";
        }
        std::cout << "Имя кандидата: " << candidats[i].GetName() << '\n'
                  << "Пол: " << m << '\n'
                  << "Регион: " << candidats[i].GetRegion() << '\n'
                  << "Количество голосов: " << candidats[i].GetVotesNumber() << '\n'
                  << '\n';
    }
}
}  // namespace Candidats
