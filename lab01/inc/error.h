#ifndef ERROR_H_
#define ERROR_H_

typedef enum {
	NONE,
	WRONG_USAGE,
	CANT_OPEN_FILE,
	INVALID_FILE_FORMAT,
	ALLOC_FAIL,
	WRONG_COMMAND
} error_t;

void perrmsg(error_t error);

#endif // ERROR_H_
