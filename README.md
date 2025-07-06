# Tabela Hash para Deduplicação de Datasets

## 📝 Introdução
Este projeto implementa uma tabela hash em C++ para resolver eficientemente o problema de deduplicação em datasets, uma etapa crucial no pré-processamento de dados para Ciência de Dados e Machine Learning. A solução utiliza uma tabela hash para armazenar e verificar a existência de registros, oferecendo complexidade média O(n) para o processo de deduplicação, o que é significativamente mais rápido que abordagens tradicionais baseadas em ordenação (O(n log n)) para grandes volumes de dados.

O programa lê um arquivo CSV, identifica e remove linhas duplicadas com base em uma coluna chave, e então salva o resultado em um novo arquivo CSV.

## 🏗️ Estrutura do Projeto

```
.
├── Makefile                   # Arquivo para compilação do projeto
├── README.md                  # Este arquivo
├── dataset.csv                # Exemplo de dataset de entrada
├── dataset_sem_duplicatas.csv # Arquivo de saída com dados deduplicados
├── main.cpp                   # Contém a lógica principal do programa (leitura, processamento, escrita)
├── Registro.h                 # Definição da classe Registro
├── Registro.cpp               # Implementação da classe Registro
├── TabelaHash.h               # Definição da classe TabelaHash
└── TabelaHash.cpp             # Implementação da classe TabelaHash
```

## 📄 Formato do `dataset.csv`

O arquivo `dataset.csv` deve ser um arquivo de valores separados por vírgula (CSV). A primeira linha do arquivo é considerada o cabeçalho e é ignorada pelo programa. Cada linha subsequente representa um registro.

**Exemplo:**

```csv
ID,Nome,Email,DataCadastro
1,Ana Silva,ana.silva@email.com,2023-01-15
2,Carlos Souza,carlos.souza@email.com,2023-02-20
3,Ana Silva,ana.silva@email.com,2023-03-10
4,Pedro Lima,pedro.lima@email.com,2023-04-05
```

Neste exemplo, se a coluna `ID` (índice 0) for usada como chave, o registro com `ID=3` seria considerado uma duplicata do registro com `ID=1` se todos os outros campos também forem idênticos. No entanto, a implementação atual considera um registro duplicado se a **chave primária** (definida no `main.cpp`, por padrão a primeira coluna) já existe na tabela hash. Para uma deduplicação mais robusta, onde a duplicata é identificada pela combinação de múltiplos campos ou pela chave E os demais dados, a lógica de inserção na `TabelaHash` e a classe `Registro` (comparação) precisariam ser ajustadas.

## ⚙️ Processo de Deduplicação

1.  **Leitura do CSV:** O programa lê o arquivo `dataset.csv` linha por linha.
2.  **Extração da Chave:** Para cada linha, uma coluna é designada como a "chave" (por padrão, a primeira coluna, índice 0).
3.  **Hashing e Inserção:**
    *   A chave do registro é usada para calcular um índice na tabela hash.
    *   O programa verifica se um registro com essa chave já existe na posição correspondente da tabela (tratando colisões por encadeamento exterior).
    *   Se a chave não existir, o registro completo (chave e todos os dados da linha) é inserido na tabela.
    *   Se a chave já existir, o registro é considerado uma duplicata e não é inserido.
4.  **Escrita do Resultado:** Após processar todas as linhas, os registros únicos armazenados na tabela hash são escritos no arquivo `dataset_sem_duplicatas.csv`.

## 🛠️ Como Compilar e Executar

### Pré-requisitos
- Um compilador C++ que suporte C++11 ou superior (ex: g++)
- `make` (geralmente disponível em sistemas Linux e macOS)

### Compilação
Para compilar o projeto, navegue até o diretório raiz do projeto no terminal e execute o comando:
```bash
make
```
Isso irá gerar um arquivo executável chamado `main`.

### Execução
Após a compilação bem-sucedida, execute o programa com o seguinte comando:
```bash
./main
```
O programa irá ler o `dataset.csv` (ou o arquivo especificado em `main.cpp`), processar os dados e criar o `dataset_sem_duplicatas.csv` com os registros únicos.

### Limpeza
Para remover os arquivos objeto e o executável gerados pela compilação, use:
```bash
make clean
```