#include <iostream>
#include <memory>
#include <string>
#include <sstream>
#include <vector>

// Абстрактное выражение
class Expression {
public:
    virtual int interpret() = 0; // Метод для интерпретации выражения
    virtual ~Expression() {}
};

// Конкретное выражение (число)
class Number : public Expression {
public:
    Number(int value) : value_(value) {}

    int interpret() override {
        return value_; // Возвращаем значение числа
    }

private:
    int value_;
};

// Конкретное выражение (операция сложения)
class Addition : public Expression {
public:
    Addition(std::shared_ptr<Expression> left, std::shared_ptr<Expression> right)
        : left_(left), right_(right) {}

    int interpret() override {
        return left_->interpret() + right_->interpret(); // Сложение
    }

private:
    std::shared_ptr<Expression> left_; // Левый операнд
    std::shared_ptr<Expression> right_; // Правый операнд
};

// Конкретное выражение (операция вычитания)
class Subtraction : public Expression {
public:
    Subtraction(std::shared_ptr<Expression> left, std::shared_ptr<Expression> right)
        : left_(left), right_(right) {}

    int interpret() override {
        return left_->interpret() - right_->interpret(); // Вычитание
    }

private:
    std::shared_ptr<Expression> left_; // Левый операнд
    std::shared_ptr<Expression> right_; // Правый операнд
};

// Фабрика для создания выражений
class ExpressionParser {
public:
    static std::shared_ptr<Expression> parse(const std::string& input) {
        std::istringstream stream(input);
        std::string token;
        std::vector<std::shared_ptr<Expression>> expressions;

        while (stream >> token) {
            if (isdigit(token[0])) {
                expressions.push_back(std::make_shared<Number>(std::stoi(token))); // Число
            } else if (token == "+") {
                auto right = expressions.back(); expressions.pop_back();
                auto left = expressions.back(); expressions.pop_back();
                expressions.push_back(std::make_shared<Addition>(left, right)); // Сложение
            } else if (token == "-") {
                auto right = expressions.back(); expressions.pop_back();
                auto left = expressions.back(); expressions.pop_back();
                expressions.push_back(std::make_shared<Subtraction>(left, right)); // Вычитание
            }
        }

        return expressions.back(); // Возвращаем последнее выражение
    }
};

// Клиентский код
int main() {
    std::string expression = "5 3 - 2 +"; // (5 - 3) + 2
    auto parsedExpression = ExpressionParser::parse(expression);
    std::cout << "Result: " << parsedExpression->interpret() << std::endl; // Выводим результат

    return 0;
}