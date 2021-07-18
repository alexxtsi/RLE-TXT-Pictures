/*
 * Alexander Tsiganenko 
 *
 * complexity o(n^2)
 */

#pragma warning(disable:4996)

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <stdio.h>

#include "create.h"
#include "SaveOpen.h"


#define OPEN_RLE "open_RLE_picture"
#define OPEN_TXT "open_TXT_picture"

#define SAVE_RLE "save_RLE_picture"
#define SAVE_TXT "save_TXT_picture"

#define CS "create_square"
#define CT "create_treangle"
#define CR "create_romb"


int commandDet(char *);
void getFromInput(char *, char *, int *);
int sizeCheck(char *);
int inputCheck(char *, char *, int *, int *, int *);
void printOptions();
void fillPic(char[R][C]);

int main() {
	int commandN, index;
	int color, size, flag = 0;
	char input[CMD_LEN], command[CMD_LEN], parameter[CMD_LEN], path[CMD_LEN];
	char pic[R][C];
	do {
		index = 0;
		printOptions();
		gets(input);

		getFromInput(input, command, &index);  //geting the command from the intput 
		commandN = commandDet(command);       //determine the command
		//from 1 to 4 open and save functions
		//from 5 to 7 create functions
		switch (commandN) {
		case 1: getFromInput(input, path, &index); openRle(path, pic);  flag = 1; break;
		case 2: getFromInput(input, path, &index); openTxt(path, pic); flag = 1; break;
		case 3: getFromInput(input, path, &index); if (!flag) fillPic(pic); saveRle(path, pic);  break;
		case 4: getFromInput(input, path, &index); if (!flag) fillPic(pic); saveTxt(path, pic); break;
		case 5: if (inputCheck(input, parameter, &index, &size, &color)) create_square(size, pic, color); flag = 1; break;
		case 6: if (inputCheck(input, parameter, &index, &size, &color))  create_treangle(size, pic, color); flag = 1; break;
		case 7: if (inputCheck(input, parameter, &index, &size, &color))  create_romb(size, pic, color); flag = 1; break;
		case 8: break;
		default: printf("\nILEGAL COMMAND\n");
			break;
		}
	} while (commandN != 8);
}

// function geting size and color for the figure and check if it legal
int inputCheck(char *input, char *parameter, int *index, int *size, int *color) {

	getFromInput(input, parameter, index);
	*size = sizeCheck(parameter);
	if (*size == -1 || *size > 20) {
		printf("\n ILEGAL SIZE !!!\n\n");
		return 0;
	}
	getFromInput(input, parameter, index);
	if (!strcmp(parameter, "regular"))
		*color = 0;
	else if (!strcmp(parameter, "invert"))
		*color = 1;
	else {
		printf("\nILEGAL FORMAT OR NO FORMAT ETERED!!\n\n");
		return 0;
	}
	return 1;

}


//function geting the command from the intput
void getFromInput(char *input, char *parameter, int *index) {
	int i = 0;
	//while the index get to space of end of string
	while (input[*index] == ' ') (*index)++; //skiping the space in the input
	while (input[*index] != ' ' && input[*index] != '\0') {
		parameter[i] = input[*index];  //copy parameter or commanf to string
		i++;
		(*index)++;
	}
	parameter[i] = '\0';
	(*index)++;
}

//function convert string with size  to integer
int sizeCheck(char *sizeStr) {
	int i = 0;
	int size = 0;
	while (sizeStr[i] != '\0') {
		//check if every char of the size in the string is a number
		if (sizeStr[i] - '0' < 0 && sizeStr[i] - '0' > 9)
			return -1;
		size *= 10;
		size += (int)(sizeStr[i] - '0');

		i++;
	}
	return size;
}



//function determine the command
int commandDet(char *input) {
	if (!(strcmp(input, OPEN_RLE)))
		return 1;
	if (!(strcmp(input, OPEN_TXT)))
		return 2;
	if (!(strcmp(input, SAVE_RLE)))
		return 3;
	if (!(strcmp(input, SAVE_TXT)))
		return 4;
	if (!(strcmp(input, CS)))
		return 5;
	if (!(strcmp(input, CT)))
		return 6;
	if (!(strcmp(input, CR)))
		return 7;
	if (!(strcmp(input, "stop")))
		return 8;
	return 0;
}
//function prints all commands options
void printOptions() {
	printf("Etenr the command\nyour options:\n\n");

	printf("1)  open_RLE_picture\n");
	printf("2)  open_TXT_picture\n");
	printf("3)  save_RLE_picture\n");
	printf("4)  save_TXT_picture\n");
	printf("5)  create_square  (size)  (format regular/invert)\n");
	printf("6)  create_treangle  (size)  (format regular/invert)\n");
	printf("7)  create_romb  (size)  (format regular/invert)\n");
}


//fill the picture black squere
void fillPic(char pic[R][C]) {
	int i, j;
	for (i = 0; i < R; i++) 
		for (j = 0; j < C; j++) 
				pic[i][j] = BLACK;
}






