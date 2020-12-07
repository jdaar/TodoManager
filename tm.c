#include "stdlib.h"
#include "stdio.h"
#include "string.h"
#include "json-c/json_object.h"
#include "json-c/json_util.h"
#include <json-c/json_types.h>

// CONSTANTS

#define JSON_FILE_PATH "JSONPATH/todos.json"
#define JSON_FILE fopen(JSON_FILE_PATH, "r")
#define SAVE_JSON() json_object_to_file(JSON_FILE_PATH, root)

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

typedef void (*func_type)(char*);

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

json_object *CREATE_TODO(char* name, int value) {
	json_object *todo = json_object_new_object();
	json_object_object_add(todo, "name", json_object_new_string(name));
	json_object_object_add(todo, "completed", json_object_new_boolean(value));
	return todo;
}

char *GET_INPUT(char *inputName) {
	char* input = malloc(STR_SIZE);
	printf("%s > ", inputName);
	fgets(input, STR_SIZE, stdin);
	if (input[strlen(input) - 1] == '\n')
		input[strlen(input) - 1] = '\0';
	return input;
}

void CREATE_FORMAT() {
	json_object *root = json_object_new_object();
	json_object_object_add(root, "todos", json_object_new_array());
	SAVE_JSON();
}

// ACTIONS

void ADD_ACTION(char *parameter) {
	json_object *root = json_object_from_file(JSON_FILE_PATH);
	json_object *todos = json_object_object_get(root, "todos");
	json_object *todo = CREATE_TODO(parameter, 0);
	json_object_array_add(todos, todo);
	SAVE_JSON();
}

void REMOVE_ACTION(char *parameter) {
	json_object *root = json_object_from_file(JSON_FILE_PATH);
	json_object *todos = json_object_object_get(root, "todos");
	json_object_array_del_idx(todos, atoi(parameter), 1);
	SAVE_JSON();
}

void MODIFY_ACTION(char *parameter) {
	json_object *root = json_object_from_file(JSON_FILE_PATH);
	json_object *todos = json_object_object_get(root, "todos");
	json_object *todo = json_object_array_get_idx(todos, atoi(parameter));
	int oldBool = json_object_get_boolean(json_object_object_get(todo, "completed"));
	json_object_set_boolean(json_object_object_get(todo, "completed"), !oldBool);
	SAVE_JSON();
}

void PRINT_ALL_ACTION() {
	char *completedVals[2] = { "Uncompleted", "Completed" };
	json_object *root = json_object_from_file(JSON_FILE_PATH);
	json_object *todos = json_object_object_get(root, "todos");
	for(int i = 0; i < json_object_array_length(todos); i++) {
		json_object *todo = json_object_array_get_idx(todos, i);
		const char *name = json_object_get_string(json_object_object_get(todo, "name"));
		int completedBool = json_object_get_boolean(json_object_object_get(todo, "completed"));
		printf("%d > %s ~ %s\n", i, name, completedVals[completedBool]);
	}
}

// MODIFIERS

void ADD_MODIFIER(int* flags, char* argument, func_type action, int actionidx) {
	if (argument == NULL && actionidx != 0)
		argument = GET_INPUT("Name");
	if (flags[0] || JSON_FILE == NULL) 
		CREATE_FORMAT();
	action(argument);
}

// MAIN

int main(int argc, char** argv) {
	func_type functions[3] = { ADD_ACTION, REMOVE_ACTION, MODIFY_ACTION };
	char *argString = NULL;
	int flags[2] = { 0, 0 };
	int action = 0;
	for (int i = 1; i < argc; i++) {
		int parameter = PARAMETER_STR_TO_INT(argv[i]);
		if (parameter <= NEW_FILE - 1) 
			action = parameter;
		else {
			int newIndex = parameter - NEW_FILE;
			if (newIndex <= 1)
				flags[newIndex] = !flags[newIndex];
			else
				argString = argv[i];
		}
	}
	if (action == 0) 
		ADD_MODIFIER(flags, argString, PRINT_ALL_ACTION, action);
	else
		ADD_MODIFIER(flags, argString, functions[action - 1], action);
	return 0;
}
