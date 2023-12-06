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
#include "rsa.h"
#include "files.h"
#include "pssr.h"

class TextEncryption {

private:
    std::string plainTextMessage, messageHash, cipher, encryptedKey, signature, encodedEncryptedMessage, encodedKey, encodedInitVector,
        encodedEncryptedKey, encodedSignature;
    CryptoPP::SecByteBlock* key;
    CryptoPP::byte initVector[CryptoPP::Serpent::BLOCKSIZE];
    CryptoPP::AutoSeededRandomPool prng;
    boost::filesystem::path directory, filePathSignature, filePathMessage, filePathKey, filePathInitVector;
    CryptoPP::SHA256 hash;

public:
    TextEncryption(std::string message) {
        plainTextMessage = message;

        directory.append("./MessageComponents");
        if(!boost::filesystem::exists(directory)) boost::filesystem::create_directory(directory);
        filePathMessage = directory / "encrypted_message.txt";
        filePathKey = directory / "serpent_encryption_key.txt";
        filePathInitVector = directory / "initialisation_vector.txt";
        filePathSignature = directory / "signature.txt";
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
        HexEncodeString(cipher, encodedEncryptedMessage);
    }

    void Sign() {
        CalculateMessageHash();

        CryptoPP::RSA::PrivateKey senderPrivateKey;
        CryptoPP::FileSource senderPrivKeyInputFile("./Keys/Sender/private_key.txt", true);
        senderPrivateKey.BERDecode(senderPrivKeyInputFile);

        CryptoPP::RSASS<CryptoPP::PSSR, CryptoPP::SHA256>::Signer signer(senderPrivateKey);

        CryptoPP::StringSource stringSource(messageHash,
                                            true,
                                            new CryptoPP::SignerFilter(
                                                prng, signer,
                                                new CryptoPP::StringSink(signature), true)
                                            );
        HexEncodeString(signature, encodedSignature);
    }

    void Send() {
        SaveEncryptedMessage();
        SaveKey();
        SaveInitialisationVector();
        SaveSignature();
    }

    std::string ReturnEncodedEncryptedMessage() {
        return encodedEncryptedMessage;
    }

    std::string ReturnEncodedKey() {
        return encodedKey;
    }

private:
    void GenerateKey() {
        key = new CryptoPP::SecByteBlock(CryptoPP::Serpent::DEFAULT_KEYLENGTH);
        prng.GenerateBlock(*(key), key->size());
        prng.GenerateBlock(initVector, sizeof(initVector));
        HexEncodeKey();
        HexEncodeInitialisationVector();
    }

    void EncryptKey() {
        CryptoPP::RSA::PublicKey receiverPublicKey;
        CryptoPP::FileSource receiverPubKeyInputFile("./Keys/Receiver/public_key.txt", true);

        receiverPublicKey.BERDecode(receiverPubKeyInputFile);

        CryptoPP::RSAES_OAEP_SHA_Encryptor encryptor(receiverPublicKey);

        CryptoPP::StringSource stringSource(encodedKey,
                                            true,
                                            new CryptoPP::PK_EncryptorFilter(
                                                prng, encryptor, new CryptoPP::StringSink(
                                                    encryptedKey)
                                                )
                                            );

        HexEncodeString(encryptedKey, encodedEncryptedKey);
    }

    void CalculateMessageHash() {
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

    void HexEncodeString(std::string &inputString, std::string &outputString) {
        CryptoPP::StringSource stringSource(inputString,
                                            true,
                                            new CryptoPP::HexEncoder(
                                                new CryptoPP::StringSink(outputString)
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

    void SaveEncryptedMessage() {
        boost::filesystem::ofstream messageOutputFile(filePathMessage);
        if(!messageOutputFile.is_open()) std::cout << "ERROR: Could not open file!" << std::endl;
        else messageOutputFile << encodedEncryptedMessage;
        messageOutputFile.close();
    }

    void SaveKey() {
        EncryptKey();
        boost::filesystem::ofstream keyOutputFile(filePathKey);
        if(!keyOutputFile.is_open()) std::cout << "ERROR: Could not open file!" << std::endl;
        else keyOutputFile << encodedEncryptedKey;
        keyOutputFile.close();
    }

    void SaveInitialisationVector() {
        boost::filesystem::ofstream initVectorOutputFile(filePathInitVector);
        if(!initVectorOutputFile.is_open()) std::cout << "ERROR: Could not open file!" << std::endl;
        else initVectorOutputFile << encodedInitVector;
        initVectorOutputFile.close();
    }

    void SaveSignature() {
        boost::filesystem::ofstream signatureOutputFile(filePathSignature);
        if(!signatureOutputFile.is_open()) std::cout << "ERROR: Could not open file!" << std::endl;
        else signatureOutputFile << encodedSignature;
        signatureOutputFile.close();
    }
};
