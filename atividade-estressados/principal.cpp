#include <iostream>
#include <vector>
#include <string>

bool existe(std::vector<int> fila, int valor) {
  for (int i = 0; i < fila.size(); i++)  {
    if (fila[i] == valor) {
      return true;
    }
  }

  return false;
}

int contar(std::vector<int> fila, int valor) {
  int quantidade_vezes = 0;

  for (int i = 0; i < fila.size(); i++) {
    if (fila[i] == valor) {
      quantidade_vezes++;
    }
  }

  return quantidade_vezes;
}

int procurar_valor(std::vector<int> fila, int valor) {
  for (int i = 0; i < fila.size(); i++) {
    if (fila[i] == valor) {
      return i;
    }
  }

  return -1;
}

int procurar_valor_apartir(std::vector<int> fila, int valor, int posicao) {
  for (int i = posicao; i < fila.size(); i++) {
    if (fila[i] == valor) {
      return i;
    }
  }

  return -1;
}

int procurar_menor(std::vector<int> fila) {
  int menor = fila[0];

  for (int i = 0; i < fila.size(); i++) {
    if (menor > fila[i]) {
      menor = fila[i];
    }
  }

  return menor;
}

int procurar_menor_pos(std::vector<int> fila) {
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

int procurar_melhor_pos_se(std::vector<int> fila) {
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

float calcular_stress_medio(std::vector<int> fila) {
  float soma = 0;

  for (int i = 0; i < fila.size(); i++) {
    soma += fila[i] > 0 ? fila[i] : fila[i] * -1;
  }

  float media = soma / fila.size();

  return media;
}

std::string mais_homens_ou_mulheres(std::vector<int> fila) {
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

std::string qual_metade_eh_mais_estressada(std::vector<int> fila) {
  float soma_primeira = 0;
  float media_primeira = 0;

  float soma_segunda = 0;
  float media_segunda = 0;

  int inicio_primeira = 0;
  int final_primeira = (int) fila.size() / 2;
  int quantidade_primeira = final_primeira - inicio_primeira;
  
  int inicio_segunda = fila.size() % 2 == 0 ? (int) fila.size() / 2 : (int) fila.size() / 2 + 1;
  int final_segunda = fila.size();
  int quantidade_segunda = final_segunda - inicio_segunda;

  for (int i = inicio_primeira; i < final_primeira; i++) {
    soma_primeira += fila[i] > 0 ? fila[i] : fila[i] * -1;
  }

  media_primeira = soma_primeira / quantidade_primeira;

  for (int i = inicio_segunda; i < final_segunda; i++) {
    soma_segunda += fila[i] > 0 ? fila[i] : fila[i] * -1;
  }

  media_segunda = soma_segunda / quantidade_segunda;

  if (media_primeira > media_segunda) {
    return "primeira";
  } else if (media_segunda > media_primeira) {
    return "segunda";
  } else {
    return "empate";
  }
}

bool homens_sao_mais_estressados_que_mulheres(std::vector<int> fila) {
  float soma_homens = 0;
  float media_homens = 0;
  int quantidade_homens = 0;

  float soma_mulheres = 0;
  float media_mulheres = 0;
  int quantidade_mulheres = 0;

  for (int i = 0; i < fila.size(); i++) {
    if (fila[i] > 0) {
      soma_homens += fila[i];
      quantidade_homens++;
    } else {
      soma_mulheres += fila[i] * -1;
      quantidade_mulheres++;
    }
  }

  media_homens = soma_homens / quantidade_homens;
  media_mulheres = soma_mulheres / quantidade_mulheres;

  return media_homens > media_mulheres;
}

std::vector<int> clone(const std::vector<int> fila) {
  std::vector<int> nova_fila;

  for (int i = 0; i < fila.size(); i++) {
    nova_fila.push_back(fila[i]);
  }

  return nova_fila;
}

std::vector<int> pegar_homens(const std::vector<int> fila) {
  std::vector<int> homens;

  for (int i = 0; i < fila.size(); i++) {
    if (fila[i] > 0) {
      homens.push_back(fila[i]);
    }
  }

  return homens;
}

std::vector<int> pegar_calmos(const std::vector<int> fila) {
  std::vector<int> calmos;

  for (int i = 0; i < fila.size(); i++) {
    int valor = fila[i] > 0 ? fila[i] : fila[i] * -1;
    if (valor < 10) {
      calmos.push_back(fila[i]);
    }
  }

  return calmos;
}

std::vector<int> pegar_mulheres_calmas(const std::vector<int> fila) {
  std::vector<int> mulheres_calmas;
  
  for (int i = 0; i < fila.size(); i++) {
    if (fila[i] > -10 && fila[i] < 0) {
      mulheres_calmas.push_back(fila[i]);
    }
  }

  return mulheres_calmas;
}

std::vector<int> inverter_com_copia(const std::vector<int> fila) {
  std::vector<int> fila_invertida;

  for (int i = (fila.size() - 1); i >= 0; i--) {
    fila_invertida.push_back(fila[i]);
  }

  return fila_invertida;
}

void inverter_inplace(std::vector<int> &fila) {
  int tamanho_fila = fila.size();
  for (int i = 0; i < tamanho_fila; i++) {
    int elemento = fila[i];
    
    fila.erase(fila.begin() + i);
    fila.emplace(fila.begin(), elemento);
  }
}

void imprimir_vetor(std::vector<int> vetor) {
  for (int i = 0; i < vetor.size(); i++) {
    std::cout << vetor[i] << "\n";
  }
}

int main() {
  std::cout << existe({-1, -50, -99}, -1) << '\n'; // true
  std::cout << existe({-1, -50, -99}, 10) << '\n'; // false

  std::cout << contar({-1, -50, -1, -99}, -1) << "\n"; // 2
  std::cout << contar({-1, -50, -1, -99}, 10) << "\n"; // 0

  std::cout << procurar_valor({-1, -50, -1, -99}, -50) << "\n"; // 1
  std::cout << procurar_valor({-1, -50, -1, -99}, 10) << "\n"; // -1

  std::cout << procurar_valor_apartir({5, 3, -1, -50, -1, -99}, -1, 0) << "\n"; // 2
  std::cout << procurar_valor_apartir({5, 3, -1, -50, -1, -99}, -1, 3) << "\n"; // 4
  std::cout << procurar_valor_apartir({5, 3, -1, -50, -1, -99}, -1, 4) << "\n"; // 4

  std::cout << procurar_menor({5, 3, -1, -50, -1, -99}) << "\n"; // -99

  std::cout << procurar_menor_pos({5, 3, -1, -50, -1, -99}) << "\n"; // 5

  std::cout << procurar_melhor_pos_se({5, 3, -1, -50, -1, -99}) << "\n"; // 1
  std::cout << procurar_melhor_pos_se({-1, -50, -1, -99}) << "\n"; // -1

  std::cout << calcular_stress_medio({-1, -50, -1, -99}) << "\n"; // -37.75
  std::cout << calcular_stress_medio({5, 3, -1, -50, -1, -99}) << "\n"; // -23.8333

  std::cout << mais_homens_ou_mulheres({5, 3, -1, -50, -1, -99}) << "\n"; // "mulheres"
  std::cout << mais_homens_ou_mulheres({5, 3, 1, -50, -1, -99}) << "\n"; // "empate"
  std::cout << mais_homens_ou_mulheres({5, 3, 1, -50, -1, 99}) << "\n"; // "homens"

  std::cout << qual_metade_eh_mais_estressada({5, 3, -1, -50, -1, -99}) << "\n"; // "segunda"
  std::cout << qual_metade_eh_mais_estressada({50, 98, 2, -50, -1, -99}) << "\n"; // "empate"
  std::cout << qual_metade_eh_mais_estressada({-51, 99, 1, -50, -1, -99}) << "\n"; // "primeira"
  
  std::cout << qual_metade_eh_mais_estressada({5, 3, -1, -50, -1, -99}) << "\n"; // "segunda"
  std::cout << qual_metade_eh_mais_estressada({50, 98, 2, -50, -1, -99}) << "\n"; // "empate"
  std::cout << qual_metade_eh_mais_estressada({-51, 99, 1, -50, -1, -99}) << "\n"; // "primeira"

  std::cout << homens_sao_mais_estressados_que_mulheres({5, 3, -1, -50, -1, -99}) << "\n"; // "false"
  std::cout << homens_sao_mais_estressados_que_mulheres({60, 98, 2, -50, -1, -99}) << "\n"; // "true"
  std::cout << homens_sao_mais_estressados_que_mulheres({-51, 29, 10, -50, -20, -99}) << "\n"; // "false"

  // Clonar vetor
  std::vector<int> clone1 = clone({5, 3, -1, -50});
  std::vector<int> clone2 = clone({-51, 29, 10, -50, -20, -99});

  std::cout << "\n";
  imprimir_vetor(clone1);
  std::cout << "\n";
  imprimir_vetor(clone2);
  std::cout << "\n";

  // Retorna lista de homens
  std::vector<int> homens1 = pegar_homens({5, 3, -1, -50});
  std::vector<int> homens2 = pegar_homens({-51, 29, 10, -50, -99});

  std::cout << "\n";
  imprimir_vetor(homens1);
  std::cout << "\n";
  imprimir_vetor(homens2);
  std::cout << "\n";

  // Retorna lista de calmos
  std::vector<int> calmos1 = pegar_calmos({5, -3, -81, -50});
  std::vector<int> calmos2 = pegar_calmos({-51, -9, 5, -50, -99});

  std::cout << "\n";
  imprimir_vetor(calmos1);
  std::cout << "\n";
  imprimir_vetor(calmos2);
  std::cout << "\n";

  // Retorna lista de mulheres calmas
  std::vector<int> mulheres_calmas1 = pegar_mulheres_calmas({-5, -3, 1, 50});
  std::vector<int> mulheres_calmas2 = pegar_mulheres_calmas({-51, -9, 5, -50, -99});

  std::cout << "\n";
  imprimir_vetor(mulheres_calmas1);
  std::cout << "\n";
  imprimir_vetor(mulheres_calmas2);
  std::cout << "\n";

  // Retorna lista de mulheres calmas
  std::vector<int> vetor_invertido1 = inverter_com_copia({-5, -3, 1, 50});
  std::vector<int> vetor_invertido2 = inverter_com_copia({-51, -9, 5, -50, -99});

  std::cout << "\n";
  imprimir_vetor(vetor_invertido1);
  std::cout << "\n";
  imprimir_vetor(vetor_invertido2);
  std::cout << "\n";

  std::vector<int> vetor_para_inverter = {43, 322, 53, 4, 8, 9};
  inverter_inplace(vetor_para_inverter);

  std::cout << "\n";
  imprimir_vetor(vetor_para_inverter);
  std::cout << "\n";
}