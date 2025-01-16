#include <iostream>
#include <memory>

// Интерфейс реализации (Device)
class Device {
public:
    virtual void turnOn() = 0; // Включить устройство
    virtual void turnOff() = 0; // Выключить устройство
    virtual ~Device() {}
};

// Конкретная реализация 1 (Television)
class Television : public Device {
public:
    void turnOn() override {
        std::cout << "Television is now ON." << std::endl;
    }

    void turnOff() override {
        std::cout << "Television is now OFF." << std::endl;
    }
};

// Конкретная реализация 2 (Radio)
class Radio : public Device {
public:
    void turnOn() override {
        std::cout << "Radio is now ON." << std::endl;
    }

    void turnOff() override {
        std::cout << "Radio is now OFF." << std::endl;
    }
};

// Абстракция (RemoteControl)
class RemoteControl {
public:
    RemoteControl(std::unique_ptr<Device> device) : device_(std::move(device)) {}

    void pressPowerButton() {
        if (isOn) {
            device_->turnOff();
        } else {
            device_->turnOn();
        }
        isOn = !isOn; // Переключаем состояние
    }

private:
    std::unique_ptr<Device> device_; // Указатель на устройство
    bool isOn = false; // Состояние устройства
};

// Клиентский код
int main() {
    // Создаем телевизор и пульт
    std::unique_ptr<Device> tv = std::make_unique<Television>();
    RemoteControl remote1(std::move(tv));
    remote1.pressPowerButton(); // Включаем телевизор
    remote1.pressPowerButton(); // Выключаем телевизор

    // Создаем радио и пульт
    std::unique_ptr<Device> radio = std::make_unique<Radio>();
    RemoteControl remote2(std::move(radio));
    remote2.pressPowerButton(); // Включаем радио
    remote2.pressPowerButton(); // Выключаем радио

    return 0;
}