#include "Text.h"
#include <string>


class TextUsercom {
private:
	Text txt;
	bool display_sublevels;
	void main_menu();
	void ins_menu();
	void del_menu();
	void change_menu();
	void save_text();
	void read_text();
	void actions();
	void options();
	std::string enter_string();
	std::string enter_file_name();
public:
	TextUsercom();
	void run();
};