/*
** EPITECH PROJECT, 2024
** B5-CNA-cryptography
** File description:
** Key
*/

#ifndef KEY_HPP_
    #define KEY_HPP_
    #include <array>
    #include "Word.hpp"
    #include "Galois.hpp"

namespace Cryptography {

    namespace AES {
        /**
         * @brief Class that represents a key
         * 
         * @tparam N The size of the key
         */
        template <std::size_t N>

        /**
         * @brief The Key class
         * 
         */
        class Key {
            public:
                /**
                 * @brief Construct a new Key object
                 * 
                 * @param words The words of the key
                 */
                Key(std::vector<Word<N>> words) : _words(words)
                {
                    if (words.size() != N)
                        throw KeyError("Key must have " + std::to_string(N) + " words");
                }

                /**
                 * @brief Construct a new Key object
                 * 
                 * @param key The bytes of the key
                 */
                Key(std::string const &key, bool const hex = true, bool fill = false)
                {
                    if (hex) {
                        if (key.size() != N * N * 2)
                            throw KeyError("Key must have " + std::to_string(N * N * 2) + " bytes");

                        for (std::size_t i = 0; i < N * N; i += N) {
                            std::vector<unsigned char> bytes;
                            for (std::size_t j = 0; j < N; ++j) {
                                std::string byteStr = key.substr((i + j) * 2, 2);
                                try {
                                    unsigned char byte = static_cast<unsigned char>(std::stoi(byteStr, nullptr, 16));
                                    bytes.push_back(byte);
                                } catch (const std::invalid_argument&) {
                                    throw KeyError("Invalid hex byte: " + byteStr);
                                } catch (const std::out_of_range&) {
                                    throw KeyError("Hex byte out of range: " + byteStr);
                                }
                            }
                            _words.push_back(Word<N>(bytes));
                        }
                    } else {
                        if (!fill && key.size() != N * N)
                            throw KeyError("Key must have " + std::to_string(N * N) + " bytes");

                        for (std::size_t i = 0; i < N * N; i += N) {
                            std::vector<unsigned char> bytes;
                            for (std::size_t j = 0; j < N; ++j)
                                bytes.push_back(fill && i + j > key.size() ? 0 : key[i + j]);
                            _words.push_back(Word<N>(bytes));
                        }
                    }
                }
                
                /**
                 * @brief Destroy the Key object
                 * 
                 */
                ~Key() = default;



                /**
                 * @brief Get the words of the key
                 * 
                 * @return std::vector<Word<N>> The words of the key
                 */
                std::vector<Word<N>> get() const { return _words; }



                /**
                 * @brief Add a round key
                 * 
                 * @param key The key to add
                 */
                void addRoundKey(Key<N> const &key)
                {
                    auto words = key.get();

                    for (std::size_t i = 0; i < N; ++i)
                        _words[i] ^= words[i];
                }

                /**
                 * @brief Shift the rows of the key
                 * 
                 */
                void shiftRows()
                {
                    std::vector<Word<N>> original_words = _words;

                    for (std::size_t i = 0; i < N; ++i) {
                        for (std::size_t j = 0; j < N; ++j) {
                            _words[j].get()[i] = original_words[(j + i) % N].get()[i];
                        }
                    }
                }

                /**
                 * @brief Shift the rows of the key in the inverse way
                 * 
                 */
                void shiftRowsInv()
                {
                    std::vector<Word<N>> original_words = _words;

                    for (std::size_t i = 0; i < N; ++i) {
                        for (std::size_t j = 0; j < N; ++j) {
                            _words[j].get()[i] = original_words[(j - i + N) % N].get()[i];
                        }
                    }
                }

                /**
                 * @brief Substitute the bytes of the key
                 * 
                 */
                void subBytes()
                {
                    for (auto &word : _words)
                        word.subWord();
                }

                /**
                 * @brief Inverse substitute the bytes of the key
                 * 
                 */
                void subBytesInv()
                {
                    for (auto &word : _words)
                        word.subWordInv();
                }

                /**
                 * @brief Mix the columns of the key whit the Galois matrix
                 * 
                 */
                void mixColumns()
                {
                    std::vector<Word<N>> tmp = _words;

                    for (std::size_t i = 0; i < N; ++i) {
                        for (std::size_t j = 0; j < N; ++j) {
                            _words[i].get()[j] = 
                                Galois::multiply(tmp[i].get()[0], Galois::matrix[j][0]) ^
                                Galois::multiply(tmp[i].get()[1], Galois::matrix[j][1]) ^
                                Galois::multiply(tmp[i].get()[2], Galois::matrix[j][2]) ^
                                Galois::multiply(tmp[i].get()[3], Galois::matrix[j][3]);
                        }
                    }
                }

