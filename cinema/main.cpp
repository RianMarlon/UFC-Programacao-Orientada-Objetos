#include <iostream>
#include <ostream>
#include <sstream>
#include <vector>
#include <memory>

class Client {
  private:
    std::string id;
    std::string name;
    std::string phone;
  
  public:
    Client(std::string id = "", std::string name = "", std::string phone = "") {
      this->id = id;
      this->name = name;
      this->phone = phone;
    }

    std::string getId() const {
      return this->id;
    }

    std::string getName() const {
      return this->name;
    }

    std::string getPhone() const {
      return this->phone;
    }

    void setId(int id) {
      this->id = id;
    }

    void setName(std::string name) {
      this->name = name;
    }

    void setPhone(std::string phone) {
      this->phone = phone;
    }

    friend std::ostream& operator<<(std::ostream& os, const Client& client) {
      os << client.getId() << ":" << client.getName() << ":" << client.getPhone();
      return os;
    }
};

class Room{
  private:
    std::vector<std::shared_ptr<Client>> seats;

    bool idAlreadyExists(std::string id) {
      for (auto seat : seats) {
        if (seat == nullptr) {
          continue;
        }

        if (seat->getId() == id) {
          return true;
        }
      }

      return false;
    }

  public:
    Room(int capacity = 0) {
      this->seats.clear();
      for (int i = 0; i < capacity; i++) {
        this->seats.push_back(nullptr);
      }
    }

    std::vector<std::shared_ptr<Client>> getSeats() {
      return this->seats;
    }

    bool reserve(std::string id, std::string name, std::string phone, int index) {
      if (index < 0 || index >= this->seats.size()) {
        std::cout << "fail: cadeira nao existe\n";
        return false;
      }

      if (this->seats[index] != nullptr) {
        std::cout << "fail: cadeira ocupada\n";
        return false;
      }

      bool idAlreadyExists = this->idAlreadyExists(id);

      if (idAlreadyExists) {
        std::cout << "fail: id esta sendo usado por outro cliente\n";
        return false;
      }

      this->seats[index] = std::make_shared<Client>(id, name, phone);
      return true;
    }

    void cancel(std::string id) {
      for (int i = 0; i < this->seats.size(); i++) {
        if (this->seats[i] == nullptr) {
          continue;
        }

        if (this->seats[i]->getId() == id) {
          this->seats[i] = nullptr;
          return;
        }
      }

      std::cout << "fail: cliente nao esta no cinema\n";
    }
    
    friend std::ostream& operator<<(std::ostream& os, const Room& room) {
      os << "[ ";

      for (auto seat : room.seats) {
        if (seat != nullptr) {
          os << *seat << " ";
        } else {
          os << "- ";
        }
      }

      os << "]";

      return os;
    }
};

int main() {
  Room room;

  while(true) {
    std::string line;
    std::getline(std::cin, line);
    std::stringstream ss(line);
    std::string cmd;
    ss >> cmd;
    
    if(cmd == "encerrar") {
      break;
    } else if(cmd == "ajuda") {
        std::cout << "iniciar _capacidade;\n"
          << "mostrar;\n"
          << "reservar _idCliente _nome _telefone _cadeira;\n"
          << "cancelar _idCliente;\n"
          << "fechar;\n"
          << "encerrar;\n";
    } else if(cmd == "iniciar") {
      int capacity {0};
      ss >> capacity;
      
      room = Room(capacity);
    } else if(cmd == "mostrar") {
      std::cout << room << "\n";
    } else if(cmd == "reservar") {
      std::string id {""};
      std::string name {""};
      std::string phone {""};
      int index {0};
      ss >> id >> name >> phone >> index;
      
      room.reserve(id, name, phone, index);
    } else if(cmd == "cancelar") {
      std::string id;

      ss >> id;
      room.cancel(id);
    } else {
      std::cout << "fail: comando invalido\n";
    }
  }
}
