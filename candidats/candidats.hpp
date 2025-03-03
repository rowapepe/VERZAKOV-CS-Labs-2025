#pragma once
#include <cstddef>
#include <iostream>

namespace Candidats {
class Candidat {
 private:
    char* name;
    bool male;
    char* region;
    int votesNumber;

 public:
    Candidat(const char* n = "\0", bool m = false, const char* r = "\0", int vn = 0);
    Candidat(const Candidat& other);

    ~Candidat();

    void SetName(const char* n);
    void SetMale(bool m);
    void SetRegion(const char* r);
    void SetVotesNumber(int vn);

    const char* GetName() const;
    bool GetMale() const;
    const char* GetRegion() const;
    int GetVotesNumber() const;

    Candidat& operator=(const Candidat& other);
    friend std::ostream& operator<<(std::ostream& os, const Candidat& candidat);
    friend std::istream& operator>>(std::istream& is, Candidat& candidat);
    bool operator==(const char* n);
    bool operator<(const Candidat& candidat2);
    bool operator<(const char* n);

    static void Resize(Candidat*& candidats, int& size);
    static void DeleteDB(Candidat*& candidats);

    static void ReadDB(Candidat*& candidats, int& size);
    static void WriteDB(Candidat*& candidats, int size);
    static void SortDB(Candidat*& candidats, int left, int right);
    static void AddElement(Candidat*& candidats, int& size);
    static void DeleteElement(Candidat*& candidats, int& size);
    static void EditDB(Candidat*& candidats, int size);
    static void PrintDB(Candidat*& candidats, int size);
};
}  // namespace Candidats
