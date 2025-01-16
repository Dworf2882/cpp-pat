#include <iostream>
#include <memory>
#include <vector>
#include <cmath>

// Впереди объявляем классы
class Circle;
class Rectangle;

// Интерфейс посетителя
class ShapeVisitor {
public:
    virtual void visit(const std::shared_ptr<Circle>& circle) = 0; // Метод для обработки круга
    virtual void visit(const std::shared_ptr<Rectangle>& rectangle) = 0; // Метод для обработки прямоугольника
    virtual ~ShapeVisitor() {}
};

// Интерфейс элемента
class Shape {
public:
    virtual void accept(const std::shared_ptr<ShapeVisitor>& visitor) = 0; // Метод для приема посетителя
    virtual ~Shape() {}
};

// Конкретный элемент (Круг)
class Circle : public Shape, public std::enable_shared_from_this<Circle> {
public:
    Circle(double radius) : radius_(radius) {}

    void accept(const std::shared_ptr<ShapeVisitor>& visitor) override {
        visitor->visit(shared_from_this()); // Передаем себя посетителю
    }

    double getRadius() const {
        return radius_;
    }

private:
    double radius_; // Радиус круга
};

// Конкретный элемент (Прямоугольник)
class Rectangle : public Shape, public std::enable_shared_from_this<Rectangle> {
public:
    Rectangle(double width, double height) : width_(width), height_(height) {}

    void accept(const std::shared_ptr<ShapeVisitor>& visitor) override {
        visitor->visit(shared_from_this()); // Передаем себя посетителю
    }

    double getWidth() const {
        return width_;
    }

    double getHeight() const {
        return height_;
    }

private:
    double width_;  // Ширина прямоугольника
    double height_; // Высота прямоугольника
};

// Конкретный посетитель (Вычисление площади)
class AreaVisitor : public ShapeVisitor {
public:
    void visit(const std::shared_ptr<Circle>& circle) override {
        double area = M_PI * circle->getRadius() * circle->getRadius();
        std::cout << "Area of Circle: " << area << std::endl;
    }

    void visit(const std::shared_ptr<Rectangle>& rectangle) override {
        double area = rectangle->getWidth() * rectangle->getHeight();
        std::cout << "Area of Rectangle: " << area << std::endl;
    }
};

// Конкретный посетитель (Вычисление периметра)
class PerimeterVisitor : public ShapeVisitor {
public:
    void visit(const std::shared_ptr<Circle>& circle) override {
        double perimeter = 2 * M_PI * circle->getRadius();
        std::cout << "Perimeter of Circle: " << perimeter << std::endl;
    }

    void visit(const std::shared_ptr<Rectangle>& rectangle) override {
        double perimeter = 2 * (rectangle->getWidth() + rectangle->getHeight());
        std::cout << "Perimeter of Rectangle: " << perimeter << std::endl;
    }
};

// Клиентский код
int main() {
    std::vector<std::shared_ptr<Shape>> shapes;
    shapes.push_back(std::make_shared<Circle>(5.0)); // Круг с радиусом 5
    shapes.push_back(std::make_shared<Rectangle>(4.0, 6.0)); // Прямоугольник 4x6

    AreaVisitor areaVisitor;
    PerimeterVisitor perimeterVisitor;

    // Вычисляем площади всех фигур
    for (const auto& shape : shapes) {
        shape->accept(std::make_shared<AreaVisitor>(areaVisitor));
    }

    std::cout << std::endl;

    // Вычисляем периметры всех фигур
    for (const auto& shape : shapes) {
        shape->accept(std::make_shared<PerimeterVisitor>(perimeterVisitor));
    }

    return 0;
}