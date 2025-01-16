#include <iostream>
#include <memory>
#include <string>
#include <vector>

// Хранитель (Memento)
class Memento {
public:
    Memento(const std::string& state) : state_(state) {}

    std::string getState() const {
        return state_; // Возвращаем сохраненное состояние
    }

private:
    std::string state_; // Состояние объекта
};

// Производитель (Originator)
class TextEditor {
public:
    void setText(const std::string& text) {
        text_ = text; // Устанавливаем текст
    }

    std::string getText() const {
        return text_; // Возвращаем текущий текст
    }

    std::shared_ptr<Memento> save() {
        return std::make_shared<Memento>(text_); // Сохраняем текущее состояние
    }

    void restore(const std::shared_ptr<Memento>& memento) {
        text_ = memento->getState(); // Восстанавливаем состояние из хранителя
    }

private:
    std::string text_; // Текущий текст
};

// Управляющий (Caretaker)
class History {
public:
    void save(const std::shared_ptr<Memento>& memento) {
        history_.push_back(memento); // Сохраняем хранитель в истории
    }

    std::shared_ptr<Memento> undo() {
        if (history_.empty()) {
            return nullptr; // Если история пуста, возвращаем nullptr
        }
        auto memento = history_.back(); // Получаем последний сохраненный хранитель
        history_.pop_back(); // Удаляем его из истории
        return memento; // Возвращаем хранитель
    }

private:
    std::vector<std::shared_ptr<Memento>> history_; // История сохраненных состояний
};

// Клиентский код
int main() {
    TextEditor editor;
    History history;

    // Устанавливаем текст и сохраняем состояние
    editor.setText("Version 1");
    history.save(editor.save());

    editor.setText("Version 2");
    history.save(editor.save());

    editor.setText("Version 3");
    std::cout << "Current text: " << editor.getText() << std::endl;

    // Восстанавливаем предыдущее состояние
    editor.restore(history.undo());
    std::cout << "After undo: " << editor.getText() << std::endl;

    // Восстанавливаем еще одно предыдущее состояние
    editor.restore(history.undo());
    std::cout << "After another undo: " << editor.getText() << std::endl;

    return 0;
}