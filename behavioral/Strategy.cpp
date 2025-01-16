#include <iostream>
#include <vector>
#include <memory>

// Интерфейс стратегии
class SortStrategy {
public:
    virtual void sort(std::vector<int>& data) = 0; // Метод для сортировки
    virtual ~SortStrategy() {}
};

// Конкретная стратегия (Сортировка пузырьком)
class BubbleSort : public SortStrategy {
public:
    void sort(std::vector<int>& data) override {
        for (size_t i = 0; i < data.size() - 1; ++i) {
            for (size_t j = 0; j < data.size() - i - 1; ++j) {
                if (data[j] > data[j + 1]) {
                    std::swap(data[j], data[j + 1]); // Меняем местами
                }
            }
        }
        std::cout << "Sorted using Bubble Sort." << std::endl;
    }
};

// Конкретная стратегия (Сортировка выбором)
class SelectionSort : public SortStrategy {
public:
    void sort(std::vector<int>& data) override {
        for (size_t i = 0; i < data.size() - 1; ++i) {
            size_t minIndex = i;
            for (size_t j = i + 1; j < data.size(); ++j) {
                if (data[j] < data[minIndex]) {
                    minIndex = j; // Находим индекс минимального элемента
                }
            }
            std::swap(data[i], data[minIndex]); // Меняем местами
        }
        std::cout << "Sorted using Selection Sort." << std::endl;
    }
};

// Контекст
class Sorter {
public:
    Sorter(std::shared_ptr<SortStrategy> strategy) : strategy_(strategy) {}

    void setStrategy(std::shared_ptr<SortStrategy> strategy) {
        strategy_ = strategy; // Устанавливаем новую стратегию
    }

    void sort(std::vector<int>& data) {
        strategy_->sort(data); // Делегируем вызов стратегии
    }

private:
    std::shared_ptr<SortStrategy> strategy_; // Текущая стратегия
};

// Клиентский код
int main() {
    std::vector<int> data = {5, 3, 8, 6, 2};

    // Используем сортировку пузырьком
    Sorter sorter(std::make_shared<BubbleSort>());
    sorter.sort(data);

    // Выводим отсортированный массив
    for (int num : data) {
        std::cout << num << " ";
    }
    std::cout << std::endl;

    // Меняем стратегию на сортировку выбором
    data = {5, 3, 8, 6, 2}; // Сбрасываем данные
    sorter.setStrategy(std::make_shared<SelectionSort>());
    sorter.sort(data);

    // Выводим отсортированный массив
    for (int num : data) {
        std::cout << num << " ";
    }
    std::cout << std::endl;

    return 0;
}