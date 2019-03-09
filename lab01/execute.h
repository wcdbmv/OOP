#ifndef EXECUTE_H_
#define EXECUTE_H_

#include "command.h"
#include "error.h"

error_t execute(command_t command, const command_data_t *command_data);

#endif // EXECUTE_H_
