#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <windows.h>

#define Y 6
#define X 5
#define MAX_U 20

void print_howto();

void print_ground(int ground[Y][X]) { //화면에 ground 출력
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

void textcolor(int color_number) {   //글씨 색 변경
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color_number);
}

void print_heart(int heart) { //목숨 ♥로 표현
    printf("남은 목숨: ");
    textcolor(4);
    for (int i = 0; i < heart; i++)
        printf("♥");
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

void zero(int ground[Y][X], _POINT d1, _POINT d2) { //_POINT값을 0으로 초기화
    ground[d1.x][d1.y] = 0;
    ground[d2.x][d2.y] = 0;
}

void del(int arr[Y][X], int num) { //한 줄의 값이 모두 0일 때 그 줄을 맨 밑으로 내림 
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

void ground_add(int ground[Y][X], int level) { //줄 추가 함수
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


void rank_record(char name[], int score) {
    /*여기부터*/
    FILE* fp_rank;
    int numUsers = 0;
    int r_score[MAX_U];
    char r_name[MAX_U][10]; //글자수 최대 10 

    fp_rank = fopen("rank.txt", "r");
    if (fp_rank == NULL) {
        printf("파일 열 수 없음");
        exit(1);
    }

    while (feof(fp_rank) == 0) {
        fscanf(fp_rank, "%s %d", r_name[numUsers], &r_score[numUsers]);
        numUsers++;
    }

    fclose(fp_rank);
    /*여기 줄일 수 있을 거 같은데 그럴러면 구조체 써야 될듯*/

    for (int i = numUsers; i > 1; i--)
    {
        if (r_score[i] > score) {
            break;
        }
        else {
            //rank 의 i 위치에 name과 score 넣어줌
        }
    }

}

void record(char name[], int score) {
    FILE* fp_record = NULL;
    fp_record = fopen("record.txt", "a");

    if (fp_record == NULL) { printf("파일 열기에 실패했습니다.\n"); }

    fprintf(fp_record, "%s %d\n", name, score);

    fclose(fp_record);

    rank_record(name, score);
}

void print_rank() {
    FILE* fp_rank;
    int numUsers = 0;
    int r_score[MAX_U];
    char r_name[MAX_U][10]; //글자수 최대 10 

    fp_rank = fopen("rank.txt", "r");
    if (fp_rank == NULL) {
        printf("파일 열 수 없음");
        exit(1);
    }

    while (feof(fp_rank) == 0) {
        fscanf(fp_rank, "%s %d", r_name[numUsers], &r_score[numUsers]);
        numUsers++;
    }

    fclose(fp_rank);

    textcolor(3);
    printf("  순위  이름  점수");
    printf("\n------------------\n");
    textcolor(1);
    for (int i = 0; i < numUsers; i++)
    {
        printf("%4d위 %4s %4d\n", i, r_name[i], r_score[i]);
    }
    textcolor(7);
   
}

void lose(char name[], int final_score) {
    record(name, final_score);
    printf("\nGame Over\n");
    printf("\nfinal score : %d\n", final_score);
}
  

int main() {
    int level=0, score = 0, heart = 0, addnum = 0, final_score = 0;
    char name[20];
    char button = NULL;
    printf("Number Match Game\n\n");
    print_howto();
    printf("난이도를 설정하세요(입력한 난이도의 숫자 갯수가 생성됩니다) >> ");
    scanf("%d", &level);
    printf("이름을 입력하시요 >> ");
    scanf("%s", name);
    printf("게임 시작 : s / 게임 랭킹 r >> ");

    while (1) {
        scanf("%c", &button);
        if (button == 's') {
            system("cls || clear");
            break;
        }
        else if (button == 'r') {
            system("cls || clear");
            print_rank();
            return 0;
        }
    }

    srand((unsigned)time(NULL));
    int ground[Y][X];
    for (int i = 0; i < Y; i++)
        for (int j = 0; j < X; j++)
            ground[i][j] = rand() % level + 1;

    printf("score:%d\n", score);
    print_heart(5 - heart);
    print_ground(ground);

    while (1) {
        _POINT d1, d2;
        final_score = 5 * (level - 1) + score;
        printf("첫 번째 좌표를 입력하시오:");
        scanf("%d %d", &d1.x, &d1.y);

        if (d1.x != 0 && d1.y != 0) {
            d1.x--; d1.y--;
            printf("두 번째 좌표를 입력하시오:");
            scanf("%d %d", &d2.x, &d2.y);
            printf("\n");
            d2.x--; d2.y--;
            if (match1(ground, d1, d2) || match2(ground, d1, d2) || match3(ground, d1, d2) || match4(ground, d1, d2))
                zero(ground, d1, d2);
            else {
                printf("다시 입력하세요.\n\n");
                heart++;
                if (heart == 5) {
                    lose(name,final_score);
                    break;
                }
                
            }
            system("cls || clear");
            printf("score:%d\n",score);
            print_heart(5 - heart);
            print_ground(ground);
            scan(ground, &score, addnum);
        }
        else {
            if (score != 0) {
                ground_add(ground, level);
                addnum++;
            }
            else {
                printf("다시 입력하세요.\n\n");
                heart++;
                if (heart == 5) {
                    lose(name, final_score);
                    break;
                }
            }

        }
        if (score == 5) {
            printf("승리하셨습니다! 다음 단계로 넘어갑니다.\n");
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
    printf("*게임 방법*\n1.가로, 세로, 대각선으로 닿아있는 같은 숫자의 좌표를 입력해 숫자를 0으로 만든다.\n  (n열의 마지막 행과 n+1열의 첫번째 행도 가로에 포함한다.)\n2.4줄을 0으로 만들면 승리한다.\n3.첫 번째 좌표 입력에서 0 0을 입력하는 경우 숫자가 추가된다.\n\n* 좌표 입력 예시: 1 3(첫 번째 줄 세번 째)\n\n");
}
