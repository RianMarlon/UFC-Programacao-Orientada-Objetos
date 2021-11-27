#include <iostream>
#include <ostream>
#include <sstream>
#include <string>
#include <vector>
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
    std::string name;
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
    Contact(std::string name = "", std::vector<Phone> phones = {}) {
      this->name = name;

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
      os << contact.prefix << " " << contact.name;
      std::vector<Phone> phones = contact.phones;

      for (int i = 0; i < (int) phones.size(); i++) {
        os << " " << "[" << i << ":" << phones[i] << "]";
      }

      return os;
    }
};

class Phonebook {
  private:
    std::vector<Contact> contacts;

    int findPosByName(std::string name) {
      for (int i = 0; i < (int) this->contacts.size(); i++) {
        if (contacts[i].getName() == name) {
          return i;
        }
      }

      return -1;
    }

    void sortContacts() {
      std::sort(this->contacts.begin(), this->contacts.end(), [](Contact contact1, Contact contact2){
        return contact1.getName() < contact2.getName();
      });
    }

  public:
    Phonebook(): contacts {} {};

    void addContact(Contact contact) {
      int positionContactAlreadyExists = findPosByName(contact.getName());

      if (positionContactAlreadyExists == -1) {
        this->contacts.push_back(contact);
      } else {
        for (auto phone : contact.getPhones()) {
          this->contacts[positionContactAlreadyExists].addPhone(phone);
        }
      }

      this->sortContacts();
    }

    Contact* findContact(std::string name) {
      int position = this->findPosByName(name);

      if (position == -1) {
        std::cout << "fail: contato nao encontrado";
        return nullptr;
      }

      return &this->contacts[position];
    }
    
    void removeContact(std::string name) {
      int position = findPosByName(name);

      if (position == -1) {
        std::cout << "fail: contato nao existe\n";
        return;
      }
      
      this->contacts.erase(this->contacts.begin() + position);
      this->sortContacts();
    }

    std::vector<Contact> search(std::string pattern) {
      std::vector<Contact> contactsFinded;

      for (auto& contact : this->contacts) {
        if (contact.getName().find(pattern) != std::string::npos) {
          contactsFinded.push_back(contact);
        } else {
          for (auto& phone : contact.getPhones()) {
            std::stringstream ss;
            ss << phone;
            std::string textPhone = ss.str();

            if (textPhone.find(pattern) != std::string::npos) {
              contactsFinded.push_back(contact);
              break;
            }
          }
        }
      }

      return contactsFinded;
    }

    std::vector<Contact> getContacts() const {
      return this->contacts;
    }

    friend std::ostream& operator<<(std::ostream& os, const Phonebook& phonebook) {
      std::vector<Contact> contacts = phonebook.getContacts();
      for (int i = 0; i < (int) contacts.size(); i++) {
        os << contacts[i] << "\n";
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

      std::vector<Contact> contactsFinded = phonebook.search(pattern);
      for (int i = 0; i < (int) contactsFinded.size(); i++) {
        std::cout << contactsFinded[i] << "\n";
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
      
      phonebook.addContact(Contact(nameContact, phones));
    } else if(cmd == "remover") {
      std::string nameContact {""};
      ss >> nameContact;

      phonebook.removeContact(nameContact);
    } else {
      std::cout << "fail: comando invalido\n";
    }
  }
}