                /**
                 * @brief Mix the columns of the key whit the Galois matrix in the inverse way
                 * 
                 */
                void mixColumnsInv()
                {
                    std::vector<Word<N>> tmp = _words;

                    for (std::size_t i = 0; i < N; ++i) {
                        for (std::size_t j = 0; j < N; ++j) {
                            _words[i].get()[j] = 
                                Galois::multiply(tmp[i].get()[0], Galois::matrixInv[j][0]) ^
                                Galois::multiply(tmp[i].get()[1], Galois::matrixInv[j][1]) ^
                                Galois::multiply(tmp[i].get()[2], Galois::matrixInv[j][2]) ^
                                Galois::multiply(tmp[i].get()[3], Galois::matrixInv[j][3]);
                        }
                    }
                }

                /**
                 * @brief Reverse the key in little endian
                 * 
                 */
                void reverseLittleEndian()
                {
                    for (auto &word : _words)
                        word.reverseLittleEndian();
                }

                /**
                 * @brief Expand the key
                 * 
                 * @param round The round
                 * @return Key The expanded key
                 */
                Key expandKey(std::size_t const round)
                {
                    Word<N> lastWord = _words.back();
                    std::vector<Word<N>> words;

                    lastWord.rotWord();
                    lastWord.subWord();
                    lastWord.rCon(round);

                    for (std::size_t i = 0; i < N; ++i) {
                        std::vector<unsigned char> bytes;
                        for (std::size_t j = 0; j < N; ++j)
                            bytes.push_back(_words[i].get()[j] ^ lastWord.get()[j]);
                        words.push_back(Word<N>(bytes));
                        lastWord = words.back();
                    }
                    return Key<N>(words);
                }


                /**
                 * @brief Return the key as a string with hexa values
                 * 
                 * @return std::string 
                 */
                std::string toString() const
                {
                    std::string str;

                    for (auto &word : _words)
                        str += word.toString();
                    return str;
                }
                


                /**
                 * @brief The overload of the == operator
                 * 
                 * @param key The key to compare
                 * @return true If the keys are equals
                 * @return false otherwise
                 */
                bool operator==(Key<N> const &key) const
                {
                    auto words = key.get();

                    for (std::size_t i = 0; i < N; ++i)
                        if (_words[i] != words[i])
                            return false;
                    return true;
                }

                /**
                 * @brief The overload of the != operator
                 * 
                 * @param key The key to compare
                 * @return true If the keys are not equals
                 * @return false otherwise
                 */
                bool operator!=(Key<N> const &key) const { return !(*this == key); }


                /**
                 * @brief The overload of the == operator
                 * 
                 * @param key The key to compare
                 * @return true If the keys are equals
                 * @return false otherwise
                 */
                bool operator==(std::array<unsigned char, N * N> const &key) const
                {
                    for (std::size_t i = 0; i < N; ++i) {
                        for (std::size_t j = 0; j < N; ++j) {
                            if (_words[i].get()[j] != key[i * N + j])
                                return false;
                        }
                    }
                    return true;
                }

                /**
                 * @brief The overload of the != operator
                 * 
                 * @param key The key to compare
                 * @return true If the keys are not equals
                 * @return false otherwise
                 */
                bool operator!=(std::array<unsigned char, N * N> const &key) const { return !(*this == key); }


                /**
                 * @brief Exception class for the Key
                 * 
                 */
                class KeyError : public std::exception {
                    public:
                        /**
                         * @brief Construct a new Key Error object
                         * 
                         * @param message The message of the exception
                         */
                        KeyError(std::string const &message) : _message("Key Error: " + message) {};
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
                 * @brief The words of the key
                 * 
                 */
                std::vector<Word<N>> _words;
        };


        /**
         * @brief Generate keys
         * 
         * @tparam N The size of the key
         * @param key The initial key
         * @param nbKeys The number of keys to generate
         * @return std::vector<Key<N>> The generated keys
         */
        template <std::size_t N>
        std::vector<Key<N>> keyExpension(Key<N> const &key, std::size_t const nbKeys)
        {
            std::vector<Key<N>> keys = {key};
            
            for (std::size_t k = 1; k < nbKeys; ++k)
                keys.push_back(keys.back().expandKey(k));
            return keys;
        }



        /**
         * @brief iostream operator << for the Key class
         * 
         * @tparam N The size of the key
         * @param os The ostream
         * @param key The key
         * @return std::ostream& The ostream
         */
        template <std::size_t N>
        std::ostream &operator<<(std::ostream &os, const Key<N> &key)
        {
            auto words = key.get();
        
            os << "[";
            for (std::size_t i = 0; i < N; i++)
                os << words[i] << ((i + 1 < N) ? ", " : "]");
            return os;
        }
    }
}
#endif /* !KEY_HPP_ */
