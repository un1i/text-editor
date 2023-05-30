#include "Text.h"
#include <cstring>
#include <string>
#include <Windows.h>

TextMem TextLink::mem_header;

TextLink::TextLink(Tstr s, TextLink* n, TextLink* d) {
	strncpy(str, s, TextLink::MAX_LINE_LEN);
	str[TextLink::MAX_LINE_LEN - 1] = '\0';
	next = n;
	down = d;
}

void TextLink::init_mem_system(int size) {
	mem_header.first = (TextLink*) new char[sizeof(TextLink) * size];
	mem_header.free = mem_header.first;
	mem_header.last = mem_header.first + (size - 1);
	TextLink* link = mem_header.first;
	for (link; link != mem_header.last; link++)
		link->next = link + 1;
	link->next = NULL;
}

void TextLink::print_free_link() {
	TextLink* cur = mem_header.free;
	int counter = 0;
	while (cur != NULL) {
		std::cout << ++counter << " - " << cur << '\n';
		cur = cur->next;
	}
}

void* TextLink::operator new(size_t size) {
	TextLink* link = mem_header.free;
	if (link != NULL)
		mem_header.free = link->next;
	return link;
}

void TextLink::operator delete(void* del_link) {
	TextLink* link = (TextLink*)del_link;
	link->next = mem_header.free;
	mem_header.free = link;
}

void TextLink::mem_cleaner(Text& txt) {
	/*std::cout << "Очистка памяти...\n";
	Sleep(1000);*/
	std::string st;
	for (txt.reset(); !txt.is_ended(); txt.go_next()) {
		st = txt.get_line();
		if(st.find("&&&") != 0)
			txt.set_line("&&&" + st);
	}
	TextLink* link = mem_header.free;
	for (; link != NULL; link = link->next)
		strcpy(link->str, "&&&");

	for (link = mem_header.first; link <= mem_header.last; link++)
		if (strstr(link->str, "&&&") != NULL)
			strcpy(link->str, link->str + 3);
		else
			delete link;
}

bool TextLink::is_atom() {
	return down == NULL;
}

TextLink* TextLink::get_next() {
	return next;
}

TextLink* TextLink::get_down()
{
	return down;
}

TextLink* TextLink::get_copy() {
	return new TextLink(str, next, down);
}

void TextLink::print(std::ostream& os, bool is_current) {
	if (is_current) {
		HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
		int col = 33;
		SetConsoleTextAttribute(hConsole, 228);
		os << str;
		SetConsoleTextAttribute(hConsole, 15);
		os << " ";
	}
	else
		os << str << " ";
}
