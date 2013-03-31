#include "files.h"

int main(int argc, char* argv[]) {
	files program(argv[1], argv[2]);
	program.init();
	return 0;
}
