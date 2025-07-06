#include "TabelaHash.h"
#include <vector> // Para std::vector
#include <list>   // Para std::list
#include <string> // Para std::string
#include <functional> // Para std::function, std::hash
#include <cmath>    // Para std::floor

// Implementação das funções de hash auxiliares
size_t TabelaHash::hashDivisao(const std::string& chave) {
  size_t hash = 0;
  for (char c : chave) {
    hash = hash * 31 + c; // Um valor primo comum para multiplicação em hashing
  }
  return hash % tamanho;
}

size_t TabelaHash::hashMultiplicacao(const std::string& chave) {
  const double A = 0.6180339887; // Constante relacionada à razão áurea
  size_t hash_val = 0;
  for (char c : chave) {
    hash_val = hash_val * 31 + c;
  }
  double val = hash_val * A;
  return static_cast<size_t>(tamanho * (val - std::floor(val)));
}

size_t TabelaHash::hashDobra(const std::string& chave) {
  size_t hash = 0;
  // Simples exemplo de dobra, pode ser mais sofisticado
  for (size_t i = 0; i < chave.length(); i += 4) {
    unsigned int segmento = 0;
    for (size_t j = 0; j < 4 && i + j < chave.length(); ++j) {
      segmento = (segmento << 8) + chave[i+j];
    }
    hash += segmento;
  }
  return hash % tamanho;
}

size_t TabelaHash::hashPadrao(const std::string& chave) {
  // Utiliza a função hash padrão da STL para strings
  return std::hash<std::string>{}(chave) % tamanho;
}

// Construtor
TabelaHash::TabelaHash(size_t tamanho, const std::string& metodoColisao, const std::string& tipoHash)
    : tamanho(tamanho), metodoColisao(metodoColisao) {
  tabela.resize(tamanho);

  if (tipoHash == "divisao") {
    funcaoHash = [this](const std::string& chave_str) { return this->hashDivisao(chave_str); };
  } else if (tipoHash == "multiplicacao") {
    funcaoHash = [this](const std::string& chave_str) { return this->hashMultiplicacao(chave_str); };
  } else if (tipoHash == "dobra") {
    funcaoHash = [this](const std::string& chave_str) { return this->hashDobra(chave_str); };
  } else { // Padrão ou qualquer outro valor
    funcaoHash = [this](const std::string& chave_str) { return this->hashPadrao(chave_str); };
  }
}

// Insere um registro na tabela hash
bool TabelaHash::inserir(const Registro& registro) {
  size_t indice = funcaoHash(registro.chave);

  if (metodoColisao == "encadeamento_exterior") {
    for (const auto& reg : tabela[indice]) {
      if (reg.chave == registro.chave) { // Verifica apenas pela chave para duplicatas
        // Se a política fosse verificar todos os dados, seria: if (reg == registro)
        return false; // Chave duplicada encontrada
      }
    }
    tabela[indice].push_back(registro);
    return true;
  }
  // Outros métodos de tratamento de colisão poderiam ser implementados aqui.
  // Por simplicidade, este exemplo foca no encadeamento exterior.
  return false; // Se o método de colisão não for suportado ou falhar
}

// Busca um registro pela chave
Registro* TabelaHash::buscar(const std::string& chave) {
  size_t indice = funcaoHash(chave);
  for (auto& reg : tabela[indice]) {
    if (reg.chave == chave) {
      return &reg;
    }
  }
  return nullptr; // Não encontrado
}

// Remove um registro pela chave
bool TabelaHash::remover(const std::string& chave) {
  size_t indice = funcaoHash(chave);
  for (auto it = tabela[indice].begin(); it != tabela[indice].end(); ++it) {
    if (it->chave == chave) {
      tabela[indice].erase(it);
      return true;
    }
  }
  return false; // Não encontrado
}

// Retorna todos os registros únicos
std::vector<Registro> TabelaHash::obterRegistrosUnicos() const {
  std::vector<Registro> registros;
  for (const auto& bucket : tabela) {
    for (const auto& reg : bucket) {
      registros.push_back(reg);
    }
  }
  return registros;
}
