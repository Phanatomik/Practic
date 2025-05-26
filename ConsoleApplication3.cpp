#include <iostream>
#include <vector>
#include <ctime>
#include <cstdlib>
#include <iomanip>
#include <cmath>
using namespace std;

// Структура для статистики сортировки
struct SortStats {
    long long comparisons = 0;
    long long swaps = 0;
};

// Функция пузырьковой сортировки
void bubbleSort(vector<int>& arr, SortStats* stats) {
    int n = arr.size();
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            stats->comparisons++;
            if (arr[j] > arr[j + 1]) {
                swap(arr[j], arr[j + 1]);
                stats->swaps++;
            }
        }
    }
}

// Функция сортировки вставками
void insertionSort(vector<int>& arr, SortStats& stats) {
    int n = arr.size();
    for (int i = 1; i < n; i++) {
        int key = arr[i];
        int j = i - 1;
        stats.comparisons++; // Первое сравнение
        while (j >= 0 && arr[j] > key) {
            arr[j + 1] = arr[j];
            stats.swaps++;
            j--;
            if (j >= 0) stats.comparisons++;
        }
        arr[j + 1] = key;
    }
}

// Функция генерации случайного массива
vector<int> generateArray(int size, int minVal = 0, int maxVal = 10000) {
    vector<int> arr(size);
    for (int i = 0; i < size; i++)
        arr[i] = minVal + rand() % (maxVal - minVal + 1);
    return arr;
}

// Красивая печать массива
void printArray(const vector<int>& arr) {
    int show = min(20, (int)arr.size());
    for (int i = 0; i < show; i++)
        cout << arr[i] << " ";
    if (arr.size() > show) cout << "...";
    cout << endl;
}

int main() {
    setlocale(LC_ALL, "Russian");
    srand(time(0));

    // Заданные размеры массивов
    vector<int> sizes = { 61, 141, 325, 747, 1720, 3956, 9100 };

    cout << "Сравнение пузырьковой сортировки и сортировки вставками" << endl;
    cout << "-------------------------------------------------------" << endl;
    cout << setw(7) << "Размер"
        << setw(15) << "Пуз. сравнения"
        << setw(15) << "Пуз. перест."
        << setw(15) << "Вст. сравнения"
        << setw(15) << "Вст. перест." << endl;

    // Эксперименты с разными размерами
    for (int size : sizes) {
        // 1. Генерируем исходный массив
        vector<int> arr = generateArray(size);

        // 2. Копируем массивы для каждой сортировки
        vector<int> bubbleArr = arr;
        vector<int> insertArr = arr;

        // 3. Статистика
        SortStats bubbleStats, insertStats;

        // 4. Сортируем
        bubbleSort(bubbleArr, &bubbleStats);          // Через указатель
        insertionSort(insertArr, insertStats);        // Через ссылку

        // 5. Выводим статистику
        cout << setw(7) << size
            << setw(15) << bubbleStats.comparisons
            << setw(15) << bubbleStats.swaps
            << setw(15) << insertStats.comparisons
            << setw(15) << insertStats.swaps << endl;

        // 6. Для первого размера показать массивы
        if (size == sizes[0]) {
            cout << "\nИсходный массив (" << size << "): ";
            printArray(arr);

            cout << "Отсортирован пузырьком: ";
            printArray(bubbleArr);

            cout << "Отсортирован вставками: ";
            printArray(insertArr);
            cout << endl;
        }
    }

    cout << endl;
    return 0;
}