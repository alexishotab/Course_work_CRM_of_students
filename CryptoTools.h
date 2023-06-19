#include <string>
#include <ctime>
#include <iostream>
#include <fstream>
using namespace std;


class CryptoTools {
	string pathToFile = "data.dat";
public:
	CryptoTools(string _pathToFile) {
		pathToFile = _pathToFile;
	}

	string generatePassword() {
		srand(static_cast<unsigned int>(time(nullptr)));

		string pass;
		pass.reserve(64); // ����������� ����� ��� 64 ��������

		for (size_t i = 0; i < 64; ++i) {
			switch (rand() % 3) {
			case 0:
				pass.push_back(static_cast<char>(rand() % 10 + '0'));
				break;
			case 1:
				pass.push_back(static_cast<char>(rand() % 26 + 'A'));
				break;
			case 2:
				pass.push_back(static_cast<char>(rand() % 26 + 'a'));
				break;
			}
		}

		std::ofstream file("key.txt", ios_base::out | ios::binary);
		file.write(pass.c_str(), pass.size());
		file.close();
		return pass;
	}

	bool encrypt(string password) {
		string command = "openssl\\bin\\openssl.exe enc -aes-256-cbc -salt -in " + pathToFile + " -out db.dat.enc -pass pass:" + password;
		system(command.c_str());
		if (remove("data.dat") != 0) {
			cout << "������ � ������� ��� 1: �� ������ data.dat";
		}
		command = "openssl\\bin\\openssl.exe rsautl -encrypt -inkey rsa.public -pubin -in key.txt -out key.txt.enc";
		system(command.c_str());
		if (remove("key.txt") != 0) {
			cout << "������ � ������� ��� 2 �� ������ key.txt";
		}
		return true;
	}

	string readPassword() {
		string pass;
		pass.resize(64);

		ifstream file("key.txt", ios::binary);
		if (!file) {
			cout << "\nError opening file key.txt\n";
			return "";
		}
		file.read(&pass[0], 64);
		file.close();
		return pass;
	}

	bool decrypt() {
		string command = "openssl\\bin\\openssl.exe rsautl -decrypt -inkey rsa.private -in key.txt.enc -out key.txt";
		system(command.c_str());
		if (remove("key.txt.enc") != 0) {
			cout << "������ � ������� ��� 1 �� ������ key.txt.enc";
		}
		string password = readPassword();
		//cout <<"������:"<< password;
		if (remove("key.txt") != 0) {
			cout << "������ � ������� ��� 2 �� ������ key.txt";
		}
		command = "openssl\\bin\\openssl.exe enc -aes-256-cbc -d -in db.dat.enc -out data.dat -pass pass:";
		command += password;
		system(command.c_str());

		if (remove("db.dat.enc") != 0) {
			cout << "������ � ������� ��� 1 �� ������ db.dat.enc";
		}

		return true;
	}
};
