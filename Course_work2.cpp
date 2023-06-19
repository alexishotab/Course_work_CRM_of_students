#include <iostream>
#include <fstream>
#include <string> //не используется в сохранение данных - только для проверок и шифрования (пароль)
#include <stdlib.h>
#include <stdio.h>
#include <windows.h> 
#include <clocale>
#include "Student.h"
#include "StudentList.h"
#include "Check.h"
#include "CryptoTools.h"

using namespace std;

void printDate(unsigned short day, unsigned short month, unsigned short year, int wLine) {
    //int w = 2;
    int delta = (wLine) / 2 - 1;
    cout << left;
    cout.width(delta); cout << " ";
    if (day > 9) {
        cout << day;
    }
    else {
        cout << "0" << day;
    }
    cout << ".";
    if (month > 9) {
        cout << month;
    }
    else {
        cout << "0" << month;
    }
    cout << ".";
    cout << year;
    cout.width(delta); cout << " ";
}

void DrawLine() {
    for (int i = 0; i < 177; i++) {
        cout << "-";
    }
    cout << "\n";
}

void myCentr(string s, int wLine) {

    int w = s.length();
    int delta = (wLine - w) / 2;
    cout << left;
    cout.width(delta); cout << " ";
    cout << s;
    cout.width(delta + 1); cout << " ";
}

void WriteStream(StudentList* list) {
    system("cls");
    ofstream file;
    file.open("data.dat", ios_base::out | ios::binary);
    char spa = ' ';
    int i = 0;
    StudentNode* current = list->getMyHead();
    file << list->getCountStudent() << '\n';
    while (current != nullptr) {
        file << current->data.getID() << spa << current->data.getSurname() << spa <<
            current->data.getName() << spa << current->data.getPatronymic() << spa <<
            current->data.getGender() << spa << current->data.getDateBirthday().day << spa <<
            current->data.getDateBirthday().month << spa << current->data.getDateBirthday().year << spa <<
            current->data.getFaculty() << spa << current->data.getDepartment() << spa <<
            current->data.getGroup() << spa << current->data.getCurrentSemestr() << spa <<
            current->data.getAdmissionYear() << spa;

        for (int i = 0; i < current->data.getCurrentSemestr(); i++) {
            file << current->data.semesters[i].counter_lessons << spa;
            for (int j = 0; j < current->data.semesters[i].counter_lessons; j++) {
                file << current->data.semesters[i].subjects[j] << spa
                    << current->data.semesters[i].marks[j] << spa;
            }
        }
        file << '\n';
        i++;
        current = current->next;
    }
    file.close();


    /*file.open("data.txt", ios_base::out);
    i = 0;
    current = list->getMyHead();
    file << list->getCountStudent() << '\n';
    while (current != nullptr) {
        file << current->data.getID() << spa << current->data.getSurname() << spa <<
            current->data.getName() << spa << current->data.getPatronymic() << spa <<
            current->data.getGender() << spa << current->data.getDateBirthday().day << spa <<
            current->data.getDateBirthday().month << spa << current->data.getDateBirthday().year << spa <<
            current->data.getFaculty() << spa << current->data.getDepartment() << spa <<
            current->data.getGroup() << spa << current->data.getCurrentSemestr() << spa <<
            current->data.getAdmissionYear() << spa;

        for (int i = 0; i < current->data.getCurrentSemestr(); i++) {
            file << current->data.semesters[i].counter_lessons << spa;
            for (int j = 0; j < current->data.semesters[i].counter_lessons; j++) {
                file << current->data.semesters[i].subjects[j] << spa
                    << current->data.semesters[i].marks[j] << spa;
            }
        }
        file << '\n';
        i++;
        current = current->next;
    }
    file.close();*/
}

