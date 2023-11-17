#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <windows.h>
#define Y 6
#define X 5

void print_ground(int ground[Y][X]) { //화면에 ground 출력
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

int match1(int ground[Y][X], _POINT d1, _POINT d2) { //상하 관계의 _POINT 값이 같은지 판별
	if (d1.x == d2.x && abs(d1.y - d2.y) == 1)
		if (ground[d1.x][d1.y] == ground[d2.x][d2.y])
			return 1;
	return 0;
}

int match2(int ground[Y][X], _POINT d1, _POINT d2) { //좌우 관계의 _POINT 값이 같은지 판별
	if (d1.y == d2.y && abs(d1.x - d2.x) == 1)
		if (ground[d1.x][d1.y] == ground[d2.x][d2.y])
			return 1;
	return 0;
}

int match3(int ground[Y][X], _POINT d1, _POINT d2) { //대각선 관계의 _POINT 값이 같은지 판별
	if (abs(d1.x - d2.x) == 1 && abs(d1.y - d2.y) == 1)
		if (ground[d1.x][d1.y] == ground[d2.x][d2.y])
			return 1;
	return 0;
}

int match4(int ground[Y][X], _POINT d1, _POINT d2) { //n열의 마지막 행과 n+1열의 첫 번째 행의 _POINT 값이 같은지 판별
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
	printf("*게임 방법*\n1.가로, 세로, 대각선으로 닿아있는 같은 숫자의 좌표를 입력해 숫자를 0으로 만든다.\n  (n열의 마지막 행과 n+1열의 첫번째 행도 가로에 포함한다.)\n2.4줄을 0으로 만들면 승리한다.\n3.첫 번째 좌표 입력에서 0 0을 입력하는 경우 숫자가 추가된다.\n\n난이도를 설정하세요(입력한 난이도의 숫자 갯수가 생성됩니다):");
	scanf("%d", &level);
	printf("이름을 입력하시요:");
	scanf("%s", name);
	printf("좌표 입력 예시: 1 3(첫 번째 줄 세번 째)\n\n");

	srand((unsigned)time(NULL));
	int ground[Y][X];
	for (int i = 0; i < Y; i++)
		for (int j = 0; j < X; j++)
			ground[i][j] = rand() % level + 1;

	print_ground(ground);

	while (score < 4) {
		_POINT d1, d2;
		printf("첫 번째 좌표를 입력하시오:");
		scanf_s("%d %d", &d1.x, &d1.y);

		if (d1.x != 0 && d1.y != 0) {
			d1.x--; d1.y--;
			printf("두 번째 좌표를 입력하시오:");
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
				printf("남은 목숨: %d\n",5-heart);
				printf("다시 입력하세요.\n\n");
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
			printf("\n%s님이 승리하였습니다!\n\n", name);
		}
	}
}

