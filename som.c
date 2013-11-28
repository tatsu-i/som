#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "data.h"

void input(){
	int i = rand()%DSIZE;
	som.select[0] = som.X[i][0];
	som.select[1] = som.X[i][1];
	som.select[2] = som.X[i][2];
	sprintf(gui.str, "勝者ノード: R=%lf G=%lf B=%lf", 
			som.select[0], som.select[1], som.select[2]);
}
void init_map(){
	int i = 0,j = 0,k=0;
	srand((unsigned)time(NULL));
	for(i = 0;i < N;i++){
		for(j = 0;j < N;j++){
			for (k = 0; k < R; k++) {
				som.map[j][i][k] = (double)rand()/RAND_MAX;
			}
		}
	}
	for (i = 0; i < DSIZE; i++) {
		for (k = 0; k < R; k++) {
			som.X[i][k] = (double)rand()/RAND_MAX;
		}
	}
	input();
}
void win(int x, int y, int coller){
	gui.arcr[x][y] = coller;
}

void select_win(){
	double min = 100, res;
	int i, j;
	if (som.t == T) return;
	win(som.Ci, som.Cj, 0);
	for (j = 0; j < N; j++) {
		for (i = 0; i < N; i++) {
			res = sqrt(
					(som.select[0] - som.map[i][j][0])*(som.select[0] - som.map[i][j][0])+
					(som.select[1] - som.map[i][j][1])*(som.select[1] - som.map[i][j][1])+
					(som.select[2] - som.map[i][j][2])*(som.select[2] - som.map[i][j][2])
					);
			if(res < min){
				som.Ci = i, som.Cj = j;
				min = res;
			}
		}
	}
	win(som.Ci, som.Cj, 255);
}

double hci(int i, int j){
	double a_t = ALPHA*(1.0-(som.t/T));
	double sig_t = (N/3.0*(1.0-som.t/T))*(N/3.0*(1.0-som.t/T));
	double res =  a_t*exp(
			-1.0*(
			 (i-som.Ci)*(i-som.Ci)+
			 (j-som.Cj)*(j-som.Cj)
			)/sig_t
		   );
	return res;
}
void update_map(){
	int i, j ,k;
	if (som.t == T) return;
	for (i = 0; i < N; i++) {
		for (j = 0; j < N; j++) {
			for (k = 0; k < R; k++) {
				som.map[i][j][k] += hci(i,j)*(som.select[k]-som.map[i][j][k]);
			}
		}
	}
	som.t++;
}
