#include <iostream>

class Vehicle {
  protected:
    std::string color {""};
    int velocity {0};
    bool on {false};
    
  public: 
    Vehicle(std::string color) {
      this->color = color;
    }

    std::string getColor() const {
      return this->color;
    }

    int getVelocity() const {
      return this->velocity;
    }

    bool itsOn() const {
      return this->on;
    }

    virtual void turnOn() {
      if (on) {
        std::cout << "Veículo está ligado\n";
      } else {
        this->on = true;
      }
    }

    virtual void turnOff() {
      if (!on) {
        std::cout << "Veículo está desligado6\n";
      } else {
        this->on = false;
        this->velocity = 0;
      }
    }
    
    virtual void accelerate(int value) {
      if (this->on) {
        this->velocity += value;
      }
    }

    virtual void brake(int value) {
      if (this->on) {
        if ((this->velocity - value) < 0) {
          this->velocity = 0;
        } else {
          this->velocity -= value;
        }
      }
    }

    friend std::ostream& operator<<(std::ostream& os, const Vehicle& vehicle) {
      os << vehicle.color << ":" << vehicle.velocity << ":" << vehicle.on;
      return os;
    }
};

class Car : public Vehicle {
  private:
    int numberOfPorts {2};
  
  public:
    Car(std::string color, int numberOfPorts): Vehicle{color} {
      this->numberOfPorts = numberOfPorts;
    }

    int getNumberOfPorts() const {
      return this->numberOfPorts;
    }

    virtual void turnOn() {
      if (on) {
        std::cout << "Carro está ligado\n";
      } else {
        this->on = true;
      }
    }

    virtual void turnOff() {
      if (on) {
        std::cout << "Carro está desligado\n";
      } else {
        this->on = true;
        this->velocity = 0;
      }
    }

    friend std::ostream& operator<<(std::ostream& os, const Car& car) {
      os << car.color << ":" << car.velocity << ":" << car.on << ":" << car.numberOfPorts;
      return os;
    }
};

class Motorcycle : public Vehicle {
  private:
    int numberOfTires {2};
  
  public:
    Motorcycle(std::string color, int numberOfTires): Vehicle{color} {
      if (numberOfTires > 4) {
        this->numberOfTires = 4;
      } else {
        this->numberOfTires = numberOfTires;
      }
    }

    int getNumberOfTires() const {
      return this->numberOfTires;
    }

    virtual void turnOn() {
      if (on) {
        std::cout << "Moto está ligado\n";
      } else {
        this->on = true;
      }
    }

    virtual void turnOff() {
      if (on) {
        std::cout << "Moto está desligado\n";
      } else {
        this->on = true;
        this->velocity = 0;
      }
    }

    friend std::ostream& operator<<(std::ostream& os, const Motorcycle& motorcycle) {
      os << motorcycle.color << ":" << motorcycle.velocity << ":" << motorcycle.on << ":" << motorcycle.numberOfTires;
      return os;
    }
};

int main() {
  Car car1 {"Preto", 4};
  car1.turnOn();
  car1.accelerate(80);
  car1.brake(30);
  car1.turnOn();

  Motorcycle motorcycle1 {"Azul", 2};
  motorcycle1.turnOn();
  motorcycle1.accelerate(120);
  motorcycle1.brake(30);
  motorcycle1.turnOn();

  std::cout << car1 << "\n";
  std::cout << motorcycle1 << "\n";

  Vehicle vehicle1 = Vehicle("Vermelho");
  vehicle1.turnOn();
  vehicle1.brake(10);
  vehicle1.brake(10);
  vehicle1.turnOn();

  Vehicle &vehicle2 = car1;
  vehicle2.brake(30);
  vehicle2.turnOn();

  Vehicle* vehicle3 = &motorcycle1;
  vehicle3->brake(15);
  vehicle3->turnOn();

  std::cout << car1 << "\n";
  std::cout << motorcycle1 << "\n";
  std::cout << vehicle1 << "\n";
  std::cout << vehicle2 << "\n";
  std::cout << *vehicle3 << "\n";
}