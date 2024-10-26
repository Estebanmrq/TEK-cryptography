/*
** EPITECH PROJECT, 2024
** B-CNA-500-PAR-5-1-cryptography-esteban.marques
** File description:
** tests_cryptography
*/

#include <criterion/criterion.h>
#include <criterion/redirect.h>
#include <iostream>

#include "Cryptography.hpp"

// Fonctionnality

// XOR

Test (Cryptography, xor_encrypt, .init = cr_redirect_stdout)
{
    try {
        Cryptography::Cryptography crypto({"xor", "-c", "-b", "576861742069732064656164206d6179206e6576657220646965"}, "You know nothing, Jon Snow");
        crypto.run();

        cr_assert_stdout_eq_str("20070f2700071c6a4449060a490515164e4e12190b190011063c\n");
    } catch (const std::exception &e) {
        cr_assert(false, "%s", e.what());
    }
}

Test (Cryptography, xor_decrypt, .init = cr_redirect_stdout)
{
    try {
        Cryptography::Cryptography crypto({"xor", "-d", "-b", "576861742069732064656164206d6179206e6576657220646965"}, "20070f2700071c6a4449060a490515164e4e12190b190011063c");
        crypto.run();

        cr_assert_stdout_eq_str("You know nothing, Jon Snow\n");
    } catch (const std::exception &e) {
        cr_assert(false, "%s", e.what());
    }
}

// AES

Test (Cryptography, aes_encrypt, .init = cr_redirect_stdout)
{
    try {
        Cryptography::Cryptography crypto({"aes", "-c", "-b", "57696e74657220697320636f6d696e67"}, "All men must die");
        crypto.run();

        cr_assert_stdout_eq_str("744ce22c385958348f0df26eceb62eef\n");
    } catch (const std::exception &e) {
        cr_assert(false, "%s", e.what());
    }
}

Test (Cryptography, aes_decrypt, .init = cr_redirect_stdout)
{
    try {
        Cryptography::Cryptography crypto({"aes", "-d", "-b", "57696e74657220697320636f6d696e67"}, "744ce22c385958348f0df26eceb62eef");
        crypto.run();

        cr_assert_stdout_eq_str("All men must die\n");
    } catch (const std::exception &e) {
        cr_assert(false, "%s", e.what());
    }
}

// RSA

Test (Cryptography, rsa_keygen_small_key, .init = cr_redirect_stdout)
{
    try {
        Cryptography::Cryptography crypto({"rsa", "-g", "d3", "e3"});
        crypto.run();

        cr_assert_stdout_eq_str("public key: 0101-19bb\nprivate key: 9d5b-19bb\n");
    } catch (const std::exception &e) {
        cr_assert(false, "%s", e.what());
    }
}

Test (Cryptography, rsa_keygen_large_key, .init = cr_redirect_stdout)
{
    try {
        Cryptography::Cryptography crypto({"rsa", "-g", "4b1da73924978f2e9c1f04170e46820d648edbee12ccf4d4462af89b080c86e1", "bb3ca1e126f7c8751bd81bc8daa226494efb3d128f72ed9f6cacbe96e14166cb"});
        crypto.run();

        cr_assert_stdout_eq_str("public key: 010001-c9f91a9ff3bd6d84005b9cc8448296330bd23480f8cf8b36fd4edd0a8cd925de139a0076b962f4d57f50d6f9e64e7c41587784488f923dd60136c763fd602fb3\nprivate key: 81b08f4eb6dd8a4dd21728e5194dfc4e349829c9991c8b5e44b31e6ceee1e56a11d66ef23389be92ef7a4178470693f509c90b86d4a1e1831056ca0757f3e209-c9f91a9ff3bd6d84005b9cc8448296330bd23480f8cf8b36fd4edd0a8cd925de139a0076b962f4d57f50d6f9e64e7c41587784488f923dd60136c763fd602fb3\n");
    } catch (const std::exception &e) {
        cr_assert(false, "%s", e.what());
    }
}

Test (Cryptography, rsa_cypher_small_key, .init = cr_redirect_stdout)
{
    try {
        Cryptography::Cryptography crypto({"rsa", "-c", "0101-19bb"}, "WF");
        crypto.run();

        cr_assert_stdout_eq_str("8f84\n");
    } catch (const std::exception &e) {
        cr_assert(false, "%s", e.what());
    }
}

Test (Cryptography, rsa_cypher_large_key, .init = cr_redirect_stdout)
{
    try {
        Cryptography::Cryptography crypto({"rsa", "-c", "010001-c9f91a9ff3bd6d84005b9cc8448296330bd23480f8cf8b36fd4edd0a8cd925de139a0076b962f4d57f50d6f9e64e7c41587784488f923dd60136c763fd602fb3"}, "The night is dark and full of terrors");
        crypto.run();

        cr_assert_stdout_eq_str("445b349e7318ad6af16b0bbb718be88ba1c41751f95751cd58857f88fe31f970405c6ec3f16d79172543bf4e571b5596d212f3e79cd08ef14abd244e325b80\n");
    } catch (const std::exception &e) {
        cr_assert(false, "%s", e.what());
    }
}

