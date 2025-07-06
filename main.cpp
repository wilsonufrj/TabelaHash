#include "TabelaHash.h" // Inclui a definição da TabelaHash e indiretamente Registro.h
#include <iostream>     // Para std::cout, std::cerr
#include <fstream>      // Para std::ifstream, std::ofstream
#include <sstream>      // Para std::stringstream
#include <vector>       // Para std::vector
#include <string>       // Para std::string

// Usar std:: explicitamente ou declarar 'using namespace std;' no escopo da função ou globalmente (se apropriado para .cpp)
// Para este arquivo, vamos usar std:: explicitamente para clareza.

std::vector<Registro> lerCSV(const std::string& nomeArquivo, size_t colunaChave = 0) {
  std::vector<Registro> registros;
  std::ifstream arquivo(nomeArquivo);
  std::string linha;

  if (!arquivo.is_open()) {
    std::cerr << "Erro ao abrir o arquivo " << nomeArquivo << std::endl;
    return registros;
  }

  // Pula o cabeçalho
  if (!getline(arquivo, linha)) {
    std::cerr << "Erro ao ler o cabeçalho ou arquivo vazio: " << nomeArquivo << std::endl;
    return registros;
  }

  while (getline(arquivo, linha)) {
    std::stringstream ss(linha);
    std::string campo;
    std::vector<std::string> dadosLinha;
    std::string chave;

    size_t colunaAtual = 0;
    while (getline(ss, campo, ',')) {
      if (colunaAtual == colunaChave) {
        chave = campo;
      }
      dadosLinha.push_back(campo);
      colunaAtual++;
    }

    if (!chave.empty()) {
      registros.emplace_back(chave, dadosLinha);
    } else if (!dadosLinha.empty()) {
        // Fallback: se a coluna chave estiver vazia mas existirem outros dados,
        // talvez usar o primeiro campo como chave, ou registrar um aviso.
        // Por ora, vamos assumir que uma chave vazia para uma linha com dados é um problema ou a linha deve ser ignorada.
        // Se a linha inteira estiver vazia (além da chave), getline não a pegaria ou ss estaria vazia.
        std::cerr << "Aviso: Linha com dados mas chave vazia encontrada. Chave da coluna: " << colunaChave << ". Linha: " << linha << std::endl;
    }
  }

  arquivo.close();
  return registros;
}

void escreverCSV(const std::string& nomeArquivo, const std::vector<Registro>& registros, const std::vector<std::string>& cabecalho) {
  std::ofstream arquivo(nomeArquivo);

  if (!arquivo.is_open()) {
    std::cerr << "Erro ao criar o arquivo " << nomeArquivo << std::endl;
    return;
  }

  // Escreve o cabeçalho
  if (!cabecalho.empty()) {
    for (size_t i = 0; i < cabecalho.size(); ++i) {
      arquivo << cabecalho[i];
      if (i < cabecalho.size() - 1) {
        arquivo << ",";
      }
    }
    arquivo << "\n";
  } else {
      // Se não houver cabeçalho, podemos escrever um padrão ou deixar como está.
      // O README menciona que a primeira linha é o cabeçalho.
      // Para consistência, idealmente leríamos e preservaríamos o cabeçalho original.
  }


  for (const auto& reg : registros) {
    // Assume que reg.dados contém todos os campos na ordem correta, incluindo a chave
    for (size_t i = 0; i < reg.dados.size(); ++i) {
      arquivo << reg.dados[i];
      if (i != reg.dados.size() - 1) {
        arquivo << ",";
      }
    }
    arquivo << "\n";
  }

  arquivo.close();
}

std::vector<std::string> lerCabecalho(const std::string& nomeArquivo) {
    std::ifstream arquivo(nomeArquivo);
    std::string linha;
    std::vector<std::string> cabecalho;

    if (!arquivo.is_open()) {
        std::cerr << "Erro ao abrir o arquivo para ler o cabeçalho: " << nomeArquivo << std::endl;
        return cabecalho;
    }

    if (getline(arquivo, linha)) {
        std::stringstream ss(linha);
        std::string campo;
        while (getline(ss, campo, ',')) {
            cabecalho.push_back(campo);
        }
    }
    arquivo.close();
    return cabecalho;
}


int main() {
  std::string arquivoEntrada = "dataset.csv";
  std::string arquivoSaida = "dataset_sem_duplicatas.csv";
  size_t colunaChave = 0; // Coluna 0 (ID) como chave para deduplicação

  std::vector<std::string> cabecalho = lerCabecalho(arquivoEntrada);
  auto registros = lerCSV(arquivoEntrada, colunaChave);

  if (registros.empty() && cabecalho.empty()) {
      std::cerr << "Nenhum dado lido do arquivo de entrada ou arquivo não encontrado." << std::endl;
      return 1;
  }


  TabelaHash tabela(registros.size() > 0 ? registros.size() : 100, "encadeamento_exterior", "divisao");

  int duplicatasRejeitadas = 0;
  for (const auto& reg : registros) {
    if (!tabela.inserir(reg)) {
        duplicatasRejeitadas++;
    }
  }

  auto registrosUnicos = tabela.obterRegistrosUnicos();

  escreverCSV(arquivoSaida, registrosUnicos, cabecalho);

  std::cout << "Deduplicação concluída." << std::endl;
  std::cout << "Registros lidos: " << registros.size() << std::endl;
  std::cout << "Registros únicos escritos: " << registrosUnicos.size() << std::endl;
  std::cout << "Duplicatas rejeitadas: " << duplicatasRejeitadas << std::endl;


  return 0;
}