void ReadStream(StudentList* list) {
    char ID[30], surname[30], name[30], patronymic[30], gender, faculty[20], department[20], group[20];
    Date date_birthday;
    int current_semestr, admission_year, countS;
    Record_book semesters[9];
    ifstream file;
    file.open("data.dat", ios_base::in || ios_base::binary);
    file >> countS;
    for (int i = 0; i<countS; i++) {
        file >> ID >> surname >> name >> patronymic >> gender >> date_birthday.day >>
            date_birthday.month >> date_birthday.year >> faculty >> department >> group >>
            current_semestr >> admission_year;
        for (int sess_id = 0; sess_id < current_semestr; sess_id++) {
            int countOfItems;
            file >> countOfItems;
            semesters[sess_id].counter_lessons = countOfItems;
            for (int pair_id = 0; pair_id < countOfItems; pair_id++) {
                file >> semesters[sess_id].subjects[pair_id] >> semesters[sess_id].marks[pair_id];
            }
        }
        Student student(ID, surname, name, patronymic, gender, date_birthday, faculty, department, group, current_semestr, admission_year, semesters);
        list->addStudent(&student);
        /*cout << "- Студент " << ID << ' ' << surname << ' ' << name << ' ' << patronymic << ' ' << gender << ' ' << date_birthday.year << ' ' << faculty
            << ' ' << department << ' ' << group << ' ' << current_semestr << ' ' << admission_year << ' ' << semesters->marks[0];*/
    }
    file.close();
}

