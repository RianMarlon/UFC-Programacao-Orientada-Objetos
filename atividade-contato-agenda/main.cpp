#include <iostream>
#include <ostream>
#include <sstream>
#include <string>
#include <vector>
#include <regex>

class Phone {
  private:
    std::string type;
    std::string number;
  
  public:
    Phone(std::string type, std::string number) {
      if (Phone::validateType(type)) {
        if (Phone::validateNumber(number)) {
          this->setType(type);
          this->setNumber(number);
        } else {
          std::cout << "fail: numero invalido\n";  
        }
      } else {
        std::cout << "fail: tipo de numero invalido\n";
      }
    }

    static bool validate(std::string type, std::string number) {
      return Phone::validateType(type) && Phone::validateNumber(number);
    }

    static bool validateType(std::string type) {
      const std::regex base_regex("casa|fixo|tim|claro|oi|vivo");
      std::smatch match;
      
      return std::regex_match(type, match, base_regex);
    }

    static bool validateNumber(std::string number) {
      const std::regex regexCharacteres("[[:digit:]\\(\\)\\.]+");
      std::smatch match;
      
      return std::regex_match(number, match, regexCharacteres);
    }
    
    std::string getType() const {
      return this->type;
    }

    std::string getNumber() const {
      return this->number;
    }

    void setType(std::string type) {
      if (Phone::validateType(type)) {
        this->type = type;
        return;
      }

      std::cout << "fail: tipo de numero invalido\n";
    }

    void setNumber(std::string number) {
      if (Phone::validateNumber(number)) {
        this->number = number;
        return;
      }

      std::cout << "fail: numero invalido\n";
    }

    friend std::ostream& operator<<(std::ostream& os, const Phone& phone) {
      os << phone.getType() << ":" << phone.getNumber();
      return os;
    }
};

class Contact {
  private:
    std::string name;
    std::vector<Phone> phones;

  protected:
    std::string prefix = "-";

  public:
    Contact(std::string name = "", std::vector<Phone> phones = {}) {
      this->name = name;

      if ((int) phones.size() > 0) {
        for (Phone phone : phones) {
          this->addPhone(phone);
        }
      }
    }

    void addPhone(Phone phone) {
      if (Phone::validate(phone.getType(), phone.getNumber())) {
        this->phones.push_back(phone);
      }
    }
    
    void rmPhone(int index) {
      if (index < 0 || index >= (int) this->phones.size()) {
        std::cout << "fail: telefone nao existe\n";
        return;
      }
      
      auto it = this->phones.begin();
      this->phones.erase(it + index);
    }

    std::string getPrefix() const {
      return this->prefix;
    }

    std::string getName() const {
      return this->name;
    }

    std::vector<Phone> getPhones() const {
      return this->phones;
    }

    void setName(std::string name) {
      this->name = name;
    }

    friend std::ostream& operator<<(std::ostream& os, const Contact& contact) {
      os << contact.getPrefix() << " " << contact.getName();
      std::vector<Phone> phones = contact.getPhones();

      for (int i = 0; i < (int) phones.size(); i++) {
        os << " " << "[" << i << ":" << phones[i] << "]";
      }

      return os;
    }
};

int main() {
  Contact contact = Contact();

  while(true) {
    std::string line;
    std::getline(std::cin, line);
    std::stringstream ss(line);
    std::string cmd;
    ss >> cmd;
    
    if(cmd == "encerrar") {
      break;
    } else if(cmd == "ajuda") {
        std::cout << "iniciar _nomeContato;\n"
          << "mostrar;\n"
          << "adicionar _tipoNumero _numero;\n"
          << "remover _indice;\n"
          << "encerrar;\n";
    } else if(cmd == "iniciar") {
      std::string name {""};
      ss >> name;
      
      contact = Contact(name, {});
    } else if(cmd == "mostrar") {
      std::cout << contact << "\n";
    } else if(cmd == "adicionar") {
      std::string type {""};
      std::string number {""};
      ss >> type >> number;
      
      contact.addPhone(Phone(type, number));
    } else if(cmd == "remover") {
      int index {0};
      ss >> index;

      contact.rmPhone(index);
    } else {
      std::cout << "fail: comando invalido\n";
    }
  }
}
