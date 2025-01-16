#include <iostream>
#include <vector>
#include <memory>

// Интерфейс итератора
class Iterator {
public:
    virtual bool hasNext() = 0; // Проверяет, есть ли следующий элемент
    virtual std::string next() = 0; // Возвращает следующий элемент
    virtual ~Iterator() {}
};

// Интерфейс агрегата
class Aggregate {
public:
    virtual std::shared_ptr<Iterator> createIterator() = 0; // Создает итератор
    virtual ~Aggregate() {}
};

// Конкретный итератор
class BookIterator : public Iterator {
public:
    BookIterator(const std::vector<std::string>& books) : books_(books), index_(0) {}

    bool hasNext() override {
        return index_ < books_.size(); // Проверяем, есть ли следующий элемент
    }

    std::string next() override {
        return books_[index_++]; // Возвращаем следующий элемент и увеличиваем индекс
    }

private:
    const std::vector<std::string>& books_; // Ссылка на коллекцию книг
    size_t index_; // Текущий индекс
};

// Конкретный агрегат
class BookCollection : public Aggregate {
public:
    void addBook(const std::string& book) {
        books_.push_back(book); // Добавляем книгу в коллекцию
    }

    std::shared_ptr<Iterator> createIterator() override {
        return std::make_shared<BookIterator>(books_); // Создаем итератор
    }

private:
    std::vector<std::string> books_; // Коллекция книг
};

// Клиентский код
int main() {
    BookCollection collection;
    collection.addBook("The Catcher in the Rye");
    collection.addBook("To Kill a Mockingbird");
    collection.addBook("1984");

    // Создаем итератор для обхода коллекции
    auto iterator = collection.createIterator();

    // Обходим коллекцию и выводим книги
    while (iterator->hasNext()) {
        std::cout << iterator->next() << std::endl;
    }

    return 0;
}