void NewStudent(StudentList* list) {
    Check check;
    char ID[30], surname[30], name[30], patronymic[30], faculty[20], department[20], group[20];
    int current_semestr, admission_year;
    Record_book semesters[9];
    Date date_birthday;
    char gender;
    StudentInFile* st = new StudentInFile();
    char temp[2] = { '0','\0' };
    char temp2 = getchar();
    cout << "\nВведите номер студенческого билета или введите 0, чтобы вернуться: : ";
    cin.getline(ID, 30); 
    if (list->IsCompareArrays(ID, temp)) { system("cls"); return; }
    if (check.checkLength(ID, 30) == false||check.checkNoSpecialSymbols(ID)==false|| check.checkNoSpace(ID)==false) {
        cout << "\nНеверный ввод! Введите без пробелов и спец.символов (макс.длина: 30)...\n";
        Sleep(1500);
        system("cls");
        return;
    }
    StudentNode* result = list->FindStudetnByID(ID);
    if (result != nullptr) {
        cout << "\nТакой студент уже существует! Возврат в меню...\n";
        Sleep(1500);
        system("cls");
        return;
    }
     
    strcpy_s(st->ID, ID);
    cout << "\nВведите Фамилию студента: ";
    cin.getline(surname, 30);  strcpy_s(st->surname, surname);
    if (check.checkLength(surname, 30) == false || check.checkNoSpecialSymbols(surname) == false || check.checkNoSpace(surname) == false) {
        cout << "\nНеверный ввод! Введите без пробелов и спец.символов (макс.длина: 30)...\n";
        Sleep(1500);
        system("cls");
        return;
    }
     
    cout << "\nВведите Имя студента: ";
    cin.getline(name, 30);   strcpy_s(st->name, name);
    if (check.checkLength(name, 30) == false || check.checkNoSpecialSymbols(name) == false || check.checkNoSpace(name) == false) {
        cout << "\nНеверный ввод! Введите без пробелов и спец.символов (макс.длина: 30)...\n";
        Sleep(1500);
        system("cls");
        return;
    }
    cout << "\nВведите Отчество : ";
    cin.getline(patronymic, 30);   strcpy_s(st->patronymic, patronymic);
    if (check.checkLength(patronymic, 30) == false || check.checkNoSpecialSymbols(patronymic) == false || check.checkNoSpace(patronymic) == false) {
        cout << "\nНеверный ввод! Введите без пробелов и спец.символов (макс.длина: 30)...\n";
        Sleep(1500);
        system("cls");
        return;
    }
    cout << "\nВведите пол (М/Ж): ";
    cin >> gender; st->gender = gender;
    if (gender != 'М' && gender != 'Ж') {
        cout << "\nНеверный ввод! Введите букву М или Ж...\n";
        Sleep(1500);
        system("cls");
        return;
    }
    cout << "\nВведите день рождения через пробел (01 01 2022): ";
    cin >> date_birthday.day >> date_birthday.month >> date_birthday.year; st->date_birthday = date_birthday;
    string strday = to_string(date_birthday.day);
    string strmonth = to_string(date_birthday.month);
    string stryear = to_string(date_birthday.year);
    if (check.checkDate(date_birthday.day, date_birthday.month, date_birthday.year)==false||check.checkNoLettersOrSymbols(strday.c_str())==false || check.checkNoLettersOrSymbols(strmonth.c_str()) == false || check.checkNoLettersOrSymbols(stryear.c_str()) == false) {
        cout << "\nНеверный ввод! Такой даты не существует...\n";
        Sleep(1500);
        system("cls");
        return;
    }
    char c; while (cin.get(c) && c != '\n');
    cout << "\nВведите Институт: ";
    cin.getline(faculty, 20);  
    if (check.checkLength(faculty, 20) == false || check.checkNoSpecialSymbols(faculty) == false || check.checkNoSpace(faculty) == false) {
        cout << "\nНеверный ввод! Введите без пробелов и спец.символов (макс.длина: 20)...\n";
        Sleep(1500);
        system("cls");
        return;
    }
    cout << "\nВведите Кафедру: ";
    cin.getline(department, 20);  
    if (check.checkLength(department, 20) == false || check.checkNoSpace(department) == false) {
        cout << "\nНеверный ввод! Введите без пробелов и спец.символов (макс.длина: 20)...\n";
        Sleep(1500);
        system("cls");
        return;
    }
    cout << "\nВведите Группу: ";
    cin.getline(group, 20);   strcpy_s(st->faculty, faculty); strcpy_s(st->department, department); strcpy_s(st->group, group);
    if (check.checkLength(group, 20) == false || check.checkNoSpace(group) == false) {
        cout << "\nНеверный ввод! Введите без пробелов и спец.символов (макс.длина: 20)...\n";
        Sleep(1500);
        system("cls");
        return;
    }
    cout << "\nВведите текущий семестр по счету у студента, и Год поступления: ";
    cin >> current_semestr >> admission_year; st->current_semestr = current_semestr; st->admission_year = admission_year;
    string cursem = to_string(current_semestr);
    string admyear = to_string(admission_year);
    if  (check.checkNoLettersOrSymbols(cursem.c_str()) == false || check.checkNoLettersOrSymbols(admyear.c_str()) == false || admission_year <1971 || admission_year>2050 || (current_semestr>9 || current_semestr <1)) {
        cout << "\nНеверный ввод! Количество сессий <=9, год должен быть >1970 ...\n";
        Sleep(1500);
        system("cls");
        return;
    }
    cout << st->ID << st->surname << st->name << st->patronymic << st->faculty << st->department << st->group << st->current_semestr << st->admission_year << st->gender << st->date_birthday.day << st->date_birthday.month;
    cout << "\nВвод данных зачетной книжки:\n";
    for (int i = 0; i < current_semestr; i++) {
        cout << "\nВвод данных семестра номер " << i + 1;
        int counter_lessons;
        cout << "\nВведите, сколько предметов было в данном семестре: ";
        cin >> counter_lessons;
        string cntless = to_string(counter_lessons);
        if (check.checkNoLettersOrSymbols(cntless.c_str()) == false|| (counter_lessons > 10 || counter_lessons <1 )) {
            cout << "\nНеверный ввод! Количество предметов от 1 до 10 включительно ...\n";
            cout << "Введено 2 предмета (по умолчанию)";
            counter_lessons = 2;
        }
        st->semesters[i].counter_lessons = counter_lessons;
        semesters[i].counter_lessons = counter_lessons;
        for (int j = 0; j < counter_lessons; j++) {
            int mark;
            char lesson[100];
            char c; while (cin.get(c) && c != '\n');
            cout << "Введите название предмета: ";
            cin.getline(lesson, 100); 
            bool flag = true;
            char newlesson[30] = "TEST";
            if (check.checkLength(lesson, 100) == false || check.checkNoSpace(lesson) == false) {
                cout << "\nНеверный ввод! Введите без пробелов и спец.символов (макс.длина: 100)...\n";
                flag = false;
            }
            cout << "Введите оценку за него:";
            cin >> mark;
            string mrk = to_string(mark);
            if (check.checkNoLettersOrSymbols(mrk.c_str()) == false || (mark > 5 || mark <2)) {
                cout << "\nНеверный ввод! Оценка от 1 до 5 ...\n";
                cout << "Введена оценка за экзамен - 4  (по умолчанию)";
                mark = 4;
            }
            semesters[i].marks[j] = mark; st->semesters[i].marks[j] = mark;
            if (flag) {
                strcpy_s(semesters[i].subjects[j], sizeof(semesters[i].subjects[j]), lesson);
                strcpy_s(st->semesters[i].subjects[j], sizeof(st->semesters[i].subjects[j]), lesson);
            }
            else {
                strcpy_s(semesters[i].subjects[j], sizeof(semesters[i].subjects[j]), newlesson);
                strcpy_s(st->semesters[i].subjects[j], sizeof(st->semesters[i].subjects[j]), newlesson);
            }
        }
    }
    Student current(ID, surname, name, patronymic, gender, date_birthday, faculty, department, group, current_semestr, admission_year, semesters);
    list->addStudent(&current);
    //cout << "с он: в NewStudent Class " << current.semesters[current_semestr].subjects[0];
    //cout << " Вот он: в  NewStudent struct " << st->semesters[0].subjects[0];
    delete st;
    cout << "\n\nСтудент успешно добавлен!";
    Sleep(1500);
    system("cls");
    return;
}

