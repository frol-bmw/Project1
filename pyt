import tkinter as tk
from tkinter import messagebox
from datetime import datetime

# Функция для преобразования даты в строку
def format_date(date):
    return date.strftime('%Y-%m-%d %H:%M')

# Класс для представления одной задачи
class Task:
    def __init__(self, description, category, priority, deadline):
        self.description = description
        self.category = category
        self.priority = priority
        self.deadline = deadline

# Главная форма приложения
class TaskManager(tk.Frame):
    def __init__(self, master=None):
        super().__init__(master)
        self.master = master
        self.pack()
        self.create_widgets()

    def create_widgets(self):
        # Список задач
        self.task_list = tk.Listbox(self)
        self.task_list.pack(side='left', fill='both', expand=True)

        # Кнопки управления задачами
        control_frame = tk.Frame(self)
        control_frame.pack(side='right', fill='y')

        add_button = tk.Button(control_frame, text='Добавить задачу', command=self.add_task)
        add_button.pack(fill='x', pady=5)

        edit_button = tk.Button(control_frame, text='Редактировать задачу', command=self.edit_task)
        edit_button.pack(fill='x', pady=5)

        delete_button = tk.Button(control_frame, text='Удалить задачу', command=self.delete_task)
        delete_button.pack(fill='x', pady=5)

        records_button = tk.Button(control_frame, text='Записи', command=self.records)
        records_button.pack(fill='x', pady=5)

        view_button = tk.Button(control_frame, text='Просмотреть задачи', command=self.view_tasks)
        view_button.pack(fill='x', pady=5)

        # Загружаем существующие задачи
        self.load_tasks()

    def load_tasks(self):
        # Здесь нужно загрузить задачи из файла или базы данных
        tasks = [
            Task('Задача 1', 'Работа', 1, datetime.now()),
            Task('Задача 2', 'Личное', 2, datetime.now()),
            Task('Задача 3', 'Другое', 3, datetime.now()),
        ]

        for task in tasks:
            self.task_list.insert('end', f'{task.description} ({task.category}, {format_date(task.deadline)})')

    def add_task(self):
        AddTaskDialog(self)

    def edit_task(self):
        selected_index = self.task_list.curselection()
        if len(selected_index) > 0:
            selected_task = self.task_list.get(selected_index[0])
            parts = selected_task.split('(', maxsplit=1)[0].strip()
            EditTaskDialog(parts, self)

    def delete_task(self):
        selected_index = self.task_list.curselection()
        if len(selected_index) > 0:
            confirm = messagebox.askyesno('Подтверждение', 'Вы уверены, что хотите удалить задачу?')
            if confirm:
                self.task_list.delete(selected_index[0])

    def records(self):
        RecordsDialog(self)

    def view_tasks(self):
        ViewTasksDialog(self)

# Диалоговое окно для добавления задачи
class AddTaskDialog(tk.Toplevel):
    def __init__(self, parent):
        super().__init__(parent)
        self.parent = parent
        self.title('Добавить задачу')
        self.create_widgets()

    def create_widgets(self):
        # Поле для описания задачи
        description_label = tk.Label(self, text='Описание:')
        description_label.grid(row=0, column=0, sticky='w')
        self.description_entry = tk.Entry(self)
        self.description_entry.grid(row=0, column=1, padx=10, pady=5)

        # Выбор категории
        category_label = tk.Label(self, text='Категория:')
        category_label.grid(row=1, column=0, sticky='w')
        self.category_var = tk.StringVar(value='Работа')
        categories = ['Работа', 'Личное', 'Другое']
        self.category_menu = tk.OptionMenu(self, self.category_var, *categories)
        self.category_menu.grid(row=1, column=1, padx=10, pady=5)

        # Выбор приоритета
        priority_label = tk.Label(self, text='Приоритет:')
        priority_label.grid(row=2, column=0, sticky='w')
        priorities = [str(i) for i in range(1, 6)]
        self.priority_var = tk.IntVar(value=1)
        self.priority_menu = tk.OptionMenu(self, self.priority_var, *priorities)
        self.priority_menu.grid(row=2, column=1, padx=10, pady=5)

        # Дата дедлайна
        deadline_label = tk.Label(self, text='Дедлайн:')
        deadline_label.grid(row=3, column=0, sticky='w')
        self.deadline_entry = tk.Entry(self)
        self.deadline_entry.grid(row=3, column=1, padx=10, pady=5)

        # Кнопки подтверждения и отмены
        button_frame = tk.Frame(self)
        button_frame.grid(row=4, columnspan=2, pady=10)

        ok_button = tk.Button(button_frame, text='ОК', command=self.ok_pressed)
        ok_button.pack(side='left', padx=5)

        cancel_button = tk.Button(button_frame, text='Отмена', command=self.destroy)
        cancel_button.pack(side='left', padx=5)

    def ok_pressed(self):
        description = self.description_entry.get()
        category = self.category_var.get()
        priority = self.priority_var.get()
        deadline = self.deadline_entry.get()

        new_task = Task(description, category, priority, datetime.strptime(deadline, '%Y-%m-%d %H:%M'))
        self.parent.task_list.insert('end', f'{new_task.description} ({new_task.category}, {format_date(new_task.deadline)})')
        self.destroy()

