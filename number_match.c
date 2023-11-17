#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <windows.h>
#define Y 6
#define X 5

void print_ground(int ground[Y][X]) { //ȭ�鿡 ground ���
	system("cls || clear");
	printf("    | 1 2 3 4 5\n");
	printf("  --|-----------\n");
	for (int i = 0; i < Y; i++) {
		printf("  %d | ", i + 1);
		for (int j = 0; j < X; j++)
			printf("%d ", ground[i][j]);
		printf("\n");
	}
	printf("\n");
}

typedef struct _POINT {
	int x;
	int y;
}_POINT;

int abs(int num) {
	return(num > 0 ? num : -num);
}

int match1(int ground[Y][X], _POINT d1, _POINT d2) { //���� ������ _POINT ���� ������ �Ǻ�
	if (d1.x == d2.x && abs(d1.y - d2.y) == 1)
		if (ground[d1.x][d1.y] == ground[d2.x][d2.y])
			return 1;
	return 0;
}

int match2(int ground[Y][X], _POINT d1, _POINT d2) { //�¿� ������ _POINT ���� ������ �Ǻ�
	if (d1.y == d2.y && abs(d1.x - d2.x) == 1)
		if (ground[d1.x][d1.y] == ground[d2.x][d2.y])
			return 1;
	return 0;
}

int match3(int ground[Y][X], _POINT d1, _POINT d2) { //�밢�� ������ _POINT ���� ������ �Ǻ�
	if (abs(d1.x - d2.x) == 1 && abs(d1.y - d2.y) == 1)
		if (ground[d1.x][d1.y] == ground[d2.x][d2.y])
			return 1;
	return 0;
}

int match4(int ground[Y][X], _POINT d1, _POINT d2) { //n���� ������ ��� n+1���� ù ��° ���� _POINT ���� ������ �Ǻ�
	if (d1.y == 4 && d2.y == 0 && d2.x - d1.x == 1) {
		if (ground[d1.x][d1.y] == ground[d2.x][d2.y])
			return 1;
	}
	else if (d2.y == 4 && d1.y == 0 && d1.x - d2.x == 1)
		if (ground[d1.x][d1.y] == ground[d2.x][d2.y])
			return 1;
	return 0;
}

void zero(int ground[Y][X], _POINT d1, _POINT d2) {
	ground[d1.x][d1.y] = 0;
	ground[d2.x][d2.y] = 0;
}

void del(int arr[Y][X], int num) {
	for (int i = num; i < Y; i++)
		for (int j = 0; j < X; j++)
			if (i + 1 < Y) {
				int temp = arr[i][j];
				arr[i][j] = arr[i + 1][j];
				arr[i + 1][j] = temp;
			}
	print_ground(arr);
}

int scan(int ground[Y][X], int* score, int addnum) {
	int a = 0;
	while (a < 2) {
		for (int i = 0; i < Y - *score + addnum; i++) {
			int sum = 0;
			for (int j = 0; j < X; j++)
				if (ground[i][j] == 0)
					sum++;
			if (sum == 5) {
				del(ground, i);
				*score += 1;
			}
		}
		a++;
	}
	return 0;
}

void ground_add(int ground[Y][X], int level) {
	for (int i = 0; i < Y; i++) {
		int sum = 0;
		for (int j = 0; j < X; j++) {
			if (ground[i][j] == 0)
				sum++;
			if (sum == 5) {
				for (int j = 0; j < Y; j++)
					ground[i][j] = rand() % level + 1;
				break;
			}
		}
	}
	print_ground(ground);
}

int main() {
	int level, score = 0, heart = 0, addnum = 0;
	char name[20];
	printf("Number Match Game\n");
	printf("*���� ���*\n1.����, ����, �밢������ ����ִ� ���� ������ ��ǥ�� �Է��� ���ڸ� 0���� �����.\n  (n���� ������ ��� n+1���� ù��° �൵ ���ο� �����Ѵ�.)\n2.4���� 0���� ����� �¸��Ѵ�.\n3.ù ��° ��ǥ �Է¿��� 0 0�� �Է��ϴ� ��� ���ڰ� �߰��ȴ�.\n\n���̵��� �����ϼ���(�Է��� ���̵��� ���� ������ �����˴ϴ�):");
	scanf("%d", &level);
	printf("�̸��� �Է��Ͻÿ�:");
	scanf("%s", name);
	printf("��ǥ �Է� ����: 1 3(ù ��° �� ���� °)\n\n");

	srand((unsigned)time(NULL));
	int ground[Y][X];
	for (int i = 0; i < Y; i++)
		for (int j = 0; j < X; j++)
			ground[i][j] = rand() % level + 1;

	print_ground(ground);

	while (score < 4) {
		_POINT d1, d2;
		printf("ù ��° ��ǥ�� �Է��Ͻÿ�:");
		scanf_s("%d %d", &d1.x, &d1.y);

		if (d1.x != 0 && d1.y != 0) {
			d1.x--; d1.y--;
			printf("�� ��° ��ǥ�� �Է��Ͻÿ�:");
			scanf_s("%d %d", &d2.x, &d2.y);
			printf("\n");
			d2.x--; d2.y--;
			if (match1(ground, d1, d2) || match2(ground, d1, d2) || match3(ground, d1, d2) || match4(ground, d1, d2))
				zero(ground, d1, d2);
			else {
				heart++;
				if (heart == 5) {
					printf("\nGame Over\n\n", name);
					break;
				}
				printf("���� ���: %d\n",5-heart);
				printf("�ٽ� �Է��ϼ���.\n\n");
			}
			print_ground(ground);
			scan(ground, &score, addnum);
			printf("score:%d\n", score);
		}
		else {
			ground_add(ground, level);
			addnum++;
		}
		if (score == 5) {
			printf("\n%s���� �¸��Ͽ����ϴ�!\n\n", name);
		}
	}
}

