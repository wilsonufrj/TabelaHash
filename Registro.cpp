#include "Registro.h" // Inclui a definição da classe do arquivo de cabeçalho

// Implementação do construtor
Registro::Registro(const std::string& chave, const std::vector<std::string>& dados)
    : chave(chave), dados(dados) {}

// Implementação do operador de igualdade
bool Registro::operator==(const Registro& outro) const {
  return chave == outro.chave && dados == outro.dados;
}