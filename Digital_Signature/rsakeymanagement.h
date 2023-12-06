#ifndef RSAKEYMANAGEMENT_H
#define RSAKEYMANAGEMENT_H

#define RSA_KEY_SIZE 2048

#endif // RSAKEYMANAGEMENT_H


#include <boost/filesystem.hpp>
#include <iostream>
#include <string>
#include "rsa.h"
#include "osrng.h"
#include "files.h"

bool KeysExist() {
    boost::filesystem::path keys, keysSender, keysReceiver;
    keys.append("./Keys");
    keysSender.append("./Keys/Sender");
    keysReceiver.append("./Keys/Receiver");

    if(boost::filesystem::exists(keys) && boost::filesystem::exists(keysSender) && boost::filesystem::exists(keysReceiver)) {
        boost::filesystem::path privKeySender, pubKeySender, privKeyReceiver, pubKeyReceiver;
        privKeySender = keysSender / "private_key.txt";
        pubKeySender = keysSender / "public_key.txt";
        privKeyReceiver = keysReceiver / "private_key.txt";
        pubKeyReceiver = keysReceiver / "public_key.txt";

        if(
            boost::filesystem::exists(privKeySender) &&
            boost::filesystem::exists(pubKeySender) &&
            boost::filesystem::exists(privKeyReceiver) &&
            boost::filesystem::exists(pubKeyReceiver)
            )
            return true;
        else return false;
    }
    else return false;
}

class RSAKeyManagement {
    private:
        CryptoPP::RSA::PrivateKey privateKeyS, privateKeyR;
        CryptoPP::AutoSeededRandomPool prng;
        boost::filesystem::path mainDirectory, directorySender, directoryReceiver;

    public:
        RSAKeyManagement() {
            mainDirectory.append("./Keys");
            directorySender.append("./Keys/Sender");
            directoryReceiver.append("./Keys/Receiver");

            if(!boost::filesystem::exists(mainDirectory)) boost::filesystem::create_directory(mainDirectory);
            if(!boost::filesystem::exists(directorySender)) boost::filesystem::create_directory(directorySender);
            if(!boost::filesystem::exists(directoryReceiver)) boost::filesystem::create_directory(directoryReceiver);

            privateKeyS.GenerateRandomWithKeySize(prng, RSA_KEY_SIZE);
            CryptoPP::RSA::PublicKey publicKeyS(privateKeyS);

            privateKeyR.GenerateRandomWithKeySize(prng, RSA_KEY_SIZE);
            CryptoPP::RSA::PublicKey publicKeyR(privateKeyR);

            CryptoPP::FileSink outputPrKS("./Keys/Sender/private_key.txt");
            privateKeyS.DEREncode(outputPrKS);

            CryptoPP::FileSink outputPuKS("./Keys/Sender/public_key.txt");
            publicKeyS.DEREncode(outputPuKS);

            CryptoPP::FileSink outputPrKR("./Keys/Receiver/private_key.txt");
            privateKeyR.DEREncode(outputPrKR);

            CryptoPP::FileSink outputPuKR("./Keys/Receiver/public_key.txt");
            publicKeyR.DEREncode(outputPuKR);
        }
};
