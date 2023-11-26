#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <windows.h>

#define Y 6
#define X 5
#define MAX_U 20
#define RANKER 5

void print_howto(); // ���ӹ�� ���
void print_title(); // title ���
void rank_record(name, final_score);

/*����ü ����*/
typedef struct _POINT {
    int x;
    int y;
}_POINT;

typedef struct record {
    int score[MAX_U];
    char name[MAX_U][10];
}RECORD;



/*��Ÿ �Լ�*/
void textcolor(int color_number) {   //�۾� �� ����
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color_number);
}

void swap_int(int* x, int* y) { //int�� swap
    int tmp;
    tmp = *x;
    *x = *y;
    *y = tmp;
}

void swap_char(char* str1, char* str2) //char�� swap
{
    char* temp = (char*)malloc((strlen(str1) + 1) * sizeof(char));
    strcpy(temp, str1);
    strcpy(str1, str2);
    strcpy(str2, temp);
    free(temp);
}

int abs(int num) { //���� ���
    return(num > 0 ? num : -num);
}



/*��� �Լ�*/
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

void print_rank() { // rank ���
    FILE* fp_rank;
    RECORD user;
    int count = 0;

    fp_rank = fopen("rank.txt", "r");
    if (fp_rank == NULL) {
        printf("���� �� �� ����");
        exit(1);
    }

    while (feof(fp_rank) == 0) {
        fscanf(fp_rank, "%s %d", user.name[count], &user.score[count]);
        count++;
    }

    fclose(fp_rank);

    textcolor(3);
    printf("\n");
    printf("    ����   �̸�   ����");
    printf("\n   -------------------\n");
    textcolor(7);
    for (int i = 0; i < RANKER; i++) {
        printf("%6d�� %6s %6d\n", i + 1, user.name[i], user.score[i]);
    }
    printf("\n\n");
}

void msg(int wrongput, int win) { // �ٽ� �Է��ϼ��� �޼��� ���
    textcolor(3);
    if (wrongput) {
        printf("�߸��� �Է�! �ٽ� �Է��ϼ���\n\n");
    }
    if (win) {
        printf("�¸��ϼ̽��ϴ�! ���� �ܰ�� �Ѿ�ϴ�.\n\n");
    }
    textcolor(7);
}

void lose(char name[], int final_score) { // �й� �� ȭ�� ���, ���� ��� �� ���
    system("cls || clear");
    printf("\n   Game Over...\n");
    printf("   %s���� ���� : %d\n\n", name, final_score);
    rank_record(name, final_score);
    print_rank();
}



/*���� �Լ�*/
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



/*rank ��� �Լ�*/
void make_rankfile() { // rank ���� ����
    FILE* fp_rank;
    fp_rank = fopen("rank.txt", "w");
    for (int i = 0; i < RANKER; i++) {
        fprintf(fp_rank, "name 0\n");
    }
    fclose(fp_rank);
}

void rank_record(char name[], int score) { //������ rank ���Ͽ� ���
    FILE* fp_rank;
    RECORD user;
    int count = 0;

    fp_rank = fopen("rank.txt", "r+");
    if (fp_rank == NULL) {
        make_rankfile();
        fp_rank = fopen("rank.txt", "r+");
    }

    while (feof(fp_rank) == 0) {
        fscanf(fp_rank, "%s %d", user.name[count], &user.score[count]);
        count++;
    }

    if (user.score[RANKER - 1] < score) {
        strcpy(user.name[RANKER - 1], name);
        user.score[RANKER - 1] = score;
    }

    for (int i = RANKER - 1; i > 0; i--) {
        if (user.score[i] > user.score[i - 1]) {
            swap_int(&user.score[i], &user.score[i - 1]);
            swap_char(&user.name[i], &user.name[i - 1]);
        }
        else {
            break;
        }
    }

    fp_rank = fopen("rank.txt", "w");
    if (fp_rank == NULL) {
        printf("���� �� �� ����");
        exit(1);
    }

    for (int i = 0; i < RANKER; i++) {
        fprintf(fp_rank, "%s %d\n", user.name[i], user.score[i]);
    }

    fclose(fp_rank);
}



