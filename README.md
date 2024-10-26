# Cryptography 🔐

**Project Name**: Cryptography  
**Binary Name**: `my_pgp`  
**Language**: `cpp`  
**Compilation**: Uses `Makefile` for compilation with rules for `re`, `clean`, and `fclean`.

## Summary 📋
- [Project Overview](#project-overview)
- [Installation](#installation)
- [Usage](#usage)
- [Crypto Systems](#crypto-systems)
  - [XOR](#xor)
  - [AES](#aes)
  - [RSA](#rsa)
  - [PGP (Pretty Good Privacy)](#pgp-pretty-good-privacy)
- [Contributors](#contributors)

## Project Overview 💡

`my_pgp` is a cryptography tool that allows you to perform encryption and decryption operations using various algorithms. This project implements cryptographic algorithms such as XOR, AES, and RSA to ensure secure communication.

## Installation && Build ⚙️

To install the project
```bash
git clone git@github.com:EpitechPromo2027/B-CNA-500-PAR-5-1-cryptography-esteban.marques.git
cd B-CNA-500-PAR-5-1-cryptography-esteban.marques
```

To build the project
```bash
make
```

To clean up the project of all precompilation files:
```bash
make clean
```

To clean up the project of all binaries:
```bash
make fclean
```

To start test:
```bash
make tests_run
```


## Usage 🔑

- **CRYPTO_SYSTEM**: Specifies the cryptosystem to use:
  - `xor`: XOR algorithm
  - `aes`: 128-bit AES algorithm
  - `rsa`: RSA algorithm
  - `pgp-xor`: RSA + XOR algorithm
  - `pgp-aes`: RSA + AES algorithm

- **MODE**: Operation mode:
  - `-c`: Cipher a clear message
  - `-d`: Decipher an encrypted message
  - `-g`: Generate public/private key pair (for RSA only)

- **OPTIONS**:
  - `-b`: Block mode (applies only to XOR, AES, and PGP). In block mode, message and key must be the same size.
  
- **key**: Key used for ciphering/deciphering. Incompatible with `-g` mode.


## Crypto Systems 🔐

### XOR

XOR encryption ciphers a message by applying the XOR operator with a key. It's simple but vulnerable if the key isn't the same length as the message.

Example:

```txt
~/B-CNA-500> echo "You know nothing, Jon Snow" > message
~/B-CNA-500> ./my_pgp xor -c -b 576861742069732064656164206d6179206e6576657220646965 < message > ciphered
~/B-CNA-500> cat -e ciphered
20070f2700071c6a4449060a490515164e4e12190b190011063c$
~/B-CNA-500> ./my_pgp xor -d -b 576861742069732064656164206d6179206e6576657220646965 < ciphered | cat -e
You know nothing, Jon Snow$
```


### AES

AES encryption uses a 128-bit key. The message is encrypted in blocks of 128 bits. It is a more secure and practical algorithm than XOR.


Here is an example in block mode:
```txt
~/B-CNA-500> echo "All men must die" > message
~/B-CNA-500> ./my_pgp aes -c -b 57696e74657220697320636f6d696e67 < message > ciphered
~/B-CNA-500> cat -e ciphered
744ce22c385958348f0df26eceb62eef$
~/B-CNA-500> ./my_pgp aes -d -b 57696e74657220697320636f6d696e67 < ciphered | cat -e
All men must die$
```

> In stream mode, the data will be ciphered block by block. 
> If the last block is smaller than 128 bits, it will be padded with zeros.


### RSA

RSA is an asymmetric cryptography algorithm that allows secure key exchange. It generates public and private key pairs, and uses them to encrypt and decrypt messages. Public keys can be shared openly, while private keys remain confidential.

Here is an example with small keys:

```bash
~/B-CNA-500> ./my_pgp rsa -g d3 e3 | cat -e
public key: 0101-19bb$
private key: 9d5b-19bb$
~/B-CNA-500> echo "WF" | ./my_pgp rsa -c 0101-19bb > ciphered
~/B-CNA-500> cat -e ciphered
8f84$
~/B-CNA-500> cat ciphered | ./my_pgp rsa -d 9d5b-19bb | cat -e
WF$
```

And here is another one with larger keys:

```bash
~/B-CNA-500> ./my_pgp rsa -g  4b1da73924978f2e9c1f04170e46820d648edbee12ccf4d4462af89b080c86e1 bb3ca1e126f7c8751bd81bc8daa226494efb3d128f72ed9f6cacbe96e14166cb
public key: 010001-c9f91a9ff3bd6d84005b9cc8448296330bd23480f8cf8b36fd4edd0a8cd925de139a0076b962f4d57f50d6f9e64e7c41587784488f923dd60136c763fd602fb3
private key: 81b08f4eb6dd8a4dd21728e5194dfc4e349829c9991c8b5e44b31e6ceee1e56a11d66ef23389be92ef7a4178470693f509c90b86d4a1e1831056ca0757f3e209-c9f91a9ff3bd6d84005b9cc8448296330bd23480f8cf8b36fd4edd0a8cd925de139a0076b962f4d57f50d6f9e64e7c41587784488f923dd60136c763fd602fb3
~/B-CNA-500> echo "The night is dark and full of terrors" | ./my_pgp rsa -c 010001-c9f91a9ff3bd6d84005b9cc8448296330bd23480f8cf8b36fd4edd0a8cd925de139a0076b962f4d57f50d6f9e64e7c41587784488f923dd60136c763fd602fb3 > ciphered
~/B-CNA-500> cat ciphered
445b349e7318ad6af16b0bbb718be88ba1c41751f95751cd58857f88fe31f970405c6ec3f16d79172543bf4e571b5596d212f3e79cd08ef14abd244e325b80
~/B-CNA-500> cat ciphered | ./my_pgp rsa -d 81b08f4eb6dd8a4dd21728e5194dfc4e349829c9991c8b5e44b31e6ceee1e56a11d66ef23389be92ef7a4178470693f509c90b86d4a1e1831056ca0757f3e209-c9f91a9ff3bd6d84005b9cc8448296330bd23480f8cf8b36fd4edd0a8cd925de139a0076b962f4d57f50d6f9e64e7c41587784488f923dd60136c763fd602fb3
The night is dark and full of terrors
```

### PGP (Pretty Good Privacy)

PGP combines asymmetric and symmetric cryptography:
1. A random symmetric key is generated.
2. The message is encrypted using the symmetric key (XOR or AES).
3. The symmetric key is then encrypted using RSA and shared with the recipient.

#### PGP AES

To facilitate debugging, the “random” symmetric key will be part of the key given in parameter the program, for encryption and decryption, in this format: `SYMMETRIC_KEY:RSA_KEY`.
The ciphered symmetric key is displayed on the first line of your output, followed by the ciphered message.

```bash
echo "All men must die" | ./my_pgp pgp-aes -c -b 57696e74657220697320636f6d696e67:010001-c9f91a9ff3bd6d84005b9cc8448296330bd23480f8cf8b36fd4edd0a8cd925de139a0076b962f4d57f50d6f9e64e7c41587784488f923dd60136c763fd602fb3 | cat -e
97f2af4c1b712008c1e46935f446756443a8a700f20581d138e4e6916afe5c5f9b9d6eaa0a870374b686f1a024f9bbb88c23c766654579339caf55afd149d41d$
744ce22c385958348f0df26eceb62eef$
~/B-CNA-500> echo "744ce22c385958348f0df26eceb62eef" | ./my_pgp pgp-aes -d -b 97f2af4c1b712008c1e46935f446756443a8a700f20581d138e4e6916afe5c5f9b9d6eaa0a870374b686f1a024f9bbb88c23c766654579339caf55afd149d41d:81b08f4eb6dd8a4dd21728e5194dfc4e349829c9991c8b5e44b31e6ceee1e56a11d66ef23389be92ef7a4178470693f509c90b86d4a1e1831056ca0757f3e209-c9f91a9ff3bd6d84005b9cc8448296330bd23480f8cf8b36fd4edd0a8cd925de139a0076b962f4d57f50d6f9e64e7c41587784488f923dd60136c763fd602fb3 | cat -e
All men must die$
```

#### PGP XOR

To facilitate debugging, the “random” symmetric key will be part of the key given in parameter the program, for encryption and decryption, in this format: `SYMMETRIC_KEY:RSA_KEY`.
The ciphered symmetric key is displayed on the first line of your output, followed by the ciphered message.


```bash
echo "You know nothing, Jon Snow" | ./my_pgp pgp-xor -c -b 576861742069732064656164206d6179206e6576657220646965:010001-c9f91a9ff3bd6d84005b9cc8448296330bd23480f8cf8b36fd4edd0a8cd925de139a0076b962f4d57f50d6f9e64e7c41587784488f923dd60136c763fd602fb3 | cat -e
8e157dad5de9b552327bbc0979312c6ae634d8f1d868c0a5a0910c7f87475c78061bd110bf36d908ecbb7549bbfc29f3431eae5789bbac30fbf27c75e7b4433e$
20070f2700071c6a4449060a490515164e4e12190b190011063c$
~/B-CNA-500> echo "20070f2700071c6a4449060a490515164e4e12190b190011063c" | ./my_pgp pgp-xor -d -b 8e157dad5de9b552327bbc0979312c6ae634d8f1d868c0a5a0910c7f87475c78061bd110bf36d908ecbb7549bbfc29f3431eae5789bbac30fbf27c75e7b4433e:81b08f4eb6dd8a4dd21728e5194dfc4e349829c9991c8b5e44b31e6ceee1e56a11d66ef23389be92ef7a4178470693f509c90b86d4a1e1831056ca0757f3e209-c9f91a9ff3bd6d84005b9cc8448296330bd23480f8cf8b36fd4edd0a8cd925de139a0076b962f4d57f50d6f9e64e7c41587784488f923dd60136c763fd602fb3 | cat -e
You know nothing, Jon Snow$
```

## Contributors 👥

- **Main Contributor**: [MARQUES Esteban](https://github.com/Estebanmrq/), [PRIEZ Clement](https://github.com/Warred14/)
