#include <iostream>
#include <vector>
#include <cmath>

std::vector<int> sozinhos(const std::vector<int> fila) {
  std::vector<int> elementosSozinhos = {};

  for(int i = 0; i < fila.size(); i++) {
    bool existe = false;
    int vezesRepetidas = 0;

    for(int j = 0; j < elementosSozinhos.size(); j++) {
      if (fila[i] == elementosSozinhos[j]) {
        existe = true;
        break;
      }
    }

    for(int k = 0; k < fila.size(); k++) {
      if (std::abs(fila[i]) == std::abs(fila[k])) {
        vezesRepetidas++;
      }
    }

    if (!existe && vezesRepetidas == 1)
      elementosSozinhos.push_back(fila[i]);
  }

  return elementosSozinhos;
}

int maisOcorrencias(const std::vector<int> fila) {
  int maiorQuantidadeRepeticao = 0;

  for (int i = 0; i < fila.size(); i++) {
    int quantidadeElementosRepetidos = 0;

    for (int j = 0; j < fila.size(); j++) {
      if (std::abs(fila[i]) == std::abs(fila[j])) {
        quantidadeElementosRepetidos++;
      }
    }

    if (quantidadeElementosRepetidos > maiorQuantidadeRepeticao) {
      maiorQuantidadeRepeticao = quantidadeElementosRepetidos;
    }
  }

  return maiorQuantidadeRepeticao;
}

std::vector<int> maisRecorrentes(const std::vector<int> fila) {
  std::vector<int> elementosMaisRecorrentes = {};

  int maiorQuantidadeRepeticao = 0;

  for (int i = 0; i < fila.size(); i++) {
    int quantidadeElementosRepetidos = 0;

    for (int k = 0; k < fila.size(); k++) {
      if (std::abs(fila[i]) == std::abs(fila[k])) {
        quantidadeElementosRepetidos++;
      }
    }

    if (quantidadeElementosRepetidos >= maiorQuantidadeRepeticao) {      
      maiorQuantidadeRepeticao = quantidadeElementosRepetidos;
    }
  }

  for (int i = 0; i < fila.size(); i++) {
    int quantidadeElementosRepetidos = 0;
    bool existe = false;

    for (int j = 0; j < elementosMaisRecorrentes.size(); j++) {
      if (std::abs(fila[i]) == std::abs(elementosMaisRecorrentes[j])) {
        existe = true;
      }
    }

    if (!existe) {
      for (int k = 0; k < fila.size(); k++) {
        if (std::abs(fila[i]) == std::abs(fila[k])) {
          quantidadeElementosRepetidos++;
        }
      }

      if (quantidadeElementosRepetidos == maiorQuantidadeRepeticao) {      
        elementosMaisRecorrentes.push_back(std::abs(fila[i]));
      }
    }
  }

  return elementosMaisRecorrentes;
}

void imprimirVetor(const std::vector<int> vetor) {
  for (int i = 0; i < vetor.size(); i++) {
    std::cout << vetor[i] << "\n";
  }
}

int main() {
  std::vector<int> elementosSozinhos = sozinhos({1, 3, 4, 3, -6, -1, -2, -2});
  imprimirVetor(elementosSozinhos);
  std::cout << "\n";

  int nivelMaiorRepeticao = maisOcorrencias({1, 3, 4, 5, -1, -5, -5});
  std::cout << nivelMaiorRepeticao << "\n\n";

  std::vector<int> elementosMaisRecorrentes = maisRecorrentes({1, 3, 4, 5, -1, -5, -5, 3, -3});
  imprimirVetor(elementosMaisRecorrentes);
}