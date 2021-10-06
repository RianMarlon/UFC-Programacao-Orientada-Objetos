#include <iostream>
#include <vector>
#include <string>

float calcularStressMedio(std::vector<int> fila) {
  float soma = 0;

  for (int i = 0; i < fila.size(); i++) {
    soma += std::abs(fila[i]);
  }

  float media = soma / fila.size();

  return media;
}

std::string maisHomensOuMulheres(std::vector<int> fila) {
  int homens = 0;
  int mulheres = 0;

  for (int i = 0; i < fila.size(); i++) {
    if (fila[i] > 0) {
      homens++;
    }

    else if (fila[i] < 0) {
      mulheres++;
    }
  }

  if (homens > mulheres) {
    return "homens";
  } else if (mulheres > homens) {
    return "mulheres";
  } else {
    return "empate";
  }
}

std::string qualMetadeEhMaisEstressada(std::vector<int> fila) {
  float somaPrimeira = 0;
  float mediaPrimeira = 0;

  float somaSegunda = 0;
  float mediaSegunda = 0;

  int inicioPrimeira = 0;
  int finalPrimeira = (int) fila.size() / 2;
  int quantidadePrimeira = finalPrimeira - inicioPrimeira;
  
  int inicioSegunda = fila.size() % 2 == 0 ? (int) fila.size() / 2 : (int) fila.size() / 2 + 1;
  int finalSegunda = fila.size();
  int quantidadeSegunda = finalSegunda - inicioSegunda;

  for (int i = inicioPrimeira; i < finalPrimeira; i++) {
    somaPrimeira += std::abs(fila[i]);
  }

  mediaPrimeira = somaPrimeira / quantidadePrimeira;

  for (int i = inicioSegunda; i < finalSegunda; i++) {
    somaSegunda += std::abs(fila[i]);
  }

  mediaSegunda = somaSegunda / quantidadeSegunda;

  if (mediaPrimeira > mediaSegunda) {
    return "primeira";
  } else if (mediaSegunda > mediaPrimeira) {
    return "segunda";
  } else {
    return "empate";
  }
}

bool homensSaoMaisEstressadosQueMulheres(std::vector<int> fila) {
  float somaHomens = 0;
  float mediaHomens = 0;
  int quantidadeHomens = 0;

  float somaMulheres = 0;
  float mediaMulheres = 0;
  int quantidadeMulheres = 0;

  for (int i = 0; i < fila.size(); i++) {
    if (fila[i] > 0) {
      somaHomens += fila[i];
      quantidadeHomens++;
    } else {
      somaMulheres += std::abs(fila[i]);
      quantidadeMulheres++;
    }
  }

  mediaHomens = somaHomens / quantidadeHomens;
  mediaMulheres = somaMulheres / quantidadeMulheres;

  return mediaHomens > mediaMulheres;
}

int main() {
  std::cout << calcularStressMedio({-1, -50, -1, -99}) << "\n"; // -37.75
  std::cout << calcularStressMedio({5, 3, -1, -50, -1, -99}) << "\n"; // -23.8333

  std::cout << maisHomensOuMulheres({5, 3, -1, -50, -1, -99}) << "\n"; // "mulheres"
  std::cout << maisHomensOuMulheres({5, 3, 1, -50, -1, -99}) << "\n"; // "empate"
  std::cout << maisHomensOuMulheres({5, 3, 1, -50, -1, 99}) << "\n"; // "homens"

  std::cout << qualMetadeEhMaisEstressada({5, 3, -1, -50, -1, -99}) << "\n"; // "segunda"
  std::cout << qualMetadeEhMaisEstressada({50, 98, 2, -50, -1, -99}) << "\n"; // "empate"
  std::cout << qualMetadeEhMaisEstressada({-51, 99, 1, -50, -1, -99}) << "\n"; // "primeira"
  
  std::cout << qualMetadeEhMaisEstressada({5, 3, -1, -50, -1, -99}) << "\n"; // "segunda"
  std::cout << qualMetadeEhMaisEstressada({50, 98, 2, -50, -1, -99}) << "\n"; // "empate"
  std::cout << qualMetadeEhMaisEstressada({-51, 99, 1, -50, -1, -99}) << "\n"; // "primeira"

  std::cout << homensSaoMaisEstressadosQueMulheres({5, 3, -1, -50, -1, -99}) << "\n"; // "false"
  std::cout << homensSaoMaisEstressadosQueMulheres({60, 98, 2, -50, -1, -99}) << "\n"; // "true"
  std::cout << homensSaoMaisEstressadosQueMulheres({-51, 29, 10, -50, -20, -99}) << "\n"; // "false"
}