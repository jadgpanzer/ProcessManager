#include "util.h"
static bool is_option(const char* arg) {
	regex reg_option = regex("-.+$");
	cmatch match;
	bool result = regex_match(arg, match, reg_option);
	return result;
}
static bool is_para(const char* arg) {
	regex reg_para = regex("^(?!-).+$");
	cmatch match;
	bool result = regex_match(arg, match, reg_para);
	return result;
}

static bool is_pid(const char* pid) {
	regex reg_pid = regex("[0-9]+");
	cmatch match;
	bool result = regex_match(pid, match, reg_pid);
	return result;
}

static bool is_path(const char* path) {
	regex reg_pid = regex(".+\.exe");
	cmatch match;
	bool result = regex_match(path, match, reg_pid);
	return result;
}