void ChooseWhatToChange(StudentList* list, StudentNode* student) {
    int command;
    cout << "Выберите действие : \n(0) Выход в меню\n(1) Поменять ФИО\n(2) Поменять дату рождения\n" <<
        "(3) Поменять год поступления\n(4) Поменять направление/группу\n(5) Поменять гендер\n(6) Поменять оценки в последнем семестре\n";

    cout << "\nВведите комманду: " << endl;
    cin >> command;
    cout << '\n';
    char surname[30], name[30], father[30];
    unsigned short day, month, year;
    int year2;
    Check check;
    string strday;
    string strmonth;
    string stryear;
    string cntless;
    string admyear;
    string cursem;
    string mrk;
    Record_book semesters[9];
    char faculty[20], department[20], group[20];
    char gender;
    Date date;
    char c; while (cin.get(c) && c != '\n');
    switch (command) {
    case 0:
        break;
    case 1:
        cout << "Введите Фамилию: ";
        cin.getline(surname,30);  
        if (check.checkLength(surname, 30) == false || check.checkNoSpecialSymbols(surname) == false || check.checkNoSpace(surname) == false) {
            cout << "\nНеверный ввод! Введите без пробелов и спец.символов (макс.длина: 30)...\n";
            Sleep(1500);
            system("cls");
            return;
        }
        student->data.setSurname(surname);
        cout << "Введите Имя: ";
        cin.getline(name,30);  
        if (check.checkLength(name, 30) == false || check.checkNoSpecialSymbols(name) == false || check.checkNoSpace(name) == false) {
            cout << "\nНеверный ввод! Введите без пробелов и спец.символов (макс.длина: 30)...\n";
            Sleep(1500);
            system("cls");
            return;
        }
        student->data.setName(name);
        cout << "Введите Отчество: ";
        cin.getline(father,30);  
        if (check.checkLength(father, 30) == false || check.checkNoSpecialSymbols(father) == false || check.checkNoSpace(father) == false) {
            cout << "\nНеверный ввод! Введите без пробелов и спец.символов (макс.длина: 30)...\n";
            Sleep(1500);
            system("cls");
            return;
        }
        student->data.setPatronymic (father);
        cout << "Вы успешно поменяли студенту " << student->data.getID() << " ФИО";
        Sleep(1500);
        break;
    case 2:
        cout << "Введите День: ";
        cin >> day;
        cout << "Введите Месяц: ";
        cin >> month;
        cout << "Введите Год: ";
        cin >> year;
        date = { day, month, year };
        strday = to_string(day);
        strmonth = to_string(month);
        stryear = to_string(year);
        if (check.checkDate(day,month,year) == false || check.checkNoLettersOrSymbols(strday.c_str()) == false || check.checkNoLettersOrSymbols(strmonth.c_str()) == false || check.checkNoLettersOrSymbols(stryear.c_str()) == false) {
            cout << "\nНеверный ввод! Такой даты не существует...\n";
            Sleep(1500);
            system("cls");
            return;
        }
        student->data.setDateBirthday(date);
        cout << "Вы успешно поменяли студенту " << student->data.getID()<< " день рождения";
        Sleep(1500);
        break;
    case 3:
        cin >> year2;
        admyear = to_string(year2);
        if (check.checkNoLettersOrSymbols(admyear.c_str()) == false || year2 < 1971||year2>2050) {
            cout << "\nНеверный ввод! Год должен быть >1970 ...\n";
            Sleep(1500);
            system("cls");
            return;
        }
        student->data.setAdmissionYear(year2);
        cout << "Вы успешно поменяли студенту " << student->data.getID() << " год поступления";
        Sleep(1500);
        break;
    case 4:
        cout << "Введите Факультет: ";
        cin.getline(faculty,20);  
        if (check.checkLength(faculty, 20) == false || check.checkNoSpecialSymbols(faculty) == false || check.checkNoSpace(faculty) == false) {
            cout << "\nНеверный ввод! Введите без пробелов и спец.символов (макс.длина: 20)...\n";
            Sleep(1500);
            system("cls");
            return;
        }
        student->data.setFaculty(faculty);
        cout << "Введите Кафедру: ";
        cin.getline(department,20);  
        if (check.checkLength(department, 20) == false ||  check.checkNoSpace(department) == false) {
            cout << "\nНеверный ввод! Введите без пробелов и спец.символов (макс.длина: 20)...\n";
            Sleep(1500);
            system("cls");
            return;
        }
        student->data.setDepartment(department);
        cout << "Введите Группу: ";
        cin.getline(group,20);  
        if (check.checkLength(group, 20) == false || check.checkNoSpace(group) == false) {
            cout << "\nНеверный ввод! Введите без пробелов и спец.символов (макс.длина: 20)...\n";
            Sleep(1500);
            system("cls");
            return;
        }
        student->data.setGroup(group);
        cout << "Вы успешно поменяли студенту " << student->data.getID() << " направление/группу";
        Sleep(1500);
        break;
    case 5:
        cout << "Введите пол студента (М или Ж): ";
        cin >> gender;
        if (gender != 'М' && gender != 'Ж') {
            cout << "\nНеверный ввод! Введите букву М или Ж...\n";
            Sleep(1500);
            system("cls");
            return;
        }
        student->data.setGender(gender);
        cout << "Вы успешно поменяли студенту " << student->data.getID() << " гендер (но он остался того же пола, все по законам РФ)";
        Sleep(1500);
        break;
    case 6:
        cout << "Меняем зачетную книгу студента: "<< endl;
        cout << "\nВведите, сколько семестров обучался студент (1-9):";
        int current_semestr;
        cin >> current_semestr;
        cursem = to_string(current_semestr);
        if (check.checkNoLettersOrSymbols(cursem.c_str()) == false || current_semestr >9 || current_semestr <1) {
            cout << "\nНеверный ввод! Количество сессий <=9, год должен быть >1970 ...\n";
            Sleep(1500);
            system("cls");
            return;
        }
        for (int i = 0; i < current_semestr; i++) {
            cout << "\nВвод данных семестра номер " << i + 1;
            int counter_lessons;
            cout << "\nВведите, сколько предметов было в данном семестре: ";
            cin >> counter_lessons;
            cntless = to_string(counter_lessons);
            if (check.checkNoLettersOrSymbols(cntless.c_str()) == false || counter_lessons > 10 || counter_lessons <1) {
                cout << "\nНеверный ввод! Количество предметов от 1 до 10 включительно ...\n";
                Sleep(1500);
                system("cls");
                return;
            }
            semesters[i].counter_lessons = counter_lessons;
            for (int j = 0; j < counter_lessons; j++) {
                int mark;
                char lesson[100];
                char c; while (cin.get(c) && c != '\n');
                cout << "Введите название предмета: ";
                cin.getline(lesson, 100);  
                if (check.checkLength(lesson, 100) == false || check.checkNoSpace(lesson) == false) {
                    cout << "\nНеверный ввод! Введите без пробелов и спец.символов (макс.длина: 100)...\n";
                    Sleep(1500);
                    system("cls");
                    return;
                }
                cout << "Введите оценку за него:";
                cin >> mark;
                mrk = to_string(mark);
                if (check.checkNoLettersOrSymbols(mrk.c_str()) == false || (mark > 5 || mark < 2)) {
                    cout << "\nНеверный ввод! Оценка от 1 до 5 ...\n";
                    Sleep(1500);
                    system("cls");
                    return;
                }
                semesters[i].marks[j] = mark;
                strcpy_s(semesters[i].subjects[j], sizeof(semesters[i].subjects[j]), lesson);
            }
        }
        student->data.setAllSemestr(semesters, current_semestr);
        Sleep(1500);
        return;
    }
}

