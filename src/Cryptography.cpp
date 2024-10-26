/*
** EPITECH PROJECT, 2024
** B5-CNA-cryptography
** File description:
** Cryptography
*/

#include <fstream>
#include <iostream>

#include "AES.hpp"
#include "XOR.hpp"
#include "RSA.hpp"
#include "PGPAES.hpp"
#include "PGPXOR.hpp"
#include "Cryptography.hpp"

void Cryptography::Cryptography::help()
{
    std::ifstream file(HELP_FILE_PATH);
    std::string line;

    if (!file.is_open())
        throw(CriptographyException("Error while trying to display the help usage"));
    while (std::getline(file, line))
        std::cout << line << std::endl;
    file.close();
}

void Cryptography::Cryptography::_setInput()
{
    char c;

    if (_input.size() > 0)
        return;
    while (std::cin.get(c)) {
        if (c == '\0')
            break;
        _input += c;
    }
    if (_input.size() > 0 && _input[_input.size() - 1] == '\n')
        _input.pop_back();
}

void Cryptography::Cryptography::_setFlags()
{
    for (std::size_t i = 0; i < _args.size(); i++) {
        if (_args[i][0] == '-') {
            _flags.push_back(_args[i]);
            _args.erase(_args.begin() + i);
            i--;
        }
    }
}

void Cryptography::Cryptography::run()
{
    std::string method;

    for (auto &arg : _args)
        if (arg == "-h" || arg == "--help")
            help();
    
    if (_args.size() < 1)
        throw CriptographyException("Invalid number of arguments");
    if (CRYPTO_METHODS.find(_args[0]) == CRYPTO_METHODS.end())
        throw CriptographyException("Invalid method");
    method = _args[0];
    _args.erase(_args.begin());
    _setFlags();
    CRYPTO_METHODS.at(method)();
}

void Cryptography::Cryptography::_xor()
{
    std::map<std::string, bool> flags = {
        {"-c", false},
        {"-d", false},
        {"-b", false},
    };

    for (auto &flag : _flags) {
        if (flags.find(flag) == flags.end())
            throw CriptographyException("Invalid flag");
        flags[flag] = true;
    }

    if ((flags["-c"] && flags["-d"]) || (!flags["-c"] && !flags["-d"]))
        throw CriptographyException("Invalid flags combination");

    if (_args.size() != 1)
        throw CriptographyException("Invalid number of arguments");


    XOR XOR(_args[0]);
    
    _setInput();

    if ((flags["-b"] && flags["-c"] && _input.size() != _args[0].size() / 2)
    || (flags["-b"] && flags["-d"] && _input.size() != _args[0].size())
    || (!flags["-b"] && flags["-c"] && _input.size() > _args[0].size() / 2)
    || (!flags["-b"] && flags["-d"] && _input.size() > _args[0].size()))
        throw CriptographyException("Invalid block size");


    if (flags["-c"])
        std::cout << XOR.encrypt(_input, !flags["-b"]) << std::endl;
    else
        std::cout << XOR.decrypt(_input, !flags["-b"]) << std::endl;
}

void Cryptography::Cryptography::_aes()
{
    std::map<std::string, bool> flags = {
        {"-c", false},
        {"-d", false},
        {"-b", false},
    };

    for (auto &flag : _flags) {
        if (flags.find(flag) == flags.end())
            throw CriptographyException("Invalid flag");
        flags[flag] = true;
    }

    if ((flags["-c"] && flags["-d"]) || (!flags["-c"] && !flags["-d"]))
        throw CriptographyException("Invalid flags combination");

    if (_args.size() != 1)
        throw CriptographyException("Invalid number of arguments");
    

    AES::AES aes(_args[0]);
    
    _setInput();

    if ((flags["-b"] && flags["-c"] && _input.size() != _args[0].size() / 2)
    || (flags["-b"] && flags["-d"] && _input.size() != _args[0].size()))
        throw CriptographyException("Invalid block size");

    if (flags["-c"])
        std::cout << aes.encrypt(_input) << std::endl;
    else
        std::cout << aes.decrypt(_input) << std::endl;
}

