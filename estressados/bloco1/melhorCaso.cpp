#include <iostream>
#include <vector>
#include <string>

int procurarMenor(const std::vector<int> fila) {
  int menor = fila[0];

  for (int i = 0; i < fila.size(); i++) {
    if (menor > fila[i]) {
      menor = fila[i];
    }
  }

  return menor;
}

int procurarMenorPos(const std::vector<int> fila) {
  int posicao = -1;

  for (int i = 0; i < fila.size(); i++) {
    if (i == 0) {
      posicao = i;
    } else if (fila[posicao] > fila[i]) {
      posicao = i;
    }
  }

  return posicao;
}

int procurarMelhorPosSe(const std::vector<int> fila) {
  int posicao = -1;

  for (int i = 0; i < fila.size(); i++) {
    if (fila[i] > 0) {  
      if (posicao == -1) {
        posicao = i;
      } else if (fila[posicao] > fila[i]) {
        posicao = i;
      }
    }
  }

  return posicao;
}

int main() {
  std::cout << procurarMenor({5, 3, -1, -50, -1, -99}) << "\n"; // -99

  std::cout << procurarMenorPos({5, 3, -1, -50, -1, -99}) << "\n"; // 5

  std::cout << procurarMelhorPosSe({5, 3, -1, -50, -1, -99}) << "\n"; // 1
  std::cout << procurarMelhorPosSe({-1, -50, -1, -99}) << "\n"; // -1
}