#include "stdlib.h"
#include "stdio.h"
#include "string.h"
#include "json-c/json_object.h"
#include "json-c/json_util.h"
#include <json-c/json_types.h>

// CONSTANTS

#define JSON_FILE_PATH "JSONPATH/todos.json"
#define JSON_FILE fopen(JSON_FILE_PATH, "r")

#define STR_SIZE sizeof(char) * 200

// ACTION INDEXES

#define ADD 1
#define REMOVE 2
#define MODIFY 3
#define GET 4

// FLAG INDEXES

#define NEW_FILE 5
#define UNDEFINED 10

// TYPEDEFS

typedef void (*func_type)(void);

// FUNCTIONS

int PARAMETER_STR_TO_INT(char* actionSTR) {
	if(!strcmp(actionSTR, "-n"))
			return ADD;
	if(!strcmp(actionSTR, "-r"))
			return REMOVE;
	if(!strcmp(actionSTR, "-m"))
			return MODIFY;
	if(!strcmp(actionSTR, "-N"))
			return NEW_FILE;
	return UNDEFINED;
}

void CREATE_FORMAT() {
	json_object *root = json_object_new_object();
	json_object_object_add(root, "todos", json_object_new_array());
	json_object_to_file(JSON_FILE_PATH, root);
}

// ACTIONS

void ADD_ACTION() {
	json_object *root = json_object_from_file(JSON_FILE_PATH);
	printf("%s", json_object_to_json_string(root));
}

void REMOVE_ACTION() {
	printf("REMOVING");
}

void MODIFY_ACTION() {
	printf("MODIFY");
}

// MODIFIERS

void ADD_MODIFIER(int* flags, func_type action) {
	if (flags[0]) {
		CREATE_FORMAT();
		ADD_ACTION();
	}
}


// MAIN

int main(int argc, char** argv) {
	func_type functions[3] = { ADD_ACTION, REMOVE_ACTION, MODIFY_ACTION };
	char *argString = malloc(STR_SIZE);
	int flags[2] = { 1, 1 };
	int action = 0;

	for (int i = 1; i < argc; i++) {
		int parameter = PARAMETER_STR_TO_INT(argv[i]);
		if (parameter <= 3) 
			action = parameter;
		else 
			flags[parameter - 5] = !flags[parameter - 5];
		
	}

	if (action == 0) 
		ADD_MODIFIER(flags, functions[action]);
	else
		ADD_MODIFIER(flags, functions[action - 1]);

	return 0;
}
