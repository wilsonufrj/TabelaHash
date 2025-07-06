#ifndef TABELAHASH_H
#define TABELAHASH_H

#include "Registro.h" // Inclui a definição da classe Registro
#include <vector>
#include <list>
#include <string>
#include <functional> // Para std::function
#include <cmath>      // Para floor em hashMultiplicacao
#include <iostream>   // Para std::hash em hashPadrao (embora std::hash seja para tipos básicos)

// É preferível usar std::vector, std::list, std::string, std::function
// em vez de "using namespace std;" em arquivos de cabeçalho.

class TabelaHash {
 private:
  std::vector<std::list<Registro>> tabela;
  size_t tamanho;
  std::function<size_t(const std::string&)> funcaoHash;
  std::string metodoColisao; // Pode ser útil no futuro para diferentes estratégias

  // Funções de hash auxiliares (privadas)
  size_t hashDivisao(const std::string& chave);
  size_t hashMultiplicacao(const std::string& chave);
  size_t hashDobra(const std::string& chave);
  size_t hashPadrao(const std::string& chave); // Usando std::hash<std::string>

 public:
  // Construtor
  TabelaHash(size_t tamanho = 100,
             const std::string& metodoColisao = "encadeamento_exterior",
             const std::string& tipoHash = "divisao");

  // Insere um registro na tabela hash (com tratamento de duplicatas)
  bool inserir(const Registro& registro);

  // Busca um registro pela chave
  Registro* buscar(const std::string& chave);

  // Remove um registro pela chave
  bool remover(const std::string& chave);

  // Retorna todos os registros únicos (para deduplicação)
  std::vector<Registro> obterRegistrosUnicos() const;
};

#endif // TABELAHASH_H