void EditStudent(StudentList* list) {
    char input[30];
    Check check;
    cout << "Введите номер студенческого билета, если вы хотите изменить студента. Введите 0, чтобы вернуться: ";
    char c; while (cin.get(c) && c != '\n');
    cin.getline(input,30);  
    char temp[2] ={'0','\0'};
    if (check.checkLength(input, 30) == false || check.checkNoSpecialSymbols(input) == false || check.checkNoSpace(input) == false) {
        cout << "\nНеверный ввод! Введите без пробелов и спец.символов (макс.длина: 30)...\n";
        Sleep(1500);
        system("cls");
        return;
    }
    if (list->IsCompareArrays(input,temp)) { system("cls"); return; }
    StudentNode* result = list->FindStudetnByID(input);
    if (result == nullptr) {
        cout << "\nСтудент не найден! Выберете другого студента\n";
        Sleep(1500);
        system("cls");
        return;
    }
    else {
        cout << "\nНайден студент " << result->data.getSurname()<< " " << result->data.getName() << " !\n";
    }
    Sleep(1500);
    system("cls");
    ChooseWhatToChange(list, result);
    system("cls");
}

void DeleteStudent(StudentList* list) {
    char input[30];
    Check check;
    cout << "Введите номер студенческого билета, если вы хотите изменить студента. Введите 0, чтобы вернуться: ";
    char c; while (cin.get(c) && c != '\n');
    cin.getline(input, 30);
    char temp[2] = { '0','\0' };
    if (check.checkLength(input, 30) == false || check.checkNoSpecialSymbols(input) == false || check.checkNoSpace(input) == false) {
        cout << "\nНеверный ввод! Введите без пробелов и спец.символов (макс.длина: 30)...\n";
        Sleep(1500);
        system("cls");
        return;
    }
    if (list->IsCompareArrays(input, temp)) { system("cls"); return; }
    StudentNode* result = list->FindStudetnByID(input);
    if (result == nullptr) {
        cout << "\nСтудент не найден! Выберете другого студента\n";
        Sleep(1500);
        system("cls");
        return;
    }
    else {
        cout << "\nНайден и удален студент " << result->data.getSurname() << " " << result->data.getName() << " !\n";
        list->deleteStudent(result->data.getID());
    }
    Sleep(1500);
    system("cls");
    ChooseWhatToChange(list, result);
    system("cls");
}

