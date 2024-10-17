#include <iostream>
#include <string>
#include <stdexcept>
#include <vector>

class Calendar {
private:
    int day;
    int month;
    int year;
    std::string event;

    void validateDate() {
        if (month < 1 || month > 12) {
            throw std::invalid_argument("Invalid month.");
        }
        if (day < 1 || day > daysInMonth()) {
            throw std::invalid_argument("Invalid day.");
        }
        if (year < 0) {
            throw std::invalid_argument("Invalid year.");
        }
    }

    int daysInMonth() const {
        switch (month) {
        case 4: case 6: case 9: case 11:
            return 30;
        case 2:
            return (isLeapYear()) ? 29 : 28;
        default:
            return 31;
        }
    }

    bool isLeapYear() const {
        return (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);
    }

public:
    Calendar(int d = 1, int m = 1, int y = 2000, std::string e = "No event")
        : day(d), month(m), year(y), event(e) {
        validateDate();
    }

    Calendar& operator=(const Calendar& other) {
        if (this != &other) {
            day = other.day;
            month = other.month;
            year = other.year;
            event = other.event;
            validateDate();
        }
        return *this;
    }

    Calendar& operator+=(int days) {
        day += days;
        while (day > daysInMonth()) {
            day -= daysInMonth();
            month++;
            if (month > 12) {
                month = 1;
                year++;
            }
        }
        validateDate();
        return *this;
    }

    Calendar& operator-=(int days) {
        day -= days;
        while (day < 1) {
            month--;
            if (month < 1) {
                month = 12;
                year--;
            }
            day += daysInMonth();
        }
        validateDate();
        return *this;
    }

    bool operator==(const Calendar& other) const {
        return day == other.day && month == other.month && year == other.year && event == other.event;
    }

    bool operator!=(const Calendar& other) const {
        return !(*this == other);
    }

    bool operator>(const Calendar& other) const {
        if (year != other.year) return year > other.year;
        if (month != other.month) return month > other.month;
        return day > other.day;
    }

    bool operator>=(const Calendar& other) const {
        return (*this > other) || (*this == other);
    }

    bool operator<(const Calendar& other) const {
        return !(*this >= other);
    }

    bool operator<=(const Calendar& other) const {
        return !(*this > other);
    }

    bool findEvent(const std::string& keyword) const {
        return event.find(keyword) != std::string::npos;
    }

    bool findEventByDate(int d, int m, int y) const {
        return (day == d && month == m && year == y);
    }

    bool findEventByDay(int d) const {
        return day == d;
    }

    bool findEventByMonth(int m) const {
        return month == m;
    }

    bool findEventByYear(int y) const {
        return year == y;
    }

    std::string getEventDate() const {
        return std::to_string(day) + "/" + std::to_string(month) + "/" + std::to_string(year);
    }

    std::string getEvent() const { return event; }

    void setEvent(const std::string& e) { event = e; }

    void printDate() const {
        std::cout << day << "/" << month << "/" << year << " - " << event << std::endl;
    }
};

void searchByCriteria(const std::vector<Calendar>& events) {
    int choice;
    std::cout << "Choose search criteria:\n1. By event name\n2. By day\n3. By month\n4. By year\n5. By full date\n";
    std::cin >> choice;
    std::cin.ignore();
    switch (choice) {
    case 1: {
        std::string keyword;
        std::cout << "Enter event name: ";
        std::getline(std::cin, keyword);
        bool found = false;
        for (const auto& event : events) {
            if (event.findEvent(keyword)) {
                std::cout << "Event found: " << event.getEventDate() << " - " << event.getEvent() << std::endl;
                found = true;
            }
        }
        if (!found) {
            std::cout << "Event not found.\n";
        }
        break;
    }
    case 2: {
        int day;
        std::cout << "Enter day: ";
        std::cin >> day;
        bool found = false;
        for (const auto& event : events) {
            if (event.findEventByDay(day)) {
                std::cout << "Event found: " << event.getEventDate() << " - " << event.getEvent() << std::endl;
                found = true;
            }
        }
        if (!found) {
            std::cout << "No events on this day.\n";
        }
        break;
    }
    case 3: {
        int month;
        std::cout << "Enter month: ";
        std::cin >> month;
        bool found = false;
        for (const auto& event : events) {
            if (event.findEventByMonth(month)) {
                std::cout << "Event found: " << event.getEventDate() << " - " << event.getEvent() << std::endl;
                found = true;
            }
        }
        if (!found) {
            std::cout << "No events in this month.\n";
        }
        break;
    }
    case 4: {
        int year;
        std::cout << "Enter year: ";
        std::cin >> year;
        bool found = false;
        for (const auto& event : events) {
            if (event.findEventByYear(year)) {
                std::cout << "Event found: " << event.getEventDate() << " - " << event.getEvent() << std::endl;
                found = true;
            }
        }
        if (!found) {
            std::cout << "No events in this year.\n";
        }
        break;
    }
    case 5: {
        int day, month, year;
        std::cout << "Enter day: ";
        std::cin >> day;
        std::cout << "Enter month: ";
        std::cin >> month;
        std::cout << "Enter year: ";
        std::cin >> year;
        bool found = false;
        for (const auto& event : events) {
            if (event.findEventByDate(day, month, year)) {
                std::cout << "Event found: " << event.getEventDate() << " - " << event.getEvent() << std::endl;
                found = true;
            }
        }
        if (!found) {
            std::cout << "No events on this date.\n";
        }
        break;
    }
    default:
        std::cout << "Invalid choice.\n";
    }
}

int main() {
    std::vector<Calendar> events = {
        Calendar(5, 1, 2024, "Birthday"),
        Calendar(25, 12, 2024, "Christmas"),
        Calendar(1, 1, 2024, "New Year"),
        Calendar(8, 3, 2024, "International Women's Day")
    };

    searchByCriteria(events);

    return 0;
}