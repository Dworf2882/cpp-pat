#include <iostream>
#include <string>
#include <memory>

// Интерфейс обработчика
class SupportHandler {
public:
    virtual void setNext(std::shared_ptr<SupportHandler> next) = 0; // Устанавливает следующий обработчик
    virtual void handleRequest(const std::string& request) = 0; // Обрабатывает запрос
    virtual ~SupportHandler() {}
};

// Конкретный обработчик 1 (Уровень 1 поддержки)
class SupportLevel1 : public SupportHandler {
public:
    void setNext(std::shared_ptr<SupportHandler> next) override {
        next_ = next;
    }

    void handleRequest(const std::string& request) override {
        if (request == "Level 1") {
            std::cout << "Support Level 1: Handling request: " << request << std::endl;
        } else if (next_) {
            next_->handleRequest(request); // Передаем запрос следующему обработчику
        }
    }

private:
    std::shared_ptr<SupportHandler> next_;
};

// Конкретный обработчик 2 (Уровень 2 поддержки)
class SupportLevel2 : public SupportHandler {
public:
    void setNext(std::shared_ptr<SupportHandler> next) override {
        next_ = next;
    }

    void handleRequest(const std::string& request) override {
        if (request == "Level 2") {
            std::cout << "Support Level 2: Handling request: " << request << std::endl;
        } else if (next_) {
            next_->handleRequest(request); // Передаем запрос следующему обработчику
        }
    }

private:
    std::shared_ptr<SupportHandler> next_;
};

// Конкретный обработчик 3 (Уровень 3 поддержки)
class SupportLevel3 : public SupportHandler {
public:
    void setNext(std::shared_ptr<SupportHandler> next) override {
        next_ = next;
    }

    void handleRequest(const std::string& request) override {
        if (request == "Level 3") {
            std::cout << "Support Level 3: Handling request: " << request << std::endl;
        } else {
            std::cout << "Support Level 3: No handler for request: " << request << std::endl;
        }
    }

private:
    std::shared_ptr<SupportHandler> next_;
};

// Клиентский код
int main() {
    // Создаем обработчики
    auto level1 = std::make_shared<SupportLevel1>();
    auto level2 = std::make_shared<SupportLevel2>();
    auto level3 = std::make_shared<SupportLevel3>();

    // Устанавливаем цепочку обработчиков
    level1->setNext(level2);
    level2->setNext(level3);

    // Отправляем запросы
    level1->handleRequest("Level 1"); // Обрабатывается на уровне 1
    level1->handleRequest("Level 2"); // Обрабатывается на уровне 2
}