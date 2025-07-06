
#include "Registro.cpp"

class TabelaHash {
 private:
  vector<list<Registro>> tabela;
  size_t tamanho;
  function<size_t(const string&)> funcaoHash;
  string metodoColisao;

  // Funções de hash auxiliares
  size_t hashDivisao(const string& chave) {
    size_t hash = 0;
    for (char c : chave) {
      hash = hash * 31 + c;
    }
    return hash % tamanho;
  }

  size_t hashMultiplicacao(const string& chave) {
    const double A = 0.6180339887;  // Constante áurea
    size_t hash = 0;
    for (char c : chave) {
      hash = hash * 31 + c;
    }
    double valor = hash * A;
    return static_cast<size_t>(tamanho * (valor - floor(valor)));
  }

  size_t hashDobra(const string& chave) {
    size_t hash = 0;
    for (char c : chave) {
      hash = (hash << 5) ^ (hash >> 27) ^ c;
    }
    return hash % tamanho;
  }

  size_t hashPadrao(const string& chave) {
    return hash<string>{}(chave) % tamanho;
  }

 public:
  // Construtor
  TabelaHash(size_t tamanho = 100,
             const string& metodoColisao = "encadeamento_exterior",
             const string& tipoHash = "divisao")
      : tamanho(tamanho), metodoColisao(metodoColisao) {
    tabela.resize(tamanho);

    // Seleciona a função de hash
    if (tipoHash == "divisao") {
      funcaoHash = [this](const string& chave) {
        return this->hashDivisao(chave);
      };
    } else if (tipoHash == "multiplicacao") {
      funcaoHash = [this](const string& chave) {
        return this->hashMultiplicacao(chave);
      };
    } else if (tipoHash == "dobra") {
      funcaoHash = [this](const string& chave) {
        return this->hashDobra(chave);
      };
    } else {
      funcaoHash = [this](const string& chave) {
        return this->hashPadrao(chave);
      };
    }
  }

  // Insere um registro na tabela hash (com tratamento de duplicatas)
  bool inserir(const Registro& registro) {
    size_t indice = funcaoHash(registro.chave);

    if (metodoColisao == "encadeamento_exterior") {
      // Verifica se já existe um registro igual
      for (const auto& reg : tabela[indice]) {
        if (reg == registro) {
          return false;  // Registro duplicado
        }
      }
      tabela[indice].push_back(registro);
      return true;
    }
    // Outros métodos de tratamento de colisão podem ser implementados aqui
    return false;
  }

  // Busca um registro pela chave
  Registro* buscar(const string& chave) {
    size_t indice = funcaoHash(chave);

    for (auto& reg : tabela[indice]) {
      if (reg.chave == chave) {
        return &reg;
      }
    }
    return nullptr;
  }

  // Remove um registro pela chave
  bool remover(const string& chave) {
    size_t indice = funcaoHash(chave);

    for (auto it = tabela[indice].begin(); it != tabela[indice].end(); ++it) {
      if (it->chave == chave) {
        tabela[indice].erase(it);
        return true;
      }
    }
    return false;
  }

  // Retorna todos os registros únicos (para deduplicação)
  vector<Registro> obterRegistrosUnicos() const {
    vector<Registro> registros;

    for (const auto& bucket : tabela) {
      for (const auto& reg : bucket) {
        registros.push_back(reg);
      }
    }

    return registros;
  }
};
