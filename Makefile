##
## EPITECH PROJECT, 2024
## B5-CNA-cryptography
## File description:
## Makefile
##

CXX ?= g++
BIN = my_pgp
BIN_TESTS = unit_tests

FILES_UNIT	=	*.gc*

CFLAGS += -Wall -Wextra -Wpedantic -std=c++17
CPPFLAGS += -iquote./include -iquote./include/aes -iquote./include/xor -iquote./include/rsa -iquote./include/pgp-aes -iquote./include/pgp-xor
LDFLAGS += -lgmp -lgmpxx
TEST_LDFLAGS = --coverage -lcriterion

# Source files

SRC_PATH =	./src
TEST_PATH = ./tests

MAIN =	$(SRC_PATH)/main.cpp
SRC =	$(SRC_PATH)/Cryptography.cpp	\
		$(SRC_PATH)/aes/SBox.cpp		\
		$(SRC_PATH)/aes/RCon.cpp		\
		$(SRC_PATH)/aes/AES.cpp			\
		$(SRC_PATH)/aes/Galois.cpp		\
		$(SRC_PATH)/xor/XOR.cpp			\
		$(SRC_PATH)/rsa/RSA.cpp			\
		$(SRC_PATH)/rsa/RSAKey.cpp		\
		$(SRC_PATH)/pgp-aes/PGPAES.cpp	\
		$(SRC_PATH)/pgp-xor/PGPXOR.cpp	\

SRC_TESTS = $(TEST_PATH)/tests_key_expension.cpp		\
			$(TEST_PATH)/tests_Key.cpp  				\
			$(TEST_PATH)/tests_Word.cpp					\
			$(TEST_PATH)/tests_RCon.cpp					\
			$(TEST_PATH)/tests_message_cyphering.cpp	\
			$(TEST_PATH)/tests_cryptography.cpp			\


MAIN_OBJ	=	$(MAIN:.cpp=.o)
OBJS += $(SRC:.cpp=.o)

# Methods

%.o: %.cpp
	$(CXX) $(CFLAGS) $(CPPFLAGS) -c -o $@ $<

all: $(BIN)

$(BIN): $(OBJS) $(MAIN_OBJ)
	$(CXX) $(OBJS) $(MAIN_OBJ) -o $(BIN) $(CFLAGS) $(CPPFLAGS) $(LDFLAGS)

unit_tests: clean
	$(CXX) $(SRC) $(SRC_TESTS) -o $(BIN_TESTS) $(CFLAGS) $(CPPFLAGS) $(LDFLAGS) $(TEST_LDFLAGS)

tests_run: unit_tests
	-./$(BIN_TESTS)

clean:
	$(RM) $(OBJS) $(MAIN_OBJ) $(FILES_UNIT)

fclean: clean
	$(RM) $(BIN) $(BIN_TESTS)

re: fclean all

.PHONY: all $(BIN) clean fclean re unit_tests tests_run
