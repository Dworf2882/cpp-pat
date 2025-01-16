#include <iostream>
#include <memory>
#include <string>

// Интерфейс субъекта
class Image {
public:
    virtual void display() = 0; // Метод для отображения изображения
    virtual ~Image() {}
};

// Реальный субъект (реальное изображение)
class RealImage : public Image {
public:
    RealImage(const std::string& filename) : filename_(filename) {
        loadImageFromDisk(); // Загружаем изображение из диска
    }

    void display() override {
        std::cout << "Displaying " << filename_ << std::endl;
    }

private:
    std::string filename_;

    void loadImageFromDisk() {
        std::cout << "Loading " << filename_ << std::endl;
    }
};

// Прокси
class ProxyImage : public Image {
public:
    ProxyImage(const std::string& filename) : filename_(filename), realImage_(nullptr) {}

    void display() override {
        if (!realImage_) {
            realImage_ = std::make_shared<RealImage>(filename_); // Загружаем реальное изображение при первом вызове
        }
        realImage_->display(); // Вызываем метод отображения реального изображения
    }

private:
    std::string filename_;
    std::shared_ptr<RealImage> realImage_; // Указатель на реальное изображение
};

// Клиентский код
int main() {
    std::shared_ptr<Image> image1 = std::make_shared<ProxyImage>("image1.jpg");
    std::shared_ptr<Image> image2 = std::make_shared<ProxyImage>("image2.jpg");

    // Изображение загружается только при первом вызове display()
    image1->display(); // Загружается и отображается

    image2->display(); // Загружается и отображается

    return 0;
}