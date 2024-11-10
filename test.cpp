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

 do {
        std::cout << "\nМеню управления задачами:\n";
        std::cout << "1. Добавить задачу\n";
        std::cout << "2. Редактировать задачу\n";
        std::cout << "3. Показать задачи\n";
        std::cout << "4. Выход\n";
        std::cout << "Введите ваш выбор: ";
        std::cin >> choice;

        if (choice == 1) {
            std::string description, deadline;
            int priority;
            std::cout << "Введите описание задачи: ";
            std::cin.ignore(); // Игнорируем символ новой строки, оставшийся в буфере
            std::getline(std::cin, description);
            std::cout << "Введите срок выполнения: ";
            std::getline(std::cin, deadline);
            std::cout << "Введите приоритет (1-5): ";
            std::cin >> priority;
            manager.addTask(description, deadline, priority);
        } else if (choice == 2) {
            int index;
            std::string description, deadline;
            int priority;
            std::cout << "Введите индекс задачи для редактирования: ";
            std::cin >> index;
            std::cout << "Введите новое описание задачи: ";
            std::cin.ignore();
            std::getline(std::cin, description);
            std::cout << "Введите новый срок выполнения: ";
            std::getline(std::cin, deadline);
            std::cout << "Введите новый приоритет (1-5): ";
            std::cin >> priority;
            manager.editTask(index - 1, description, deadline, priority);
        } else if (choice == 3) {
            manager.displayTasks();
        }
    } while (choice != 4);
