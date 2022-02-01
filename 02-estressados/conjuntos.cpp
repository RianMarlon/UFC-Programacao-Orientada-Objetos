#include <iostream>
#include <vector>
#include <cmath>

std::vector<int> exclusivos(const std::vector<int> fila) {
  std::vector<int> elementosExclusivos = {};
  for(int i = 0; i < fila.size(); i++) {
    bool existe = false;
    for(int j = 0; j < elementosExclusivos.size(); j++) {
      if (fila[i] == elementosExclusivos[j]) {
        existe = true;
        break;
      }
    }

    if (!existe)
      elementosExclusivos.push_back(fila[i]);
  }

  return elementosExclusivos;
}

std::vector<int> diferentes(const std::vector<int> fila) {
  std::vector<int> elementosDiferentesNiveis = {};

  for(int i = 0; i < fila.size(); i++) {
    bool existe = false;

    for(int j = 0; j < elementosDiferentesNiveis.size(); j++) {
      if (std::abs(fila[i]) == std::abs(elementosDiferentesNiveis[j])) {
        existe = true;
        break;
      }
    }

    if (!existe) {
      elementosDiferentesNiveis.push_back(std::abs(fila[i]));
    }
  }

  return elementosDiferentesNiveis;
}

std::vector<int> abandonados(const std::vector<int> fila) {
  std::vector<int> elementosAbandonados = {};
  for(int i = 0; i < fila.size(); i++) {
    bool existe = false;

    for(int j = 0; j < elementosAbandonados.size(); j++) {
      if (fila[i] == elementosAbandonados[j]) {
        existe = true;
        break;
      }
    }

    if (!existe) {
      for(int k = 0; k <= fila.size(); k++) {
        if (i != k && fila[i] == fila[k]) {
          elementosAbandonados.push_back(fila[i]);
        }
      }
    }
  }

  return elementosAbandonados;
}

void imprimirVetor(const std::vector<int> vetor) {
  for (int i = 0; i < vetor.size(); i++) {
    std::cout << vetor[i] << "\n";
  }
}

int main() {
  std::vector<int> elementosExclusivos = exclusivos({1, 3, 4, 3, -1, -2, -2});

  imprimirVetor(elementosExclusivos);
  std::cout << "\n";

  std::vector<int> elementosDiferentesNiveis = diferentes({1, 3, 4, 3, -1, -2, -2});

  imprimirVetor(elementosDiferentesNiveis);
  std::cout << "\n";

  std::vector<int> elementosAbandonados = abandonados({1, 3, 4, 3, -1, -2, -2, -2});
  
  std::cout << "\n";
  imprimirVetor(elementosAbandonados);
}