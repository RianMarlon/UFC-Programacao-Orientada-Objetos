#include <iostream>
#include <vector>
#include <cmath>

int casais(const std::vector<int> fila) {
  std::vector<int> posicoesCasados = {};
  int quantidadeCasais = 0;

  for(int i = 0; i < fila.size(); i++) {
    bool estaCasado = false;

    for (int j = 0; j < posicoesCasados.size(); j++) {
      if (i == posicoesCasados[j]) {
        estaCasado = true;
        break;
      }
    }

    if (!estaCasado) {
      for(int k = 0; k < fila.size(); k++) {
        estaCasado = false;
        for (int l = 0; l < posicoesCasados.size(); l++) {
          if (k == posicoesCasados[l]) {
            estaCasado = true;
            break;
          }
        }

        if (!estaCasado) {
          if (fila[i] != fila[k] && std::abs(fila[i]) == std::abs(fila[k])) {
            quantidadeCasais++;
            posicoesCasados.push_back(i);
            posicoesCasados.push_back(k);
          }
        }
      }
    }
  }

  return quantidadeCasais;
}

int trios(std::vector<int> fila) {
  std::vector<int> posicoesTrios = {};
  int quantidadeTrios = 0;

  for(int i = 0; i < fila.size(); i++) {
    std::vector<int> posicoes = { i };
    bool pertenceTrio = false;

    for(int j = 0; j < posicoesTrios.size(); j++) {
      if (i == posicoesTrios[j]) {
        pertenceTrio = true;
        break;
      }
    }

    if (!pertenceTrio) {
      for(int k = 0; k < fila.size(); k++) {
        pertenceTrio = false;

        for(int m = 0; m < posicoesTrios.size(); m++) {
          if (k == posicoesTrios[m]) {
            pertenceTrio = true;
            break;
          }
        }

        if (!pertenceTrio) {
          if (i != k) {
            if (std::abs(fila[i]) == std::abs(fila[k])) {
              if (posicoes.size() < 3) {
                posicoes.push_back(k);
              } else {
                break;
              }
            }
          }
        }
      }
    }

    if (posicoes.size() > 2) {
      for(int k = 0; k < posicoes.size(); k++) {
        posicoesTrios.push_back(posicoes[k]);
      }
      
      quantidadeTrios++;
    }
  }

  return quantidadeTrios;
}

void imprimirVetor(const std::vector<int> vetor) {
  for (int i = 0; i < vetor.size(); i++) {
    std::cout << vetor[i] << "\n";
  }
}

int main() {
  int quantidadeCasais = casais({1, 3, 4, 3, -6, -1, 2, -2, -6});
  std::cout << quantidadeCasais << "\n\n";

  int quantidadeTrios = trios({1, 3, 4, 3, -4, 2, -3, -1, 4, -4, 4});
  std::cout << quantidadeTrios;
}