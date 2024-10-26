/*
** EPITECH PROJECT, 2024
** B5-CNA-cryptography
** File description:
** main
*/

#include <iostream>
#include "Cryptography.hpp"


int main(int ac, char **av)
{
    try {
        Cryptography::Cryptography crypto(std::vector<std::string>(av + 1, av + ac));
        crypto.run();
        return Cryptography::Cryptography::EXIT_SUCCESS_CODE;
    } catch (const std::exception &e) {
        std::cerr << e.what() << std::endl;
        return Cryptography::Cryptography::EXIT_FAILURE_CODE;
    }
}
