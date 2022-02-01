#include <iostream>
#include <ostream>
#include <sstream>
#include <string>
#include <vector>
#include <map>
#include <regex>

std::vector<std::string> mySplit(std::string text, char delimiter) {
  int currentPosition = 0;
  int previousPosition = 0;

  std::vector<std::string> texts;
  
  while (currentPosition < text.length()) {
    if (text[currentPosition] == delimiter) {
      texts.push_back(text.substr(previousPosition, currentPosition - previousPosition));
      previousPosition = currentPosition + 1;
    } else if (currentPosition == (text.length() - 1)) {
      texts.push_back(text.substr(previousPosition, currentPosition - previousPosition + 1));
      previousPosition = currentPosition;
    }

    currentPosition++;
  }

  return texts;
}

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
      os << phone.type << ":" << phone.number;
      return os;
    }
};

class Contact {
  private:
    std::vector<Phone> phones;
    std::string prefix = "-";

    void sortPhones() {
      std::sort(this->phones.begin(), this->phones.end(), [](Phone phone1, Phone phone2){
        if (phone1.getType() != phone2.getType()) {
          return phone1.getType() < phone2.getType();
        }

        return phone1.getNumber() < phone2.getNumber();
      });
    }

  public:
    Contact(std::vector<Phone> phones = {}) {
      if ((int) phones.size() > 0) {
        for (Phone phone : phones) {
          this->addPhone(phone);
        }
      }

      this->sortPhones();
    }

    void addPhone(Phone phone) {
      if (Phone::validate(phone.getType(), phone.getNumber())) {
        this->phones.push_back(phone);
      }

      this->sortPhones();
    }
    
    void removePhone(int index) {
      if (index < 0 || index >= (int) this->phones.size()) {
        std::cout << "fail: telefone nao existe\n";
        return;
      }
      
      auto it = this->phones.begin();
      this->phones.erase(it + index);
      this->sortPhones();
    }

    std::string getPrefix() const {
      return this->prefix;
    }

    std::vector<Phone> getPhones() const {
      return this->phones;
    }

    friend std::ostream& operator<<(std::ostream& os, const Contact& contact) {
      os << contact.prefix;
      std::vector<Phone> phones = contact.phones;

      for (int i = 0; i < (int) phones.size(); i++) {
        os << " " << "[" << i << ":" << phones[i] << "]";
      }

      return os;
    }
};

class Phonebook {
  private:
    std::map<std::string, Contact> contacts;

  public:
    Phonebook(): contacts {} {};

    void addContact(std::string name, Contact contact) {
      auto it = this->contacts.find(name);

      if (it != this->contacts.end()) {
        for (auto phone : contact.getPhones()) {
          this->contacts[name].addPhone(phone);
        }
      } else {
        this->contacts.insert(std::make_pair(name, contact));
      }
    }

    Contact* findContact(std::string name) {
      auto it = this->contacts.find(name);

      if (it != this->contacts.end()) {
        return &it->second;
      }

      std::cout << "fail: contato nao encontrado";
      return nullptr;
    }
    
    void removeContact(std::string name) {
      auto it = this->contacts.find(name);

      if (it != this->contacts.end()) {
        this->contacts.erase(it);
        return;
      }
      
      std::cout << "fail: contato nao existe\n";
    }

    std::map<std::string, Contact> search(std::string pattern) {
      std::map<std::string, Contact> contactsFinded;

      for (auto& contact : this->contacts) {
        if (contact.first.find(pattern) != std::string::npos) {
          contactsFinded.insert(std::make_pair(contact.first, contact.second));
        } else {
          for (auto& phone : contact.second.getPhones()) {
            std::stringstream ss;
            ss << phone;
            std::string textPhone = ss.str();

            if (textPhone.find(pattern) != std::string::npos) {
              contactsFinded.insert(std::make_pair(contact.first, contact.second));
              break;
            }
          }
        }
      }

      return contactsFinded;
    }

    std::map<std::string, Contact> getContacts() const {
      return this->contacts;
    }

    friend std::ostream& operator<<(std::ostream& os, const Phonebook& phonebook) {
      for (auto [name, contact] : phonebook.getContacts()) {
        os << name << " " << contact << "\n";
      }

      return os;
    }
};

int main() {
  Phonebook phonebook = Phonebook();

  while(true) {
    std::string line;
    std::getline(std::cin, line);
    std::stringstream ss(line);
    std::string cmd;
    ss >> cmd;
    
    if(cmd == "encerrar") {
      break;
    } else if(cmd == "ajuda") {
        std::cout << "mostrar;\n"
          << "pesquisar _texto;\n"
          << "adicionar _nomeContato _tipo:_numero[];\n"
          << "remover _nomeContato;\n"
          << "encerrar;\n";
    } else if(cmd == "mostrar") {
      std::cout << phonebook << "\n";
    } else if(cmd == "pesquisar") {
      std::string pattern;
      ss >> pattern;

      auto contactsFinded = phonebook.search(pattern);
      for (auto contact : contactsFinded) {
        std::cout << contact.first << " " << contact.second << "\n";
      }
    } else if(cmd == "adicionar") {
      std::string nameContact {""};
      std::vector<Phone> phones {};
      ss >> nameContact;

      while(true) {
        std::string currentContact;

        if(ss >> currentContact) {
          std::string type = mySplit(currentContact, ':')[0];
          std::string number = mySplit(currentContact, ':')[1];

          phones.push_back(Phone(type, number));
        } else {
          break;
        }
      }
      
      phonebook.addContact(nameContact, Contact(phones));
    } else if(cmd == "remover") {
      std::string nameContact {""};
      ss >> nameContact;

      phonebook.removeContact(nameContact);
    } else {
      std::cout << "fail: comando invalido\n";
    }
  }
}
