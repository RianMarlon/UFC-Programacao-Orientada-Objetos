#include <iostream>
#include <vector>
#include <sstream>

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
  std::vector<Grafite> grafites;
  
  Lapiseira(float calibre) : calibre { calibre } {}

  bool inserir(Grafite grafite) {
    if (grafite.calibre != calibre) {
      std::cout << "fail: calibre incompatível\n";
      return false;
    }

    this->grafites.push_back(grafite); 
  }
  
  void mostrarGrafites() {
    if (this->grafites.size() > 0) {
      for (int i = 0; i < this->grafites.size(); i++) {
        std::cout << grafites[i] << "\n";
      }
    } else {
      std::cout << "warning: grafites acabaram\n";
    }
  }

  void escrever(int folhas) {
    int folhasEscritas { 0 };

    while (this->grafites.size() > 0 && folhasEscritas != folhas) {
      if (this->grafites[0].tamanho >= this->grafites[0].desgastePorFolha()) {
        this->grafites[0].tamanho -= this->grafites[0].desgastePorFolha();
        folhasEscritas++;
      } else {
        this->remover(); 
      }
    }

    if (folhasEscritas == 0) {
      std::cout << "warning: grafites acabaram\n";
    } else if (folhas > folhasEscritas) {
      std::cout << "fail: folhas escritas completas: " << folhasEscritas << "\n";
      std::cout << "warning: grafites acabaram\n";
    }
  }

  Grafite* remover() {
    if (this->grafites.size() > 0) {
      Grafite grafiteRemovido = this->grafites[0];
      this->grafites.erase(this->grafites.begin());
      return &grafiteRemovido;
    } else {
      std::cout << "warning: lapiseira sem grafite\n";
      return nullptr;
    }
  }

  friend std::ostream& operator<<(std::ostream& os, const Lapiseira& lapiseira) {
    if (lapiseira.grafites.size() > 0) {
      os << "calibre: " << lapiseira.calibre << ", " << lapiseira.grafites[0];
    } else {
      os << "calibre: " << lapiseira.calibre << ", " << "grafite: null";
    }

    return os;
  }
};

int main() {
  Lapiseira lapiseira = Lapiseira(0.5f);

  while(true) {
    std::string line;
    std::cout << "$" << " ";
    std::getline(std::cin, line);
    std::stringstream ss(line);
    std::string cmd;
    ss >> cmd;  

    if(cmd == "iniciar") {
      float calibre {};
      ss >> calibre;
      lapiseira = Lapiseira(calibre);
    } else if(cmd == "ajuda") {
      std::cout << "iniciar _calibre;\n" 
        << "mostrar;\n"
        << "mostrar_grafites;\n"
        << "inserir _calibre _dureza _tamanho;\n"
        << "remover;\n"
        << "escrever _folhas\n";
    } else if(cmd == "inserir") {
      float calibre {};
      std::string dureza {};
      int tamanho {};
      ss >> calibre;
      ss >> dureza;
      ss >> tamanho;

      lapiseira.inserir(Grafite(calibre, dureza, tamanho));
    } else if(cmd == "mostrar") {
      std::cout << lapiseira << "\n";
    } else if(cmd == "mostrar_grafites") {
      lapiseira.mostrarGrafites();
    } else if (cmd == "escrever") {
      int paginas {};
      ss >> paginas;
      lapiseira.escrever(paginas);
    } else if(cmd == "remover") {
      lapiseira.remover();
    } else if(cmd == "encerrar") {
      break;
    } else {
      std::cout << "fail: comando invalido" << "\n";
    }
  }

  return 0;
}