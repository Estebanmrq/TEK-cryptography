/*
** EPITECH PROJECT, 2024
** B5-CNA-cryptography
** File description:
** Galois
*/

#ifndef GALOIS_HPP_
    #define GALOIS_HPP_
    #include <vector>

namespace Cryptography {

    namespace AES {
        /**
         * @brief Class that represents the Galois field
         * 
         */
        class Galois {
            public:
                /**
                 * @brief Multiply two numbers in the Galois field
                 * 
                 * @param val1 The first number 
                 * @param val2 The second number
                 * @return unsigned char The result of the multiplication
                 */
                static unsigned char multiply(unsigned char val1, unsigned char val2);

                /**
                 * @brief The matrix used to multiply two numbers in the Galois field
                 * 
                 */
                static const std::vector<std::vector<unsigned char>> matrix;

                /**
                 * @brief The matrix used to multiply two numbers in the Galois field in the inverse way
                 * 
                 */
                static const std::vector<std::vector<unsigned char>> matrixInv;
            private:
        };
    }

}

#endif /* !GALOIS_HPP_ */