int main() {
    int level, score = 0, heart = 0, addnum = 0, final_score = 0, wrongput = FALSE, win = FALSE;
    char name[20];
    char button = ' ';

    print_title();
    while (1) {
        printf("\n\n\t\t  press any button!");
        getch(button);
        if (button != NULL) {
            system("cls || clear");
            break;
        }
    }

    print_howto();
    printf("�̸��� �Է��Ͻÿ� >> ");
    scanf("%s", name);
    printf("���̵��� �����ϼ���(�Է��� ���̵��� ���� ������ �����˴ϴ�) >> ");
    scanf("%d", &level);

    while (1) {
        printf("���� ���� : s / ���� ��ŷ r >> ");
        scanf(" %c", &button);
        if (button == 's') {
            system("cls || clear");
            break;
        }
        else if (button == 'r') {
            system("cls || clear");
            print_rank();
            continue;
        }
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
                    lose(name, final_score);
                    break;
                }
                else {
                    wrongput = TRUE;
                }
            }
        }
        else {
            if (score != 0) {
                ground_add(ground, level);
                addnum++;
            }
            else {
                heart++;
                if (heart == 5) {
                    lose(name, final_score);
                    break;
                }
                else {
                    wrongput = TRUE;
                }
            }
        }

        if (score == 5) {
            win = TRUE;
            level++;
            score = 0;
            for (int i = 0; i < Y; i++)
                for (int j = 0; j < X; j++)
                    ground[i][j] = rand() % level + 1;
        }

        scan(ground, &score, addnum);
        print_heart(5 - heart, score, level);
        print_ground(ground);
        msg(wrongput, win);
        wrongput = FALSE;
        win = FALSE;
    }
}

void print_howto() {
    textcolor(6);
    printf("*���� ���*\n1.����, ����, �밢������ ����ִ� ���� ������ ��ǥ�� �Է��� ���ڸ� 0���� �����.\n  (n���� ������ ��� n+1���� ù��° �൵ ���ο� �����Ѵ�.)\n2.4���� 0���� ����� �¸��Ѵ�.\n3.ù ��° ��ǥ �Է¿��� 0 0�� �Է��ϴ� ��� ���ڰ� �߰��ȴ�.\n\n* ��ǥ �Է� ����: 1 3(ù ��° �� ���� °)\n\n");
    textcolor(7);
}

void print_title() {
    textcolor(3);
    printf("\n\n  @@  @@   @@  @@  @@   @@    @@@@@   @@@@@@    @@@@@  \n  @@ @@@   @@  @@  @@@ @@@   @@  @@       @@   @@  @@  \n  @@@@@@   @@  @@  @@@@@@@   @@  @@       @@   @@  @@  \n  @@@@@@   @@  @@  @@ @ @@    @@@@@     @@@@    @@@@@  \n  @@@ @@   @@  @@  @@   @@   @@  @@       @@     @@@@  \n  @@  @@   @@  @@  @@   @@   @@  @@       @@    @@ @@  \n  @@  @@    @@@@   @@   @@    @@@@@   @@@@@@   @@  @@  \n\n  @@   @@       @@       @@@@@@      @@@@      @@  @@  \n  @@@ @@@      @@@@        @@       @@  @@     @@  @@  \n  @@@@@@@     @@  @@       @@           @@     @@  @@  \n  @@ @ @@     @@@@@@       @@           @@     @@@@@@  \n  @@   @@     @@  @@       @@           @@     @@  @@  \n  @@   @@     @@  @@       @@       @@  @@     @@  @@  \n  @@   @@     @@  @@       @@        @@@@      @@  @@  \n");
    textcolor(7);
}