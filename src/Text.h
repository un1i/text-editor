#include <stack>
#include "TextLink.h"

class Text {
private:
	TextLink* first;
	TextLink* current;
	std::stack<TextLink*> path;
	std::stack<std::pair<TextLink*, int >> it;
	size_t tab_counter;
	bool end_it;
	TextLink* get_first_atom(TextLink* link);
	TextLink* get_new_link(TextLink::Tstr str = "", TextLink* next = NULL, TextLink* down = NULL);
	void print_text(TextLink* link);
	void print_sublevels(TextLink* link);
	TextLink* read_text(std::ifstream& file);
	void write_text(TextLink* cur, std::ofstream& file);
	void print_tabs();
public:
	Text(TextLink* link = NULL);
	~Text() {};
	Text* get_copy();

	int go_first_link();
	int go_down_link();
	int go_next_link();
	int go_prev_link();

	std::string get_line();
	void set_line(std::string str);

	void ins_down_line(std::string str);
	void ins_down_section(std::string str);
	void ins_next_line(std::string str);
	void ins_next_section(std::string str);
	void del_down_line();
	void del_down_section();
	void del_next_line();
	void del_next_section();

	int reset();
	int is_ended() const;
	int go_next();

	void read(const char* file_name);
	void write(const char* file_name);

	void print(bool display_sublevels = false);
	void clear();
	void run_garbage_collector();
};