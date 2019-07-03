#ifndef UTIL_H
#define UTIL_H

#define SAFE_DELETE(ptr) if(ptr != NULL){delete ptr;ptr = NULL;}
#define SAFE_DELETE_ARRAY(ptr) if(ptr != NULL){delete[] ptr;ptr = NULL;}

#define DOUBLE_EPSILON 1e-10
#define PI 3.14159265359
#define FLOAT_EPSILON 1e-7
#define ZERO(value) ((value) < FLOAT_EPSILON && (value) > -FLOAT_EPSILON)
#endif // UTIL_H