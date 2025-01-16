#include <iostream>
#include <memory>

// Целевой интерфейс (NewSystem)
class NewSystem {
public:
    virtual void request() = 0; // Метод, который будет вызываться клиентом
    virtual ~NewSystem() {}
};

// Адаптируемый класс (OldSystem)
class OldSystem {
public:
    void specificRequest() {
        std::cout << "OldSystem: Specific request." << std::endl;
    }
};

// Адаптер (Adapter)
class Adapter : public NewSystem {
public:
    Adapter(std::shared_ptr<OldSystem> oldSystem) : oldSystem_(oldSystem) {}

    void request() override {
        std::cout << "Adapter: Adapting request to OldSystem." << std::endl;
        oldSystem_->specificRequest(); // Перенаправляем вызов к адаптируемому классу
    }

private:
    std::shared_ptr<OldSystem> oldSystem_; // Указатель на адаптируемый класс
};

// Клиентский код
int main() {
    // Создаем адаптируемый объект
    std::shared_ptr<OldSystem> oldSystem = std::make_shared<OldSystem>();

    // Создаем адаптер
    std::shared_ptr<NewSystem> adapter = std::make_shared<Adapter>(oldSystem);

    // Используем адаптер
    adapter->request();

    return 0;
}