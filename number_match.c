#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <windows.h>

#define Y 6
#define X 5
#define MAX_U 20
#define RANKER 5

void print_howto(); // 게임방법 출력
void print_title(); // title 출력
void rank_record(name, final_score);

/*구조체 선언*/
typedef struct _POINT {
    int x;
    int y;
}_POINT;

typedef struct record {
    int score[MAX_U];
    char name[MAX_U][10];
}RECORD;



/*기타 함수*/
void textcolor(int color_number) {   //글씨 색 변경
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color_number);
}

void swap_int(int* x, int* y) { //int형 swap
    int tmp;
    tmp = *x;
    *x = *y;
    *y = tmp;
}

void swap_char(char* str1, char* str2) //char형 swap
{
    char* temp = (char*)malloc((strlen(str1) + 1) * sizeof(char));
    strcpy(temp, str1);
    strcpy(str1, str2);
    strcpy(str2, temp);
    free(temp);
}

int abs(int num) { //절댓값 계산
    return(num > 0 ? num : -num);
}



/*출력 함수*/
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

void print_heart(int heart, int score, int level) { //목숨 ♥로 표현
    system("cls || clear");
    printf("score:%d\n", (level - 1) * 5 + score);
    printf("남은 목숨: ");
    textcolor(4);
    for (int i = 0; i < heart; i++)
        printf("♥");
    printf("\n");
    textcolor(7);
}

void print_rank() { // rank 출력
    FILE* fp_rank;
    RECORD user;
    int count = 0;

    fp_rank = fopen("rank.txt", "r");
    if (fp_rank == NULL) {
        printf("파일 열 수 없음");
        exit(1);
    }

    while (feof(fp_rank) == 0) {
        fscanf(fp_rank, "%s %d", user.name[count], &user.score[count]);
        count++;
    }

    fclose(fp_rank);

    textcolor(3);
    printf("\n");
    printf("    순위   이름   점수");
    printf("\n   -------------------\n");
    textcolor(7);
    for (int i = 0; i < RANKER; i++){
        printf("%6d위 %6s %6d\n", i + 1, user.name[i], user.score[i]);
    }
    printf("\n\n");
}

void msg(int wrongput, int win) { // 다시 입력하세요 메세지 출력
    textcolor(3);
    if (wrongput) {
        printf("잘못된 입력! 다시 입력하세요\n\n");
    }
    if (win) {
        printf("승리하셨습니다! 다음 단계로 넘어갑니다.\n\n");
    }
    textcolor(7);
}

void lose(char name[], int final_score) { // 패배 시 화면 출력, 점수 기록 및 출력
    system("cls || clear");
    printf("\n   Game Over...\n");
    printf("   %s님의 점수 : %d\n\n", name, final_score);
    rank_record(name, final_score);
    print_rank();
}



/*로직 함수*/
int match(int ground[Y][X], _POINT d1, _POINT d2) {
    if (d1.x == d2.x && abs(d1.y - d2.y) == 1)        //상하 관계의 _POINT 값이 같은지 판별
        if (ground[d1.x][d1.y] == ground[d2.x][d2.y])
            return 1;
    if (d1.y == d2.y && abs(d1.x - d2.x) == 1)       //좌우 관계의 _POINT 값이 같은지 판별
        if (ground[d1.x][d1.y] == ground[d2.x][d2.y])
            return 1;
    if (abs(d1.x - d2.x) == 1 && abs(d1.y - d2.y) == 1) //대각선 관계의 _POINT 값이 같은지 판별
        if (ground[d1.x][d1.y] == ground[d2.x][d2.y])
            return 1;
    if (d1.y == 4 && d2.y == 0 && d2.x - d1.x == 1)   //n열의 마지막 행과 n+1열의 첫 번째 행의 _POINT 값이 같은지 판별
        if (ground[d1.x][d1.y] == ground[d2.x][d2.y])
            return 1;
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

int scan(int ground[Y][X], int* score, int addnum) {  //한 줄이 모두 0인지 판별
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



/*rank 기록 함수*/
void make_rankfile() { // rank 파일 생성
    FILE* fp_rank;
    fp_rank = fopen("rank.txt", "w");
    for (int i = 0; i < RANKER; i++){
        fprintf(fp_rank, "name 0\n");
    }
    fclose(fp_rank);
}

void rank_record(char name[], int score) { //점수를 rank 파일에 기록
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
        printf("파일 열 수 없음");
        exit(1);
    }

    for (int i = 0; i < RANKER; i++){
        fprintf(fp_rank, "%s %d\n", user.name[i], user.score[i]);
    }

    fclose(fp_rank);
}



int main() {
    int level, score = 0, heart = 0, addnum = 0, final_score = 0, wrongput = FALSE , win = FALSE;
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
    printf("이름을 입력하시오 >> ");
    scanf("%s", name);
    printf("난이도를 설정하세요(입력한 난이도의 숫자 갯수가 생성됩니다) >> ");
    scanf("%d", &level);

    while (1) {
        printf("게임 시작 : s / 게임 랭킹 r >> ");
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
        printf("첫 번째 좌표를 입력하시오:");
        scanf("%d %d", &d1.x, &d1.y);

        if (d1.x != 0 && d1.y != 0) {
            d1.x--; d1.y--;
            printf("두 번째 좌표를 입력하시오:");
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
        msg(wrongput,win);
        wrongput = FALSE;
        win = FALSE;
    }
}

void print_howto() {
    textcolor(6);
    printf("*게임 방법*\n1.가로, 세로, 대각선으로 닿아있는 같은 숫자의 좌표를 입력해 숫자를 0으로 만든다.\n  (n열의 마지막 행과 n+1열의 첫번째 행도 가로에 포함한다.)\n2.4줄을 0으로 만들면 승리한다.\n3.첫 번째 좌표 입력에서 0 0을 입력하는 경우 숫자가 추가된다.\n\n* 좌표 입력 예시: 1 3(첫 번째 줄 세번 째)\n\n");
    textcolor(7);
}

void print_title() {
    textcolor(3);
    printf("\n\n  @@  @@   @@  @@  @@   @@    @@@@@   @@@@@@    @@@@@  \n  @@ @@@   @@  @@  @@@ @@@   @@  @@       @@   @@  @@  \n  @@@@@@   @@  @@  @@@@@@@   @@  @@       @@   @@  @@  \n  @@@@@@   @@  @@  @@ @ @@    @@@@@     @@@@    @@@@@  \n  @@@ @@   @@  @@  @@   @@   @@  @@       @@     @@@@  \n  @@  @@   @@  @@  @@   @@   @@  @@       @@    @@ @@  \n  @@  @@    @@@@   @@   @@    @@@@@   @@@@@@   @@  @@  \n\n  @@   @@       @@       @@@@@@      @@@@      @@  @@  \n  @@@ @@@      @@@@        @@       @@  @@     @@  @@  \n  @@@@@@@     @@  @@       @@           @@     @@  @@  \n  @@ @ @@     @@@@@@       @@           @@     @@@@@@  \n  @@   @@     @@  @@       @@           @@     @@  @@  \n  @@   @@     @@  @@       @@       @@  @@     @@  @@  \n  @@   @@     @@  @@       @@        @@@@      @@  @@  \n");
    textcolor(7);
}
