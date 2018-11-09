#include "stdafx.h"
#include <string>
#include <fstream>
#include <time.h>
#include <random>
#include <shellapi.h>

class Generate {

	int l1, l2, h1, h2;
	std::string t;
	HWND h;

public:
	Generate(int low_1, int low_2, int high_1, int high_2, std::string type, HWND hwnd) {
		t = type;
		l1 = low_1;
		l2 = low_2;
		h1 = high_1;
		h2 = high_2;
		h = hwnd;
		srand(time(NULL));
	}

	Generate() {
		t = "";
		l1 = 0;
		l2 = 0;
		h1 = 0;
		h2 = 0;
		srand(time(NULL));
	}

	void build() {
		int a, b, c, d;
		std::ofstream quiz;
		std::ofstream answers;
		quiz.open("quiz.txt", std::ofstream::out);
		answers.open("answers.txt", std::ofstream::out);
		if (t == "add") {
			for (int i = 0; i < 24; i++) {
				a = l1 + (std::rand() % (h1 - l1 + 1));
				b = l2 + (std::rand() % (h2 - l2 + 1));
				c = a + b;
				if (i % 2 == 0) {
					quiz << i + 1 << ". " << a << " + " << b << " =\t\t\t\t\t\t";
				}
				else {
					quiz << i + 1 << ". " << a << " + " << b << " =\n\n\n\n";
				}
				answers << i + 1 << ". " << c << "\n";
			}
		}
		else if (t == "sub") {
			for (int i = 0; i < 24; i++) {
				a = l1 + (std::rand() % (h1 - l1 + 1));
				b = l2 + (std::rand() % (h2 - l2 + 1));
				if (a < b) {
					d = a;
					a = b;
					b = d;
				}
				c = a - b;
				if (i % 2 == 0) {
					quiz << i + 1 << ". " << a << " - " << b << " =\t\t\t\t\t\t";
				}
				else {
					quiz << i + 1 << ". " << a << " - " << b << " =\n\n\n\n";
				}
				answers << i + 1 << ". " << c << "\n";
			}
		}
		else if (t == "mul") {
			for (int i = 0; i < 24; i++) {
				a = l1 + (std::rand() % (h1 - l1 + 1));
				b = l2 + (std::rand() % (h2 - l2 + 1));
				c = a * b;
				if (i % 2 == 0) {
					quiz << i + 1 << ". " << a << " x " << b << " =\t\t\t\t\t\t";
				}
				else {
					quiz << i + 1 << ". " << a << " x " << b << " =\n\n\n\n";
				}
				answers << i + 1 << ". " << c << "\n";
			}
		}
		else if (t == "div"){
			for (int i = 0; i < 24; i++) {
				a = l1 + (std::rand() % (h1 - l1 + 1));
				b = l2 + (std::rand() % (h2 - l2 + 1));	
				if (a < b) {
					d = a;
					a = b;
					b = d;
				}
				c = a / b;
				if (i % 2 == 0) {
					quiz << i + 1 << ". " << a << " " << char(247) << " " << b << " =\t\t\t\t\t\t";
				}
				else {
					quiz << i + 1 << ". " << a << " " << char(247) << " " << b << " =\n\n\n\n";
				}
				answers << i + 1 << ". " << c << " r " << a % b << "\n";
			}
		}

	}

};