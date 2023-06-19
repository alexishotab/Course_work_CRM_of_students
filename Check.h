#include <cstring>
#include <iostream>

class Check {
public:
    bool checkLength(char arr[], int N) {
        return std::strlen(arr) < N;
    }

    bool checkNoSpace(char arr[]) {
        for (int i = 0; i < std::strlen(arr); i++) {
            if (arr[i] == ' ') {
                return false;
            }
        }
        return true;
    }

    bool checkCyrillic(char arr[]) {
        for (int i = 0; i < std::strlen(arr); i++) {
            if (!((arr[i] >= 'À' && arr[i] <= 'ß') || (arr[i] >= 'à' && arr[i] <= 'ÿ'))) {
                return false;
            }
        }
        return true;
    }

    bool checkNoLettersOrSymbols(const char arr[]) {
        for (int i = 0; i < std::strlen(arr); i++) {
            if (arr[i] < '0' || arr[i] > '9') {
                return false;
            }
        }
        return true;
    }

    bool checkNoSpecialSymbols(char arr[]) {
        for (int i = 0; i < std::strlen(arr); i++) {
            if (!((arr[i] >= 'A' && arr[i] <= 'Z') || (arr[i] >= 'a' && arr[i] <= 'z') || (arr[i] >= 'À' && arr[i] <= 'ß') || (arr[i] >= 'à' && arr[i] <= 'ÿ') || (arr[i] >= '0' && arr[i] <= '9'))) {
                return false;
            }
        }
        return true;
    }

    bool checkDate(int day, int month, int year) {
        if (year < 1970) return false;

        if (month < 1 || month > 12) return false;

        int daysInMonth[] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };

        if ((year % 4 == 0 && year % 100 != 0) || year % 400 == 0)
            daysInMonth[1] = 29;

        return day > 0 && day <= daysInMonth[month - 1];
    }
};