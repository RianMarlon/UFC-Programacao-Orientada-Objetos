#include <iostream>
#include <vector>
#include <sstream>

struct Pessoa {
  std::string nome;
  int idade;

  Pessoa(std::string nome = "", int idade = 0) {
    this->nome = nome;
    this->idade = idade;
  }

  friend std::ostream& operator<<(std::ostream& os, const Pessoa& pessoa) {
    os << pessoa.nome << ":" << pessoa.idade;
    return os;
  }
};

struct Motoca {
  Pessoa* pessoa { nullptr };
  int tempo { 0 };
  int potencia { 1 };

  Motoca() {}

  bool inserirPessoa(Pessoa* pessoa) {
    if (this->pessoa != nullptr) {
      std::cout << "fail: moto ocupada\n";
      return false;
    }

    if (pessoa->idade > 10) {
      std::cout << "fail: muito grande para andar de moto\n";
      return false;
    }

    this->pessoa = pessoa;
    return true;
  }

  void comprarTempo(int tempo) {
    this->tempo += tempo;
  }

  bool dirigir(int tempo) {
    if (this->pessoa == nullptr) {
      std::cout << "fail: moto vazia\n";
      return false;
    }

    if (this->tempo > 0) {
      if (tempo > this->tempo) {
        std::cout << "fail: andou " << this->tempo << " min e acabou o tempo\n";
        this->tempo = 0;
      } else {
        this->tempo -= tempo;
      }
    } else {
      std::cout << "fail: tempo zerado\n";
    }

    return true;
  }

  void buzinar() {
    std::cout << "P" << std::string(this->potencia, 'e') << "m\n";
  }

  Pessoa* removerPessoa() {
    if (this->pessoa != nullptr) {
      Pessoa* pessoaRemovida = this->pessoa;
      this->pessoa = nullptr;
      return pessoaRemovida;
    } else {
      std::cout << "fail: moto vazia\n";
      return nullptr;
    }
  }

  friend std::ostream& operator<<(std::ostream& os, const Motoca& motoca) {
    if (motoca.pessoa != nullptr) {
      os << "potencia: " << motoca.potencia << ", minutos: " << motoca.tempo << ", pessoa: [" << *motoca.pessoa << "]";
    } else {
      os << "potencia: " << motoca.potencia << ", minutos: " << motoca.tempo << ", pessoa: null";
    }
    
    return os;
  }
};

int main() {
  Motoca motoca = Motoca();

  while(true) {
    std::string line;
    std::cout << "$" << " ";
    std::getline(std::cin, line);
    std::stringstream ss(line);
    std::string cmd;
    ss >> cmd;

    if (cmd == "iniciar") {
      int potencia {};
      ss >> potencia;
      motoca.potencia = potencia;
    } else if(cmd == "ajuda") {
        std::cout << "iniciar _potencia;\n"
          << "mostrar;\n"
          << "inserir _nome _idade;\n"
          << "comprar _tempo;\n"
          << "dirigir _tempo;\n"
          << "buzinar;\n"
          << "remover;\n"
          << "encerrar\n";
    } else if (cmd == "mostrar") {
      std::cout << motoca << "\n";
    } else if (cmd == "inserir") {
      std::string nome {};
      int idade {};
      ss >> nome >> idade;
      Pessoa* pessoa = new Pessoa(nome, idade);

      if (!motoca.inserirPessoa(pessoa)) {
        delete pessoa;
      }
    } else if (cmd == "comprar") {
      int tempo {};
      ss >> tempo;
      motoca.comprarTempo(tempo);
    } else if (cmd == "dirigir") {
      int tempo {};
      ss >> tempo;
      motoca.dirigir(tempo);
    } else if (cmd == "buzinar") {
      motoca.buzinar();
    } else if (cmd == "remover") {
      Pessoa* pessoaRemovida = motoca.removerPessoa();

      if (pessoaRemovida != nullptr) {
        delete pessoaRemovida;
      }
    } else if (cmd == "encerrar") {
      break;
    } else {
      std::cout << "Comando nao existe\n";
    }
  }

  return 0;
}