#include <iostream>
#include <vector>

std::vector<int> inverterComCopia(const std::vector<int> fila) {
  std::vector<int> filaInvertida;

  for (int i = (fila.size() - 1); i >= 0; i--) {
    filaInvertida.push_back(fila[i]);
  }

  return filaInvertida;
}

void inverterInplace(std::vector<int> &fila) {
  for (int i = 0; i < (fila.size() / 2); i++) {
    int posicao = fila.size() - i - 1;
    int valorTemporario = fila[posicao];
    fila[posicao] = fila[i];
    fila[i] = valorTemporario;
  }
}

int sortear(const std::vector<int> fila) {
  int numeroAleatorio = rand() % fila.size();

  return fila[numeroAleatorio];
}

void embaralhar(std::vector<int> &fila) {
  for (int i = 0; i < fila.size(); i++) {
    int numeroAleatorio = rand() % fila.size();

    int valorTemporario = fila[i];
    fila[i] = fila[numeroAleatorio];
    fila[numeroAleatorio] = valorTemporario;
  }
}

void ordenar(std::vector<int> &fila) {
  for (int i = 0; i < fila.size(); i++) {
    for (int j = 0; j < fila.size(); j++) {
      if (j > i && fila[j] < fila[i]) {
        int valorTemporario = fila[i];
        fila[i] = fila[j];
        fila[j] = valorTemporario;
      }
    }
  }
}

void imprimirVetor(std::vector<int> vetor) {
  for (int i = 0; i < vetor.size(); i++) {
    std::cout << vetor[i] << "\n";
  }
}

int main() {
  std::vector<int> vetorInvertido1 = inverterComCopia({-5, -3, 1, 50});
  std::cout << "\n";
  imprimirVetor(vetorInvertido1);
  std::cout << "\n";

  std::vector<int> vetorParaInverter = {43, 322, 593, 53, 4, 8, 9};
  inverterInplace(vetorParaInverter);

  std::cout << "\n";
  imprimirVetor(vetorParaInverter);
  std::cout << "\n";

  std::vector<int> vetorParaSortear = {43, 322, 53, 4, 8, 9};
  std::cout << sortear(vetorParaSortear) << "\n";

  std::vector<int> vetorParaEmbaralhar = {43, 322, 53, 4, 8, 9};
  embaralhar(vetorParaEmbaralhar);

  std::cout << "\n";
  imprimirVetor(vetorParaEmbaralhar);
  std::cout << "\n";

  std::vector<int> vetorParaOrdenar = {43, 222, 5, 40, 80, 9};
  ordenar(vetorParaOrdenar);

  std::cout << "\n";
  imprimirVetor(vetorParaOrdenar);
  std::cout << "\n";
}