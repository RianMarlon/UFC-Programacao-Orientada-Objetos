#include <iostream>
#include <vector>
#include <string>
#include <cmath>
#include <random>
#include <ctime>

std::vector<int> inverterComCopia(const std::vector<int> fila) {
  std::vector<int> filaInvertida;

  for (int i = (fila.size() - 1); i >= 0; i--) {
    filaInvertida.push_back(fila[i]);
  }

  return filaInvertida;
}

void inverterInplace(std::vector<int> &fila) {
  int tamanhoFila = fila.size();
  for (int i = 0; i < tamanhoFila; i++) {
    int elemento = fila[i];
    
    fila.erase(fila.begin() + i);
    fila.emplace(fila.begin(), elemento);
  }
}

int sortear(const std::vector<int> fila) {
  srand(time(0));

  int numeroAleatorio = rand() % fila.size();

  return fila[numeroAleatorio];
}

void imprimirVetor(std::vector<int> vetor) {
  for (int i = 0; i < vetor.size(); i++) {
    std::cout << vetor[i] << "\n";
  }
}

int main() {
  // Retorna lista de mulheres calmas
  std::vector<int> vetorInvertido1 = inverterComCopia({-5, -3, 1, 50});
  std::vector<int> vetorInvertido2 = inverterComCopia({-51, -9, 5, -50, -99});

  std::cout << "\n";
  imprimirVetor(vetorInvertido1);
  std::cout << "\n";
  imprimirVetor(vetorInvertido2);
  std::cout << "\n";

  std::vector<int> vetorParaInverter = {43, 322, 53, 4, 8, 9};
  inverterInplace(vetorParaInverter);

  std::cout << "\n";
  imprimirVetor(vetorParaInverter);
  std::cout << "\n";

  std::vector<int> vetorParaSortear = {43, 322, 53, 4, 8, 9};
  
  std::cout << sortear(vetorParaSortear) << "\n";
}