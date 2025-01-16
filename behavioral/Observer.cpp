#include <iostream>
#include <vector>
#include <memory>

// Интерфейс наблюдателя
class Observer {
public:
    virtual void update(float temperature) = 0; // Метод для обновления состояния
    virtual ~Observer() {}
};

// Интерфейс субъекта
class Subject {
public:
    virtual void addObserver(std::shared_ptr<Observer> observer) = 0; // Добавление наблюдателя
    virtual void removeObserver(std::shared_ptr<Observer> observer) = 0; // Удаление наблюдателя
    virtual void notifyObservers() = 0; // Уведомление наблюдателей
    virtual ~Subject() {}
};

// Конкретный субъект (Метеостанция)
class WeatherStation : public Subject {
public:
    void addObserver(std::shared_ptr<Observer> observer) override {
        observers_.push_back(observer); // Добавляем наблюдателя
    }

    void removeObserver(std::shared_ptr<Observer> observer) override {
        observers_.erase(std::remove(observers_.begin(), observers_.end(), observer), observers_.end()); // Удаляем наблюдателя
    }

    void notifyObservers() override {
        for (const auto& observer : observers_) {
            observer->update(temperature_); // Уведомляем всех наблюдателей
        }
    }

    void setTemperature(float temperature) {
        temperature_ = temperature; // Устанавливаем новую температуру
        notifyObservers(); // Уведомляем наблюдателей об изменении
    }

private:
    std::vector<std::shared_ptr<Observer>> observers_; // Список наблюдателей
    float temperature_; // Текущая температура
};

// Конкретный наблюдатель (Дисплей)
class Display : public Observer {
public:
    void update(float temperature) override {
        std::cout << "Current temperature: " << temperature << "°C" << std::endl; // Обновляем состояние
    }
};

// Клиентский код
int main() {
    auto weatherStation = std::make_shared<WeatherStation>();
    auto display = std::make_shared<Display>();

    weatherStation->addObserver(display); // Добавляем дисплей как наблюдателя

    // Изменяем температуру
    weatherStation->setTemperature(25.0f);
    weatherStation->setTemperature(30.0f);

    return 0;
}