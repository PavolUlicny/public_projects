//this is a simple hex viewer for (mainly text) files
//to start, enter the name of the file you want to use with the file header (has to be in the same directory as the .cpp file)
//then, enter on which byte in the text file you want to start (0 for the start of the file)
//it prints a question mark (?) for characters that it can't print
//heavily inspired by the "hexed.it" hex editor


//include necessary modules
#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <windows.h>
#include <iomanip>
#include <cctype>

//function with the code 
void hex_viewer() {

	//set console output to UTF-8 (to support some special characters)
	SetConsoleOutputCP(CP_UTF8);

	//ask for file name
	std::string file_name = "";
	std::cout << "Enter file name: ";
	std::getline(std::cin >> std::ws, file_name);
	std::ifstream file(file_name, std::ios::binary);

	//check if file is open
	if (!file.is_open()) {
		std::cerr << "Failed to open file." << std::endl;
		return;
	}

	//ask for the byte position
	std::cout << "Enter byte position: ";
	unsigned long long position;
	std::string input;
	std::getline(std::cin, input);

	//check if the input is a valid number
	bool valid = true;
	for (char c : input) {
		if (!std::isdigit(static_cast<unsigned char>(c))) {
			valid = false;
			break;
		}
	}

	//check if the input is valid
	if (std::cin.fail() || input.empty() || !valid) {
		std::cerr << "Invalid byte position." << std::endl;
		file.close();
		return;
	}

	//convert the input to an unsigned long long
	try {
		position = std::stoull(input);
	} catch (const std::out_of_range& e) {
		std::cerr << "Byte position is out of range." << std::endl;
		file.close();
		return;
	}

	//save the file size
	file.seekg(0, std::ios::end);
	std::streampos file_size = file.tellg();
	unsigned long long file_size_ull = static_cast<unsigned long long>(file_size);

	//check if the position is valid
	if (position >= file_size_ull) {
		std::cerr << "Position is beyond end of file." << std::endl;
		file.close();
		return;
	}

	//move the file pointer to the specified position
	file.seekg(position, std::ios::beg);

	//initialize variables for reading and displaying the file content
	short count = 0;
	unsigned long long line_start_pos = position;
	std::vector<unsigned char> buffer;

	//set the number of bytes per line
	int bytes_per_line = 20;

	//print the position (only of the first byte of each line), hex values, and ASCII representation of the bytes
	char byte;
	while (file.get(byte)) {
		if (count == bytes_per_line) {
			std::cout << std::hex << std::setw(8) << std::setfill('0') << line_start_pos << "    ";
			for (size_t i = 0; i < buffer.size(); ++i) {
				std::cout << std::hex << std::setw(2) << std::setfill('0') << static_cast<int>(buffer[i]) << ' ';
			}
			std::cout << "    ";
			for (size_t i = 0; i < buffer.size(); ++i) {
				if (std::isprint(static_cast<unsigned char>(buffer[i]))) {
					std::cout << buffer[i] << ' ';
				}
				else {
					std::cout << '?' << ' ';
				}
			}
			std::cout << std::endl;
			buffer.clear();
			line_start_pos += bytes_per_line;
			count = 0;
		}
		buffer.push_back(static_cast<unsigned char>(byte));
		count++;
	}

	//print the leftover bytes if there are any
	if (!buffer.empty()) {
		std::cout << std::hex << std::setw(8) << std::setfill('0') << line_start_pos << "    ";

		for (unsigned char b : buffer) {
			std::cout << std::hex << std::setw(2) << std::setfill('0') << static_cast<int>(b) << ' ';
		}

		for (int i = buffer.size(); i < bytes_per_line; ++i) {
			std::cout << "   ";
		}

		std::cout << "    ";

		for (unsigned char b : buffer) {
			if (std::isprint(static_cast<unsigned char>(b))) {
				std::cout << b << ' ';
			}
			else {
				std::cout << '?' << ' ';
			}
		}

		std::cout << '\n';
	}

	//close the file
	file.close();
}

//main function to run the hex viewer
int main() {

	hex_viewer();

	return 0;
}