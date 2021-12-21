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

struct Trenzinho {
  std::vector<Pessoa*> pessoas;
  int potencia { 1 };
  int capacidade { 1 };
  int tempo { 0 };

  Trenzinho() {}

  bool inserirPessoa(Pessoa* pessoa) {
    if (this->pessoas.size() == capacidade) {
      std::cout << "fail: trenzinho cheio\n";
      return false;
    }

    if (pessoa->idade > 10) {
      std::cout << "fail: muito grande para entrar no trenzinho\n";
      return false;
    }

    this->pessoas.push_back(pessoa);
    return true;
  }

  void comprarTempo(int tempo) {
    this->tempo += tempo;
  }

  bool dirigir(int tempo) {
    if (this->pessoas.size() == 0) {
      std::cout << "fail: trenzinho vazio\n";
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

  Pessoa* removerPessoa(int posicao) {
    if (this->pessoas.size() > 0 ) {
      if (posicao >= 0 && this->pessoas.size() > posicao) {
        Pessoa pessoaRemovida = *this->pessoas[posicao];
        this->pessoas[posicao] = nullptr;
        this->pessoas.erase(this->pessoas.begin() + posicao);
        return &pessoaRemovida;
      } else {
        std::cout << "fail: posicao vazia\n";
        return nullptr;
      }
    } else {
      std::cout << "fail: trenzinho vazio\n";
      return nullptr;
    }
  }

  friend std::ostream& operator<<(std::ostream& os, const Trenzinho& trenzinho) {
    os << "potencia: " << trenzinho.potencia << ", minutos: " << trenzinho.tempo << ", pessoas: ";
    if (trenzinho.pessoas.size() > 0) {
      os << "[";
      for (int i = 0; i < trenzinho.pessoas.size(); i++) {
        if (i == 0) {
          os << *trenzinho.pessoas[i];
        } else {
          os << "; " << *trenzinho.pessoas[i];
        }
      }
      os << "]";
    } else {
      os << "null";
    }
    
    return os;
  }
};

int main() {
  Trenzinho trenzinho = Trenzinho();

  while(true) {
    std::string line;
    std::cout << "$" << " ";
    std::getline(std::cin, line);
    std::stringstream ss(line);
    std::string cmd;
    ss >> cmd;

    if (cmd == "iniciar") {
      int potencia {};
      int capacidade {};
      ss >> potencia;
      ss >> capacidade;

      trenzinho.potencia = potencia;
      trenzinho.capacidade = capacidade;
    } else if(cmd == "ajuda") {
        std::cout << "iniciar _potencia _capacidade;\n"
          << "mostrar;\n"
          << "inserir _nome _idade;\n"
          << "comprar _tempo;\n"
          << "dirigir _tempo;\n"
          << "buzinar;\n"
          << "remover _posicao;\n"
          << "encerrar\n";
    } else if (cmd == "mostrar") {
      std::cout << trenzinho << "\n";
    } else if (cmd == "inserir") {
      std::string nome {};
      int idade {};
      ss >> nome >> idade;
      Pessoa* pessoa = new Pessoa(nome, idade);

      if (!trenzinho.inserirPessoa(pessoa)) {
        delete pessoa;
      }
    } else if (cmd == "comprar") {
      int tempo {};
      ss >> tempo;
      trenzinho.comprarTempo(tempo);
    } else if (cmd == "dirigir") {
      int tempo {};
      ss >> tempo;
      trenzinho.dirigir(tempo);
    } else if (cmd == "buzinar") {
      trenzinho.buzinar();
    } else if (cmd == "remover") {
      int posicao {};
      ss >> posicao;

      Pessoa* pessoaRemovida = trenzinho.removerPessoa(posicao);

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