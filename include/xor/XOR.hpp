/*
** EPITECH PROJECT, 2024
** B-CNA-500-PAR-5-1-cryptography-esteban.marques
** File description:
** XOR
*/

#ifndef XOR_HPP_
    #define XOR_HPP_
    #include <vector>
    #include <string>

namespace Cryptography {

    /**
     * @brief This class is used to encrypt and decrypt messages with XOR
     * 
     */
    class XOR {
        public:
            /**
             * @brief Construct a new XOR object
             * 
             * @param key The key to use for encryption and decryption
             */
            XOR(std::string const &key) : _okey(key), _key(_convertHexaToBytes(_hexaBigEndianToLittleEndian(key, 2))) {};

            /**
             * @brief Destroy the XOR object
             * 
             */
            ~XOR() = default;


            /**
             * @brief Get the original Key object
             * 
             * @return std::string The key
             */
            std::string getKey() const { return _okey; };

            /**
             * @brief This function is used to encrypt
             * 
             * @param message The message to encrypt
             * @param fill if true, fill the message with 0 when the key is longer than the message
             * @return std::string The encrypted or decrypted message
             */
            std::string encrypt(std::string const &message, bool fill = false);

            /**
             * @brief This function is used to decrypt messages
             * 
             * @param message The message to decrypt
             * @param fill if true, fill the message with 0 when the key is longer than the message
             * @return std::string The decrypted message
             */
            std::string decrypt(std::string const &message, bool fill = false);

            class XORException : public std::exception {
                public:
                    XORException(std::string const &message) : _message("XOR Error: " + message) {};
                    const char *what() const noexcept override { return _message.c_str(); };
                private:
                    std::string _message;
            };
        private:
            std::string const _okey;

            /**
             * @brief The key used for encryption and decryption
             * 
             */
            std::vector<unsigned char> _key;

                    /**
             * @brief Get the hexa Big Endian To Little Endian object
             * 
             * @param hexa The hexa string to convert
             * @param wordSize The size of the word
             * @return std::string The converted string
             */
            std::string _hexaBigEndianToLittleEndian(std::string const &hexa, std::size_t wordSize);

            /**
             * @brief Get the hexa Little Endian To Big Endian object
             * 
             * @param str The string to convert
             * @return std::string The converted string
             */
            std::string _convertStringToHexa(std::string const &str);

            /**
             * @brief Get the bytes To Hexa object
             * 
             * @param hexa The hexa string to convert
             * @return std::vector<unsigned char> The converted vector
             */
            std::vector<unsigned char> _convertHexaToBytes(std::string const &hexa);

    };
}

#endif /* !XOR_HPP_ */
