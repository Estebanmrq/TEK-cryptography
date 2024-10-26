/*
** EPITECH PROJECT, 2024
** B-CNA-500-PAR-5-1-cryptography-esteban.marques
** File description:
** RSA
*/

#include <iostream>
#include <sstream>
#include <iomanip>
#include "RSA.hpp"

std::string Cryptography::RSA::RSA::messageToHexa(std::string const &message)
{
    std::stringstream ss;

    for (auto c : message)
        ss << std::hex << std::setw(2) << std::setfill('0') << (int)c;
    return ss.str();
}

std::string Cryptography::RSA::RSA::hexaToMessage(std::string const &message)
{
    std::string result;

    for (std::size_t i = 0; i < message.size(); i += 2) {
        std::string byte = message.substr(i, 2);
        char chr = (char)(int)strtol(byte.c_str(), nullptr, 16);
        result.push_back(chr);
    }
    return result;
}

mpz_class Cryptography::RSA::RSA::_pgcd(mpz_class a, mpz_class m, mpz_class &x, mpz_class &y) const
{
    mpz_class x1 = 0;
    mpz_class y1 = 0;
    mpz_class gcd = 0;

    if (a == 0) {
        x = 0;
        y = 1;
        return m;
    }

    gcd = _pgcd(m % a, a, x1, y1);
    x = y1 - (m / a) * x1;
    y = x1;
    return gcd;
}

mpz_class Cryptography::RSA::RSA::_encryptionExponent(mpz_class euleurInd) const
{
    if (euleurInd < FERMAT_VALUES[0])
        throw RSAException("Encryption exponent is not coprime with Euler's indicator.");
    
    auto e = FERMAT_VALUES[0];
    for (auto f : FERMAT_VALUES) {
        if (f > euleurInd)
            return e;
        e = f;
    }
    return e;
}

mpz_class Cryptography::RSA::RSA::_modInverse(mpz_class a, mpz_class m) const
{
    mpz_class x = 0;
    mpz_class y = 0;

    _pgcd(a, m, x, y);
    return (x % m + m) % m;
}

void Cryptography::RSA::RSA::generateKeys(std::string const &ps, std::string const &qs)
{   
    mpz_class p;
    mpz_class q;

    p.set_str(RSAKey::hexaBigEndianToLittleEndian(ps), 16);
    q.set_str(RSAKey::hexaBigEndianToLittleEndian(qs), 16);

    if (mpz_probab_prime_p(p.get_mpz_t(), 20) == 0 || mpz_probab_prime_p(q.get_mpz_t(), 20) == 0)
        throw RSAException("p or q is not prime.");

    mpz_class n = p * q;

    mpz_class ei = EULEUR_INDICATOR(p, q);
    mpz_class e = _encryptionExponent(ei);
    mpz_class d = _modInverse(e, ei);

    publicKey.load(e, n);
    privateKey.load(d, n);
}

std::string Cryptography::RSA::RSA::encrypt(std::string const &message, bool isHexa)
{
    std::string encrypted;
    mpz_class mes;
    mpz_class cyp;

    mes.set_str(!isHexa ? RSAKey::hexaBigEndianToLittleEndian(messageToHexa(message)) : RSAKey::hexaBigEndianToLittleEndian(message), 16);
    if (mes >= publicKey.getN())
        throw RSAException("The message must be strictly less than the public key's n.");
    mpz_powm(cyp.get_mpz_t(), mes.get_mpz_t(), publicKey.getF().get_mpz_t(), publicKey.getN().get_mpz_t());
    encrypted = cyp.get_str(16);
    return RSAKey::hexaBigEndianToLittleEndian(encrypted.size() % 2 == 0 ? encrypted : "0" + encrypted);
}

std::string Cryptography::RSA::RSA::decrypt(std::string const &message)
{
    std::string decrypted;
    mpz_class cyp;
    mpz_class mes;

    cyp.set_str(RSAKey::hexaBigEndianToLittleEndian(message), 16);
    if (cyp >= privateKey.getN())
        throw RSAException("The message must be strictly less than the private key's n.");
    mpz_powm(mes.get_mpz_t(), cyp.get_mpz_t(), privateKey.getF().get_mpz_t(), privateKey.getN().get_mpz_t());
    decrypted = mes.get_str(16);
    return hexaToMessage(RSAKey::hexaBigEndianToLittleEndian(decrypted.size() % 2 == 0 ? decrypted : "0" + decrypted));
}
