#include <iostream>

// Абстрактный класс (Шаблонный метод)
class CaffeineBeverage {
public:
    // Шаблонный метод
    void prepareRecipe() {
        boilWater();
        brew();
        pourInCup();
        addCondiments();
    }

protected:
    virtual void brew() = 0; // Абстрактный метод для заваривания
    virtual void addCondiments() = 0; // Абстрактный метод для добавления приправ

private:
    void boilWater() {
        std::cout << "Boiling water." << std::endl; // Шаг 1: Кипятим воду
    }

    void pourInCup() {
        std::cout << "Pouring into cup." << std::endl; // Шаг 3: Наливаем в чашку
    }
};

// Конкретный класс (Чай)
class Tea : public CaffeineBeverage {
protected:
    void brew() override {
        std::cout << "Steeping the tea." << std::endl; // Шаг 2: Завариваем чай
    }

    void addCondiments() override {
        std::cout << "Adding lemon." << std::endl; // Добавляем лимон
    }
};

// Конкретный класс (Кофе)
class Coffee : public CaffeineBeverage {
protected:
    void brew() override {
        std::cout << "Dripping coffee through filter." << std::endl; // Шаг 2: Завариваем кофе
    }

    void addCondiments() override {
        std::cout << "Adding sugar and milk." << std::endl; // Добавляем сахар и молоко
    }
};

// Клиентский код
int main() {
    CaffeineBeverage* tea = new Tea();
    tea->prepareRecipe(); // Приготовление чая
    std::cout << std::endl;

    CaffeineBeverage* coffee = new Coffee();
    coffee->prepareRecipe(); // Приготовление кофе

    // Освобождаем память
    delete tea;
    delete coffee;

    return 0;
}