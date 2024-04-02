#include "util.h"
static void UnknowOptionError(const char* option) {
	printf("Unknown Option: %s\n", option);
}
static void InvalidPIDError(const char* para) {
	printf("Invalid PID:%s\n", para);
}
static void InvalidPathError(const char* path) {
	printf("Invalid Excutable File Path:%s\n", path);
}