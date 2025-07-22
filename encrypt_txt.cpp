//functions to encrypt and decrypt text files using ASCII values and a random key
//the code can't handle some special characters, but it can handle most ASCII characters

//include modules
#include <string>
#include <vector>
#include <random>
#include <sstream>

//function to encrypt text
std::string encrypt(const std::string& text) {

	//check if the input text is empty
    if (text.empty()) {
        return "";
    }

	//initialize string
    std::string line;

	//generate a random key
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> distr(1, 100);
    int roof = distr(gen);
    std::uniform_int_distribution<> distr1(1, roof);
    int key = distr1(gen);

	//initialize a vector to hold lines
	std::vector<std::string> lines;

    //a string stream to read the input text
    std::istringstream sstream(text);

	//read the input text line by line
    while (std::getline(sstream, line)) {
        lines.push_back(line);
    }

	//initialize a matrix to hold the encrypted lines
    std::vector<std::vector<int>> line_matrix(lines.size() + 1);

	//encrypt each character in the lines and store in the matrix
    for (size_t i = 0; i < lines.size(); ++i) {
        for (char c : lines[i]) {
			unsigned char uc = static_cast<unsigned char>(c);
            line_matrix[i].push_back(static_cast<int>(uc) + key);
        }
    }

	//add the key to the matrix
    line_matrix[lines.size()].push_back(key);

	//initialize a string to hold the result
    std::string result;

    //convert the matrix to a string
    for (int i = 0; i < lines.size() + 1; ++i) {
        for (int j = 0; j < line_matrix[i].size(); ++j) {
            result += std::to_string(line_matrix[i][j]);
            if (j != line_matrix[i].size() - 1) {
                result += ",";
            }
        }
        if (i != lines.size()) {
            result += "\n";
        }
    }
    
	//return the encrypted text
    return result;
}

//function to decrypt text
std::string decrypt(const std::string& text) {

	//check if the input text is empty
    if (text.empty()) {
        return "";
	}

	//initialize a string to hold the line
    std::string line;

	//initialize a matrix to hold the lines
    std::vector<std::vector<int>> line_matrix;

	//a string stream to read the input text
    std::istringstream sstream(text);

	//initialize a vector to hold numbers
    std::vector<int> numbers;

	//read the input text line by line and parse the numbers
    while (std::getline(sstream, line)) {

		//skip empty lines
        if (line.empty()) {
            continue;
		}

		//split the line by commas and convert to integers
        std::istringstream line_stream(line);
        std::string number;
        std::vector<int> numbers;

        while (std::getline(line_stream, number, ',')) {

            if (!number.empty()) {
                numbers.push_back(std::stoi(number));
            }
        }

		//if the numbers vector is not empty, add it to the line_matrix
        if (!numbers.empty()) {
            line_matrix.push_back(numbers);
		}
    }

	//get the key from the matrix and remove it
    int key = line_matrix.back()[0];
    line_matrix.pop_back();

	//initialize a string to hold the result
    std::string result;

	//decrypt each line by subtracting the key from each number
    for (size_t i = 0; i < line_matrix.size(); ++i) {
        const std::vector<int>& numbers = line_matrix[i];
        for (int num : numbers) {
            result += static_cast<char>(num - key);
        }
        if (i != line_matrix.size() - 1) {
            result += '\n';
        }
    }


	//return the decrypted text
    return result;
}

int main() {

}
