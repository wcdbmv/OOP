#ifndef LIKELY_H_
#define LIKELY_H_

#define likely(x)      __builtin_expect(!!(x), 1)
#define unlikely(x)    __builtin_expect(!!(x), 0)

#endif //LIKELY_H_
