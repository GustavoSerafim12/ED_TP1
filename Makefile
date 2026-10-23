# ==============================================================
#  Makefile - TP1
#
#  Comandos:
#    make          -> compila o programa (bin/tp1.out)
#    make run      -> compila (se preciso) e executa
#    make clean    -> apaga os arquivos gerados
# ==============================================================

# --- Compilador e flags ---------------------------------------
CXX      = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -O2 -Iinclude
# -MMD -MP: gera arquivos .d com as dependencias de cada .cpp,
# assim, se um .h mudar, os .cpp que o incluem sao recompilados.
DEPFLAGS = -MMD -MP

# --- Pastas ----------------------------------------------------
SRC_DIR = src
OBJ_DIR = obj
BIN_DIR = bin

# --- Arquivos --------------------------------------------------
# Todos os .cpp de src/ viram um .o correspondente em obj/
SRCS   = $(wildcard $(SRC_DIR)/*.cpp)
OBJS   = $(SRCS:$(SRC_DIR)/%.cpp=$(OBJ_DIR)/%.o)
DEPS   = $(OBJS:.o=.d)
TARGET = $(BIN_DIR)/tp1.out

# --- Regras ----------------------------------------------------

# Regra padrao (executada quando se digita apenas "make")
all: $(TARGET)

# Junta (linka) todos os .o no executavel final
$(TARGET): $(OBJS) | $(BIN_DIR)
	$(CXX) $(CXXFLAGS) $^ -o $@

# Compila cada .cpp em um .o separado.
# So recompila o que mudou, deixando a compilacao mais rapida.
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp | $(OBJ_DIR)
	$(CXX) $(CXXFLAGS) $(DEPFLAGS) -c $< -o $@

# Cria as pastas obj/ e bin/ caso nao existam
$(OBJ_DIR) $(BIN_DIR):
	mkdir -p $@

# Executa o programa (a entrada vem do teclado ou de um arquivo:
#   make run < entrada.txt)
run: $(TARGET)
	./$(TARGET)

# Remove tudo o que foi gerado pela compilacao
clean:
	rm -rf $(OBJ_DIR) $(BIN_DIR)

# Inclui as dependencias geradas (o "-" ignora se ainda nao existirem)
-include $(DEPS)

# Alvos que nao sao arquivos
.PHONY: all run clean
