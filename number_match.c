#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <windows.h>

#define Y 6
#define X 5
#define MAX_U 20

void print_howto();

void print_ground(int ground[Y][X]) { //ȭ�鿡 ground ���
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

void textcolor(int color_number) {   //�۾� �� ����
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color_number);
}

void print_heart(int heart, int score, int level) { //��� ���� ǥ��
    system("cls || clear");
    printf("score:%d\n", (level - 1) * 5 + score);
    printf("���� ���: ");
    textcolor(4);
    for (int i = 0; i < heart; i++)
        printf("��");
    printf("\n");
    textcolor(7);
}

typedef struct _POINT {
    int x;
    int y;
}_POINT;

int abs(int num) {
    return(num > 0 ? num : -num);
}

int match(int ground[Y][X], _POINT d1, _POINT d2) {
    if (d1.x == d2.x && abs(d1.y - d2.y) == 1)        //���� ������ _POINT ���� ������ �Ǻ�
        if (ground[d1.x][d1.y] == ground[d2.x][d2.y])
            return 1;
    if (d1.y == d2.y && abs(d1.x - d2.x) == 1)       //�¿� ������ _POINT ���� ������ �Ǻ�
        if (ground[d1.x][d1.y] == ground[d2.x][d2.y])
            return 1;
    if (abs(d1.x - d2.x) == 1 && abs(d1.y - d2.y) == 1) //�밢�� ������ _POINT ���� ������ �Ǻ�
        if (ground[d1.x][d1.y] == ground[d2.x][d2.y])
            return 1;
    if (d1.y == 4 && d2.y == 0 && d2.x - d1.x == 1)   //n���� ������ ��� n+1���� ù ��° ���� _POINT ���� ������ �Ǻ�
        if (ground[d1.x][d1.y] == ground[d2.x][d2.y])
            return 1;
        else if (d2.y == 4 && d1.y == 0 && d1.x - d2.x == 1)
            if (ground[d1.x][d1.y] == ground[d2.x][d2.y])
                return 1;
    return 0;
}

void zero(int ground[Y][X], _POINT d1, _POINT d2) { //_POINT���� 0���� �ʱ�ȭ
    ground[d1.x][d1.y] = 0;
    ground[d2.x][d2.y] = 0;
}

void del(int arr[Y][X], int num) { //�� ���� ���� ��� 0�� �� �� ���� �� ������ ���� 
    for (int i = num; i < Y; i++)
        for (int j = 0; j < X; j++)
            if (i + 1 < Y) {
                int temp = arr[i][j];
                arr[i][j] = arr[i + 1][j];
                arr[i + 1][j] = temp;
            }
    system("cls || clear");
    print_ground(arr);
}

int scan(int ground[Y][X], int* score, int addnum) {  //�� ���� ��� 0���� �Ǻ�
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

void ground_add(int ground[Y][X], int level) { //�� �߰� �Լ�
    int stopAdding = 0;
    for (int i = 0; i < Y; i++) {
        int sum = 0;
        for (int j = 0; j < X; j++) {
            if (ground[i][j] == 0)
                sum++;
            if (sum == 5) {
                for (int j = 0; j < X; j++)
                    ground[i][j] = rand() % level + 1;
                stopAdding = 1;
                break;
            }
        }
        if (stopAdding)
            break;
    }
    print_ground(ground);
}


int main() {
    int level, score = 0, heart = 0, addnum = 0, final_score = 0;
    char name[20];
    char button;
    printf("Number Match Game\n\n");
    print_howto();
    printf("�̸��� �Է��Ͻÿ� >> ");
    scanf("%s", name);
    printf("���̵��� �����ϼ���(�Է��� ���̵��� ���� ������ �����˴ϴ�) >> ");
    scanf("%d", &level);
    printf("���� ���� : s / ���� ��ŷ r >> ");

    while (1) {
        int a = 0;
        scanf("%c", &button);
        switch (button) {
        case 's':
            system("cls || clear");
            a++;
            break;
        case 'r':
            system("cls || clear");
            a++;
            break;
        }
        if (a)
            break;
    }

    srand((unsigned)time(NULL));
    int ground[Y][X];
    for (int i = 0; i < Y; i++)
        for (int j = 0; j < X; j++)
            ground[i][j] = rand() % level + 1;

    print_heart(5 - heart, score, level);
    print_ground(ground);

    while (1) {
        _POINT d1, d2;
        final_score = 5 * (level - 1) + score;
        printf("ù ��° ��ǥ�� �Է��Ͻÿ�:");
        scanf("%d %d", &d1.x, &d1.y);

        if (d1.x != 0 && d1.y != 0) {
            d1.x--; d1.y--;
            printf("�� ��° ��ǥ�� �Է��Ͻÿ�:");
            scanf("%d %d", &d2.x, &d2.y);
            printf("\n");
            d2.x--; d2.y--;
            if (match(ground, d1, d2))
                zero(ground, d1, d2);
            else {
                heart++;
                if (heart == 5) {
                    break;
                }
                printf("�ٽ� �Է��ϼ���.\n\n");
            }
            scan(ground, &score, addnum);
            print_heart(5 - heart, score, level);
            print_ground(ground);
        }
        else {
            if (score != 0) {
                ground_add(ground, level);
                addnum++;
            }
            else {
                heart++;
                if (heart == 5) {
                    break;
                }

                printf("�ٽ� �Է��ϼ���.\n\n");
            }

        }
        if (score == 5) {
            system("cls || clear");
            printf("�¸��ϼ̽��ϴ�! ���� �ܰ�� �Ѿ�ϴ�.\n");
            level++;
            score = 0;
            for (int i = 0; i < Y; i++)
                for (int j = 0; j < X; j++)
                    ground[i][j] = rand() % level + 1;

            print_ground(ground);
        }
    }
}

void print_howto() {
    printf("*���� ���*\n1.����, ����, �밢������ ����ִ� ���� ������ ��ǥ�� �Է��� ���ڸ� 0���� �����.\n  (n���� ������ ��� n+1���� ù��° �൵ ���ο� �����Ѵ�.)\n2.4���� 0���� ����� �¸��Ѵ�.\n3.ù ��° ��ǥ �Է¿��� 0 0�� �Է��ϴ� ��� ���ڰ� �߰��ȴ�.\n\n* ��ǥ �Է� ����: 1 3(ù ��° �� ���� °)\n\n");
}