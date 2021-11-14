#include <iostream>
#include <ostream>
#include <sstream>
#include <list>
#include <memory>

class Kid {
  private:
    std::string name;
    int age;
    int debt;
  
  public:
    Kid(std::string name = "", int age = 0) {
      this->name = name;
      this->age = age;
      this->debt = 0;
    }

    std::string getName() const {
      return this->name;
    }

    int getAge() const {
      return this->age;
    }

    int getDebt() {
      return this->debt;
    }

    void setAge(int age) {
      this->age = age;
    }

    void setName(std::string name) {
      this->name = name;
    }

    void incrementDebt(int value) {
      this->debt += value;
    }

    friend std::ostream& operator<<(std::ostream& os, const Kid& kid) {
      os << kid.getName() << ":" << kid.getAge();
      return os;
    }
};

class Trampoline{
  private:
    int capacity;
    int ageLimit;
    int cashBox;
    std::list<std::shared_ptr<Kid>> waiting;
    std::list<std::shared_ptr<Kid>> playing;

    std::shared_ptr<Kid> findKidByName(std::string name, std::list<std::shared_ptr<Kid>> list) {
      for (auto it = list.begin(); it != list.end(); ++it) {
        if ((*it)->getName() == name) {
          return *it;
        }
      }

      return nullptr;
    };

    std::shared_ptr<Kid> removeKid(std::string name, std::list<std::shared_ptr<Kid>>& list) {
      std::shared_ptr<Kid> kid = this->findKidByName(name, list);

      if (kid != nullptr) {
        list.remove(kid);
        return kid;
      }

      return nullptr;
    };

    void payment(std::shared_ptr<Kid> kid) {
      this->waiting.remove(kid);
      this->playing.remove(kid);
      this->cashBox += kid->getDebt();
    }

  public:
    Trampoline(int capacity = 0, int ageLimit = 0, int cashBox = 0) {
      this->capacity = capacity;
      this->ageLimit = ageLimit;
      this->cashBox = cashBox;
    }

    int getCashBox() {
      return this->cashBox;
    }

    int getDebtByKidName(std::string name) {
      std::shared_ptr<Kid> kidInPlaying = this->findKidByName(name, this->playing);

      if (kidInPlaying != nullptr) {
        return kidInPlaying->getDebt();
      }

      std::shared_ptr<Kid> kidInWaiting = this->findKidByName(name, this->waiting);

      if (kidInWaiting != nullptr) {
        return kidInWaiting->getDebt();
      }

      std::cout << "faiil: nao tem nenhuma crianca com esse nome\n";
      return -1;
    }

    void arrive(const std::shared_ptr<Kid>& kid) {
      if (kid->getAge() <= 0 || kid->getAge() > ageLimit) {
        std::cout << "fail: idade nao permitida\n";
        return;
      }

      this->waiting.push_back(kid);
    }

    void in() {
      if (this->waiting.empty()) {
        std::cout << "fail: nao tem crianca na fila de espera\n";
        return;
      }

      if ((int) this->playing.size() == this->capacity) {
        std::cout << "fail: nao tem mais espaco no pula-pula\n";
        return;
      }

      std::shared_ptr<Kid> kid = *this->waiting.begin();
      this->waiting.remove(kid);
      kid->incrementDebt(1);
      this->playing.push_back(kid);
    }

    void out() {
      if (this->playing.empty()) {
        std::cout << "fail: nao tem crianca no pula-pula\n";
        return;
      }

      std::shared_ptr<Kid> kid = *this->playing.begin();
      this->playing.remove(kid);
      this->waiting.push_back(kid);
    }

    std::shared_ptr<Kid> remove(std::string name) {
      std::shared_ptr<Kid> kidRemovedInPlaying = this->removeKid(name, this->playing);

      if (kidRemovedInPlaying != nullptr) {
        this->payment(kidRemovedInPlaying);
        return kidRemovedInPlaying;
      }

      std::shared_ptr<Kid> kidRemovedInWaiting = this->removeKid(name, this->waiting);

      if (kidRemovedInWaiting != nullptr) {
        this->payment(kidRemovedInWaiting);
        return kidRemovedInWaiting;
      }

      std::cout << "fail: nao tem nenhuma crianca com esse nome\n";
      return nullptr;
    }

    void close() {
      for (auto kid : this->waiting) {
        this->payment(kid);
      }

      for (auto kid : this->playing) {
        this->payment(kid);
      }
    }
    
    friend std::ostream& operator<<(std::ostream& os, const Trampoline& trampoline) {
      os << "=> ";

      if (trampoline.waiting.empty()) {
        os << "- ";
      } else {
        for (auto it = trampoline.waiting.rbegin(); it != trampoline.waiting.rend(); it++) {
          Kid& kid = *(*it);
          os << kid << " ";
        }
      }

      os << "=> [ ";

      if (trampoline.playing.empty()) {
        os << "- ";
      } else {
        for (auto it = trampoline.playing.rbegin(); it != trampoline.playing.rend(); it++) {
          Kid& kid = *(*it);
          os << kid << " ";
        }
      }

      os << "]";

      return os;
    }
};

int main() {
  Trampoline trampoline;

  while(true) {
    std::string line;
    std::getline(std::cin, line);
    std::stringstream ss(line);
    std::string cmd;
    ss >> cmd;
    
    if(cmd == "encerrar") {
      break;
    } else if(cmd == "ajuda") {
        std::cout << "iniciar _capacidade _idadeLimite;\n"
          << "mostrar;\n"
          << "chegou _nome _idade;\n"
          << "entrar;\n"
          << "sair;\n"
          << "saldo _nome;\n"
          << "caixa;\n"
          << "papaichegou _nome;\n"
          << "remover _nome;\n"
          << "fechar;\n"
          << "encerrar;\n";
    } else if(cmd == "iniciar") {
      int capacity {0};
      int ageLimit {0};
      ss >> capacity >> ageLimit;
      
      trampoline = Trampoline(capacity, ageLimit);
    } else if(cmd == "mostrar") {
      std::cout << trampoline << "\n";
    } else if(cmd == "chegou") {
      std::string name {""};
      int age {0};
      ss >> name >> age;
      
      trampoline.arrive(std::make_shared<Kid>(name, age));
    } else if(cmd == "entrar") {
      trampoline.in();
    } else if(cmd == "sair") {
      trampoline.out();
    } else if(cmd == "saldo") {
      std::string name {""};
      ss >> name;

      int debt = trampoline.getDebtByKidName(name);

      if (debt >= 0) {
        std::cout << debt << "\n";
      }
    } else if(cmd == "caixa") {
      int cashBox = trampoline.getCashBox();
      std::cout << cashBox << "\n";
    } else if(cmd == "papaichegou") {
      std::string name {""};
      ss >> name;

      trampoline.remove(name);
    } else if(cmd == "remover") {
      std::string name {""};
      ss >> name;

      trampoline.remove(name);
    } else if(cmd == "fechar") {
      trampoline.close();
    } else {
      std::cout << "fail: comando invalido\n";
    }
  }
}
