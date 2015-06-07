#include "../include/databaseFunctions.h"

int print_record()
{
	FILE* pFile;
	char *fileName;
	char readBuffer[100];
	printf("What is the name of the record? ");
	fileName = strdup(dynamicString(stdin));
	pFile = fopen(fileName, "r");

	if (pFile == NULL) {
	fileName = strdup(dynamicString(stdin));
	} else {
	}
	pFile = fopen(fileName, "r");
	if (pFile == NULL) {
		fprintf(stderr, "Nope, still not working. Segfault away!\n");
		exit(EXIT_FAILURE);
	} else {
		while(fgets(readBuffer, 100, pFile) != NULL) {
			printf("%s", readBuffer);	
		}
	}
	
	free(fileName);
	return FUNCTION_SUCCESS;
}

int write_record(field* fields, int num_fields)
{
	FILE* pFile;
	char *fileName;
	printf("What is the name of the record?(the file will be overwritten) ");
	fileName = strdup(dynamicString(stdin));
	pFile = fopen(fileName, "w");
	
	if (pFile == NULL) {
		fileName = strdup(dynamicString(stdin));
	} else {
	}
	pFile = fopen(fileName, "w");
	if (pFile == NULL) {
		printf("No dice. Segfault!\n");
		exit(EXIT_FAILURE);
	} else {	
		for (int i = 1; i <= num_fields; i++) 
		{
			char buffer[80];
			printf("%s: ", fields[i].name);
			scanf("%s", buffer);
			fprintf(pFile, "%s\n", buffer);
			strcpy(buffer, "");
		}
	}

	printf("done writing to record %s\n", fileName);
	fclose(pFile);
	free(fileName);
	return FUNCTION_SUCCESS;
}

int delete_record()
{
	char *recordName;
	printf("What is the name of the record(**WARNING:FILE WILL BE DELETED**)? ");
	recordName = strdup(dynamicString(stdin));
	recordName = strdup(dynamicString(stdin));
	remove(recordName);
	printf("record successfully deleted\n");
	return FUNCTION_SUCCESS;
}

int clear_record()
{
	FILE* pFile;
	char *recordName;
	printf("What is the name of the record(the file itself will not be deleted)? ");
	recordName = strdup(dynamicString(stdin));
	recordName = strdup(dynamicString(stdin));
	pFile = fopen(recordName, "w");
	if (pFile == NULL) {
		perror("The following error has occurred");
		exit(EXIT_FAILURE);
	} else {
		freopen(recordName, "w", pFile);
		printf("%s cleared successfully\n", recordName);
	}
	fclose(pFile);
	return FUNCTION_SUCCESS;
}

int create_record()
{
	FILE* pFile;
	char *recordName;
	printf("What is the name of this new record(names must not overlap)? ");
	recordName = strdup(dynamicString(stdin));
	recordName = strdup(dynamicString(stdin));
	pFile = fopen(recordName, "w");
	if (pFile == NULL) {
		perror("The following error has occurred");
		exit(EXIT_FAILURE);
	}
	printf("record created successfully\n");
	fclose(pFile);
	return FUNCTION_SUCCESS;
}

int print_schema(field* fields, int num_fields)
{
	for (int i = 1; i <= num_fields; i++)
	{
		printf("%s\n", fields[i].name);
	}
	return FUNCTION_SUCCESS;
}

int clear_schema(FILE* pFile, char *pFileName)
{
	char *recordName = strdup(pFileName);
	pFile = freopen(recordName, "w", pFile);
	return FUNCTION_SUCCESS;
}
