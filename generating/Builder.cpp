#include <iostream>
#include <string>
#include <memory>
#include <vector>
class Pizza{
public:
    void seDough(const std::string& dough){
        this->dough = dough;
    }
    void setSauce(const std::string& sauce){
        this->sauce = sauce;
    }
    void addTopping(const std::string& topping){
        toppings.push_back(topping);
    }
    void show() const{
        std::cout << "Dough: " << dough << std::endl;
        std::cout << "Sauce: " << sauce << std::endl;
        std::cout << "Toppings: " << std::endl;
        for(const auto& topping : toppings){
            std::cout << topping << std::endl;
        }
    }
private:
    std::string dough;
    std::string sauce;
    std::vector<std::string> toppings;
};

class PizzaBuilder{
public:
    virtual void buildDough() = 0;    
    virtual void buildSauce() = 0;
    virtual void addToppings() = 0;
    virtual std::unique_ptr<Pizza> getPizza() = 0;
    virtual ~PizzaBuilder() {}
};

class MarketPizzaBuilder : public PizzaBuilder{
public:
    MarketPizzaBuilder(){
        pizza = std::make_unique<Pizza>();
    }
    void buildDough(){
        pizza->seDough("market dough");
    }
    void buildSauce(){
        pizza->setSauce("market sauce");
    }
    void addToppings(){
        pizza->addTopping("market topping 1");
        pizza->addTopping("market topping 2");
    }
    std::unique_ptr<Pizza> getPizza() override{
        return std::move(pizza);
    }
private:
    std::unique_ptr<Pizza> pizza;
};

class PepperoniPizzaBuilder : public PizzaBuilder{
public:
    PepperoniPizzaBuilder(){
        pizza = std::make_unique<Pizza>();
    }
    void buildDough(){
        pizza->seDough("pepperoni dough");
    }
    void buildSauce(){
        pizza->setSauce("pepperoni sauce");
    }
    void addToppings(){
        pizza->addTopping("pepperoni topping 1");
        pizza->addTopping("pepperoni topping 2");
    }
    std::unique_ptr<Pizza> getPizza() override{
        return std::move(pizza);
    }
private:
    std::unique_ptr<Pizza> pizza;

};

class PizzaDirector{
public:
    void setBuilder(std::unique_ptr<PizzaBuilder> builder){
        this->builder = std::move(builder);
    }
    std::unique_ptr<Pizza> buildPizza(){
        builder->buildDough();
        builder->buildSauce();
        builder->addToppings();
        return builder->getPizza();
    }
private:
    std::unique_ptr<PizzaBuilder> builder;
};

int main(){
    PizzaDirector director;
    director.setBuilder(std::make_unique<MarketPizzaBuilder>());
    std::unique_ptr<Pizza> marketPizza = director.buildPizza();
    marketPizza->show();
}