void Draw(StudentList* list) {
    system("cls");
    StudentNode* current = list->getMyHead();
    cout << endl;	cout.width(176); cout.fill('-'); cout << "-" << endl;
    cout.fill(' '); cout.width(174);  cout << left << "|Список студентов Мирэа"; cout << "|" << endl;
    cout.width(175); cout.fill('-'); cout << "-" << endl;
    cout.fill(' ');
    cout << left << "|"; myCentr("ID", 16);
    cout << left << "|"; myCentr("Фамилия", 20);
    cout << left << "|"; myCentr("Имя", 20);
    cout << left << "|"; myCentr("Отчество", 20);
    cout << left << "|"; myCentr("Дата Рожд.", 17);
    cout << left << "|"; myCentr("Пол", 4);
    cout << left << "|"; myCentr("Факультет", 10);
    cout << left << "|"; myCentr("Кафедра", 10);
    cout << left << "|"; myCentr("Группа", 16);
    cout << left << "|"; myCentr("Поступил в", 10);
    cout << left << "|"; myCentr("Семестер #", 10);
    cout << " |" << endl;
    cout.width(175); cout.fill('-'); cout << "-" << endl;
    while (current != nullptr) {
        cout.fill(' ');
        cout << left << "|"; cout.width(17); cout << left << current->data.getID();
        cout << left << "|"; cout.width(20); cout << left << current->data.getSurname();
        cout << left << "|"; cout.width(20); cout << left << current->data.getName();
        cout << left << "|"; cout.width(21); cout << left << current->data.getPatronymic();
        cout << left << "|";
        printDate(current->data.getDateBirthday().day, current->data.getDateBirthday().month, current->data.getDateBirthday().year, 10);
        cout << left << "|"; cout.width(4); cout << left << current->data.getGender();
        cout << left << "|"; cout.width(11); cout << left << current->data.getFaculty();
        cout << left << "|"; cout.width(10); cout << left << current->data.getDepartment();
        cout << left << "|"; cout.width(17); cout << left << current->data.getGroup();
        cout << left << "|"; cout.width(12); cout << left << current->data.getAdmissionYear();
        cout << left << "|"; cout.width(12); cout << left << current->data.getCurrentSemestr(); cout << " |" << endl;
        cout << left << '|';
        for (int i = 0; i < current->data.getCurrentSemestr(); i++) {
            cout <<i+1 << "-й семестер: ";
            for (int j = 0; j < current->data.semesters[i].counter_lessons; j++) {
                cout << current->data.semesters[i].subjects[j] << ' '
                    << current->data.semesters[i].marks[j] << ' ';
            }
            cout << '\n' << left << '|';
        }
        cout.width(175); cout.fill('-'); cout << "-" << endl;
        current = current->next;
    }
    cout << "\nВернуться в меню? Нажмите любую клавишу";
    getchar();
    getchar();
    system("cls");
}

