#ifndef TEXTDECRYPTION_H
#define TEXTDECRYPTION_H

#endif // TEXTDECRYPTION_H

#include <boost/filesystem.hpp>
#include <string>
#include <iostream>
#include "modes.h"
#include "serpent.h"
#include "hex.h"
#include "sha.h"
#include "rsa.h"
#include "files.h"
#include "osrng.h"
#include "pssr.h"

class TextDecryption {

private:
    std::string plainTextMessage, messageHash, cipher, encodedMessage, encodedKey, encodedInitVector, encodedEncryptedKey, encryptedKey, encodedSignature, signature, errorMessage;
    CryptoPP::SecByteBlock* key;
    CryptoPP::byte initVector[CryptoPP::Serpent::BLOCKSIZE];
    boost::filesystem::path directory, filePathMessage, filePathKey, filePathInitVector, filePathSignature;
    CryptoPP::SHA256 hash;
    CryptoPP::AutoSeededRandomPool prng;
    bool decryptionPossible;

public:
    TextDecryption() {
        errorMessage = "";
        decryptionPossible = true;

        directory.append("./MessageComponents");
        filePathMessage = directory / "encrypted_message.txt";
        filePathKey = directory / "serpent_encryption_key.txt";
        filePathInitVector = directory / "initialisation_vector.txt";
        filePathSignature = directory / "signature.txt";

        if(DirectoryExists()) {
            FetchMessageFromFile();
            FetchKeyFromFile();
            FetchInitialisationVectorFromFile();
            FetchSignatureFromFile();

            if(decryptionPossible) {
                HexDecodeMessage();
                HexDecodeKey();
                HexDecodeInitialisationVector();
                HexDecodeSignature();
            }
        }
        else decryptionPossible = false;
    }

    void DecryptText() {
        CryptoPP::CBC_Mode<CryptoPP::Serpent>::Decryption decryption;
        decryption.SetKeyWithIV(*(key), key->size(), initVector);
        try {
            CryptoPP::StringSource stringSource(cipher,
                                                true,
                                                new CryptoPP::StreamTransformationFilter(
                                                    decryption, new CryptoPP::StringSink(plainTextMessage)
                                                    )
                                                );
        }
        catch(CryptoPP::Exception exception) {
            errorMessage += "ERROR: FAILED TO DECRYPT MESSAGE\n" + exception.GetWhat() + "\nLikely cause was tempering with the key or message\n\n";
        }
    }

    bool IntegrityCheck() {
        if(VerifySignature()) {
            std::string messageHash_;
            CryptoPP::StringSource stringSource(plainTextMessage,
                                                true,
                                                new CryptoPP::HashFilter(
                                                    hash,
                                                    new CryptoPP::HexEncoder(
                                                        new CryptoPP::StringSink(messageHash_)
                                                        )
                                                    )
                                                );
            if(!messageHash_.compare(messageHash)) return true;
            else return false;
        }
        else return false;

    }

    bool DecryptionPossible() {
        return decryptionPossible;
    }

    std::string ReturnPlainTextMessage() {
        return plainTextMessage;
    }

    std::string ReturnErrorMessage() {
        return errorMessage;
    }

private:
    void FetchMessageFromFile() {
        if(EncryptedMessageFileExists()) {
            boost::filesystem::ifstream messageInputFile(filePathMessage);
            if(messageInputFile.is_open()) messageInputFile >> encodedMessage;
            else {
                errorMessage += "ERROR: Could not open file containing message!\n\n";
                decryptionPossible = false;
            }
            messageInputFile.close();
        }
        else decryptionPossible = false;
    }

    void FetchKeyFromFile() {
        if(KeyFileExists()) {
            boost::filesystem::ifstream keyInputFile(filePathKey);
            if(keyInputFile.is_open()) keyInputFile >> encodedEncryptedKey;
            else {
                errorMessage += "ERROR: Could not open file containing key!\n\n";
                decryptionPossible = false;
            }
            keyInputFile.close();
        }
        else decryptionPossible = false;
    }

    void FetchInitialisationVectorFromFile() {
        if(InitialisationVectorFileExists()) {
            boost::filesystem::ifstream initVectorInputFile(filePathInitVector);
            if(initVectorInputFile.is_open()) initVectorInputFile >> encodedInitVector;
            else {
                errorMessage += "ERROR: Could not open file containing initialisation vector!\n\n";
                decryptionPossible = false;
            }
            initVectorInputFile.close();
        }
        else decryptionPossible = false;
    }

