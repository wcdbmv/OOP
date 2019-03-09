#include "receive.h"
#include "global.h"
#include "execute.h"

error_t receive_load(void) {
	command_data_t command_data = {.filename = filename};
	return execute(LOAD_MODEL, &command_data);
}

error_t receive_save(void) {
	command_data_t command_data = {.filename = filename};
	return execute(SAVE_MODEL, &command_data);
}

error_t receive_transform(void) {
	command_data_t command_data = {.transform_meta = &transform_meta};
	return execute(TRANSFORM_MODEL, &command_data);
}

error_t receive_render(void) {
	command_data_t command_data = {.screen = &screen};
	return execute(RENDER_MODEL, &command_data);
}
