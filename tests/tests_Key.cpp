/*
** EPITECH PROJECT, 2024
** B5-CNA-cryptography
** File description:
** tests_Key
*/

#include <criterion/criterion.h>
#include <criterion/redirect.h>
#include "Key.hpp"

Test (Key, KeyExceptionMissWord4)
{

    const size_t KEYSIZE = 4;
    try {
        
        Cryptography::AES::Key<KEYSIZE> key({
            Cryptography::AES::Word<KEYSIZE>({103, 97, 109, 101}),
            Cryptography::AES::Word<KEYSIZE>({32, 111, 102, 32}),
            Cryptography::AES::Word<KEYSIZE>({116, 104, 114, 111})
        });

        cr_assert(0, "No exception thrown");
    } catch (std::exception &e) {
        std::string msg = "Key Error: Key must have " + std::to_string(KEYSIZE) + " words";
        cr_assert_str_eq(e.what(), msg.c_str());
    }

}


Test (Key, KeyExceptionTooManyWord2)
{

    const size_t KEYSIZE = 2;
    try {
        
        Cryptography::AES::Key<KEYSIZE> key({
            Cryptography::AES::Word<KEYSIZE>({103, 97}),
            Cryptography::AES::Word<KEYSIZE>({32, 111}),
            Cryptography::AES::Word<KEYSIZE>({116, 104})
        });

        cr_assert(0, "No exception thrown");
    } catch (std::exception &e) {
        std::string msg = "Key Error: Key must have " + std::to_string(KEYSIZE) + " words";
        cr_assert_str_eq(e.what(), msg.c_str());
    }

}

Test (Key, KeyOperator)
{
    
        const size_t KEYSIZE = 4;
        Cryptography::AES::Key<KEYSIZE> key({
            Cryptography::AES::Word<KEYSIZE>({103, 97, 109, 101}),
            Cryptography::AES::Word<KEYSIZE>({32, 111, 102, 32}),
            Cryptography::AES::Word<KEYSIZE>({116, 104, 114, 111}),
            Cryptography::AES::Word<KEYSIZE>({110, 101, 115, 10})
        });
    
        std::array<unsigned char, KEYSIZE * KEYSIZE> expected1 = {103, 97, 109, 101, 32, 111, 102, 32, 116, 104, 114, 111, 110, 101, 115, 10};
        std::array<unsigned char, KEYSIZE * KEYSIZE> expected2 = {103, 97, 109, 101, 32, 111, 102, 32, 116, 104, 114, 111, 110, 101, 125, 10};
    
        cr_assert((key == expected1) == true);
        cr_assert((key != expected1) == false);
        cr_assert((key == expected2) == false);
        cr_assert((key != expected2) == true);
}