Test (Cryptography, rsa_decypher_small_key, .init = cr_redirect_stdout)
{
    try {
        Cryptography::Cryptography crypto({"rsa", "-d", "9d5b-19bb"}, "8f84");
        crypto.run();

        cr_assert_stdout_eq_str("WF\n");
    } catch (const std::exception &e) {
        cr_assert(false, "%s", e.what());
    }
}

Test (Cryptography, rsa_decypher_large_key, .init = cr_redirect_stdout)
{
    try {
        Cryptography::Cryptography crypto({"rsa", "-d", "81b08f4eb6dd8a4dd21728e5194dfc4e349829c9991c8b5e44b31e6ceee1e56a11d66ef23389be92ef7a4178470693f509c90b86d4a1e1831056ca0757f3e209-c9f91a9ff3bd6d84005b9cc8448296330bd23480f8cf8b36fd4edd0a8cd925de139a0076b962f4d57f50d6f9e64e7c41587784488f923dd60136c763fd602fb3"}, "445b349e7318ad6af16b0bbb718be88ba1c41751f95751cd58857f88fe31f970405c6ec3f16d79172543bf4e571b5596d212f3e79cd08ef14abd244e325b80");
        crypto.run();

        cr_assert_stdout_eq_str("The night is dark and full of terrors\n");
    } catch (const std::exception &e) {
        cr_assert(false, "%s", e.what());
    }
}

Test (Cryptography, rsa_encrypt_special_message, .init = cr_redirect_stdout)
{
    try {
        Cryptography::Cryptography crypto({"rsa", "-c", "010001-c9f91a9ff3bd6d84005b9cc8448296330bd23480f8cf8b36fd4edd0a8cd925de139a0076b962f4d57f50d6f9e64e7c41587784488f923dd60136c763fd602fb3"}, "\n\n\nhello\n\n\n");
        crypto.run();

        cr_assert_stdout_eq_str("4e22d447b9d9b16eb964feefe9da9a826eeb0693ea6375738f8e62daa4b328ddf9a8fdf02a70d10c211d48df47ed5b30bb87e2781b90bf5594df7a25bb36c00c\n");
    } catch (const std::exception &e) {
        cr_assert(false, "%s", e.what());
    }
}

Test (Cryptography, rsa_decrypt_special_message, .init = cr_redirect_stdout)
{
    try {
        Cryptography::Cryptography crypto({"rsa", "-d", "81b08f4eb6dd8a4dd21728e5194dfc4e349829c9991c8b5e44b31e6ceee1e56a11d66ef23389be92ef7a4178470693f509c90b86d4a1e1831056ca0757f3e209-c9f91a9ff3bd6d84005b9cc8448296330bd23480f8cf8b36fd4edd0a8cd925de139a0076b962f4d57f50d6f9e64e7c41587784488f923dd60136c763fd602fb3"}, "4e22d447b9d9b16eb964feefe9da9a826eeb0693ea6375738f8e62daa4b328ddf9a8fdf02a70d10c211d48df47ed5b30bb87e2781b90bf5594df7a25bb36c00c");
        crypto.run();

        cr_assert_stdout_eq_str("\n\n\nhello\n\n\n\n");
    } catch (const std::exception &e) {
        cr_assert(false, "%s", e.what());
    }
}

// PGP-AES

Test (Cryptography, pgp_aes_encrypt_message, .init = cr_redirect_stdout)
{
    try {
        Cryptography::Cryptography crypto({"pgp-aes", "-c", "57696e74657220697320636f6d696e67:010001-c9f91a9ff3bd6d84005b9cc8448296330bd23480f8cf8b36fd4edd0a8cd925de139a0076b962f4d57f50d6f9e64e7c41587784488f923dd60136c763fd602fb3"}, "All men must die");
        crypto.run();

        cr_assert_stdout_eq_str("97f2af4c1b712008c1e46935f446756443a8a700f20581d138e4e6916afe5c5f9b9d6eaa0a870374b686f1a024f9bbb88c23c766654579339caf55afd149d41d\n744ce22c385958348f0df26eceb62eef\n");
    } catch (const std::exception &e) {
        cr_assert(false, "%s", e.what());
    }
}

