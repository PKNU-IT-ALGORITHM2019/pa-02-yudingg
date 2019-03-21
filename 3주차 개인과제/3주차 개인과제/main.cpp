#include <stdio.h>
#include <math.h>
#include <string.h>

#define MAX 20

typedef struct Data {
	int x;
	int y;
};

Data local[MAX];
int n;
int seq[MAX + 1];

double tour(int num,double len, double min);
int main() {

	char name[MAX][MAX] = { "input0.txt","input1.txt","input2.txt","input3.txt","input4.txt","input5.txt","input6.txt" };

	int a=0;
	while (a < 7) {
	
		char filename[MAX];
		strcpy(filename, name[a]);

		FILE*fp = fopen(filename, "r");
		fscanf(fp, "%d", &n);
		for (int i = 0; i < n; i++)
			fscanf(fp, "%d %d", &local[i].x, &local[i].y);
		fclose(fp);

		printf("%lf\n", tour(0, 0.0, -1));

		for (int i = 0; i < n; i++)
			printf("%d ", seq[i]);
		printf("\n\n");
		
		a++;
	}
	return 0;

}

int overlap[MAX + 1] = { 0 };
double tour(int num, double len,double min) {

	for (int i = 0; i < num; i++) {
		if (overlap[i] == overlap[num])
			return -1;
	}
	if (min > 0 && min < len)
		return -1;

	if (num != 0) {
		int sqX = (local[overlap[num]].x - local[overlap[num - 1]].x)*(local[overlap[num]].x - local[overlap[num - 1]].x);
		int sqY = (local[overlap[num]].y - local[overlap[num - 1]].y)*(local[overlap[num]].y - local[overlap[num - 1]].y);
		len += sqrt(sqX + sqY);
	}
	if (n - 1 == num) {
		int sqX = (local[overlap[num]].x - local[overlap[0]].x)*(local[overlap[num]].x - local[overlap[0]].x);
		int sqY = (local[overlap[num]].y - local[overlap[0]].y)*(local[overlap[num]].y - local[overlap[0]].y);
		len += sqrt(sqX + sqY);
		if (min == -1) {
			min = len;
			for (int i = 0; i < n; i++)
				seq[i] = overlap[i];
		}
		else if (len < min) {
			min = len;
			for (int i = 0; i < n; i++)
				seq[i] = overlap[i];
		}
		return min;
	}
	double tmp;
	for (int i = 1; i < n; i++) {
		overlap[num + 1] = i;
		tmp = tour(num + 1, len, min);
		if (min == -1 && tmp > 0)
			min = tmp;
		else if (min != -1 && tmp > 0 && tmp < min)
			min = tmp;
	}
	return min;
}
