
#include <cmath>
#include <fstream>
#include <functional>
#include <iostream>
#include <list>
#include <sstream>
#include <string>
#include <vector>

using namespace std;

class Registro {
 public:
  string chave;
  vector<string> dados;

  Registro(const string& chave, const vector<string>& dados)
      : chave(chave), dados(dados) {}

  bool operator==(const Registro& outro) const {
    return chave == outro.chave && dados == outro.dados;
  }
};