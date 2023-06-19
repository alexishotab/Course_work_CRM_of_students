#include <string.h>
using namespace std;

struct Date {
    unsigned short day;
    unsigned short month;
    unsigned short year;
};

struct Record_book {
    char subjects[10][100] = { "Тест", "Тест2" };
    int marks[10] = { 5,5 };
    int counter_lessons = 2;
};

struct StudentInFile {
    char ID[30];
    char surname[30];
    char name[30];
    char patronymic[30];
    char gender;
    Date date_birthday;
    char faculty[20];
    char department[20];
    char group[20];
    int current_semestr;
    int admission_year;
    int counter_of_items = 0;
    int counter_of_3_mark = 0;
    Record_book semesters[9];
};

class Student {
    static int counter_students;
private:
    char ID[30] ="1234567890";
    char surname[30]="Тестов";
    char name[30]="Тест";
    char patronymic[30]= "Тестович";
    char gender= 'Ж';
    Date date_birthday = { 1, 1, 2000 };
    char faculty[20] = "ИКБ";
    char department[20] = "КБ";
    char group[20]= "ТЕСТ-01-01";
    int current_semestr= 1;
    int admission_year= 2020;
    int counter_of_items = 0;
    int counter_of_3_mark = 0;

public:
    Record_book semesters[9];
    // Constructor
    Student(char _ID[], char _surname[], char _name[], char _patronymic[], char _gender, Date _date_birthday, char _faculty[], char _department[], char _group[], int _current_semestr, int _admission_year, Record_book _semesters[]) {
        counter_students++;
        strcpy_s(ID, sizeof(ID), _ID);
        strcpy_s(surname, sizeof(surname), _surname);
        strcpy_s(name, sizeof(name), _name);
        strcpy_s(patronymic, sizeof(patronymic), _patronymic);
        this->gender = _gender;
        this->date_birthday.day = _date_birthday.day;
        this->date_birthday.month = _date_birthday.month;
        this->date_birthday.year = _date_birthday.year;
        strcpy_s(faculty, sizeof(faculty), _faculty);
        strcpy_s(department, sizeof(department), _department);
        strcpy_s(group, sizeof(group), _group);
        this->current_semestr = _current_semestr;
        this->admission_year = _admission_year;
        for (int i = 0; i < _current_semestr; i++) {
            semesters[i] = _semesters[i];
            for (int j = 0; j < _semesters[i].counter_lessons; j++) {
                if (_semesters[i].marks[j] == 3) { counter_of_3_mark++; }
                counter_of_items++;
            }
            //cout << "semesters в Конструкторе " << counter_of_3_mark << " вот " << counter_of_items << endl;
        }
    }

    // Destructor
    ~Student() {
        counter_students--;
    }

    // Getters
    char* getID() { return ID; }
    int getCurrentSemestr() { return current_semestr; }
    char* getSurname() { return surname; }
    char* getName() { return name; }
    char* getPatronymic() { return patronymic; }
    Date getDateBirthday() { return date_birthday; }
    int getAdmissionYear() { return admission_year; }
    char* getFaculty() { return faculty; }
    char* getDepartment() { return department; }
    char* getGroup() { return group; }
    char getGender() { return gender; }
    int getCounterStudents() { return counter_students; }
    int getCounterOf3Mark() { return counter_of_3_mark; }
    int getCounterOfLessons() { return counter_of_items; }


    // Setters
    void setLastSemestr(Record_book _semesters[], int _current_semestr) {
        int i = _current_semestr - 1;
        counter_of_items = counter_of_items - this->semesters[i].counter_lessons;
        for (int j = 0; j < semesters[i].counter_lessons; j++) {
            if (semesters[i].marks[j] == 3) { counter_of_3_mark--; }
        }

        for (int j = 0; j < _semesters[j].counter_lessons; j++) {
            this->semesters[i].marks[j] = _semesters[i].marks[j];
            if (_semesters[i].marks[j] == 3) { counter_of_3_mark++; }
            counter_of_items++;
            strcpy_s(semesters[i].subjects[j], sizeof(semesters[i].subjects[j]), _semesters[i].subjects[j]);
        }
    }

    void setCurrentSemestr(int current_semestr) {
        this->current_semestr = current_semestr;
    }

    void setSurname(char _surname[]) {
        strcpy_s(surname, sizeof(surname), _surname);
    }

    void setName(char _name[]) {
        strcpy_s(name, sizeof(name), _name);
    }

    void setPatronymic(char _patronymic[]) {
        strcpy_s(patronymic, sizeof(patronymic), _patronymic);
    }

    void setDateBirthday(Date _date_birthday) {
        this->date_birthday.day = _date_birthday.day;
        this->date_birthday.month = _date_birthday.month;
        this->date_birthday.year = _date_birthday.year;
    }

    void setAdmissionYear(int admission_year) {
        this->admission_year = admission_year;
    }

    void setFaculty(char _faculty[]) {
        strcpy_s(faculty, sizeof(faculty), _faculty);
    }

    void setDepartment(char _department[]) {
        strcpy_s(department, sizeof(department),_department);
    }

    void setGroup(char _group[]) {
        strcpy_s(group, sizeof(group), _group);
    }

    void setAllSemestr(Record_book _semesters[], int _current_semestr) {
        counter_of_3_mark = 0;
        counter_of_items = 0;
        for (int i = 0; i < _current_semestr; i++) {
            this->semesters->counter_lessons = _semesters->counter_lessons;
            for (int j = 0; j < _semesters[i].counter_lessons; j++) {
                this->semesters[i].marks[j] = _semesters[i].marks[j];
                if (_semesters[i].marks[j] == 3) { counter_of_3_mark++; }
                counter_of_items++;
                strcpy_s(semesters[i].subjects[j], sizeof(semesters[i].subjects[j]), _semesters[i].subjects[j]);
            }
        }
    }

    void setGender(char gender) {
        this->gender = gender;
    }

    float getPercent() {
        return counter_of_3_mark / counter_of_items ;
    }

    bool IsNeadedForTheTask() {
        float percent = this->getPercent();
        return (percent <= 0.25) ? true : false;
    }
};