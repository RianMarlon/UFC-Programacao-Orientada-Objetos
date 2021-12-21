#include <iostream>
#include <vector>
#include <cmath>

void remove(std::vector<int>& fila, int pessoa) {
  for(int i = 0; i < fila.size(); i++) {
    if (fila[i] == pessoa) {
      fila.erase(fila.begin() + i);

      remove(fila, pessoa);
    }
  }
}

void insert(std::vector<int>& fila, int pessoaInserir, int posicaoInserir) {
  fila.insert(fila.begin() + posicaoInserir, pessoaInserir);
}

void dance(std::vector<int>& fila) {
  for(int i = 0; i < fila.size(); i++) {
    if (i < (fila.size() - 1)) {
      if (std::abs(fila[i]) == std::abs(fila[i + 1])) {
        fila.erase(fila.begin() + i);
        fila.erase(fila.begin() + i);

        dance(fila);
      }
    }
  }
}

void imprimirVetor(const std::vector<int>& vetor) {
  for (int i = 0; i < vetor.size(); i++) {
    std::cout << vetor[i] << "\n";
  }
}

int main() {
  std::vector<int> fila = {1, 3, 7, -6, 6, 8, 7, 7, 8, 2, -9, -6};

  remove(fila, 7);
  imprimirVetor(fila);
  std::cout << "\n";

  insert(fila, 20, 3);
  imprimirVetor(fila);
  std::cout << "\n";

  dance(fila);
  imprimirVetor(fila);
  std::cout << "\n";
}