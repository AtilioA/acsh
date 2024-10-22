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
main: clean $(OBJ)/internal_commands.o $(OBJ)/external_commands.o $(OBJ)/signal_handler.o $(OBJ)/string_handler.o $(OBJ)/$(PROJETO).o
	gcc $(OBJ)/*.o -o $(EXE) $(CFLAGS)

$(OBJ)/internal_commands.o: $(SRC)/internal_commands.c $(INC)/internal_commands.h
	gcc -c $(CFLAGS) "$(SRC)/internal_commands.c" -o "$(OBJ)/internal_commands.o"

$(OBJ)/external_commands.o: $(SRC)/external_commands.c $(INC)/external_commands.h
	gcc -c $(CFLAGS) "$(SRC)/external_commands.c" -o "$(OBJ)/external_commands.o"
	
$(OBJ)/signal_handler.o: $(SRC)/signal_handler.c $(INC)/signal_handler.h
	gcc -c $(CFLAGS) "$(SRC)/signal_handler.c" -o "$(OBJ)/signal_handler.o"

$(OBJ)/string_handler.o: $(SRC)/string_handler.c $(INC)/string_handler.h
	gcc -c $(CFLAGS) "$(SRC)/string_handler.c" -o "$(OBJ)/string_handler.o"

$(OBJ)/$(PROJETO).o: $(PROJETO).c
	gcc -c $(CFLAGS) $(PROJETO).c -o "$(OBJ)/$(PROJETO).o"

# Roda o programa com valgrind e flags úteis
val: main
	valgrind --leak-check=full -v --track-origins=yes \
	--show-leak-kinds=all ./$(EXE)

# Roda o programa com valgrind sem flags
valzin: main
	valgrind ./$(EXE)

# Roda o programa com valgrind e salva resultados num .txt (entrada 3)
valtxt: main
	valgrind --leak-check=full -v --show-leak-kinds=all --track-origins=yes --verbose --log-file="valgrind-out.txt" ./$(EXE)

# Limpa objetos e o executável do programa
clean:
	-rm $(OBJ)/*.o
	-rm $(EXE)
