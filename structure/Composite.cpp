#include <iostream>
#include <memory>
#include <vector>
#include <string>

// Компонент
class FileSystemComponent {
public:
    virtual void show(int indent = 0) const = 0; // Метод для отображения
    virtual ~FileSystemComponent() {}
};

// Лист (File)
class File : public FileSystemComponent {
public:
    File(const std::string& name) : name_(name) {}

    void show(int indent = 0) const override {
        std::cout << std::string(indent, ' ') << "File: " << name_ << std::endl;
    }

private:
    std::string name_;
};

// Композит (Directory)
class Directory : public FileSystemComponent {
public:
    Directory(const std::string& name) : name_(name) {}

    void add(std::shared_ptr<FileSystemComponent> component) {
        components_.push_back(component);
    }

    void show(int indent = 0) const override {
        std::cout << std::string(indent, ' ') << "Directory: " << name_ << std::endl;
        for (const auto& component : components_) {
            component->show(indent + 2); // Увеличиваем отступ для дочерних элементов
        }
    }

private:
    std::string name_;
    std::vector<std::shared_ptr<FileSystemComponent>> components_; // Дочерние компоненты
};

// Клиентский код
int main() {
    // Создаем файлы
    auto file1 = std::make_shared<File>("file1.txt");
    auto file2 = std::make_shared<File>("file2.txt");

    // Создаем директории
    auto dir1 = std::make_shared<Directory>("dir1");
    auto dir2 = std::make_shared<Directory>("dir2");

    // Добавляем файлы в директории
    dir1->add(file1);
    dir2->add(file2);

    // Создаем корневую директорию
    auto root = std::make_shared<Directory>("root");
    root->add(dir1);
    root->add(dir2);

    // Отображаем файловую систему
    root->show();

    return 0;
}