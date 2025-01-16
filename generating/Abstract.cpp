#include <iostream>
#include <memory>
#include <string>

// Интерфейс для стульев
class Chair {
public:
    virtual void sitOn() = 0; // Чисто виртуальный метод
    virtual ~Chair() {}
};

// Интерфейс для столов
class Table {
public:
    virtual void use() = 0; // Чисто виртуальный метод
    virtual ~Table() {}
};

// Конкретный продукт: Современный стул
class ModernChair : public Chair {
public:
    void sitOn() override {
        std::cout << "Sitting on a modern chair!" << std::endl;
    }
};

// Конкретный продукт: Классический стул
class VictorianChair : public Chair {
public:
    void sitOn() override {
        std::cout << "Sitting on a Victorian chair!" << std::endl;
    }
};

// Конкретный продукт: Современный стол
class ModernTable : public Table {
public:
    void use() override {
        std::cout << "Using a modern table!" << std::endl;
    }
};

// Конкретный продукт: Классический стол
class VictorianTable : public Table {
public:
    void use() override {
        std::cout << "Using a Victorian table!" << std::endl;
    }
};

// Интерфейс абстрактной фабрики
class FurnitureFactory {
public:
    virtual std::unique_ptr<Chair> createChair() = 0; // Чисто виртуальный метод
    virtual std::unique_ptr<Table> createTable() = 0; // Чисто виртуальный метод
    virtual ~FurnitureFactory() {}
};

// Конкретная фабрика: Современная мебель
class ModernFurnitureFactory : public FurnitureFactory {
public:
    std::unique_ptr<Chair> createChair() override {
        return std::make_unique<ModernChair>();
    }
    
    std::unique_ptr<Table> createTable() override {
        return std::make_unique<ModernTable>();
    }
};

// Конкретная фабрика: Классическая мебель
class VictorianFurnitureFactory : public FurnitureFactory {
public:
    std::unique_ptr<Chair> createChair() override {
        return std::make_unique<VictorianChair>();
    }
    
    std::unique_ptr<Table> createTable() override {
        return std::make_unique<VictorianTable>();
    }
};

int main() {
    std::unique_ptr<FurnitureFactory> factory;

    // Создаем современную мебель
    factory = std::make_unique<ModernFurnitureFactory>();
    std::unique_ptr<Chair> modernChair = factory->createChair();
    std::unique_ptr<Table> modernTable = factory->createTable();
    
    modernChair->sitOn();
    modernTable->use();

    // Создаем классическую мебель
    factory = std::make_unique<VictorianFurnitureFactory>();
    std::unique_ptr<Chair> victorianChair = factory->createChair();
    std::unique_ptr<Table> victorianTable = factory->createTable();
    
    victorianChair->sitOn();
    victorianTable->use();

    return 0;
}