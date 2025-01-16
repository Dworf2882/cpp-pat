#include <iostream>
#include <memory>
#include <string>

// Интерфейс прототипа
class Shape {
public:
    virtual std::unique_ptr<Shape> clone() const = 0; // Метод клонирования
    virtual void draw() const = 0; // Метод рисования
    virtual ~Shape() {}
};

// Конкретный прототип: Круг
class Circle : public Shape {
public:
    Circle() {
        std::cout << "Circle created" << std::endl;
    }

    std::unique_ptr<Shape> clone() const override {
        return std::make_unique<Circle>(*this); // Клонирование круга
    }

    void draw() const override {
        std::cout << "Drawing a Circle" << std::endl;
    }
};

// Конкретный прототип: Квадрат
class Square : public Shape {
public:
    Square() {
        std::cout << "Square created" << std::endl;
    }

    std::unique_ptr<Shape> clone() const override {
        return std::make_unique<Square>(*this); // Клонирование квадрата
    }

    void draw() const override {
        std::cout << "Drawing a Square" << std::endl;
    }
};

// Клиентский код
int main() {
    // Создаем прототипы
    std::unique_ptr<Shape> circlePrototype = std::make_unique<Circle>();
    std::unique_ptr<Shape> squarePrototype = std::make_unique<Square>();

    // Клонируем фигуры
    std::unique_ptr<Shape> circleClone = circlePrototype->clone();
    std::unique_ptr<Shape> squareClone = squarePrototype->clone();

    // // Рисуем клонированные фигуры
    circleClone->draw();
    squareClone->draw();

    return 0;
}