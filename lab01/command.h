#ifndef COMMAND_H_
#define COMMAND_H_

#include "screen.h"
#include "transform_meta.h"

typedef enum {
	LOAD_MODEL,
	SAVE_MODEL,
	TRANSFORM_MODEL,
	RENDER_MODEL
} command_t;

typedef union {
	const char *filename;
	transform_meta_t *transform_meta;
	screen_t *screen;
} command_data_t;

#endif // COMMAND_H_
