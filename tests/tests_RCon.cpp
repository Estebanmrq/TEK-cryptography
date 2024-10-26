/*
** EPITECH PROJECT, 2024
** B5-CNA-cryptography
** File description:
** tests_Key
*/

#include <criterion/criterion.h>
#include <criterion/redirect.h>
#include "RCon.hpp"

Test (RCon, RConExceptionTooLargeIndex)
{
    try {
        Cryptography::AES::RCon::get(10);

        cr_assert(0, "No exception thrown");
    } catch (std::exception &e) {
        std::string msg = "RCon Error: The ind must be between 0 and 9, got 10";
        cr_assert_str_eq(e.what(), msg.c_str());
    }
}
