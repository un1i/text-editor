#include <iostream>


class TextLink;
class Text;

class TextMem {
private:
	TextLink* first;
	TextLink* last;
	TextLink* free;
	friend class TextLink;
};

class TextLink {
private:
	static const int MAX_LINE_LEN = 50;
	static const int MEM_SIZE = 50;
	typedef char Tstr[MAX_LINE_LEN];
	Tstr str;
	TextLink* next;
	TextLink* down;
	static TextMem mem_header;
public:
	static void init_mem_system(int size = MEM_SIZE);
	static void print_free_link();
	void* operator new(size_t size);
	void operator delete(void* link);
	static void mem_cleaner(Text& txt);
	TextLink(Tstr s = "", TextLink* next = NULL, TextLink* down = NULL);
	~TextLink() {};
	bool is_atom();
	TextLink* get_next();
	TextLink* get_down();
	TextLink* get_copy();
	void print(std::ostream& os, bool is_current);
	friend class Text;
};