/*�����ļ����������в������롣*/
/*Sudoku.exe -m 9 -n 2 -i input.txt -o output.txt*/
/*m���������n�������������i�����ļ���o����ļ�*/

#include <iostream>
#include <cstdlib>
using namespace std;

/*ȫ�ֱ���*/
int m; /*�������*/
int disksurface[10][10];/*�������棬�������Ϊ�Ź���*/

/*���������治Ψһʱ����Ҫ���ʹ��disksurface���������ò���*/
void reset() {
	for (int i = 1; i <= m; i++) {
		for (int j = 1; j <= m; j++) {
			disksurface[i][j] = 0; /*����������������Ϊ0����δ����״̬*/
		}
	}
}

/*legal�Ϸ��Ժ���������������Ƿ����������Ҫ��*/
/*����������������������Լ��������н�����һ��*/
/*���������Ϊ4689�������ж��������������ڹ��н�����һ��*/
/*��������ֱ�Ϊ�С��С����жϵ���������*/
bool legal(int i, int j, int x) {
	/*�кϷ��Լ��*/
	for (int b = 1; b <= m; b++) {
		if (x == disksurface[i][b])
			return false;
	}
	/*�кϷ��Լ��*/
	for (int a = 1; a <= m; a++) {
		if (x == disksurface[a][j])
			return false;
	}
	/*���ý������ڹ������Ϸ��Լ��*/
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

/*����������㷨��������*/
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
	int n; /*�����������*/
	FILE *input;
	FILE *output;
	/*����argv[0]�̶�Ϊ�������������һ������Ϊargv[1]���Դ�����*/
	m = atoi(argv[2]);
	n = atoi(argv[4]);
	/*��ֻ����ʽ��input�ĵ�*/
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
		reset(); /*ִ��д�����ǰ��������*/
		/*��������*/
		for (int i = 1; i <= m; i++) {
			for (int j = 1; j <= m; j++) {
				/*fscanf()��������һ���������룬�����ո���߻���ʱ����*/
				fscanf_s(input, "%d", &disksurface[i][j]);
			}
		}
		DFS(1, 1);
		/*��׷д��ʽ��output�ĵ�*/
		output = fopen("output.txt", "a");
		if (output == NULL) {
			return -1;
		}
		/*���������ĵ���ʽ����������д��*/
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
