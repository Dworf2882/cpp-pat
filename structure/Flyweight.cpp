#include <iostream>
#include <unordered_map>
#include <memory>

// Интерфейс Flyweight
class Character {
public:
    virtual void display(int x, int y) = 0; // Метод для отображения символа
    virtual ~Character() {}
};

// Конкретный Flyweight (символ)
class ConcreteCharacter : public Character {
public:
    ConcreteCharacter(char c, const std::string& font, const std::string& color)
        : character_(c), font_(font), color_(color) {}

    void display(int x, int y) override {
        std::cout << "Character: " << character_ 
                  << " | Font: " << font_ 
                  << " | Color: " << color_ 
                  << " | Position: (" << x << ", " << y << ")" << std::endl;
    }

private:
    char character_; // Символ
    std::string font_; // Шрифт
    std::string color_; // Цвет
};

// Фабрика Flyweight
class CharacterFactory {
public:
    std::shared_ptr<Character> getCharacter(char c, const std::string& font, const std::string& color) {
        std::string key = std::string(1, c) + font + color; // Уникальный ключ для символа
        if (characters_.find(key) == characters_.end()) {
            characters_[key] = std::make_shared<ConcreteCharacter>(c, font, color);
        }
        return characters_[key]; // Возвращаем существующий или новый символ
    }

private:
    std::unordered_map<std::string, std::shared_ptr<Character>> characters_; // Хранит летучие веса
};

// Клиентский код
int main() {
    CharacterFactory factory;

    // Создаем символы
    auto a1 = factory.getCharacter('A', "Arial", "Red");
    auto a2 = factory.getCharacter('A', "Arial", "Red");
    auto b1 = factory.getCharacter('B', "Arial", "Blue");

    // Отображаем символы
    a1->display(10, 20);
    a2->display(30, 40); // a1 и a2 - это один и тот же объект
    b1->display(50, 60);

    std::cout << "a1 and a2 are the same object: " << (a1 == a2) << std::endl; // Проверка на совместное использование

    return 0;
}