#include <iostream>
#include <memory>

// Интерфейс состояния
class State {
public:
    virtual void play() = 0; // Метод для воспроизведения
    virtual void pause() = 0; // Метод для паузы
    virtual void stop() = 0; // Метод для остановки
    virtual ~State() {}
};

// Контекст (Музыкальный плеер)
class MusicPlayer {
public:
    MusicPlayer() : state_(nullptr) {}

    void setState(std::shared_ptr<State> state) {
        state_ = state; // Устанавливаем текущее состояние
    }

    void play() {
        if (state_) {
            state_->play(); // Делегируем вызов текущему состоянию
        }
    }

    void pause() {
        if (state_) {
            state_->pause(); // Делегируем вызов текущему состоянию
        }
    }

    void stop() {
        if (state_) {
            state_->stop(); // Делегируем вызов текущему состоянию
        }
    }

private:
    std::shared_ptr<State> state_; // Текущее состояние
};

// Конкретное состояние (Воспроизведение)
class PlayingState : public State {
public:
    void play() override {
        std::cout << "Already playing." << std::endl; // Если уже воспроизводится
    }

    void pause() override {
        std::cout << "Pausing the music." << std::endl; // Пауза
    }

    void stop() override {
        std::cout << "Stopping the music." << std::endl; // Остановка
    }
};

// Конкретное состояние (Пауза)
class PausedState : public State {
public:
    void play() override {
        std::cout << "Resuming the music." << std::endl; // Возобновление
    }

    void pause() override {
        std::cout << "Already paused." << std::endl; // Если уже на паузе
    }

    void stop() override {
        std::cout << "Stopping the music." << std::endl; // Остановка
    }
};

// Конкретное состояние (Остановлено)
class StoppedState : public State {
public:
    void play() override {
        std::cout << "Starting the music." << std::endl; // Начало воспроизведения
    }

    void pause() override {
        std::cout << "Can't pause. Music is stopped." << std::endl; // Нельзя поставить на паузу
    }

    void stop() override {
        std::cout << "Already stopped." << std::endl; // Если уже остановлено
    }
};

// Клиентский код
int main() {
    MusicPlayer player;

    // Устанавливаем состояние "Остановлено"
    player.setState(std::make_shared<StoppedState>());
    player.play(); // Начинаем воспроизведение
    player.pause(); // Нельзя поставить на паузу
    player.stop(); // Уже остановлено

    // Устанавливаем состояние "Воспроизведение"
    player.setState(std::make_shared<PlayingState>());
    player.play(); // Уже воспроизводится
    player.pause(); // Ставим на паузу
    player.stop(); // Останавливаем
}