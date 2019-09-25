/*输入文件名以命令行参数传入。*/
/*Sudoku.exe -m 9 -n 2 -i input.txt -o output.txt*/
/*m宫格阶数，n待解答盘面数，i输入文件，o输出文件*/

#include <iostream>
#include <cstdlib>
using namespace std;

/*全局变量*/
int m; /*宫格阶数*/
int disksurface[10][10];/*宫格盘面，题设最大为九宫格*/

/*若待解盘面不唯一时，需要多次使用disksurface，进行重置操作*/
void reset() {
	for (int i = 1; i <= m; i++) {
		for (int j = 1; j <= m; j++) {
			disksurface[i][j] = 0; /*盘面上所有数重置为0，即未输入状态*/
		}
	}
}

/*legal合法性函数检测输入数字是否符合数独的要求*/
/*满足输入的数字在所在行以及所在列中仅出现一次*/
/*若宫格阶数为4689，则还需判断输入数字在所在宫中仅出现一次*/
/*输入参数分别为行、列、需判断的输入数字*/
bool legal(int i, int j, int x) {
	/*行合法性检测*/
	for (int b = 1; b <= m; b++) {
		if (x == disksurface[i][b])
			return false;
	}
	/*列合法性检测*/
	for (int a = 1; a <= m; a++) {
		if (x == disksurface[a][j])
			return false;
	}
	/*若该阶数存在宫，宫合法性检测*/
	if (m == 4 || m == 6 || m == 8 || m == 9) {
		int interval_i, interval_j;
		int begin_i, begin_j;
		switch (m)
		{
		case 4:
			interval_i = 2;
			interval_j = 2;
			break;
		case 6:
			interval_i = 2;
			interval_j = 3;
			break;
		case 8:
			interval_i = 4;
			interval_j = 2;
			break;
		case 9:
			interval_i = 3;
			interval_j = 3;
			break;
		}
		begin_i = ((i - 1) / interval_i)*interval_i + 1;
		begin_j = ((j - 1) / interval_j)*interval_j + 1;
		for (int a = begin_i; a < begin_i + interval_i; a++) {
			for (int b = begin_j; b < begin_j + interval_j; b++) {
				if (x == disksurface[a][b])
					return false;
			}
		}
	}
	return true;
}

/*以深度优先算法计算数独*/
bool DFS(int a, int b) {
	while (disksurface[a][b] != 0) {
		if (a == m && b == m) {
			return true;
		}
		else if (b == m) {
			a++;
			b = 1;
		}
		else {
			b++;
		}
	}
	for (int x = 1; x <= m; x++) {
		if (legal(a, b, x)) {
			disksurface[a][b] = x;
			if (DFS(a, b)) {
				return true;
			}
			disksurface[a][b] = 0;
		}
	}
	return false;
}

int main(int argc, char * argv[]) {
	int n; /*待解答盘面数*/
	FILE *input;
	FILE *output;
	/*由于argv[0]固定为程序名，输入第一个参数为argv[1]，以此类推*/
	m = atoi(argv[2]);
	n = atoi(argv[4]);
	/*以只读方式打开input文档*/
	input = fopen("input.txt", "r");
	if (input == NULL) {
		return -1;
	}
	output = fopen("output.txt", "w");
	if (output == NULL) {
		return -1;
	}
	fclose(output);
	while (n > 0) {
		reset(); /*执行写入操作前重置盘面*/
		/*输入盘面*/
		for (int i = 1; i <= m; i++) {
			for (int j = 1; j <= m; j++) {
				/*fscanf()函数，从一个流中输入，遇到空格或者换行时结束*/
				fscanf_s(input, "%d", &disksurface[i][j]);
			}
		}
		DFS(1, 1);
		/*以追写方式打开output文档*/
		output = fopen("output.txt", "a");
		if (output == NULL) {
			return -1;
		}
		/*将按输入文档格式将盘面数据写入*/
		for (int i = 1; i <= m; i++) {
			fprintf(output, "%d", disksurface[i][1]);
			for (int j = 2; j <= m; j++) {
				fprintf(output, " ");
				fprintf(output, "%d", disksurface[i][j]);
			}
			fprintf(output, "\n");
		}
		fprintf(output, "\n");
		n--;
		fclose(output);
	}
	fclose(input);
	return 0;
}
