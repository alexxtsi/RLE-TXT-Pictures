/*
* Alexander Tsiganenko
*
* complexity o(n^2)
*/

#pragma warning(disable:4996)

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "create.h"
//function create square
void create_square(int size, char pic[R][C], int colorFlag) {
	int i, j;
	int start = (R - size) / 2;   //start point of creating square+ 
	for (i = 0; i < R; i++) {
		for (j = 0; j < R; j++) {
			//condition for strat creation of the square
			if (i >= start && j >= start && i < size + start && j < size + start) {
				if (!colorFlag)
					pic[i][j] = BLACK;
				else
					pic[i][j] = WHITE;
			}
			else {
				if (!colorFlag)
					pic[i][j] = WHITE;
				else
					pic[i][j] = BLACK;
			}
			printf("%c", pic[i][j]);

		}
		printf("\n");

	}
}

//function create treangle
void create_treangle(int size, char pic[R][C], int colorFlag) {
	int i, j;
	int flag = 0;
	int tHight = (size + 1) / 2;     // the hight of the treangle
	int startV = R / 2 - tHight / 2;//  vertical start point of creating treangle
	int startH = R / 2 - 1;        //   horizontal start point of creating treangle


	for (i = 0; i < R; i++) {
		for (j = 0; j < R; j++) {
			//condition for strat creation of the treangle
			if (i >= startV && j >= startH && i < tHight + startV && j < R - startH - (size % 2)) {
				if (!colorFlag)
					pic[i][j] = BLACK;
				else
					pic[i][j] = WHITE;
				flag = 1;
			}
			else
				if (!colorFlag)
					pic[i][j] = WHITE;
				else
					pic[i][j] = BLACK;
			printf("%c", pic[i][j]);
		}
		if (flag) // when creation started decrise the horizontal start point
			startH--;
		printf("\n");
	}
}

void create_romb(int size, char pic[R][C], int colorFlag) {
	int i, j;
	int flag = 0;
	int rHight = size % 2 ? size : size - 1; // the hight of the romb
	int startV = R / 2 - rHight / 2;        // vertical poit of start creating the romb
	int startH = R / 2 - 1;                // horizotal point of start creating the romb
	for (i = 0; i <R; i++) {
		for (j = 0; j < R; j++) {
			//condition for strat creation of the rob
			if (i >= startV &&  j >= startH && i < rHight + startV && j < R - startH - (size % 2)) {
				if (!colorFlag)
					pic[i][j] = BLACK;
				else
					pic[i][j] = WHITE;
				flag = 1;
			}
			else
				if (!colorFlag)
					pic[i][j] = WHITE;
				else
					pic[i][j] = BLACK;
			printf("%c", pic[i][j]);
		}
		if (i >= rHight / 2 + startV) { //get to the middle of the romb
			flag = 0;                  // incrising the horizontal start point
			startH++;                 
		}
		if (flag)  // decrising the horizontal start point
			startH--;
		printf("\n");
	}
}