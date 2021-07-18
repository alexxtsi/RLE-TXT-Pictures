/*
* Alexander Tsiganenko
*
* complexity o(n^2)
*/

#pragma warning(disable:4996)

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "SaveOpen.h"

void printPic(char[R][C]);

//function saving the picture to txt file
void saveTxt(char *path, char pic[R][C]) {
	printf("file path %s\n", path);
	FILE *f = fopen(path, "w");
	if (f == NULL) {
		printf("ERORR opening file!\n");
		return;
	}
	int i, j;
	for (i = 0; i < R; i++) {
		for (j = 0; j < C; j++) {
			fputc(pic[i][j], f);
		}
		fputc('\n', f);
	}
	fclose(f);
}
//function opening picture from txt file
int openTxt(char *path, char pic[R][C]) {
	FILE *f = fopen(path, "r");
	int i, j;
	char temp;
	char message[CMD_LEN] = "ERORR opening file!";
	strcat(message, path);
	if (f == NULL) {
		printf("%s  \n", message);
		return 0;
	}
	for (i = 0; i < R; i++)
		for (j = 0; j < C; j++) {
			pic[i][j] = fgetc(f);
			if (j == C)      //not save the '\n' to the picture matrix
				temp = fgetc(f);
		}
	printPic(pic);

	fclose(f);
	return 1;
}

//function compres and save picture to RLE file
void saveRle(char *path, char pic[R][C]) {
	FILE *f = fopen(path, "wb");
	int i, j, flag;
	unsigned char byte = 0, temp;
	char colorFlag = BLACK;
	if (f == NULL) {
		printf("ERORR opening file!\n");
		return;
	}
	if (pic[0][0] == WHITE) {
		colorFlag = WHITE;
		byte |= 128;     //turning on the MSB(color) for the white color
	}
	for (i = 0; i < R; i++) {
		for (j = 0; j < C; j++) {
			flag = 0;
			if (pic[i][j] != colorFlag) { // if the color changed change the MSB (NOT on the MSB)
				flag = 1;
				colorFlag = pic[i][j];
				fprintf(f, "%c", byte);
				//change the bit of the color and the bits of the count =0
				temp = byte;
				byte |= 128;  // | 1000 0000
				byte ^= temp;
			}
			byte++;
			if ((byte == 127) || (byte == 255)) {
				flag = 1;
				fprintf(f, "%c", byte);
				byte &= 128;   //turninig off all the bits  except MSB(color)	
			}
		}
	}
	if (!flag)// if there is last char that not saved to file
		fprintf(f, "%c", byte);
	fclose(f);
}


//function opening picture from RLE file
int openRle(char* path, char pic[R][C]) {
	unsigned char byte;
	char str[R*C], color;
	int i, j = 0, k = 0, n = 0, temp = 0;
	FILE* f;
	f = fopen(path, "rb");
	char message[CMD_LEN] = "ERORR opening file!";
	strcat(message, path);
	if (f == NULL) {
		printf("%s  \n", message);
		return 0;
	}
	//while file ends
	while (!feof(f)) {
		byte = fgetc(f);
		temp += n;
		j = temp;
		if (byte <= 127)
			color = BLACK;
		else {
			color = WHITE;
			byte = byte & 127; //turning off the MSB (127-> 0111 1111b)
		}
		n = byte;

		while (j < R*R) {
			str[j] = color;
			j++;
		}
	}
	for (i = 0; i < R; i++)
		for (j = 0; j < C; j++)
			pic[i][j] = str[k++];
	if (temp < 900) {
		printf("less pixeles then expected ILEGAL FORMAT \n\n");
	}
	else
		printPic(pic);
	fclose(f);
	return 1;
}


//print the picture
void printPic(char pic[R][C]) {
	int i, j;
	for (i = 0; i < R; i++) {
		for (j = 0; j < C; j++)
			putchar(pic[i][j]);
		putchar('\n');
	}
}

