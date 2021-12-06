#include <iostream>
#include <ostream>
#include <sstream>
#include <map>
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

class Room {
  private:
    std::map<int, std::shared_ptr<Client>> seats;

    bool idAlreadyExists(std::string id) {
      for (auto& seat : seats) {
        if (seat.second->getId() == id) {
          return true;
        }
      }

      return false;
    }

  public:
    Room() {
      this->seats.clear();
    }

    std::map<int, std::shared_ptr<Client>> getSeats() {
      return this->seats;
    }

    bool reserve(std::string id, std::string name, std::string phone, int numberSeat) {
      bool idAlreadyExists = this->idAlreadyExists(id);

      if (idAlreadyExists) {
        std::cout << "fail: id esta sendo usado por outro cliente\n";
        return false;
      }

      auto [pos, success] = this->seats.insert(std::make_pair(numberSeat, std::make_shared<Client>(id, name, phone)));

      if (!success) {
        std::cout << "fail: cadeira ocupada\n";
        return false;
      }

      return true;
    }

    void cancel(std::string id) {
      for (auto& seat : seats) {
        if (seat.second->getId() == id) {
          seat.second = nullptr;
          return;
        }
      }
      
      std::cout << "fail: cliente nao esta no cinema\n";
    }
    
    friend std::ostream& operator<<(std::ostream& os, const Room& room) {
      os << "[ ";

      for (auto seat : room.seats) {
        if (seat.second != nullptr) {
          os << seat.first << ":" << *seat.second << " ";
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
        std::cout << "iniciar;\n"
          << "mostrar;\n"
          << "reservar _idCliente _nome _telefone _numeroCadeira;\n"
          << "cancelar _idCliente;\n"
          << "fechar;\n"
          << "encerrar;\n";
    } else if(cmd == "iniciar") {
      room = Room();
    } else if(cmd == "mostrar") {
      std::cout << room << "\n";
    } else if(cmd == "reservar") {
      std::string id {""};
      std::string name {""};
      std::string phone {""};
      int numberSeat {0};
      ss >> id >> name >> phone >> numberSeat;
      
      room.reserve(id, name, phone, numberSeat);
    } else if(cmd == "cancelar") {
      std::string id;

      ss >> id;
      room.cancel(id);
    } else {
      std::cout << "fail: comando invalido\n";
    }
  }
}
