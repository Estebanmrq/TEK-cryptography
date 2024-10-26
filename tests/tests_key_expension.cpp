/*
** EPITECH PROJECT, 2024
** B5-CNA-cryptography
** File description:
** tests_key_expension
*/

#include <criterion/criterion.h>
#include <criterion/redirect.h>
#include "Key.hpp"

Test(Key, KeyExpensionTestingGenerationNumber)
{
    const size_t KEYSIZE = 4;
    
    Cryptography::AES::Key<KEYSIZE> key({
        Cryptography::AES::Word<KEYSIZE>({103, 97, 109, 101}),
        Cryptography::AES::Word<KEYSIZE>({32, 111, 102, 32}),
        Cryptography::AES::Word<KEYSIZE>({116, 104, 114, 111}),
        Cryptography::AES::Word<KEYSIZE>({110, 101, 115, 10})
    });

    auto keys = Cryptography::AES::keyExpension<KEYSIZE>(key, 11);

    cr_assert_eq(keys.size(), 11);
}

// key 0 [0x67, 0x61, 0x6d, 0x65, 0x20, 0x6f, 0x66, 0x20, 0x74, 0x68, 0x72, 0x6f, 0x6e, 0x65, 0x73, 0x0a]
Test(Key, KeyExpensionTestingFirstKey)
{
    const size_t KEYSIZE = 4;
    
    Cryptography::AES::Key<KEYSIZE> key({
        Cryptography::AES::Word<KEYSIZE>({103, 97, 109, 101}),
        Cryptography::AES::Word<KEYSIZE>({32, 111, 102, 32}),
        Cryptography::AES::Word<KEYSIZE>({116, 104, 114, 111}),
        Cryptography::AES::Word<KEYSIZE>({110, 101, 115, 10})
    });

    auto keys = Cryptography::AES::keyExpension<KEYSIZE>(key, 11);
    std::array<unsigned char, KEYSIZE * KEYSIZE> expected = {0x67, 0x61, 0x6d, 0x65, 0x20, 0x6f, 0x66, 0x20, 0x74, 0x68, 0x72, 0x6f, 0x6e, 0x65, 0x73, 0x0a};

    cr_assert(keys[0] == expected);
}

// key 1 [0x2b, 0xee, 0x0a, 0xfa, 0x0b, 0x81, 0x6c, 0xda, 0x7f, 0xe9, 0x1e, 0xb5, 0x11, 0x8c, 0x6d, 0xbf]
Test(Key, KeyExpensionTestingSecondKey)
{
    const size_t KEYSIZE = 4;
    
    Cryptography::AES::Key<KEYSIZE> key({
        Cryptography::AES::Word<KEYSIZE>({103, 97, 109, 101}),
        Cryptography::AES::Word<KEYSIZE>({32, 111, 102, 32}),
        Cryptography::AES::Word<KEYSIZE>({116, 104, 114, 111}),
        Cryptography::AES::Word<KEYSIZE>({110, 101, 115, 10})
    });

    auto keys = Cryptography::AES::keyExpension<KEYSIZE>(key, 11);
    std::array<unsigned char, KEYSIZE * KEYSIZE> expected = {0x2b, 0xee, 0x0a, 0xfa, 0x0b, 0x81, 0x6c, 0xda, 0x7f, 0xe9, 0x1e, 0xb5, 0x11, 0x8c, 0x6d, 0xbf};

    cr_assert(keys[1] == expected);
}

// key 5 [0x34, 0x62, 0x17, 0x36, 0xa9, 0x1f, 0xa8, 0x3b, 0x07, 0xfd, 0xc9, 0xcf, 0xb2, 0xb6, 0x6b, 0x6a]
Test(Key, KeyExpensionTestingSixthKey)
{
    const size_t KEYSIZE = 4;
    
    Cryptography::AES::Key<KEYSIZE> key({
        Cryptography::AES::Word<KEYSIZE>({103, 97, 109, 101}),
        Cryptography::AES::Word<KEYSIZE>({32, 111, 102, 32}),
        Cryptography::AES::Word<KEYSIZE>({116, 104, 114, 111}),
        Cryptography::AES::Word<KEYSIZE>({110, 101, 115, 10})
    });

    auto keys = Cryptography::AES::keyExpension<KEYSIZE>(key, 11);
    std::array<unsigned char, KEYSIZE * KEYSIZE> expected = {0x34, 0x62, 0x17, 0x36, 0xa9, 0x1f, 0xa8, 0x3b, 0x07, 0xfd, 0xc9, 0xcf, 0xb2, 0xb6, 0x6b, 0x6a};

    cr_assert(keys[5] == expected);
}

// key 9 [0xcd, 0xd7, 0x78, 0xc0, 0x47, 0x78, 0xee, 0x2a, 0xeb, 0xf7, 0x7f, 0x54, 0x27, 0x11, 0xf6, 0x21]
Test(Key, KeyExpensionTestingTenthKey)
{
    const size_t KEYSIZE = 4;
    
    Cryptography::AES::Key<KEYSIZE> key({
        Cryptography::AES::Word<KEYSIZE>({103, 97, 109, 101}),
        Cryptography::AES::Word<KEYSIZE>({32, 111, 102, 32}),
        Cryptography::AES::Word<KEYSIZE>({116, 104, 114, 111}),
        Cryptography::AES::Word<KEYSIZE>({110, 101, 115, 10})
    });

    auto keys = Cryptography::AES::keyExpension<KEYSIZE>(key, 11);
    std::array<unsigned char, KEYSIZE * KEYSIZE> expected = {0xcd, 0xd7, 0x78, 0xc0, 0x47, 0x78, 0xee, 0x2a, 0xeb, 0xf7, 0x7f, 0x54, 0x27, 0x11, 0xf6, 0x21};

    cr_assert(keys[9] == expected);
}

// key 10 [0x79, 0x95, 0x85, 0x0c, 0x3e, 0xed, 0x6b, 0x26, 0xd5, 0x1a, 0x14, 0x72, 0xf2, 0x0b, 0xe2, 0x53]
Test(Key, KeyExpensionTestingEleventhKey)
{
    const size_t KEYSIZE = 4;
    
    Cryptography::AES::Key<KEYSIZE> key({
        Cryptography::AES::Word<KEYSIZE>({103, 97, 109, 101}),
        Cryptography::AES::Word<KEYSIZE>({32, 111, 102, 32}),
        Cryptography::AES::Word<KEYSIZE>({116, 104, 114, 111}),
        Cryptography::AES::Word<KEYSIZE>({110, 101, 115, 10})
    });

    auto keys = Cryptography::AES::keyExpension<KEYSIZE>(key, 11);
    std::array<unsigned char, KEYSIZE * KEYSIZE> expected = {0x79, 0x95, 0x85, 0x0c, 0x3e, 0xed, 0x6b, 0x26, 0xd5, 0x1a, 0x14, 0x72, 0xf2, 0x0b, 0xe2, 0x53};

    cr_assert(keys[10] == expected);
}
