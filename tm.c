#include "stdlib.h"
#include "stdio.h"
#include "string.h"

// CONSTANTS

#define JSON_FILE_PATH "JSONPATH"
#define JSON_FILE fopen(JSON_FILE_PATH, "r");

#define STR_SIZE sizeof(char) * 200

// ACTION INDEXES

#define ADD 1
#define REMOVE 2
#define MODIFY 3

// FLAG INDEXES

#define NEW_FILE 4

// FUNCTIONS

int PARAMETER_STR_TO_INT(char* actionSTR) {
	if(!strcmp(actionSTR, "-n"))
			return 1;
	if(!strcmp(actionSTR, "-r"))
			return 2;
	if(!strcmp(actionSTR, "-m"))
			return 3;
	if(!strcmp(actionSTR, "-N"))
			return 4;
	return 0;
}

// ACTIONS

void ADD_ACTION() {
	printf("ADDING");
}

void REMOVE_ACTION() {
	printf("REMOVING");
}

void MODIFY_ACTION() {
	printf("MODIFY");
}

// MAIN

int main(int argc, char** argv) {

	char *argString = malloc(STR_SIZE);

	for (int i = 1; i < argc; i++) {
		switch (PARAMETER_STR_TO_INT(argv[i])) {
			case ADD:
				ADD_ACTION();
				break;
			case REMOVE:
				REMOVE_ACTION();
				break;
			case MODIFY:
				MODIFY_ACTION();
				break;
			case NEW_FILE:
				break;
			default:
				argString = argv[i];
				break;
		}	
	}

	return 0;
}
