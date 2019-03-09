#ifndef RECEIVE_H_
#define RECEIVE_H_

#include "error.h"

error_t receive_load(void);
error_t receive_save(void);
error_t receive_transform(void);
error_t receive_render(void);

#endif // RECEIVE_H_
