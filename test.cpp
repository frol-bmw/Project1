#include <windows.h>
#include <stdio.h>
#include <tchar.h>
#include <string>
#include <vector>
#include <map>
#include <ctime>

// Структура для хранения задачи
struct Task {
    std::string description;
    std::string category;
    int priority;
    SYSTEMTIME deadline;
};

// Функция для отображения сообщения об ошибке
void ShowErrorMessage(const TCHAR* message) {
    MessageBox(NULL, message, _T("Ошибка"), MB_OK | MB_ICONERROR);
}

// Функция для ввода данных задачи
bool InputTask(Task& task) {
    TCHAR desc[256], cat[256];
    int prio;

    // Описание задачи
    if (InputBox(_T("Описание задачи:"), desc, 255) <= 0) {
        return false;
    }
    task.description = desc;

    // Категория
    if (InputBox(_T("Категория:"), cat, 255) <= 0) {
        return false;
    }
    task.category = cat;

    // Приоритет
    if (InputBoxInt(_T("Приоритет (1-низкий, 2-средний, 3-высокий):"), &prio) <= 0) {
        return false;
    }
    task.priority = prio;

    // Срок выполнения
    SYSTEMTIME st;
    GetSystemTime(&st);
    while (true) {
        if (InputDate(_T("Срок выполнения (ДД.ММ.ГГГГ):"), &st) > 0) {
            task.deadline = st;
            break;
        } else {
            ShowErrorMessage(_T("Неверный формат даты. Попробуйте снова."));
        }
    }

    return true;
}

// Функция для печати списка задач
void PrintTasks(const std::vector<Task>& tasks) {
    if (tasks.empty()) {
        MessageBox(NULL, _T("Нет задач."), _T("Сообщение"), MB_OK | MB_ICONINFORMATION);
        return;
    }

    TCHAR buffer[1024];
    wsprintf(buffer, _T("Список задач:\n"));
    for (const auto& task : tasks) {
        wsprintf(buffer, _T("%sОписание задачи: %s\n"), buffer, task.description.c_str());
        wsprintf(buffer, _T("%sКатегория: %s\n"), buffer, task.category.c_str());
        wsprintf(buffer, _T("%sПриоритет: %d\n"), buffer, task.priority);
        SYSTEMTIME st = task.deadline;
        wsprintf(buffer, _T("%sСрок: %02d.%02d.%04d\n"), buffer, st.wDay, st.wMonth, st.wYear);
        wsprintf(buffer, _T("%s----\n"), buffer);
    }
    MessageBox(NULL, buffer, _T("Задачи"), MB_OK | MB_ICONINFORMATION);
}

// Функция для добавления записи
void AddEntry(std::map<SYSTEMTIME, std::string>& entries) {
    TCHAR date[11], entry[256];

    // Дата
    if (InputBox(_T("Дата (ДД.ММ.ГГГГ):"), date, 10) <= 0) {
        return;
    }

    // Запись
    if (InputBox(_T("Запись:"), entry, 255) <= 0) {
        return;
    }

    SYSTEMTIME st;
    if (ParseDate(date, &st)) {
        entries[st] = entry;
        MessageBox(NULL, _T("Запись добавлена!"), _T("Успешно"), MB_OK | MB_ICONINFORMATION);
    } else {
        ShowErrorMessage(_T("Неверный формат даты."));
    }
}

// Функция для просмотра записей по году
void ViewEntriesByYear(const std::map<SYSTEMTIME, std::string>& entries, int year) {
    TCHAR buffer[1024];
    wsprintf(buffer, _T("Записи за %d год:\n"), year);
    bool found = false;

    for (const auto& entry : entries) {
        if (entry.first.wYear == year) {
            wsprintf(buffer, _T("%s%02d.%02d.%04d: %s\n"), buffer,
                     entry.first.wDay, entry.first.wMonth, entry.first.wYear, entry.second.c_str());
            found = true;
        }
    }

    if (!found) {
        wsprintf(buffer, _T("Записей за %d год не найдено."), year);
    }

    MessageBox(NULL, buffer, _T("Записи"), MB_OK | MB_ICONINFORMATION);
}

// Вспомогательные функции для ввода данных
int InputBox(const TCHAR* prompt, TCHAR* buffer, int size) {
    return DialogBoxParam(GetModuleHandle(NULL), MAKEINTRESOURCE(IDD_INPUTBOX), NULL, InputBoxProc, (LPARAM)(LPVOID)prompt | ((LPARAM)(LPVOID)buffer << 16) | ((LPARAM)size << 24));
}

int InputBoxInt(const TCHAR* prompt, int* value) {
    TCHAR buffer[32];
    if (InputBox(prompt, buffer, 31) > 0) {
        *value = _ttoi(buffer);
        return 1;
    }
    return 0;
}

int InputDate(const TCHAR* prompt, SYSTEMTIME* st) {
    TCHAR buffer[11];
    if (InputBox(prompt, buffer, 10) > 0) {
        return ParseDate(buffer, st);
    }
    return 0;
}

BOOL CALLBACK InputBoxProc(HWND hDlg, UINT uMsg, WPARAM wParam, LPARAM lParam) {
    switch (uMsg) {
    case WM_INITDIALOG:
    {
        TCHAR* prompt = (TCHAR*)((lParam & 0xFFFF));
        TCHAR* buffer = (TCHAR*)(((lParam >> 16) & 0xFFFF));
        int size = (lParam >> 24);
        SetWindowText(hDlg, prompt);
        SetDlgItemText(hDlg, IDC_EDIT1, buffer);
        SendDlgItemMessage(hDlg, IDC_EDIT1, EM_LIMITTEXT, (WPARAM)size, 0);
        return TRUE;
    }
    case WM_COMMAND:
        if (LOWORD(wParam) == IDOK) {
            GetDlgItemText(hDlg, IDC_EDIT1, (TCHAR*)(HIWORD(lParam)), LOWORD(lParam));
            EndDialog(hDlg, IDOK);
        } else if (LOWORD(wParam) == IDCANCEL) {
            EndDialog(hDlg, IDCANCEL);
        }
        break;
    }
    return FALSE;
}

// Вспомогательная функция для разбора даты
BOOL ParseDate(TCHAR* date, SYSTEMTIME* st) {
    return SUCCEEDED(StringTimeToSystemTime(date, _T("%d.%m.%Y"), st));
}

// Основная функция программы
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd) {
    MSG msg;
    std::vector<Task> tasks;
    std::map<SYSTEMTIME, std::string> entries;

    while (GetMessage(&msg, NULL, 0, 0)) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    return msg.wParam;
}

// Ресурс диалога для ввода текста
#include <resource.h>

// Определение ресурса диалога для ввода текста
IDD_INPUTBOX DIALOGEX 0, 0, 180, 95
STYLE DS_SETFONT | DS_MODALFRAME | WS_POPUP | WS_CAPTION | WS_SYSMENU
CAPTION "Ввод"
FONT 8, "MS Shell Dlg"
BEGIN
    DEFPUSHBUTTON   "OK",IDOK,135,20,50,14
    PUSHBUTTON      "Отмена",IDCANCEL,135,40,50,14
    EDITTEXT        IDC_EDIT1,20,20,110,14,ES_AUTOHSCROLL
    LTEXT           "",IDC_STATIC,20,5,160,8
END
