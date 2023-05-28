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
	void actions();
	void options();
	std::string enter_string();
public:
	TextUsercom();
	void run();
};