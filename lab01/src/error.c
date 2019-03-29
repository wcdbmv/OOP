#include "error.h"
#include <stdio.h>
#include "global.h"

void perrmsg(error_t error) {
	switch (error) {
	case NONE:
		break;
	case WRONG_USAGE:
		fputs("Usage: wm3dv <filename>", stderr);
		break;
	case CANT_OPEN_FILE:
		perror(filename);
		break;
	case INVALID_FILE_FORMAT:
		fprintf(stderr, "%s: Invalid file format\n", filename);
		break;
	case ALLOC_FAIL:
		perror("alloc fail");
		break;
	case WRONG_COMMAND:
		fputs("command not found", stderr);
		break;
	}
}
