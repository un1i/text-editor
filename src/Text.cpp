#include "Text.h"
#include <fstream>


Text::Text(TextLink* link) :first(link), current(link), tab_counter(0), end_it(true) {
	if (first == NULL)
		first = current = get_new_link();
};

Text*  Text::get_copy() {
	Text* res = new Text(first);
	res->current = current;
	res->path = path;
	res->it = it;
	return res;
}

TextLink* Text::get_new_link(TextLink::Tstr str, TextLink* next, TextLink* down) {
	TextLink* new_link = new TextLink(str, next, down);
	if (new_link == NULL) {
		run_garbage_collector();
		new_link = new TextLink;
		if (new_link == NULL)
			throw std::exception("Память закочилась");
	}
	return new_link;
}

void Text::run_garbage_collector() {
	TextLink* old_current = current;
	TextLink::mem_cleaner(*this);
	current = old_current;
}

int Text::go_first_link() {
	current = first;
	while (!path.empty())
		path.pop();
	return 0;
}

int Text::go_down_link() {
	if (current == NULL || current->down == NULL)
		return 1;
	path.push(current);
	current = current->down;
	return 0;
}

int Text::go_next_link() {
	if (current == NULL || current->next == NULL)
		return 1;
	path.push(current);
	current = current->next;
	return 0;
}

int Text::go_prev_link() {
	if (path.empty())
		return 1;
	current = path.top();
	path.pop();
	return 0;
}

std::string Text::get_line(){
	if (current == NULL)
		return "";

	return std::string(current->str);
}

void Text::set_line(std::string s) {
	if (current != NULL) {
		strncpy(current->str, s.c_str(), TextLink::MAX_LINE_LEN);
		current->str[TextLink::MAX_LINE_LEN - 1] = '\0';
	}
}

void Text::ins_down_line(std::string s) {
	if (current != NULL) {
		TextLink* new_link = get_new_link("", current->down, NULL);
		strncpy(new_link->str, s.c_str(), TextLink::MAX_LINE_LEN);
		new_link->str[TextLink::MAX_LINE_LEN - 1] = '\0';
		current->down = new_link;
	}
}

void Text::ins_down_section(std::string s) {
	if (current != NULL) {
		TextLink* new_link = get_new_link("", NULL, current->down);
		strncpy(new_link->str, s.c_str(), TextLink::MAX_LINE_LEN);
		new_link->str[TextLink::MAX_LINE_LEN - 1] = '\0';
		current->down = new_link;
	}
}

void Text::ins_next_line(std::string s) {

	if (current != NULL) {
		TextLink* new_link = get_new_link("", NULL, NULL);
		strncpy(new_link->str, s.c_str(), TextLink::MAX_LINE_LEN);
		new_link->str[TextLink::MAX_LINE_LEN - 1] = '\0';
		new_link->next = current->next;
		current->next = new_link;
	}
}

void Text::ins_next_section(std::string s) {
	if (current != NULL) {
		TextLink* new_link = get_new_link("", NULL, current->next);
		strncpy(new_link->str, s.c_str(), TextLink::MAX_LINE_LEN);
		new_link->str[TextLink::MAX_LINE_LEN - 1] = '\0';
		current->next = new_link;
	}
}

void Text::del_down_line() {
	if (current != NULL && current->down != NULL)
		current->down = current->down->next;
}

void Text::del_down_section() {
	if (current != NULL && current->down != NULL)
		current->down = current->down->down;
}

void Text::del_next_line() {
	if (current != NULL && current->next != NULL)
		current->next = current->next->next;
}

void Text::del_next_section() {
	if (current != NULL && current->next != NULL)
		current->next = current->next->down;
}

int Text::reset() {
	if (first == NULL)
		return 1;
	while (!it.empty())
		it.pop();
	current = first;
	it.push({ current, 0 });
	end_it = false;
	return 0;
}

int Text::is_ended() const {
	return end_it;
}

int Text::go_next() {
	while (!it.empty()) {
		TextLink* link = it.top().first;
		int condition = it.top().second;
		it.pop();

		if (condition == 0) {
			if (link->down != NULL) {
				it.push({ link, 1 });
				current = link->down;
				it.push({ current,0 });
				break;
			}
			else
				condition = 1;
		}

		if (condition == 1) {
			if (link->next != NULL) {
				current = link->next;
				it.push({ current, 0 });
				break;
			}
		}
	}

	if (it.empty()) {
		end_it = true;
		return 1;
	}
	return 0;
	
}

TextLink* Text::get_first_atom(TextLink* link) {
	if (link == NULL)
		return link;
	while (link->down != NULL)
		link = link->down;
	return link;
}

void Text::print_text(TextLink* link) {
	if (link == NULL)
		return;
	bool is_current = false;
	if (current == link)
		is_current = true;

	link->print(std::cout, is_current);

	if (link->down != NULL) {
		std::cout << '\n';
		print_text(link->down);
	}
	if (link->next != NULL) {
		print_text(link->next);
	}
	if (link->down == NULL && link->next == NULL) {
		std::cout << '\n';
	}
}

void Text::print_sublevels(TextLink* link) {
	if (link == NULL)
		return;
	bool is_current = false;
	if (current == link)
		is_current = true;

	link->print(std::cout, is_current);

	if (link->down != NULL) {
		tab_counter++;
		print_tabs();
		print_sublevels(link->down);
		tab_counter--;
	}
	if (link->next != NULL) {
		print_tabs();
		print_sublevels(link->next);
	}
}

void Text::print(bool display_sublevels) {
	if (display_sublevels) {
		print_sublevels(first);
		std::cout << '\n';
	}
	else
		print_text(first);
}

void Text::print_tabs() {
	std::cout << '\n';
	std::string tab(tab_counter, '\t');
	std::cout << tab;
}

void Text::read(const char* file_name) {
	std::ifstream file(file_name);
	if (file.is_open()) {
		delete first;
		current = NULL;
		first = read_text(file);
		if (current == NULL)
			current = first;
		file.close();
	}
	else
		throw std::exception("Неудалось открыть файл");
}

TextLink* Text::read_text(std::ifstream& file) {
	TextLink* head, *cur;
		head = cur = new TextLink;
	if (head == NULL)
		return NULL;

	char str[TextLink::MAX_LINE_LEN];
	while (!file.eof()) {
		file.getline(str, TextLink::MAX_LINE_LEN, '\n');
		if (file.fail())
			file.clear();

		if (str[0] == '{')
			cur->down = read_text(file);
		else if (str[0] == '}')
			break;
		else if (strcmp(str, "&&&") == 0)
			current = cur;
		else {
			cur->next = new TextLink(str);
			if (cur->next == NULL)
				break;
			cur = cur->next;
		}
	}
	cur = head->next;
	delete head;
	return cur;
}

void Text::write(const char* file_name) {
	std::ofstream file(file_name);
	
	if (file.is_open())
		write_text(first, file);
	else
		throw std::exception("Неудалось открыть файл");
	file.close();


}

void Text::write_text(TextLink* cur, std::ofstream& file) {
	while (cur != NULL) {
		if (cur != first)
			file << '\n';
		file << cur->str;
		if (cur == current)
			file << "\n&&&";

		if (cur->down != NULL) {
			file << "\n{";
			write_text(cur->down, file);
			file << "\n}";
		}

		cur = cur->next;
	}
}

void Text::clear() {
	first = NULL;
	TextLink::mem_cleaner(*this);
	first = current = get_new_link();
}
