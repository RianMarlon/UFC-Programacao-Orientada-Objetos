#include<iostream>
#include<vector>

int quantosTimes(const std::vector<int> fila) {
  int quantidadeTimes = 0;

  // true - mulheres
  // false - homens
  bool generoAnterior = true;
  for (int i = 0; i < fila.size(); i++) {
    bool generoAtual = true;
    bool generoPosterior = true;

    if (fila[i] < 0) {
      generoAtual = false;
    } else {
      generoAtual = true;
    }

    if ((i + true) < fila.size()) {
      if (fila[i + 1] < 0) {
        generoPosterior = false;
      } else {
        generoPosterior = true;
      }

      if (i == 0) {
        if (generoAtual == generoPosterior) {
          quantidadeTimes++;
        }
      } else {
        if (generoAnterior != generoAtual && generoAtual == generoPosterior) {
          quantidadeTimes++;
        }
      }
    }

    generoAnterior = generoAtual;
  }

  return quantidadeTimes;
}

int maiorTime(const std::vector<int> fila) {
  int quantidadeMaiorTime = 0;

  for (int i = 0; i < fila.size(); i++) {
    int quantidadeTimeAtual = 1;

    for (int j = i + 1; j < fila.size(); j++) {
      if (
        (fila[i] > 0 && fila[j] > 0) || 
        (fila[i] < 0 && fila[j] < 0)
      ) {
        quantidadeTimeAtual++;
      } else {
        break;
      }
    }

    if (quantidadeTimeAtual > quantidadeMaiorTime) {
      quantidadeMaiorTime = quantidadeTimeAtual;
    }
  }

  return quantidadeMaiorTime;
}

int sozinhos(const std::vector<int> fila) {
  int quantidadeSozinhos = 0;

  // true - mulheres
  // false - homens
  bool generoAnterior = true;
  for (int i = 0; i < fila.size(); i++) {
    bool generoAtual = true;
    bool generoPosterior = true;

    if (fila[i] < 0) {
      generoAtual = false;
    } else {
      generoAtual = true;
    }

    if ((i + true) < fila.size()) {
      if (fila[i + 1] < 0) {
        generoPosterior = false;
      } else {
        generoPosterior = true;
      }

      if (i == 0) {
        if (generoAtual != generoPosterior) {
          quantidadeSozinhos++;
        }
      } else {
        if (generoAnterior != generoAtual && generoAtual != generoPosterior) {
          quantidadeSozinhos++;
        }
      }
    }

    generoAnterior = generoAtual;
  }

  return quantidadeSozinhos;
}

void imprimirVetor(const std::vector<int> vetor) {
  for (int i = 0; i < vetor.size(); i++) {
    std::cout << vetor[i] << "\n";
  }
}

int main() {
  int quantidadeTimes = quantosTimes({-5, 51, 20, -40, 52, 32, -9, -2, -40});
  std::cout << quantidadeTimes << "\n\n";

  int quantidadeMaiorTime = maiorTime({-5, 51, 20, 50, 52, -6, 32, -9, -2, -40});
  std::cout << quantidadeMaiorTime << "\n\n";

  int quantidadeSozinhos = sozinhos({-5, 51, 20, -40, 52, -32, -9, -2, -40});
  std::cout << quantidadeSozinhos;
}