#include <sstream>
#include <iostream>
#include <vector>
#include <optional>

std::vector<std::string> mySplit(std::string texto, char delimiter) {
  int posicaoAtual = 0;
  int posicaoAnterior = 0;

  std::vector<std::string> textos;
  
  while (posicaoAtual < texto.length()) {
    if (texto[posicaoAtual] == delimiter) {
      textos.push_back(texto.substr(posicaoAnterior, posicaoAtual - posicaoAnterior));
      posicaoAnterior = posicaoAtual + 1;
    } else if (posicaoAtual == (texto.length() - 1)) {
      textos.push_back(texto.substr(posicaoAnterior, posicaoAtual - posicaoAnterior + 1));
      posicaoAnterior = posicaoAtual;
    }

    posicaoAtual++;
  }

  return textos;
}

struct Grafite {
  float calibre;
  std::string dureza;
  int tamanho;

  Grafite(float calibre, std::string dureza, int tamanho) : calibre { calibre }, dureza { dureza }, tamanho { tamanho } {};

  int desgastePorFolha() {
    if (this->dureza == "HB") {
      return 1;
    } else if (this->dureza == "2B") {
      return 2;
    } else if (this->dureza == "4B") {
      return 4;
    } else if (this->dureza == "6B") {
      return 6;
    } else {
      return 0;
    }
  }

  friend std::ostream& operator<<(std::ostream& os, const Grafite& grafite ) {
    os << "grafite: [" << grafite.calibre << ":" << grafite.dureza << ":" << grafite.tamanho << "]";
    return os;
  }
};

struct Lapiseira {
  float calibre;
  std::optional<Grafite> grafite;

  Lapiseira(float calibre) : calibre { calibre } {}

  bool inserir(Grafite grafite) {
    if (grafite.calibre != calibre) {
      std::cout << "fail: calibre incompatível\n";
      return false;
    } else if (this->grafite.has_value()) {
      std::cout << "fail: ja existe grafite\n";
      return false;
    }

    this->grafite = grafite;
  }

  void escrever(int folhas) {
    int folhasEscritas { 0 };

    if (this->grafite.has_value()) {
      while (folhas > folhasEscritas && this->grafite.value().tamanho >= this->grafite.value().desgastePorFolha()) {
        this->grafite.value().tamanho -= this->grafite.value().desgastePorFolha();
        folhasEscritas++;
      }

      if (folhas > folhasEscritas) {
        this->remover();
        std::cout << "fail: folhas escritas completas: " << folhasEscritas << "\n";
        std::cout << "warning: grafite acabou\n";
      } else if (grafite.value().tamanho == 0) {
        this->remover();
        std::cout << "warning: grafite acabou\n";
      }
    }
  }

  std::optional<Grafite> remover() {
    if (this->grafite.has_value()) {
      Grafite grafiteRemovido = this->grafite.value();
      this->grafite.reset();

      return grafiteRemovido;
    } else {
      std::cout << "warning: lapiseira sem grafite\n";
    }
  }

  friend std::ostream& operator<<(std::ostream& os, const Lapiseira& lapiseira) {
    if (lapiseira.grafite.has_value()) {
      os << "calibre: " << lapiseira.calibre << ", " << lapiseira.grafite.value();
    } else {
      os << "calibre: " << lapiseira.calibre << ", " << "grafite: null";
    }

    return os;
  }
};

struct Solver{
  static void main() {
    Lapiseira lapiseira = Lapiseira(0.5f);
    while(true) {
      std::string line;
      std::cout << "$" << " ";
      std::getline(std::cin, line);

      std::vector<std::string> ui = mySplit(line, ' ');

      if(ui[0] == "encerrar") {
        break;
      } else if(ui[0] == "ajuda") {
        std::cout << "iniciar _calibre; mostrar; inserir _calibre _dureza _tamanho; remover; escrever _folhas; encerrar\n";
      } else if(ui[0] == "iniciar") {
        lapiseira = Lapiseira(std::stof(ui[1]));
      } else if(ui[0] == "inserir") {
        float calibre = std::stof(ui[1]);
        std::string dureza = ui[2];
        int tamanho = std::stoi(ui[3]);
        lapiseira.inserir(Grafite(calibre, dureza, tamanho));
      } else if(ui[0] == "remover") {
        lapiseira.remover();
      } else if(ui[0] == "mostrar") {
        std::cout << lapiseira << "\n";
      } else if (ui[0] == "escrever") {
        lapiseira.escrever(std::stoi(ui[1]));
      } else {
        std::cout << "fail: comando invalido" << "\n";
      }
    }
  }
};

struct Manual {
  static void main() {
    //case inserindo grafites
    Lapiseira lapiseira = Lapiseira(0.5f);
    std::cout << lapiseira << "\n";
    //calibre: 0.5, grafite: null
    lapiseira.inserir(Grafite(0.7f, "2B", 50));
    //fail: calibre incompatível
    lapiseira.inserir(Grafite(0.5f, "2B", 50));
    std::cout << lapiseira << "\n";
    //calibre: 0.5, grafite: [0.5:2B:50]

    //case inserindo e removendo
    lapiseira = Lapiseira(0.3f);
    lapiseira.inserir(Grafite(0.3f, "2B", 50));
    std::cout << lapiseira << "\n";
    //calibre: 0.3, grafite: [0.3:2B:50]
    lapiseira.inserir(Grafite(0.3f, "4B", 70));
    //fail: ja existe grafite
    std::cout << lapiseira << "\n";
    //calibre: 0.3, grafite: [0.3:2B:50]
    lapiseira.remover();
    lapiseira.inserir(Grafite(0.3f, "4B", 70));
    std::cout << lapiseira << "\n";
    //calibre: 0.3, grafite: [0.3:4B:70]

    //case escrevendo 1
    lapiseira = Lapiseira(0.9f);
    lapiseira.inserir(Grafite(0.9f, "4B", 4));
    lapiseira.escrever(1);
    //warning: grafite acabou
    std::cout << lapiseira << "\n";
    //calibre: 0.9, grafite: null
    lapiseira.inserir(Grafite(0.9f, "4B", 30));
    lapiseira.escrever(6);
    std::cout << lapiseira << "\n";
    //calibre: 0.9, grafite: [0.9:4B:6]
    lapiseira.escrever(3);
    //fail: folhas escritas completas: 1
    //warning: grafite acabou
    std::cout << lapiseira << "\n";
    //calibre: 0.9, grafite: null

    //case escrevendo 2
    lapiseira = Lapiseira(0.9f);
    lapiseira.inserir(Grafite(0.9f, "2B", 15));
    std::cout << lapiseira << "\n";
    //calibre: 0.9, grafite: [0.9:2B:15]
    lapiseira.escrever(4);
    std::cout << lapiseira << "\n";
    //calibre: 0.9, grafite: [0.9:2B:7]
    lapiseira.escrever(4);
    //fail: folhas escritas completas: 3
    //warning: grafite acabou
    std::cout << lapiseira << "\n";
    //calibre: 0.9, grafite: null
  }
};

int main() {
  Solver::main();

  return 0;
}