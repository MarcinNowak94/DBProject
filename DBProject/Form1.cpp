#include "Form1.h"

using namespace DBProject;

enum class filetype { text, CSV, sql, other};


//returns handle to string object
String ^ getCureentContent() {
	std::string default = "/*return file content*/";
	String ^ content = gcnew String (default.c_str());
	return content;
};