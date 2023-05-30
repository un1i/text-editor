#include "TextUsercom.h"
#include <conio.h>
#include <Windows.h>


using namespace std;

TextUsercom::TextUsercom():txt(), display_sublevels(false) {}

string TextUsercom::enter_string() {
	string s;
	cout << "������� ������: ";
	cin.clear();
	cin.ignore(INT_MAX, '\n');
	getline(cin, s);
	return s;
}

string TextUsercom::enter_file_name() {
	string file_name;
	cout << "������� �������� �����: ";
	cin >> file_name;
	return file_name;
}

void TextUsercom::save_text() {
	system("CLS");
	try {
		string file_name = enter_file_name();
		txt.write(file_name.c_str());
		cout << "������ ������� ���������!\n";
		Sleep(1000);
	}
	catch (exception e) {
		cout << e.what() << endl;
		Sleep(1000);
	}
}

void TextUsercom::read_text() {
	try {
		string file_name = enter_file_name();
		txt.read(file_name.c_str());
	}
	catch (exception e) {
		cout << e.what() << endl;
		Sleep(1000);
	}
}


void TextUsercom::main_menu() {
	string s;
	char c;
	int menu;
	cout << "������� 1, ����� ������ ����� �� �����\n\
������� 2, ����� ������� ����� �����\n";
	cin >> menu;
	system("CLS");
	if (menu == 1) {
		read_text();
		if (txt.get_line() == "") {
			string s;
			s = enter_string();
			txt.set_line(s);
		}
	}
	else {
		string s;
		s = enter_string();
		txt.set_line(s);
	}

	while (true) {
		system("CLS");
		txt.print(display_sublevels);
		c = getch();

		if ((c == -32) && kbhit()) {
			c = getch();
			switch (c) {
			case 77: { // key "right"
				if (display_sublevels)
					txt.go_down_link();
				else
					txt.go_next_link();
				break;
			}
			case 80: { // key "down"
				if (display_sublevels)
					txt.go_next_link();
				else
					txt.go_down_link();
				break;
			}
			case 75: { // key "left"
				txt.go_prev_link();
				break;
			}
			case 72: { // key "up"
				txt.go_prev_link();
				break;
			}
			}
			continue;
		}

		switch (c) {
		case 13: { // key "enter"
			actions();
			break;
		}
		case 'f': {
			txt.go_first_link();
			break;
		}
		case 'i': { 
			ins_menu();
			break;
		}
		case 'c': {
			change_menu();
			break;
		}
		case 'd': { 
			del_menu();
			break;
		}
		case 'n': {
			if (txt.is_ended())
				txt.reset();
			else
				txt.go_next();
			break;
		}
		case 'o': {
			options();
			break;
		}
		case 's': {
			save_text();
			break;
		}
		case 27: { // key "esc"
			return;
		}
		}
	}
}

void TextUsercom::ins_menu() {
	int menu;
	cout << "������� 1, ����� �������� ������ � ������� �������\n\
������� 2, ����� �������� ������ � ����������\n\
������� 3, ����� �������� ������ � ������� �������\n\
������� 4, ����� �������� ������ � ����������\n\
������� 5, ����� ������� �����\n\
������� 0, ����� ��������� �����\n";
	cin >> menu;
	try {
		switch (menu) {
		case 1: {

			system("CLS");
			string s;
			s = enter_string();
			txt.ins_next_line(s);
			break;
		}
		case 2: {
			system("CLS");
			string s;
			s = enter_string();
			txt.ins_down_line(s);
			break;
		}
		case 3: {
			system("CLS");
			string s;
			s = enter_string();
			txt.ins_next_section(s);
			break;
		}
		case 4: {
			system("CLS");
			string s;
			s = enter_string();
			txt.ins_down_section(s);
			break;
		}
		case 5: {
			system("CLS");
			txt.print();
			break;
		}
		default: {
			system("CLS");
			break;
		}
		}
	}
	catch (exception e) {
		cout << e.what() << endl;
		cout << "������� �����-���� ������, ����� �������� �����" << endl;
		cout << "������� 1, ����� ����������";
		int resume;
		cin >> resume;
	}
}

void TextUsercom::del_menu() {
	int menu;
	cout << "������� 1, ����� ������� ������ �� �������� ������\n\
������� 2, ����� ������� ������ �� ���������\n\
������� 3, ����� ������� ������ �� �������� ������\n\
������� 4, ����� ������� ������ �� ���������\n\
������� 5, ����� ������� �����\n\
������� 0, ����� ��������� �����\n";
	cin >> menu;
	switch (menu) {
	case 1: {

		system("CLS");
		txt.del_next_line();
		break;
	}
	case 2: {
		system("CLS");
		txt.del_down_line();
		break;
	}
	case 3: {
		system("CLS");
		txt.del_next_section();
		break;
	}
	case 4: {
		system("CLS");
		txt.del_down_section();
		break;
	}
	case 5: {
		system("CLS");
		txt.print();
		break;
	}
	default: {
		system("CLS");
		break;
	}
	}
}


void TextUsercom::change_menu() {
	string s;
	int res;
	cout << "������� 1, ����� �������� ������� ������\n\
������� 0, ����� ��������� �����\n";
	cin >> res;
	if (res != 1)
		return;

	s = enter_string();
	txt.set_line(s);
}

void TextUsercom::run() {
	main_menu();
}

void TextUsercom::actions() {
	int menu;
	cout << "������� 1, ����� �������� ������\n\
������� 2, ����� ������� ������\n\
������� 3, ����� �������� ������\n\
������� 4, ����� ������� �������������� ��������\n\
������� 0, ����� ��������� �����\n";
	cin >> menu;
	switch (menu) {
	case 1: {

		system("CLS");
		ins_menu();
		break;
	}
	case 2: {
		system("CLS");
		del_menu();
		break;
	}
	case 3: {
		system("CLS");
		change_menu();
		break;
	}
	case 4: {
		system("CLS");
		options();
		break;
	}
	default: {
		system("CLS");
		break;
	}
	}
}

void TextUsercom::options() {
	int menu;
	system("CLS");
	cout << "������� 1, ����� ���������� ��������� ������\n\
������� 2, ����� ��������� ������� ������\n\
������� 3, ����� �������� ����������� ������\n\
������� 4, ����� ������� ��� ������\n\
������� 5, ����� ������ ����� �� �����\n\
������� 6, ����� ��������� ����� � ����\n\
������� 0, ����� ��������� �����\n";
	cin >> menu;
	switch (menu) {
	case 1: {
		int exit;
		system("CLS");
		TextLink::print_free_link();
		cout << "������� 1, ����� ����������\n";
		cin >> exit;
		break;
	}
	case 2: {
		system("CLS");
		txt.run_garbage_collector();
		break;
	}
	case 3: {
		system("CLS");
		display_sublevels = !display_sublevels;
		break;
	}
	case 4: {
		system("CLS");
		txt.clear();
		string s;
		s = enter_string();
		txt.set_line(s);
		break;
	}
	case 5: {
		system("CLS");
		txt.clear();
		read_text();
		break;
	}
	case 6: {
		save_text();
		break;
	}
	default: {
		system("CLS");
		break;
	}
	}
}