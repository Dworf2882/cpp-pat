#include <iostream>
#include <string>
#include <vector>
#include <memory>

// Впереди объявляем классы
class User;

// Интерфейс посредника
class ChatMediator {
public:
    virtual void sendMessage(const std::string& message, User* user) = 0; // Метод для отправки сообщения
    virtual void addUser (User* user) = 0; // Метод для добавления пользователя
    virtual ~ChatMediator() {}
};

// Коллега (Пользователь)
class User {
public:
    User(ChatMediator* mediator, const std::string& name) : mediator_(mediator), name_(name) {
        mediator_->addUser (this); // Добавляем пользователя в медиатор
    }

    void sendMessage(const std::string& message) {
        mediator_->sendMessage(message, this); // Отправляем сообщение через медиатор
    }

    void receiveMessage(const std::string& message) {
        std::cout << name_ << " received: " << message << std::endl; // Получаем сообщение
    }

private:
    ChatMediator* mediator_; // Ссылка на медиатор
    std::string name_; // Имя пользователя
};

// Конкретный посредник
class ChatRoom : public ChatMediator {
public:
    void sendMessage(const std::string& message, User* user) override {
        for (User * u : users_) {
            // Не отправляем сообщение отправителю
            if (u != user) {
                u->receiveMessage(message);
            }
        }
    }

    void addUser (User* user) override {
        users_.push_back(user); // Добавляем пользователя в список
    }

private:
    std::vector<User*> users_; // Список пользователей
};

// Клиентский код
int main() {
    ChatRoom chatRoom;

    User user1(&chatRoom, "Alice");
    User user2(&chatRoom, "Bob");
    User user3(&chatRoom, "Charlie");

    user1.sendMessage("Hello, everyone!");
    user2.sendMessage("Hi, Alice!");
    user3.sendMessage("Good morning!");

    return 0;
}