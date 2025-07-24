//this code uses a simple XOR bit encryption and decryption mechanism.
//the encryption function takes a string, generates a random key, and returns a vector of encrypted bytes.
//the decryption function takes a vector of encrypted bytes and returns the original string.
//works with any text input, including special characters and spaces.

//include modules
#include <string>
#include <vector>
#include <random>
#include <ctime>
#include <cstdint>

//function to encrypt text
std::vector<uint8_t> encrypt(const std::string& text1) {

	//check if the input text is empty
    if (text1.empty()) {
        return {};
    }

    //generate a random key
	srand(time(NULL));
    uint8_t key = rand() % 256;

    //initialize a vector to hold the encrypted bytes
	std::vector<uint8_t> byte_vector;

	//encrypt each character in the text by adding the key
    for (char c : text1) {
        byte_vector.push_back(static_cast<uint8_t>(c) ^ key);
    }

    //add the key to the vector
	byte_vector.push_back(key);

    //return the encrypted text
    return byte_vector;
}

//function to decrypt text
std::string decrypt(const std::vector<uint8_t>& encrypted) {

	//check if the encrypted vector is empty
    if (encrypted.empty()) {
        return "";
    }

	//get the key from the last byte
    uint8_t key = encrypted.back();

    std::string decrypted;

    // XOR each byte (except last) with the key to get original chars
    for (size_t i = 0; i < encrypted.size() - 1; ++i) {
        decrypted.push_back(static_cast<char>(encrypted[i] ^ key));
    }

	//return the decrypted text
    return decrypted;
}

int main() {

	return 0;
}