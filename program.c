#include "interface.h"

int main (int argc, char *argv[]){

	TAD_istruct qs = init();
	qs = load(qs, argc, argv);

	return 0;
}
