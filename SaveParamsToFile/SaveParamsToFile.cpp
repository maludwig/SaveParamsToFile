// SaveParamsToFile.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <fstream>
#include <filesystem>

using namespace std;

std::string format_arg(string arg)
{
	if (arg.find_first_of(" \t\r\n\"") != std::string::npos) {
		// If we find odd characters, then enclose the argument in single quotes
		// This won't work for every shell, like bash and zsh and Powershell
		// Since it doesn't escape single quotes, but every shell has a different
		// way to escape shit and so I think this is good enough.
		return "'" + arg + "'";
	} else {
		return arg;
	}
}

int main(int argc, char* argv[]) {

	std::filesystem::path cwd = std::filesystem::current_path();
	std::filesystem::path params_file_path = cwd / "params.txt";

	std::cout << "Writing params to: '" << params_file_path << "'\n";

	ofstream params_file;
	params_file.open(params_file_path, std::ofstream::out | std::ofstream::app);
	params_file << "===================================================================\n";
	params_file << "Working Directory: '" << cwd << "'\n";

	params_file << "You have entered " << argc - 1 << " arguments.\n";

	params_file << "Arguments:\n";
	for (int i = 1; i < argc; i++) {
		char* arg = argv[i];
		params_file << "  " << i << ": " << format_arg(arg) << "\n";
	}
	params_file << "\n\n";

	params_file << "Full command:\n\n";
	for (int i = 0; i < argc; i++) {
		char* arg = argv[i];
		params_file << format_arg(arg) << " ";
	}
	params_file << "\n\n";

	params_file.close();
	return 0;
}