void Cryptography::Cryptography::_rsa()
{
    std::map<std::string, bool> flags = {
        {"-c", false},
        {"-d", false},
        {"-g", false},
    };

    for (auto &flag : _flags) {
        if (flags.find(flag) == flags.end())
            throw CriptographyException("Invalid flag");
        flags[flag] = true;
    }

    if ((flags["-c"] && flags["-d"]) || (flags["-g"] && (flags["-c"] || flags["-d"]))
    || (!flags["-c"] && !flags["-d"] && !flags["-g"]))
        throw CriptographyException("Invalid flags combination");

    if (((flags["-c"] || flags["-d"]) && _args.size() != 1)
    || (flags["-g"] && _args.size() != 2))
        throw CriptographyException("Invalid number of arguments");


    RSA::RSA rsa;

    if (!flags["-g"])
        _setInput();

    if (flags["-g"]) {
        rsa.generateKeys(_args[0], _args[1]);
        std::cout << "public key: " << rsa.publicKey.getKey() << std::endl;
        std::cout << "private key: " << rsa.privateKey.getKey() << std::endl;
    } else if (flags["-c"]) {
        rsa.publicKey.load(_args[0]);
        std::cout << rsa.encrypt(_input) << std::endl;
    } else {
        rsa.privateKey.load(_args[0]);
        std::cout << rsa.decrypt(_input) << std::endl;
    }
}

void Cryptography::Cryptography::_pgp_aes()
{
    std::map<std::string, bool> flags = {
        {"-c", false},
        {"-d", false},
        {"-b", false},
    };

    for (auto &flag : _flags) {
        if (flags.find(flag) == flags.end())
            throw CriptographyException("Invalid flag");
        flags[flag] = true;
    }

    if ((flags["-c"] && flags["-d"]) || (!flags["-c"] && !flags["-d"]))
        throw CriptographyException("Invalid flags combination");

    if (_args.size() != 1)
        throw CriptographyException("Invalid number of arguments");

    std::size_t pos = _args[0].find(":");
    if (pos == std::string::npos)
        throw CriptographyException("Invalid key");

    std::string const aeskey = _args[0].substr(0, pos);
    std::string const rsakey = _args[0].substr(pos + 1);

    if (flags["-c"]) {
        PGPAES::PGPAES pgp_aes(aeskey);
        pgp_aes.rsa.publicKey.load(rsakey);

        _setInput();
    
        if ((flags["-b"] && _input.size() != aeskey.size() / 2))
            throw CriptographyException("Invalid block size");
    
        auto res = pgp_aes.encrypt(_input);

        std::cout << std::get<0>(res) << std::endl;
        std::cout << std::get<1>(res) << std::endl;
    } else {
        PGPAES::PGPAES pgp_aes;
        pgp_aes.rsa.privateKey.load(rsakey);
        
        _setInput();

        std::cout << pgp_aes.decrypt(_input, aeskey) << std::endl;
    }
}

void Cryptography::Cryptography::_pgp_xor()
{
    std::map<std::string, bool> flags = {
        {"-c", false},
        {"-d", false},
        {"-b", false},
    };

    for (auto &flag : _flags) {
        if (flags.find(flag) == flags.end())
            throw CriptographyException("Invalid flag");
        flags[flag] = true;
    }

    if ((flags["-c"] && flags["-d"]) || (!flags["-c"] && !flags["-d"]))
        throw CriptographyException("Invalid flags combination");

    if (_args.size() != 1)
        throw CriptographyException("Invalid number of arguments");

    std::size_t pos = _args[0].find(":");
    if (pos == std::string::npos)
        throw CriptographyException("Invalid key");

    std::string const xorkey = _args[0].substr(0, pos);
    std::string const rsakey = _args[0].substr(pos + 1);


    if (flags["-c"]) {
        PGPXOR::PGPXOR pgp_xor(xorkey);
        pgp_xor.rsa.publicKey.load(rsakey);
        
        _setInput();

        if ((flags["-b"] && _input.size() != xorkey.size() / 2))
            throw CriptographyException("Invalid block size");

        auto res = pgp_xor.encrypt(_input);

        std::cout << std::get<0>(res) << std::endl;
        std::cout << std::get<1>(res) << std::endl;
    } else {
        PGPXOR::PGPXOR pgp_xor;
        pgp_xor.rsa.privateKey.load(rsakey);

        _setInput();

        std::cout << pgp_xor.decrypt(_input, xorkey) << std::endl;
    }
}
