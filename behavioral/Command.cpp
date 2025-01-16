#include <iostream>
#include <memory>
#include <vector>

// Интерфейс команды
class Command {
public:
    virtual void execute() = 0; // Метод для выполнения команды
    virtual ~Command() {}
};

// Получатель (свет)
class Light {
public:
    void turnOn() {
        std::cout << "Light is ON." << std::endl;
    }

    void turnOff() {
        std::cout << "Light is OFF." << std::endl;
    }
};

// Конкретная команда (включить свет)
class TurnOnLightCommand : public Command {
public:
    TurnOnLightCommand(std::shared_ptr<Light> light) : light_(light) {}

    void execute() override {
        light_->turnOn(); // Выполняем действие
    }

private:
    std::shared_ptr<Light> light_; // Указатель на получателя
};

// Конкретная команда (выключить свет)
class TurnOffLightCommand : public Command {
public:
    TurnOffLightCommand(std::shared_ptr<Light> light) : light_(light) {}

    void execute() override {
        light_->turnOff(); // Выполняем действие
    }

private:
    std::shared_ptr<Light> light_; // Указатель на получателя
};

// Инициатор (пульт)
class RemoteControl {
public:
    void setCommand(std::shared_ptr<Command> command) {
        command_ = command; // Устанавливаем команду
    }

    void pressButton() {
        if (command_) {
            command_->execute(); // Вызываем команду
        }
    }

private:
    std::shared_ptr<Command> command_; // Хранит текущую команду
};

// Клиентский код
int main() {
    // Создаем получателя
    auto light = std::make_shared<Light>();

    // Создаем команды
    auto turnOn = std::make_shared<TurnOnLightCommand>(light);
    auto turnOff = std::make_shared<TurnOffLightCommand>(light);

    // Создаем пульт
    RemoteControl remote;

    // Включаем свет
    remote.setCommand(turnOn);
    remote.pressButton();

    // Выключаем свет
    remote.setCommand(turnOff);
    remote.pressButton();

    return 0;
}