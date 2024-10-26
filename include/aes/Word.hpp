/*
** EPITECH PROJECT, 2024
** B5-CNA-cryptography
** File description:
** Word
*/

#ifndef WORD_HPP_
    #define WORD_HPP_
    #include <vector>
    #include <string>
    #include <iomanip>
    #include <sstream>
    #include <exception>
    #include <algorithm>

    #include "RCon.hpp"
    #include "SBox.hpp"

namespace Cryptography {

    /**
     * @brief Namespace for the key expansion
     * 
     */
    namespace AES {

        /**
         * @brief The size of the word
         * 
         * @tparam N Size of the word
         */
        template <std::size_t N>

        /**
         * @brief Class that represents a word
         * 
         */
        class Word {
            public:
                /**
                 * @brief Construct a new Word object
                 * 
                 * @param word The bytes of the word
                 */
                Word(std::vector<unsigned char> word) : _bytes(word)
                {
                    if (word.size() != N)
                        throw WordError("Word must have " + std::to_string(N) + " bytes");
                }

                /**
                 * @brief Destroy the Word object
                 * 
                 */
                ~Word() = default;



                /**
                 * @brief Get the word
                 * 
                 * @return std::vector<unsigned char> The word
                 */
                std::vector<unsigned char> get() const { return _bytes; }

                /**
                 * @brief Get a reference to the word
                 * 
                 * @return std::vector<unsigned char> The word
                 */
                std::vector<unsigned char>& get() { return _bytes; }

                /**
                 * @brief Rotate the word
                 * 
                 */
                void rotWord() { std::rotate(_bytes.begin(), _bytes.begin() + 1, _bytes.end()); }


                /**
                 * @brief Substitute the word
                 * 
                 */
                void subWord()
                {
                    for (std::size_t i = 0; i < N; i++)
                        _bytes[i] = SBox::get(_bytes[i]);
                }

                /**
                 * @brief Substitute the word in the inverse way
                 * 
                 */
                void subWordInv()
                {
                    for (std::size_t i = 0; i < N; i++)
                        _bytes[i] = SBox::getInv(_bytes[i]);
                }

                /**
                 * @brief Apply the rcon
                 * 
                 * @param round The round
                 */
                void rCon(std::size_t const round) { _bytes[0] ^= RCon::get(round - 1); }


                /**
                 * @brief Reverse the word in little endian
                 * 
                 */
                void reverseLittleEndian()
                {
                    std::reverse(_bytes.begin(), _bytes.end());
                }

                /**
                 * @brief Return the word as a string with hexa values
                 * 
                 * @return std::string 
                 */
                std::string toString() const
                {
                    std::string str;

                    for (auto &byte : _bytes) {
                        std::stringstream ss;
                        ss << std::hex << std::setw(2) << std::setfill('0') << (int)byte;
                        str += ss.str();
                    }
                    return str;
                }


                /**
                 * @brief Overload of the ^ operator
                 * 
                 * @param word The word
                 * @return Word The word
                 */
                Word &operator^=(Word const &word)
                {
                    auto bytes = word.get();

                    for (std::size_t i = 0; i < N; ++i)
                        _bytes[i] ^= bytes[i];
                    return *this;
                }


                /**
                 * @brief Exception class for Word
                 * 
                 */
                class WordError : public std::exception {
                    public:
                        /**
                         * @brief Construct a new Word Error object
                         * 
                         * @param message The message of the exception
                         */
                        WordError(std::string const &message) : _message("Word Error: " + message) {};
                        /**
                         * @brief Get the message of the exception
                         * 
                         * @return const char* The message of the exception
                         */
                        const char *what() const noexcept override { return _message.c_str(); };
                    private:
                        /**
                         * @brief The message of the exception
                         * 
                         */
                        std::string _message;
                };

            private:
                /**
                 * @brief The bytes of the word
                 * 
                 */
                std::vector<unsigned char> _bytes;
        };


        /**
         * @brief Overload of the << operator
         * 
         * @tparam N The size of the word
         * @param os The output stream
         * @param word The word
         * @return std::ostream& The output stream
         */
        template <std::size_t N>
        std::ostream &operator<<(std::ostream &os, const Word<N> &word)
        {
            auto bytes = word.get();
        
            for (std::size_t i = 0; i < N; ++i)
                os << "0x" << std::hex << std::setw(2) << std::setfill('0') << (int)bytes[i] << ((i + 1 < N) ? ", " : "");
            return os;
        }
    }

}
#endif /* !WORD_HPP_ */
