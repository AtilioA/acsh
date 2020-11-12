# ACSH - INTEGRANTES:
# Atílio Antônio Dadalto
# Philipe Aguiar Marques
# Renan Moreira Gomes

OBJ      := obj
SRC      := src
INC      := include
CFLAGS   := -lm -g -O2 -Wall -pedantic -Wextra -Wwrite-strings
EXE 	 := acsh
PROJETO  := main

# Cria objetos de todos os arquivos de código-fonte para então linká-los no programa final
main: clean $(OBJ)/sys_wrapper.o $(OBJ)/signal_handler.o $(OBJ)/string_handler.o $(OBJ)/utils.o $(OBJ)/$(PROJETO).o
	gcc $(OBJ)/*.o -o $(EXE) $(CFLAGS)

$(OBJ)/sys_wrapper.o: $(SRC)/sys_wrapper.c $(INC)/sys_wrapper.h
	gcc -c $(CFLAGS) "$(SRC)/sys_wrapper.c" -o "$(OBJ)/sys_wrapper.o"

$(OBJ)/signal_handler.o: $(SRC)/signal_handler.c $(INC)/signal_handler.h
	gcc -c $(CFLAGS) "$(SRC)/signal_handler.c" -o "$(OBJ)/signal_handler.o"

$(OBJ)/string_handler.o: $(SRC)/string_handler.c $(INC)/string_handler.h
	gcc -c $(CFLAGS) "$(SRC)/string_handler.c" -o "$(OBJ)/string_handler.o"

$(OBJ)/utils.o: $(SRC)/utils.c $(INC)/utils.h
	gcc -c $(CFLAGS) "$(SRC)/utils.c" -o "$(OBJ)/utils.o"

$(OBJ)/$(PROJETO).o: $(PROJETO).c
	gcc -c $(CFLAGS) $(PROJETO).c -o "$(OBJ)/$(PROJETO).o"

# Roda o programa com valgrind e flags úteis (entrada 3)
# val: main
# 	valgrind --leak-check=full -v --track-origins=yes \
# 	--show-leak-kinds=all ./$(EXE)

# # Roda o programa com valgrind sem flags (entrada 3)
# valzin: main
# 	valgrind ./$(EXE)

# # Roda o programa com valgrind e salva resultados num .txt (entrada 3)
# valtxt: main
# 	valgrind --leak-check=full -v --show-leak-kinds=all --track-origins=yes --verbose --log-file="valgrind-out.txt" ./$(EXE)

# Limpa objetos e o executável do programa
clean:
	-rm $(OBJ)/*.o
	-rm $(EXE)
