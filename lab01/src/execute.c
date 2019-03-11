#include "execute.h"
#include "render.h"

error_t execute(command_t command, const command_data_t *command_data) {
	static model_t model = EMPTY_MODEL;
	error_t error = NONE;
	switch (command) {
	case LOAD_MODEL:
		error = load_model(&model, command_data->filename);
		break;
	case SAVE_MODEL:
		error = dump_model(&model, command_data->filename);
		break;
	case TRANSFORM_MODEL:
		error = transform_model(&model, command_data->transform_meta);
		break;
	case RENDER_MODEL:
		error = render_model(&model, command_data->screen);
		break;
	case DELETE_MODEL:
		delete_model(&model);
		break;
	default:
		error = WRONG_COMMAND;
		break;
	}
	return error;
}
