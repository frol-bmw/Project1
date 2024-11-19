#include <iostream>
#include <vector>
#include <string>
#include <algorithm> // for sort
#include <ctime>    // for time_t

using namespace std;

struct Task {
    string description;
    string category;

    int priority; // 1: low, 2: medium, 3: high
    time_t deadline; // Unix timestamp
};


void addTask(vector<Task>& tasks) {
    Task newTask;
    cout << "Описание задачи: ";
    getline(cin >> ws, newTask.description); 

    cout << "Категория: ";
    getline(cin >> ws, newTask.category);

    cout << "Приоритет (1-низкий, 2-средний, 3-высокий): ";
    cin >> newTask.priority;
    cin.ignore(); // очищаем буфер после cin

    cout << "Срок выполнения (ДД.ММ.ГГГГ): ";
    string dateStr;
    getline(cin >> ws, dateStr);
    //  Преобразование строки даты в time_t - упрощенное, без проверки формата
    //В реальном приложении нужна более надежная обработка даты!
    int day, month, year;
    sscanf(dateStr.c_str(), "%d.%d.%d", &day, &month, &year);
    tm tm_deadline = {0, 0, 0, day, month - 1, year - 1900}; //month -1, year -1900
    newTask.deadline = mktime(&tm_deadline);


    tasks.push_back(newTask);
    cout << "Задача добавлена!\n";
}

void printTasks(const vector<Task>& tasks) {
    if (tasks.empty()) {
        cout << "Нет задач.\n";
        return;
    }
    for (const auto& task : tasks) {
        cout << "Описание задачи: " << task.description << endl;
        cout << "Категория: " << task.category << endl;
     
        cout << "Приоритет: " << task.priority << endl;
        cout << "Срок: " << ctime(&task.deadline); 
        cout << "----\n";
    }
}

int main() {
    vector<Task> tasks;
    int choice;

    do {
        cout << "\nМеню:\n";
        cout << "1. Добавить задачу\n";
        cout << "2. Вывести задачи\n";
        cout << "0. Выход\n";
        cout << "Выбор: ";
        cin >> choice;
        cin.ignore(); // очищаем буфер после cin

        switch (choice) {
            case 1: addTask(tasks); break;
            case 2: printTasks(tasks); break;
            case 0: cout << "До свидания!\n"; break;
            default: cout << "Неверный выбор.\n";
        }
    } while (choice != 0);

    return 0;
}
