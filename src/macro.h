#ifndef MACRO_H_
#define MACRO_H_

#define FOREACH_STRINGIFYABLE_TYPE   \
    GENERATE_FOR(int)                \
    GENERATE_FOR(unsigned)           \
    GENERATE_FOR(long)               \
    GENERATE_FOR(unsigned long)      \
    GENERATE_FOR(long long)          \
    GENERATE_FOR(unsigned long long) \
    GENERATE_FOR(float)              \
    GENERATE_FOR(double)             \
    GENERATE_FOR(long double)

#endif