#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <ctime>
#include <sstream>
#include <iomanip>

using namespace std;

struct Task {
    string description;
    string category;
    int priority;
    time_t deadline;
};

//Improved date parsing with error handling
time_t parseDate(const string& dateStr) {
    tm tm_deadline;
    strptime(dateStr.c_str(), "%d.%m.%Y", &tm_deadline); 
    return mktime(&tm_deadline);
}


void addTask(vector<Task>& tasks) {
    Task newTask;
    cout << "Описание задачи: ";
    getline(cin >> ws, newTask.description);
    cout << "Категория: ";
    getline(cin >> ws, newTask.category);
    cout << "Приоритет (1-низкий, 2-средний, 3-высокий): ";
    cin >> newTask.priority;
    cin.ignore(); 

    string dateStr;
    while (true){ 
        cout << "Срок выполнения (ДД.ММ.ГГГГ): ";
        getline(cin >> ws, dateStr);
        newTask.deadline = parseDate(dateStr);
        if (newTask.deadline != -1) break;
        cerr << "Неверный формат даты. Попробуйте снова.\n";
    }

    tasks.push_back(newTask);
    cout << "Задача добавлена!\n";
}


void printTasks(const vector<Task>& tasks) {
    if (tasks.empty()) {
        cout << "Нет задач.\n";
        return;
    }
    for (const auto& task : tasks) {
        cout << "Описание Задачи: " << task.description << endl;
        cout << "Категория: " << task.category << endl;
        cout << "Приоритет: " << task.priority << endl;
        char buffer[80];
        strftime(buffer, 80, "%d.%m.%Y", localtime(&task.deadline));
        cout << "Срок: " << buffer << endl;
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
        cin.ignore(); 
        switch (choice) {
            case 1: addTask(tasks); break;
            case 2: printTasks(tasks); break;
            case 0: cout << "До свидания!\n"; break;
            default: cout << "Неверный выбор.\n";
        }
    } while (choice != 0);
    return 0;
}
