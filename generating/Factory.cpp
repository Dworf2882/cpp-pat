#include <iostream>
#include <memory>
#include <string>

// Интерфейс продукта
class Car {
public:
    virtual void drive() = 0; // Чисто виртуальный метод
    virtual ~Car() {}
};
// Конкретный продукт: Спортивный автомобиль
class SportsCar : public Car {
public:
    void drive() override {
        std::cout << "Driving a sports car!" << std::endl;
    }
};

// Конкретный продукт: Седан
class Sedan : public Car {
public:
    void drive() override {
        std::cout << "Driving a sedan!" << std::endl;
    }
};
// Интерфейс создателя
class CarFactory {
public:
    virtual std::unique_ptr<Car> createCar() = 0; // Чисто виртуальный метод
    virtual ~CarFactory() {}
};
// Конкретная фабрика для спортивных автомобилей
class SportsCarFactory : public CarFactory {
public:
    std::unique_ptr<Car> createCar() override {
        return std::make_unique<SportsCar>();
    }
};

// Конкретная фабрика для седанов
class SedanFactory : public CarFactory {
public:
    std::unique_ptr<Car> createCar() override {
        return std::make_unique<Sedan>();
    }
};
int main() {
    std::unique_ptr<CarFactory> factory;

    // Создаем спортивный автомобиль
    factory = std::make_unique<SportsCarFactory>();
    std::unique_ptr<Car> car1 = factory->createCar();
    car1->drive();

    // Создаем седан
    factory = std::make_unique<SedanFactory>();
    std::unique_ptr<Car> car2 = factory->createCar();
    car2->drive();

    return 0;
}