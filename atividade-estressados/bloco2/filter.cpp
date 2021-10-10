#include <iostream>
#include <vector>
#include <string>

std::vector<int> clone(const std::vector<int> fila) {
  std::vector<int> novaFila;

  for (int i = 0; i < fila.size(); i++) {
    novaFila.push_back(fila[i]);
  }

  return novaFila;
}

std::vector<int> pegarHomens(const std::vector<int> fila) {
  std::vector<int> homens;

  for (int i = 0; i < fila.size(); i++) {
    if (fila[i] > 0) {
      homens.push_back(fila[i]);
    }
  }

  return homens;
}

std::vector<int> pegarCalmos(const std::vector<int> fila) {
  std::vector<int> calmos;

  for (int i = 0; i < fila.size(); i++) {
    int valor = fila[i] > 0 ? fila[i] : fila[i] * -1;
    if (valor < 10) {
      calmos.push_back(fila[i]);
    }
  }

  return calmos;
}

std::vector<int> pegarMulheresCalmas(const std::vector<int> fila) {
  std::vector<int> mulheresCalmas;
  
  for (int i = 0; i < fila.size(); i++) {
    if (fila[i] > -10 && fila[i] < 0) {
      mulheresCalmas.push_back(fila[i]);
    }
  }

  return mulheresCalmas;
}

void imprimirVetor(const std::vector<int> vetor) {
  for (int i = 0; i < vetor.size(); i++) {
    std::cout << vetor[i] << "\n";
  }
}

int main() {
  // Clonar vetor
  std::vector<int> clone1 = clone({5, 3, -1, -50});
  std::vector<int> clone2 = clone({-51, 29, 10, -50, -20, -99});

  imprimirVetor(clone1);
  std::cout << "\n";
  imprimirVetor(clone2);
  std::cout << "\n";

  // Retorna lista de homens
  std::vector<int> homens1 = pegarHomens({5, 3, -1, -50});
  std::vector<int> homens2 = pegarHomens({-51, 29, 10, -50, -99});

  imprimirVetor(homens1);
  std::cout << "\n";
  imprimirVetor(homens2);
  std::cout << "\n";

  // Retorna lista de calmos
  std::vector<int> calmos1 = pegarCalmos({5, -3, -81, -50});
  std::vector<int> calmos2 = pegarCalmos({-51, -9, 5, -50, -99});

  imprimirVetor(calmos1);
  std::cout << "\n";
  imprimirVetor(calmos2);
  std::cout << "\n";

  // Retorna lista de mulheres calmas
  std::vector<int> mulheresCalmas1 = pegarMulheresCalmas({-5, -3, 1, 50});
  std::vector<int> mulheresCalmas2 = pegarMulheresCalmas({-51, -9, 5, -50, -99});

  imprimirVetor(mulheresCalmas1);
  std::cout << "\n";
  imprimirVetor(mulheresCalmas2);
}