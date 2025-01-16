#include <iostream>

// Подсистема 1: Телевизор
class Television {
public:
    void turnOn() {
        std::cout << "Television is now ON." << std::endl;
    }

    void turnOff() {
        std::cout << "Television is now OFF." << std::endl;
    }
};

// Подсистема 2: Проигрыватель DVD
class DVDPlayer {
public:
    void turnOn() {
        std::cout << "DVD Player is now ON." << std::endl;
    }

    void turnOff() {
        std::cout << "DVD Player is now OFF." << std::endl;
    }

    void play() {
        std::cout << "Playing DVD." << std::endl;
    }
};

// Подсистема 3: Звуковая система
class SoundSystem {
public:
    void turnOn() {
        std::cout << "Sound System is now ON." << std::endl;
    }

    void turnOff() {
        std::cout << "Sound System is now OFF." << std::endl;
    }

    void setVolume(int level) {
        std::cout << "Setting volume to " << level << "." << std::endl;
    }
};

// Фасад
class HomeTheaterFacade {
public:
    HomeTheaterFacade() 
        : tv_(new Television()), dvdPlayer_(new DVDPlayer()), soundSystem_(new SoundSystem()) {}

    void watchMovie() {
        std::cout << "Getting ready to watch a movie..." << std::endl;
        tv_->turnOn();
        soundSystem_->turnOn();
        soundSystem_->setVolume(10);
        dvdPlayer_->turnOn();
        dvdPlayer_->play();
    }

    void endMovie() {
        std::cout << "Shutting down the home theater..." << std::endl;
        dvdPlayer_->turnOff();
        soundSystem_->turnOff();
        tv_->turnOff();
    }

private:
    Television* tv_;
    DVDPlayer* dvdPlayer_;
    SoundSystem* soundSystem_;
};

// Клиентский код
int main() {
    HomeTheaterFacade homeTheater;
    homeTheater.watchMovie(); // Подготовка к просмотру фильма
    homeTheater.endMovie();   // Завершение просмотра фильма

    return 0;
}