void DrawTask89(StudentList* list) {
    system("cls");
    Check check;
    int year1, year2, counter = 0;
    cout << "Введите через пробел 2 числа - промежуток годов рождения, в котором ищете студентов (например: 2001 2005): ";
    cin >> year1 >> year2;
    string styear1 = to_string(year1);
    string styear2 = to_string(year2);
    if (check.checkNoLettersOrSymbols(styear1.c_str()) == false || check.checkNoLettersOrSymbols(styear2.c_str()) == false || year1 > year2) {
        cout << "\nНеверный ввод! Введите 2 числа через пробел, первое число меньше второго ...\n";
        Sleep(1500);
        system("cls");
        return;
    }
    StudentNode* current = list->getMyHead();
    cout << endl;	cout.width(176); cout.fill('-'); cout << "-" << endl;
    cout.fill(' '); cout.width(174);  cout << left << "|Список студентов, у которых меньше 25% троект за все время: "; cout << "|" << endl;
    cout.width(175); cout.fill('-'); cout << "-" << endl;
    cout.fill(' ');
    cout << left << "|"; myCentr("ID", 16);
    cout << left << "|"; myCentr("Фамилия", 20);
    cout << left << "|"; myCentr("Имя", 20);
    cout << left << "|"; myCentr("Отчество", 20);
    cout << left << "|"; myCentr("Дата Рожд.", 17);
    cout << left << "|"; myCentr("Пол", 4);
    cout << left << "|"; myCentr("Факультет", 10);
    cout << left << "|"; myCentr("Кафедра", 10);
    cout << left << "|"; myCentr("Группа", 16);
    cout << left << "|"; myCentr("Поступил в", 10);
    cout << left << "|"; myCentr("Семестер #", 10);
    cout << " |" << endl;
    cout.width(175); cout.fill('-'); cout << "-" << endl;
    while (current != nullptr) {
        float result = static_cast<float>(current->data.getCounterOf3Mark()) / current->data.getCounterOfLessons();
        if (result < 0.25 && current->data.getDateBirthday().year >= year1 && current->data.getDateBirthday().year <= year2) {
            cout.fill(' ');
            cout << left << "|"; cout.width(17); cout << left << current->data.getID();
            cout << left << "|"; cout.width(20); cout << left << current->data.getSurname();
            cout << left << "|"; cout.width(20); cout << left << current->data.getName();
            cout << left << "|"; cout.width(21); cout << left << current->data.getPatronymic();
            cout << left << "|";
            printDate(current->data.getDateBirthday().day, current->data.getDateBirthday().month, current->data.getDateBirthday().year, 10);
            cout << left << "|"; cout.width(4); cout << left << current->data.getGender();
            cout << left << "|"; cout.width(11); cout << left << current->data.getFaculty();
            cout << left << "|"; cout.width(10); cout << left << current->data.getDepartment();
            cout << left << "|"; cout.width(17); cout << left << current->data.getGroup();
            cout << left << "|"; cout.width(12); cout << left << current->data.getAdmissionYear();
            cout << left << "|"; cout.width(12); cout << left << current->data.getCurrentSemestr(); cout << " |" << endl;
            cout << left << "|"; cout << left << "Количество троек: " << left << current->data.getCounterOf3Mark() << left
                << " Всего оценок: " << left << current->data.getCounterOfLessons(); cout.width(139); cout <<right << "|" << endl;
            cout << left << "|";
            for (int i = 0; i < current->data.getCurrentSemestr(); i++) {
                cout << i + 1 << "-й семестер: ";
                for (int j = 0; j < current->data.semesters[i].counter_lessons; j++) {
                    cout << current->data.semesters[i].subjects[j] << ' '
                        << current->data.semesters[i].marks[j] << ' ';
                }
                cout << '\n' << left << '|';
            }
            cout.width(175); cout.fill('-'); cout << "-" << endl;
        }
        current = current->next;
    }
    cout << "\nВернуться в меню? Нажмите любую клавишу";
    getchar();
    getchar();
    system("cls");
}

