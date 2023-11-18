#ifndef TEXTDECRYPTION_H
#define TEXTDECRYPTION_H

#endif // TEXTDECRYPTION_H

#include <boost/filesystem.hpp>
#include <string>
#include <iostream>
#include "modes.h"
#include "serpent.h"
#include "hex.h"

class TextDecryption {

private:
    std::string plainTextMessage, cipher, encodedMessage, encodedKey, encodedInitVector;
    CryptoPP::SecByteBlock* key;
    CryptoPP::byte initVector[CryptoPP::Serpent::BLOCKSIZE];
    boost::filesystem::path directory, filePathKey, filePathMessage, filePathInitVector;
    bool decryptionPossible;

public:
    TextDecryption() {
        decryptionPossible = true;

        directory.append("./MessageComponents");
        filePathKey = directory / "serpent_encryption_key.txt";
        filePathMessage = directory / "encrypted_message.txt";
        filePathInitVector = directory / "initialisation_vector.txt";

        if(DirectoryExists()) {
            FetchMessageFromFile();
            FetchKeyFromFile();
            FetchInitialisationVectorFromFile();

            if(decryptionPossible) {
                HexDecodeMessage();
                HexDecodeKey();
                HexDecodeInitialisationVector();
            }
        }
        else decryptionPossible = false;
    }

    void DecryptText() {
        CryptoPP::CBC_Mode<CryptoPP::Serpent>::Decryption decryption;
        decryption.SetKeyWithIV(*(key), key->size(), initVector);
        CryptoPP::StringSource stringSource(cipher,
                                            true,
                                            new CryptoPP::StreamTransformationFilter(
                                                decryption, new CryptoPP::StringSink(plainTextMessage)
                                                )
                                            );
    }

    std::string ReturnPlainTextMessage() {
        return plainTextMessage;
    }

    bool DecryptionPossible() {
        return decryptionPossible;
    }

private:
    void FetchMessageFromFile() {
        if(EncryptedMessageFileExists()) {
            boost::filesystem::ifstream messageInputFile(filePathMessage);
            if(messageInputFile.is_open()) {
                messageInputFile >> encodedMessage;
                messageInputFile.close();
            }
        }
        else decryptionPossible = false;
    }

    void FetchKeyFromFile() {
        if(KeyFileExists()) {
            boost::filesystem::ifstream keyInputFile(filePathKey);
            if(keyInputFile.is_open()) {
                keyInputFile >> encodedKey;
                keyInputFile.close();
            }
        }
        else decryptionPossible = false;
    }

    void FetchInitialisationVectorFromFile() {
        if(InitialisationVectorFileExists()) {
            boost::filesystem::ifstream initVectorInputFile(filePathInitVector);
            if(initVectorInputFile.is_open()) {
                initVectorInputFile >> encodedInitVector;
                initVectorInputFile.close();
            }
        }
        else decryptionPossible = false;
    }

    bool EncryptedMessageFileExists() {
        boost::filesystem::ifstream messageInputFile(filePathMessage);
        if(!messageInputFile.is_open()) {
            std::cout << "ERROR: Could not open file containing encrypted message!" << std::endl << std::endl;
            return false;
        }
        else {
            messageInputFile.close();
            return true;
        }
    }

    bool KeyFileExists() {
        boost::filesystem::ifstream keyInputFile(filePathKey);
        if(!keyInputFile.is_open()) {
            std::cout << "ERROR: Could not open file containing encryption key!" << std::endl << std::endl;
            return false;
        }
        else {
            keyInputFile.close();
            return true;
        }
    }

    bool InitialisationVectorFileExists() {
        boost::filesystem::ifstream initVectorInputFile(filePathInitVector);
        if(!initVectorInputFile.is_open()) {
            std::cout << "ERROR: Could not open file containing initialisation vector!" << std::endl << std::endl;
            return false;
        }
        else {
            initVectorInputFile.close();
            return true;
        }
    }

    bool DirectoryExists() {
        if(!boost::filesystem::exists(directory)) {
            std::cout << "ERROR: Could not find directory 'MessageComponents'" << std::endl;
            std::cout << "Try sending a message first..." << std::endl << std::endl;
            return false;
        }
        else return true;
    }

    void HexDecodeMessage() {
        CryptoPP::StringSource stringSource(encodedMessage,
                                            true,
                                            new CryptoPP::HexDecoder(
                                                new CryptoPP::StringSink(cipher)
                                                )
                                            );
    }

    void HexDecodeKey() {
        std::string key_;
        CryptoPP::StringSource stringSource(encodedKey,
                                            true,
                                            new CryptoPP::HexDecoder(
                                                new CryptoPP::StringSink(key_)
                                                )
                                            );
        key = new CryptoPP::SecByteBlock(CryptoPP::Serpent::DEFAULT_KEYLENGTH);
        CryptoPP::ArraySource arraySource(reinterpret_cast<const CryptoPP::byte*>(key_.data()),
                                          key_.size(),
                                          true,
                                          new CryptoPP::ArraySink(key->BytePtr(), key->size())
                                          );
    }

    void HexDecodeInitialisationVector() {
        std::string initVector_;
        CryptoPP::StringSource stringSource(encodedInitVector,
                                            true,
                                            new CryptoPP::HexDecoder(
                                                new CryptoPP::StringSink(initVector_)
                                                )
                                            );
        CryptoPP::ArraySource arraySource(reinterpret_cast<const CryptoPP::byte*>(initVector_.data()),
                                          CryptoPP::Serpent::BLOCKSIZE,
                                          true,
                                          new CryptoPP::ArraySink(initVector, CryptoPP::Serpent::BLOCKSIZE)
                                          );
    }
};
