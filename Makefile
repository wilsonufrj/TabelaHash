CXX = g++
# Usar -std=c++11 ou mais recente, como c++17 se o compilador suportar.
# -Wall para todos os warnings, -g para informações de debug.
# -I. para incluir o diretório atual na busca por headers (útil para Registro.h, TabelaHash.h)
CXXFLAGS = -std=c++11 -Wall -g -I.

# Arquivos fonte .cpp
SRCS = Registro.cpp TabelaHash.cpp main.cpp

# Arquivos objeto .o (gerados a partir dos .cpp)
OBJS = $(SRCS:.cpp=.o)

# Nome do executável final
TARGET = main

# Regra padrão: compilar tudo
all: $(TARGET)

# Regra para linkar o executável final a partir dos arquivos objeto
# $(OBJS) depende implicitamente das regras de compilação de .o
$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJS)

# Regra genérica para compilar arquivos .cpp em .o
# $< é o primeiro pré-requisito (o arquivo .cpp)
# $@ é o nome do alvo (o arquivo .o)
# Adicionamos as dependências dos arquivos .h para que a recompilação ocorra se eles mudarem.
Registro.o: Registro.cpp Registro.h
	$(CXX) $(CXXFLAGS) -c Registro.cpp -o Registro.o

TabelaHash.o: TabelaHash.cpp TabelaHash.h Registro.h
	$(CXX) $(CXXFLAGS) -c TabelaHash.cpp -o TabelaHash.o

main.o: main.cpp TabelaHash.h Registro.h
	$(CXX) $(CXXFLAGS) -c main.cpp -o main.o

# Regra para limpar arquivos compilados
clean:
	rm -f $(OBJS) $(TARGET)

# Declara alvos que não são arquivos
.PHONY: all clean
