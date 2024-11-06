#include <iostream>

int main()
{
using namespace std;
struct Task {
    string title;
    string description;
    string category;
    int priority; // 
    };

  void displayMenu() {
    cout << "Записная книжка" << endl;
    cout << "1. Добавить запись" << endl;
    cout << "2. Просмотреть записи" << endl;
    cout << "3. Изменить запись" << endl;
    cout << "4. Удалить запись" << endl;
    cout << "5. Сохранить в файл" << endl;
    cout << "6. Загрузить из файла" << endl;
    cout << "7. Выход" << endl;
 
}
void Zadaniedobavlenie(vector<Task>& tasks) {
    Task new1;
    cout << "Введите заголовок задачи: ";
    getline(cin, new1.title);
    cout << "Введите описание задачи: ";
    getline(cin, new1.description);
    cout << "Введите категорию задачи: ";
    getline(cin, new1.category);
    cout << "Введите приоритет задачи (1 - низкий, 2 - средний, 3 - высокий): ";
    cin >> newTask.priority;
}
