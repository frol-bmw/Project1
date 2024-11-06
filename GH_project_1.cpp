#include <iostream>
#include <clocale>

using namespace std;


int main() {
    setlocale(LC_CTYPE, "rus");
    Notebook notebook;
    int year, month, day;
    string entry;
    char choice;
    //¬вод записей
    do {
        cout << "¬ведите год: ";
        cin >> year;
        cout << "¬ведите мес€ц: ";
        cin >> month;
        cout << "¬ведите день: ";
        cin >> day;

        cout << "¬ведите запись: ";
        cin.ignore(); 
        getline(cin, entry);

        notebook.addEntry(year, month, day, entry);

        cout << "’отите добавить еще одну запись? (y/n): ";
        cin >> choice;

    } while (choice == 'y' || choice == 'Y');

    //ѕросмотр записей
    do {
        cout << "¬ведите год дл€ просмотра записи: ";
        cin >> year;
        cout << "¬ведите мес€ц дл€ просмотра записи: ";
        cin >> month;
        cout << "¬ведите день дл€ просмотра записи: ";
        cin >> day;

        notebook.viewEntry(year, month, day);

        cout << "’отите просмотреть другую запись? (y/n): ";
        cin >> choice;

    } while (choice == 'y' || choice == 'Y');

    return 0;
}