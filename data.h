#include <stdint.h>
#define N 20
#define R 3
#define DSIZE N*N
#define T 10000//学習回数
#define ALPHA 0.5//学習率


struct SOM{
	int Ci;
	int Cj;
	int t;
	double select[R];
	double X[DSIZE][R];
	double map[N][N][R];
}som;
struct GUI {
	char str[250];
	double arcr[N][N];
}gui;
