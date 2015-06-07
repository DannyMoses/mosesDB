#pragma once

// the error codes for all(most) functions will be defined here
// TODO: make these better

#define FUNCTION_SUCCESS 0 // complete success
#define FUNCTION_POSSIBLE_UNDEF 1 // possible that behavior is different than what user expects
#define FUNCTION_ERROR -1 // error that the program can recover from
#define FUNCTION_FATAL_ERROR -2 // error that the program cannot recover from
