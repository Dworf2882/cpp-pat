#include <iostream>
#include <memory>
#include <string>

// Компонент
class Coffee {
public:
    virtual std::string getDescription() const = 0; // Метод для получения описания
    virtual double cost() const = 0; // Метод для получения стоимости
    virtual ~Coffee() {}
};

// Конкретный компонент (Простое кофе)
class SimpleCoffee : public Coffee {
public:
    std::string getDescription() const override {
        return "Simple coffee";
    }

    double cost() const override {
        return 2.0; // Стоимость простого кофе
    }
};

// Декоратор
class CoffeeDecorator : public Coffee {
public:
    CoffeeDecorator(std::shared_ptr<Coffee> coffee) : coffee_(coffee) {}

    std::string getDescription() const override {
        return coffee_->getDescription(); // Передаем вызов декорируемому объекту
    }

    double cost() const override {
        return coffee_->cost(); // Передаем вызов декорируемому объекту
    }

protected:
    std::shared_ptr<Coffee> coffee_; // Указатель на декорируемый объект
};

// Конкретный декоратор (Молоко)
class MilkDecorator : public CoffeeDecorator {
public:
    MilkDecorator(std::shared_ptr<Coffee> coffee) : CoffeeDecorator(coffee) {}

    std::string getDescription() const override {
        return coffee_->getDescription() + ", with milk"; // Добавляем описание
    }

    double cost() const override {
        return coffee_->cost() + 0.5; // Добавляем стоимость молока
    }
};

// Конкретный декоратор (Сахар)
class SugarDecorator : public CoffeeDecorator {
public:
    SugarDecorator(std::shared_ptr<Coffee> coffee) : CoffeeDecorator(coffee) {}

    std::string getDescription() const override {
        return coffee_->getDescription() + ", with sugar"; // Добавляем описание
    }

    double cost() const override {
        return coffee_->cost() + 0.2; // Добавляем стоимость сахара
    }
};

// Клиентский код
int main() {
    // Создаем простое кофе
    std::shared_ptr<Coffee> coffee = std::make_shared<SimpleCoffee>();
    std::cout << coffee->getDescription() << " costs $" << coffee->cost() << std::endl;

    // Добавляем молоко
    coffee = std::make_shared<MilkDecorator>(coffee);
    std::cout << coffee->getDescription() << " costs $" << coffee->cost() << std::endl;

    // Добавляем сахар
    coffee = std::make_shared<SugarDecorator>(coffee);
    std::cout << coffee->getDescription() << " costs $" << coffee->cost() << std::endl;

    return 0;
}