int Start(StudentList* List) {
    int command;
    cout << "Выберите действие : \n(0) Выход из программы\n(1) Распечатать всех студентов\n(2) Добавление данных\n" <<
        "(3) Изменение данных\n(4) Удаление данных\n(5) Задание";
;
    cout << "\nВведите комманду: " << endl;
    cin >> command;
    int flag = 1;
    switch (command) {
    case 0:
        flag = 0;
        break;
    case 1:
        cout << "Draw" << endl;
        Sleep(1500);
        Draw(List);
        break;
    case 2:
        cout << "Add" << endl;
        Sleep(1500);
        system("cls");
        NewStudent(List);
        break;
    case 3:
        cout << "Edit" << endl;
        Sleep(1500);
        system("cls");
        EditStudent(List);
        break;
    case 4:
        cout << "Delete" << endl;
        Sleep(1500);
        DeleteStudent(List);
        break;
    case 5:
        cout << "Do the task" << endl;
        Sleep(1500);
        DrawTask89(List);
        break;
    }
    return flag;
}

int Student::counter_students = 0;

int main() {
    setlocale(LC_ALL, "Russian");
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    CryptoTools crypt("data.dat");
    crypt.decrypt();
    StudentList list;
    ReadStream(&list);
    int flag;
    while (true) {
        system("cls");
        flag = Start(&list);
        if (flag == 0) { break; }
    }
    WriteStream(&list);
    string pass = crypt.generatePassword();
    bool flag2 = crypt.encrypt(pass);
    if (flag2) { cout << "Файл успешно зашифрован!"; }
    else { cout << "Ошибка шифровки файла!"; return 1; }
    return 0;
}