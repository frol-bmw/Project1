#include <iostream>
#include <clocale>

using namespace std;


int main() {
    setlocale(LC_CTYPE, "rus");
    Notebook notebook;
    int year, month, day;
    string entry;
    char choice;
    //���� �������
    do {
        cout << "������� ���: ";
        cin >> year;
        cout << "������� �����: ";
        cin >> month;
        cout << "������� ����: ";
        cin >> day;

        cout << "������� ������: ";
        cin.ignore(); 
        getline(cin, entry);

        notebook.addEntry(year, month, day, entry);

        cout << "������ �������� ��� ���� ������? (y/n): ";
        cin >> choice;

    } while (choice == 'y' || choice == 'Y');

    //�������� �������
    do {
        cout << "������� ��� ��� ��������� ������: ";
        cin >> year;
        cout << "������� ����� ��� ��������� ������: ";
        cin >> month;
        cout << "������� ���� ��� ��������� ������: ";
        cin >> day;

        notebook.viewEntry(year, month, day);

        cout << "������ ����������� ������ ������? (y/n): ";
        cin >> choice;

    } while (choice == 'y' || choice == 'Y');

    return 0;
}