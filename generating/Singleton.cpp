
#include <iostream>
#include <memory>

class Singleton {
public:
    // Удаляем конструктор, копирующий конструктор и оператор присваивания
    Singleton(const Singleton&) = delete;
    Singleton& operator=(const Singleton&) = delete;

    // Метод для получения единственного экземпляра
    static std::unique_ptr<Singleton>& getInstance() {
        static std::unique_ptr<Singleton> instance(new Singleton());
        return instance;
    }

    void someBusinessLogic() {
        std::cout << "Выполнение бизнес-логики" << std::endl;
    }

private:
    // Приватный конструктор
    Singleton() {
        std::cout << "Создание экземпляра Singleton" << std::endl;
    }
};

int main() {
    // Получаем единственный экземпляр Singleton
    Singleton::getInstance()->someBusinessLogic();

    // Получаем еще один экземпляр Singleton
    Singleton::getInstance()->someBusinessLogic();

    return 0;
}