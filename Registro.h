#ifndef REGISTRO_H
#define REGISTRO_H

#include <string>
#include <vector>
#include <sstream> // Para std::stringstream em futuras implementações, se necessário
#include <fstream> // Para std::ifstream, std::ofstream em futuras implementações, se necessário
#include <iostream> // Para std::cout, std::cerr em futuras implementações, se necessário
#include <list> // Para std::list em futuras implementações, se necessário
#include <functional> // Para std::function em futuras implementações, se necessário
#include <cmath> // Para std::cmath em futuras implementações, se necessário


// Usar using namespace std; em arquivos .h geralmente é desencorajado
// para evitar poluição do namespace global. É melhor usar std:: prefixo.

class Registro {
 public:
  std::string chave;
  std::vector<std::string> dados;

  Registro(const std::string& chave, const std::vector<std::string>& dados);

  bool operator==(const Registro& outro) const;
};

#endif // REGISTRO_H
