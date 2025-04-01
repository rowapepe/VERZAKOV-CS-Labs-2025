#include <iostream>
#include <iomanip>
#include <list>

class Date {
 private:
    int day;
    int month;
    int year;

 public:
    Date() : day(1), month(1), year(1970) {}

    Date(int d, int m, int y) : day(d), month(m), year(y) {}

    void Print() const {
        std::cout << std::setw(2) << std::setfill('0') << day << "." << std::setw(2) << std::setfill('0') << month << "." << year << std::endl;
    }

    bool operator==(const Date& other) const { return (day == other.day && month == other.month && year == other.year); }

    bool operator<(const Date& other) const {
        if (year != other.year)
            return year < other.year;
        if (month != other.month)
            return month < other.month;
        return day < other.day;
    }

    int GetYear() const { return year; }
};

void PrintList(const std::list<Date>& dates) {
    for (const Date& date : dates) {
        date.Print();
    }
    std::cout << std::endl;
}

int main() {
    std::list<Date> dates;
    dates.emplace_back(1, 2, 1963);
    dates.emplace_back(14, 7, 1995);
    dates.emplace_back(7, 12, 2088);
    dates.emplace_back(5, 3, 2030);
    dates.emplace_back(24, 9, 2013);
    dates.emplace_back(19, 9, 2020);


    PrintList(dates);

    std::list<Date> futureDates;
    for (Date date : dates) {
        if (date.GetYear() > 2025) {
            futureDates.push_back(date);
        }
    }

    std::cout << "Будущие даты:" << std::endl;
    PrintList(futureDates);

    return 0;
}
