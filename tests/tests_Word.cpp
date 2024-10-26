/*
** EPITECH PROJECT, 2024
** B5-CNA-cryptography
** File description:
** tests_Word
*/

#include <criterion/criterion.h>
#include <criterion/redirect.h>
#include "Word.hpp"

Test (Word, WordException)
{
    const size_t KEYSIZE = 4;
    try {
        
        Cryptography::AES::Word<KEYSIZE> word({103, 97, 109});

        cr_assert(0, "No exception thrown");
    } catch (std::exception &e) {
        std::string msg = "Word Error: Word must have " + std::to_string(KEYSIZE) + " bytes";
        cr_assert_str_eq(e.what(), msg.c_str());
    }
}
