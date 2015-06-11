#pragma once
#include <stdio.h>
#include <stdarg.h>

#define prompt(args...) printf("mosesdb> "); printf(args);

#define LOG(args...) \
	FILE* log_file = fopen("mosesdb.log", "a"); \
	if (log_file != NULL) { \
		fprintf(log_file, "mosesdb log> "); \
		fprintf(log_file, args); \
	} else printf("LOG ERROR\n"); 

#define DEBUG(args...) \
	fprintf(stderr, "mosesdb debug> "); \
	fprintf(stderr, args);