Test (Cryptography, pgp_aes_decrypt_message, .init = cr_redirect_stdout)
{
    try {
        Cryptography::Cryptography crypto({"pgp-aes", "-d", "97f2af4c1b712008c1e46935f446756443a8a700f20581d138e4e6916afe5c5f9b9d6eaa0a870374b686f1a024f9bbb88c23c766654579339caf55afd149d41d:81b08f4eb6dd8a4dd21728e5194dfc4e349829c9991c8b5e44b31e6ceee1e56a11d66ef23389be92ef7a4178470693f509c90b86d4a1e1831056ca0757f3e209-c9f91a9ff3bd6d84005b9cc8448296330bd23480f8cf8b36fd4edd0a8cd925de139a0076b962f4d57f50d6f9e64e7c41587784488f923dd60136c763fd602fb3"}, "744ce22c385958348f0df26eceb62eef");
        crypto.run();

        cr_assert_stdout_eq_str("All men must die\n");
    } catch (const std::exception &e) {
        cr_assert(false, "%s", e.what());
    }
}

// PGP-XOR

Test (Cryptography, pgp_xor_encrypt_message, .init = cr_redirect_stdout)
{
    try {
        Cryptography::Cryptography crypto({"pgp-xor", "-c", "576861742069732064656164206d6179206e6576657220646965:010001-c9f91a9ff3bd6d84005b9cc8448296330bd23480f8cf8b36fd4edd0a8cd925de139a0076b962f4d57f50d6f9e64e7c41587784488f923dd60136c763fd602fb3"}, "You know nothing, Jon Snow");
        crypto.run();

        cr_assert_stdout_eq_str("8e157dad5de9b552327bbc0979312c6ae634d8f1d868c0a5a0910c7f87475c78061bd110bf36d908ecbb7549bbfc29f3431eae5789bbac30fbf27c75e7b4433e\n20070f2700071c6a4449060a490515164e4e12190b190011063c\n");
    } catch (const std::exception &e) {
        cr_assert(false, "%s", e.what());
    }
}

Test (Cryptography, pgp_xor_decrypt_message, .init = cr_redirect_stdout)
{
    try {
        Cryptography::Cryptography crypto({"pgp-xor", "-d", "8e157dad5de9b552327bbc0979312c6ae634d8f1d868c0a5a0910c7f87475c78061bd110bf36d908ecbb7549bbfc29f3431eae5789bbac30fbf27c75e7b4433e:81b08f4eb6dd8a4dd21728e5194dfc4e349829c9991c8b5e44b31e6ceee1e56a11d66ef23389be92ef7a4178470693f509c90b86d4a1e1831056ca0757f3e209-c9f91a9ff3bd6d84005b9cc8448296330bd23480f8cf8b36fd4edd0a8cd925de139a0076b962f4d57f50d6f9e64e7c41587784488f923dd60136c763fd602fb3"}, "20070f2700071c6a4449060a490515164e4e12190b190011063c");
        crypto.run();

        cr_assert_stdout_eq_str("You know nothing, Jon Snow\n");
    } catch (const std::exception &e) {
        cr_assert(false, "%s", e.what());
    }
}


// Error handling

// XOR error handling

Test (Cryptography, xor_exception_invalid_flags_combination, .init = cr_redirect_stdout)
{
    try {
        Cryptography::Cryptography crypto({"xor", "-c", "-d", "-b", "576861742069732064656164206d6179206e6576657220646965"});
        crypto.run();

        cr_assert(false, "No exception thrown");
    } catch (const std::exception &e) {
        cr_assert(true);
    }
}

Test (Cryptography, xor_exception_invalid_block_size, .init = cr_redirect_stdout)
{
    try {
        Cryptography::Cryptography crypto({"xor", "-c", "-b", "576861742069732064656164206d6179206e6576657220646965"}, "You know nothing, Jon Snow!");
        crypto.run();

        cr_assert(false, "No exception thrown");
    } catch (const std::exception &e) {
        cr_assert(true);
    }
}

Test (Cryptography, xor_exception_invalid_flag, .init = cr_redirect_stdout)
{
    try {
        Cryptography::Cryptography crypto({"xor", "-c", "-z", "576861742069732064656164206d6179206e6576657220646965"});
        crypto.run();

        cr_assert(false, "No exception thrown");
    } catch (const std::exception &e) {
        cr_assert(true);
    }
}

Test (Cryptography, xor_exception_invalid_number_of_arguments, .init = cr_redirect_stdout)
{
    try {
        Cryptography::Cryptography crypto({"xor", "-c", "-b", "576861742069732064656164206d6179206e6576657220646965", "error"});
        crypto.run();

        cr_assert(false, "No exception thrown");
    } catch (const std::exception &e) {
        cr_assert(true);
    }
}

Test (Cryptography, xor_exception_invalid_block_size_2, .init = cr_redirect_stdout)
{
    try {
        Cryptography::Cryptography crypto({"xor", "-c", "-b", "3"});
        crypto.run();

        cr_assert(false, "No exception thrown");
    } catch (const std::exception &e) {
        cr_assert(true);
    }
}
