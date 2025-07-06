#include <TabelaHash.cpp>

vector<Registro> lerCSV(const string& nomeArquivo, size_t colunaChave = 0) {
  vector<Registro> registros;
  ifstream arquivo(nomeArquivo);
  string linha;

  if (!arquivo.is_open()) {
    cerr << "Erro ao abrir o arquivo " << nomeArquivo << endl;
    return registros;
  }

  getline(arquivo, linha);

  while (getline(arquivo, linha)) {
    stringstream ss(linha);
    string campo;
    vector<string> dados;
    string chave;

    size_t colunaAtual = 0;
    while (getline(ss, campo, ',')) {
      if (colunaAtual == colunaChave) {
        chave = campo;
      }
      dados.push_back(campo);
      colunaAtual++;
    }

    if (!chave.empty()) {
      registros.emplace_back(chave, dados);
    }
  }

  arquivo.close();
  return registros;
}

void escreverCSV(const string& nomeArquivo, const vector<Registro>& registros) {
  ofstream arquivo(nomeArquivo);

  if (!arquivo.is_open()) {
    cerr << "Erro ao criar o arquivo " << nomeArquivo << endl;
    return;
  }

  arquivo << "Chave,Dados\n";

  for (const auto& reg : registros) {
    arquivo << reg.chave << ",";
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

int main() {
  string arquivoEntrada = "dataset.csv";
  string arquivoSaida = "dataset_sem_duplicatas.csv";

  auto registros = lerCSV(arquivoEntrada, 0);

  TabelaHash tabela(100, "encadeamento_exterior", "divisao");

  for (const auto& reg : registros) {
    tabela.inserir(reg);
  }

  auto registrosUnicos = tabela.obterRegistrosUnicos();

  escreverCSV(arquivoSaida, registrosUnicos);

  cout << "Deduplicação concluída. Registros únicos: " << registrosUnicos.size()
       << " (original: " << registros.size() << ")" << endl;

  return 0;
}