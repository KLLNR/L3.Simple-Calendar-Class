#include <iostream>
#include <string>

using namespace std;

class Calendar {
private:
    int day;
    int month;
    int year;
    string event;

    bool isValidDate(int d, int m, int y) {
        if (m < 1 || m > 12) return false;

        int daysInMonth[] = { 31, (y % 4 == 0 && (y % 100 != 0 || y % 400 == 0)) ? 29 : 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
        return d >= 1 && d <= daysInMonth[m - 1];
    }

    void adjustDate() {
        int daysInMonth[] = { 31, (year % 4 == 0 && (year % 100 != 0 || year % 400 == 0)) ? 29 : 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
        while (day > daysInMonth[month - 1]) {
            day -= daysInMonth[month - 1];
            month++;
            if (month > 12) {
                month = 1;
                year++;
            }
        }
        while (day < 1) {
            month--;
            if (month < 1) {
                month = 12;
                year--;
            }
            day += daysInMonth[month - 1];
        }
    }

public:
    Calendar(int d = 1, int m = 1, int y = 2024, string e = "") {
        if (!isValidDate(d, m, y)) throw invalid_argument("Invalid date");
        day = d;
        month = m;
        year = y;
        event = e;
    }                                                                    

    ~Calendar() {
    }

 
    int getDay() const { return day; }
    int getMonth() const { return month; }
    int getYear() const { return year; }
    string getEvent() const { return event; }

    void setDate(int d, int m, int y) {
        if (!isValidDate(d, m, y)) throw invalid_argument("Invalid date");
        day = d;
        month = m;
        year = y;
    }

    void setEvent(string e) { event = e; }

    Calendar& operator=(const Calendar& other) {
        if (this != &other) {
            day = other.day;
            month = other.month;
            year = other.year;
            event = other.event;
        }
        return *this;
    }

    Calendar& operator+=(int days) {
        day += days;
        adjustDate();
        return *this;
    }

    Calendar& operator-=(int days) {
        day -= days;
        adjustDate();
        return *this;
    }

    bool findEvent(int searchYear) const {
        return year == searchYear;
    }


    bool operator==(const Calendar& other) const {
        return day == other.day && month == other.month && year == other.year;
    }

    bool operator!=(const Calendar& other) const {
        return !(*this == other);
    }

    bool operator<(const Calendar& other) const {
        if (year != other.year) return year < other.year;
        if (month != other.month) return month < other.month;
        return day < other.day;
    }

    bool operator<=(const Calendar& other) const {
        return *this < other || *this == other;
    }

    bool operator>(const Calendar& other) const {
        return !(*this <= other);
    }

    bool operator>=(const Calendar& other) const {
        return !(*this < other);
    }

 
    bool findEvent(const string& searchEvent) const {
        return event.find(searchEvent) != string::npos;
    }
};

int main() {
    try {
        Calendar cal1(10, 10, 2024, "Birthday");
        Calendar cal2(5, 11, 2024, "Meeting");

        cout << "Event on cal1: " << cal1.getEvent() << endl;

        cal1 += 10;
        cout << "Date after adding 10 days: " << cal1.getDay() << "/" << cal1.getMonth() << "/" << cal1.getYear() << endl;

        cal1 -= 15;
        cout << "Date after subtracting 15 days: " << cal1.getDay() << "/" << cal1.getMonth() << "/" << cal1.getYear() << endl;

        if (cal1 > cal2) {
            cout << "cal1 is later than cal2" << endl;
        }

        if (cal2.findEvent("Meeting")) {
            cout << "Event 'Meeting' found in cal2" << endl;
        }

    }
    catch (const invalid_argument& e) {
        cerr << e.what() << endl;
    }



    return 0;
}

