#ifndef TEXTENCRYPTION_H
#define TEXTENCRYPTION_H

#endif // TEXTENCRYPTION_H

#include <boost/filesystem.hpp>
#include <string>
#include <iostream>
#include "modes.h"
#include "osrng.h"
#include "serpent.h"
#include "hex.h"
#include "sha.h"

class TextEncryption {

private:
    std::string plainTextMessage, messageHash, cipher, encodedMessage, encodedKey, encodedInitVector;
    CryptoPP::SecByteBlock* key;
    CryptoPP::byte initVector[CryptoPP::Serpent::BLOCKSIZE];
    CryptoPP::AutoSeededRandomPool prng;
    boost::filesystem::path directory, filePathHash, filePathMessage, filePathKey, filePathInitVector;
    CryptoPP::SHA256 hash;

public:
    TextEncryption(std::string message) {
        plainTextMessage = message;
        directory.append("./MessageComponents");
        if(!boost::filesystem::exists(directory)) boost::filesystem::create_directory(directory);
        filePathMessage = directory / "encrypted_message.txt";
        filePathKey = directory / "serpent_encryption_key.txt";
        filePathInitVector = directory / "initialisation_vector.txt";
        filePathHash = directory / "message_hash.txt";
    }

    void CreateMessageHash() {
        CryptoPP::StringSource stringSource(plainTextMessage,
                               true,
                               new CryptoPP::HashFilter(
                                   hash,
                                   new CryptoPP::HexEncoder(
                                       new CryptoPP::StringSink(messageHash)
                                       )
                                   )
                               );
    }

    void EncryptMessage() {
        GenerateKey();
        CryptoPP::CBC_Mode<CryptoPP::Serpent>::Encryption encryption;
        encryption.SetKeyWithIV(*(key), key->size(), initVector);
        CryptoPP::StringSource stringSource(plainTextMessage,
                                            true,
                                            new CryptoPP::StreamTransformationFilter(
                                                encryption,
                                                new CryptoPP::StringSink(cipher)
                                                )
                                            );
        HexEncodeMessage();
    }

    std::string ReturnMessageHash() {
        return messageHash;
    }

    std::string ReturnCipher() {
        return cipher;
    }

    std::string ReturnEncodedMessage() {
        return encodedMessage;
    }

    std::string ReturnEncodedKey() {
        return encodedKey;
    }

    std::string ReturnEncodedInitVector() {
        return encodedInitVector;
    }

    void SaveMessageHash() {
        boost::filesystem::ofstream hashOutputFile(filePathHash);
        if(!hashOutputFile.is_open()) std::cout << "ERROR: Could not open file!" << std::endl;
        else {
            hashOutputFile << messageHash;
            hashOutputFile.close();
        }
    }

    void SaveEncryptedMessage() {
        boost::filesystem::ofstream messageOutputFile(filePathMessage);
        if(!messageOutputFile.is_open()) std::cout << "ERROR: Could not open file!" << std::endl;
        else {
            messageOutputFile << encodedMessage;
            messageOutputFile.close();
        }
    }

    void SaveKey() {
        boost::filesystem::ofstream keyOutputFile(filePathKey);
        if(!keyOutputFile.is_open()) std::cout << "ERROR: Could not open file!" << std::endl;
        else {
            keyOutputFile << encodedKey;
            keyOutputFile.close();
        }
    }

    void SaveInitialisationVector() {
        boost::filesystem::ofstream initVectorOutputFile(filePathInitVector);
        if(!initVectorOutputFile.is_open()) std::cout << "ERROR: Could not open file!" << std::endl;
        else {
            initVectorOutputFile << encodedInitVector;
            initVectorOutputFile.close();
        }
    }

private:
    void GenerateKey() {
        key = new CryptoPP::SecByteBlock(CryptoPP::Serpent::DEFAULT_KEYLENGTH);
        prng.GenerateBlock(*(key), key->size());
        prng.GenerateBlock(initVector, sizeof(initVector));
        HexEncodeKey();
        HexEncodeInitialisationVector();
    }

    void HexEncodeMessage() {
        CryptoPP::StringSource stringSource(cipher,
                                            true,
                                            new CryptoPP::HexEncoder(
                                                new CryptoPP::StringSink(encodedMessage)
                                                )
                                            );
    }

    void HexEncodeKey() {
        CryptoPP::byte* byteArray = key->BytePtr();
        std::string key_ = "";

        for(int i = 0; i < key->size(); i++) key_ += byteArray[i];

        CryptoPP::StringSource stringSource(key_,
                                            true,
                                            new CryptoPP::HexEncoder(
                                                new CryptoPP::StringSink(encodedKey)
                                                )
                                            );
    }

    void HexEncodeInitialisationVector() {
        std::string initVector_ = "";

        for(int i = 0; i < CryptoPP::Serpent::BLOCKSIZE; i++) initVector_ += initVector[i];

        CryptoPP::StringSource stringSource(initVector_,
                                            true,
                                            new CryptoPP::HexEncoder(
                                                new CryptoPP::StringSink(encodedInitVector)
                                                )
                                            );
    }
};
