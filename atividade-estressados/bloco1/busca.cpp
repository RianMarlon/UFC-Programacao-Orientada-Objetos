#include <iostream>
#include <vector>
#include <string>
#include <cmath>

bool existe(const std::vector<int> fila, int valor) {
  for (int i = 0; i < fila.size(); i++)  {
    if (fila[i] == valor) {
      return true;
    }
  }

  return false;
}

int contar(const std::vector<int> fila, int valor) {
  int quantidadeVezes = 0;

  for (int i = 0; i < fila.size(); i++) {
    if (fila[i] == valor) {
      quantidadeVezes++;
    }
  }

  return quantidadeVezes;
}

int procurarValor(const std::vector<int> fila, int valor) {
  for (int i = 0; i < fila.size(); i++) {
    if (fila[i] == valor) {
      return i;
    }
  }

  return -1;
}

int procurarValorApartir(const std::vector<int> fila, int valor, int posicao) {
  for (int i = posicao; i < fila.size(); i++) {
    if (fila[i] == valor) {
      return i;
    }
  }

  return -1;
}

int main() {
  std::cout << existe({-1, -50, -99}, -1) << '\n'; // true
  std::cout << existe({-1, -50, -99}, 10) << '\n'; // false

  std::cout << contar({-1, -50, -1, -99}, -1) << "\n"; // 2
  std::cout << contar({-1, -50, -1, -99}, 10) << "\n"; // 0

  std::cout << procurarValor({-1, -50, -1, -99}, -50) << "\n"; // 1
  std::cout << procurarValor({-1, -50, -1, -99}, 10) << "\n"; // -1

  std::cout << procurarValorApartir({5, 3, -1, -50, -1, -99}, -1, 0) << "\n"; // 2
  std::cout << procurarValorApartir({5, 3, -1, -50, -1, -99}, -1, 3) << "\n"; // 4
  std::cout << procurarValorApartir({5, 3, -1, -50, -1, -99}, -1, 4) << "\n"; // 4
}
