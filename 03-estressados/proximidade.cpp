#include<iostream>
#include<vector>
#include<cmath>

int briga(const std::vector<int> fila) {
  int quantidadeBrigas = 0;
  for (int i = 0; i < fila.size(); i++) {
    if (i > 0 && (i + 1) < fila.size()) {
      if (std::abs(fila[i]) > 50) {
        if (std::abs(fila[i - 1]) > 30 && std::abs(fila[i + 1]) > 30) {
          quantidadeBrigas++;
        } 
      }
    }
  }

  return quantidadeBrigas;
}

std::vector<int> apaziguado(const std::vector<int> fila) {
  std::vector<int> posicoesApaziguados = {};

  for (int i = 0; i < fila.size(); i++) {
    if (i > 0 && (i + 1) < fila.size()) {
      if (std::abs(fila[i]) > 80) {
        if (std::abs(fila[i - 1]) < 10 || std::abs(fila[i + 1]) < 10) {
          posicoesApaziguados.push_back(i);
        } 
      }
    }
  }

  return posicoesApaziguados;
}

void imprimirVetor(const std::vector<int> vetor) {
  for (int i = 0; i < vetor.size(); i++) {
    std::cout << vetor[i] << "\n";
  }
}

int main() {
  int quantidadeBrigas = briga({32, 51, 20, -40, 52, 32, -2});
  std::cout << quantidadeBrigas << "\n\n";

  std::vector<int> posicoesApaziguados = apaziguado({32, 9, 85, -5, 52, 98, -20});
  imprimirVetor(posicoesApaziguados);
}