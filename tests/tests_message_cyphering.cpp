/*
** EPITECH PROJECT, 2024
** B5-CNA-cryptography
** File description:
** tests_message_cyphering
*/

#include <criterion/criterion.h>
#include <criterion/redirect.h>
#include "Key.hpp"

Test(Key, MessageCyphering)
{
    const size_t KEYSIZE = 4;
        
        Cryptography::AES::Key<KEYSIZE> key({
            Cryptography::AES::Word<KEYSIZE>({103, 97, 109, 101}),
            Cryptography::AES::Word<KEYSIZE>({32, 111, 102, 32}),
            Cryptography::AES::Word<KEYSIZE>({116, 104, 114, 111}),
            Cryptography::AES::Word<KEYSIZE>({110, 101, 115, 10})
        });

        Cryptography::AES::Key<KEYSIZE> message({
            Cryptography::AES::Word<KEYSIZE>({0x54, 0x68, 0x65, 0x20}),
            Cryptography::AES::Word<KEYSIZE>({0x49, 0x72, 0x6f, 0x6e}),
            Cryptography::AES::Word<KEYSIZE>({0x20, 0x54, 0x68, 0x72}),
            Cryptography::AES::Word<KEYSIZE>({0x6f, 0x6e, 0x65, 0x2e})
        });

        auto keys = Cryptography::AES::keyExpension(key, 11);

        message.addRoundKey(keys[0]);
        
        std::array<unsigned char, KEYSIZE * KEYSIZE> expected1 = {0x33, 0x09, 0x08, 0x45, 0x69, 0x1d, 0x09, 0x4e, 0x54, 0x3c, 0x1a, 0x1d, 0x01, 0x0b, 0x16, 0x24};
        cr_assert(message == expected1);


        for (std::size_t i = 1; i < 10; ++i) {
            message.subBytes();
            message.shiftRows();
            message.mixColumns();
            message.addRoundKey(keys[i]);
        }
        
        std::array<unsigned char, KEYSIZE * KEYSIZE> expected2 = {0x2a, 0x70, 0x1a, 0xbe, 0xef, 0x67, 0xf5, 0x1b, 0x6e, 0xab, 0x8e, 0x70, 0x29, 0x3c, 0x00, 0x2c};
        cr_assert(message == expected2);

        message.subBytes();
        message.shiftRows();
        message.addRoundKey(keys[10]);
        
        std::array<unsigned char, KEYSIZE * KEYSIZE> expected3 = {0x9c, 0x10, 0x9c, 0x7d, 0xe1, 0x8f, 0x08, 0x88, 0x4a, 0xf1, 0xb6, 0xdd, 0x57, 0x5a, 0x04, 0x02};
        cr_assert(message == expected3);
}

Test (Key, MessageDecyphering)
{
    const size_t KEYSIZE = 4;

    Cryptography::AES::Key<KEYSIZE> key({
        Cryptography::AES::Word<KEYSIZE>({103, 97, 109, 101}),
        Cryptography::AES::Word<KEYSIZE>({32, 111, 102, 32}),
        Cryptography::AES::Word<KEYSIZE>({116, 104, 114, 111}),
        Cryptography::AES::Word<KEYSIZE>({110, 101, 115, 10})
    });

    Cryptography::AES::Key<KEYSIZE> encryptedMessage({
        Cryptography::AES::Word<KEYSIZE>({0x9c, 0x10, 0x9c, 0x7d}),
        Cryptography::AES::Word<KEYSIZE>({0xe1, 0x8f, 0x08, 0x88}),
        Cryptography::AES::Word<KEYSIZE>({0x4a, 0xf1, 0xb6, 0xdd}),
        Cryptography::AES::Word<KEYSIZE>({0x57, 0x5a, 0x04, 0x02})
    });

    auto keys = Cryptography::AES::keyExpension(key, 11);

    encryptedMessage.addRoundKey(keys[10]);
    encryptedMessage.shiftRowsInv();
    encryptedMessage.subBytesInv();

    std::array<unsigned char, KEYSIZE * KEYSIZE> expected2 = {0x2a, 0x70, 0x1a, 0xbe, 0xef, 0x67, 0xf5, 0x1b, 0x6e, 0xab, 0x8e, 0x70, 0x29, 0x3c, 0x00, 0x2c};
    cr_assert(encryptedMessage == expected2);

    for (std::size_t i = 9; i > 0; --i) {
        encryptedMessage.addRoundKey(keys[i]);
        encryptedMessage.mixColumnsInv();
        encryptedMessage.shiftRowsInv();
        encryptedMessage.subBytesInv();
    }

    std::array<unsigned char, KEYSIZE * KEYSIZE> expected1 = {0x33, 0x09, 0x08, 0x45, 0x69, 0x1d, 0x09, 0x4e, 0x54, 0x3c, 0x1a, 0x1d, 0x01, 0x0b, 0x16, 0x24};
    cr_assert(encryptedMessage == expected1);

    encryptedMessage.addRoundKey(keys[0]);

    std::array<unsigned char, KEYSIZE * KEYSIZE> expected3 = {0x54, 0x68, 0x65, 0x20, 0x49, 0x72, 0x6f, 0x6e, 0x20, 0x54, 0x68, 0x72, 0x6f, 0x6e, 0x65, 0x2e};
    cr_assert(encryptedMessage == expected3);
}