# Диалоговое окно для редактирования задачи
class EditTaskDialog(AddTaskDialog):
    def __init__(self, task_description, parent):
        super().__init__(parent)
        self.title('Редактировать задачу')
        self.description_entry.insert(0, task_description)

    def ok_pressed(self):
        edited_description = self.description_entry.get()
        self.parent.task_list.delete(self.parent.task_list.curselection()[0])
        self.parent.task_list.insert(self.parent.task_list.curselection()[0], edited_description)
        self.destroy()

# Диалоговое окно для ведения записей
class RecordsDialog(tk.Toplevel):
    def __init__(self, parent):
        super().__init__(parent)
        self.parent = parent
        self.title('Записи')
        self.create_widgets()

    def create_widgets(self):
        record_text = tk.Text(self, height=15, width=50)
        record_text.pack(padx=10, pady=10)

        close_button = tk.Button(self, text='Закрыть', command=self.destroy)
        close_button.pack(pady=5)

# Диалоговое окно для ведения записей
class RecordsDialog(tk.Toplevel):
    def __init__(self, parent):
        super().__init__(parent)
        self.parent = parent
        self.title('Записи')
        self.create_widgets()

    def create_widgets(self):
        self.record_text = tk.Text(self, height=15, width=50)
        self.record_text.pack(padx=10, pady=10)

        add_button = tk.Button(self, text='Добавить запись', command=self.add_record)
        add_button.pack(pady=5)

        close_button = tk.Button(self, text='Закрыть', command=self.destroy)
        close_button.pack(pady=5)

    def add_record(self):
        record = self.record_text.get('1.0', tk.END)
        if record.strip():
            with open('records.txt', 'a', encoding='utf-8') as file:
                file.write(record + '\n')
            self.record_text.delete('1.0', tk.END)
            messagebox.showinfo('Запись добавлена', 'Запись успешно добавлена.')
        else:
            messagebox.showerror('Ошибка', 'Запись не может быть пустой.')


# Диалоговое окно для ведения записей
class RecordsDialog(tk.Toplevel):
    def __init__(self, parent):
        super().__init__(parent)
        self.parent = parent
        self.title('Записи')
        self.create_widgets()

    def create_widgets(self):
        self.record_text = tk.Text(self, height=15, width=50)
        self.record_text.pack(padx=10, pady=10)

        add_button = tk.Button(self, text='Добавить запись', command=self.add_record)
        add_button.pack(pady=5)

        view_button = tk.Button(self, text='Просмотреть записи', command=self.view_records)
        view_button.pack(pady=5)

        delete_button = tk.Button(self, text='Удалить запись', command=self.delete_record)
        delete_button.pack(pady=5)

        close_button = tk.Button(self, text='Закрыть', command=self.destroy)
        close_button.pack(pady=5)

    def add_record(self):
        record = self.record_text.get('1.0', tk.END)
        if record.strip():
            with open('records.txt', 'a', encoding='utf-8') as file:
                file.write(record + '\n')
            self.record_text.delete('1.0', tk.END)
            messagebox.showinfo('Запись добавлена', 'Запись успешно добавлена.')
        else:
            messagebox.showerror('Ошибка', 'Запись не может быть пустой.')

    def view_records(self):
        try:
            with open('records.txt', 'r', encoding='utf-8') as file:
                records = file.read()
                self.record_text.delete('1.0', tk.END)
                self.record_text.insert('1.0', records)
        except FileNotFoundError:
            messagebox.showerror('Ошибка', 'Записи не найдены.')

    def delete_record(self):
        try:
            with open('records.txt', 'r', encoding='utf-8') as file:
                records = file.readlines()
            if records:
                records.pop(0)  # Удаляем первую запись
                with open('records.txt', 'w', encoding='utf-8') as file:
                    file.writelines(records)
                messagebox.showinfo('Запись удалена', 'Первая запись успешно удалена.')
            else:
                messagebox.showerror('Ошибка', 'Записи не найдены.')
        except FileNotFoundError:
            messagebox.showerror('Ошибка', 'Записи не найдены.')






# Запуск приложения
if __name__ == '__main__':
    root = tk.Tk()
    root.title('Менеджер задач')
    root.geometry('800x600')
    app = TaskManager(master=root)
    app.mainloop()
