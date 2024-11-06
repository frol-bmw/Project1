#include <iostream>
#include <clocale>

using namespace std;


int main() {
    setlocale(LC_ALL, "Russian");
    Notebook notebook;
    int year, month, day;
    string entry;
    char choice;
    //Ввод записей
    do {
        cout << "Введите год: ";
        cin >> year;
        cout << "Введите месяц: ";
        cin >> month;
        cout << "Введите день: ";
        cin >> day;

        cout << "Введите запись: ";
        cin.ignore(); 
        getline(cin, entry);

        notebook.addEntry(year, month, day, entry);

        cout << "Хотите добавить еще одну запись? (y/n): ";
        cin >> choice;

    } while (choice == 'y' || choice == 'Y');

    //Просмотр записей
    do {
        cout << "Введите год для просмотра записи: ";
        cin >> year;
        cout << "Введите месяц для просмотра записи: ";
        cin >> month;
        cout << "Введите день для просмотра записи: ";
        cin >> day;

        notebook.viewEntry(year, month, day);

        cout << "Хотите просмотреть другую запись? (y/n): ";
        cin >> choice;

    } while (choice == 'y' || choice == 'Y');

    return 0;
}