    void FetchSignatureFromFile() {
        if(SignatureFileExists()) {
            boost::filesystem::fstream signatureInputFile(filePathSignature);
            if(signatureInputFile.is_open()) signatureInputFile >> encodedSignature;
            else {
                errorMessage += "ERROR: Could not open file containing signature!\n\n";
                decryptionPossible = false;
            }
            signatureInputFile.close();
        }
        else decryptionPossible = false;
    }

    bool DirectoryExists() {
        if(!boost::filesystem::exists(directory)) {
            errorMessage += "ERROR: Could not find directory 'MessageComponents'\nTry sending a message first...\n\n";
            return false;
        }
        else return true;
    }

    bool EncryptedMessageFileExists() {
        if(!boost::filesystem::exists(filePathMessage)) {
            errorMessage += "ERROR: Could not find the file containing the encrypted message!\n\n";
            return false;
        }
        else return true;
    }

    bool KeyFileExists() {
        if(!boost::filesystem::exists(filePathKey)) {
            errorMessage += "ERROR: Could not find the file containing the encryption key!\n\n";
            return false;
        }
        else return true;
    }

    bool InitialisationVectorFileExists() {
        boost::filesystem::ifstream initVectorInputFile(filePathInitVector);
        if(!boost::filesystem::exists(filePathInitVector)) {
            errorMessage += "ERROR: Could not the file containing the initialisation vector!\n\n";
            return false;
        }
        else return true;
    }

    bool SignatureFileExists() {
        if(!boost::filesystem::exists(filePathSignature)) {
            errorMessage += "ERROR: Could not find the file containing message hash!\n\n";
            return false;
        }
        else return true;
    }

    bool VerifySignature() {
        bool verified = true;
        CryptoPP::RSA::PublicKey senderPublicKey;
        CryptoPP::FileSource senderPubKeyInputFile("./Keys/Sender/public_key.txt", true);
        senderPublicKey.BERDecode(senderPubKeyInputFile);

        CryptoPP::RSASS<CryptoPP::PSSR, CryptoPP::SHA256>::Verifier verifier(senderPublicKey);

        try {
            CryptoPP::StringSource stringSource(signature,
                                                true,
                                                new CryptoPP::SignatureVerificationFilter(
                                                    verifier,
                                                    new CryptoPP::StringSink(
                                                        messageHash), CryptoPP::SignatureVerificationFilter::THROW_EXCEPTION | CryptoPP::SignatureVerificationFilter::PUT_MESSAGE
                                                    )
                                                );
        }
        catch(CryptoPP::Exception exception) {
            errorMessage += "ERROR: FAILED TO VERIFY SIGNATURE\n" + exception.GetWhat() + "\n\n";
            verified = false;
        }
        return verified;
    }

    void DecryptKey() {
        HexDecodeEncryptedKey();
        CryptoPP::RSA::PrivateKey receiverPrivateKey;
        CryptoPP::FileSource receiverPrivKeyInputFile("./Keys/Receiver/private_key.txt", true);

        receiverPrivateKey.BERDecode(receiverPrivKeyInputFile);

        CryptoPP::RSAES_OAEP_SHA_Decryptor decryptor(receiverPrivateKey);

        try {
            CryptoPP::StringSource stringSource(encryptedKey,
                                                true,
                                                new CryptoPP::PK_DecryptorFilter(
                                                    prng, decryptor, new CryptoPP::StringSink(
                                                                        encodedKey)
                                                    )
                                                );
        }
        catch(CryptoPP::Exception exception) {
            errorMessage += "ERROR: FAILED TO DECRYPT KEY\n" + exception.GetWhat() + "\nLikely cause was tempering with the key\n\n";
        }
    }

    void HexDecodeMessage() {
        CryptoPP::StringSource stringSource(encodedMessage,
                                            true,
                                            new CryptoPP::HexDecoder(
                                                new CryptoPP::StringSink(cipher)
                                                )
                                            );
    }

    void HexDecodeEncryptedKey() {
        CryptoPP::StringSource stringSource(encodedEncryptedKey,
                                            true,
                                            new CryptoPP::HexDecoder(
                                                new CryptoPP::StringSink(encryptedKey)
                                                )
                                            );
    }

    void HexDecodeKey() {
        DecryptKey();
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

    void HexDecodeSignature() {
        CryptoPP::StringSource stringSource(encodedSignature,
                                            true,
                                            new CryptoPP::HexDecoder(
                                                new CryptoPP::StringSink(
                                                    signature)
                                                )
                                            );
    }
};
