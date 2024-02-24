/* sample */

#include <time.h>
#include <stdlib.h>
#include <sys/types.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>

/* マクロで文字列化する */
#define FNAME(str) F_NAME(str)
#define F_NAME(str) #str
#define N 50 /* 試行回数 */
#define OID (id^1) /* 相手の id */

/* ここを関数名に書き換える */
#define ID_00 p_0
#define ID_01 p_1

/*
int sct[2][2]:点数表

自分 相手
[0][0]: 協調 協調
[0][1]: 協調 裏切り
[1][0]: 裏切り 協調
[1][1]: 裏切り 裏切り
int *h:過去の手
*(h+2*i+ID):i 回目の ID の手
int sc[2]:点数
sc[ID]:ID の点
*/

/*
次の手を計算する関数のプロトタイプ宣言
名前は何でもよい。引数も必要に応じて変えること
この例では
自分の ID、今何回目か、現在までの点数、過去の手の配列
を渡している。
*/

int ID_00(int ID, int n, int SC[2], int *H);/*関数 0*/
int ID_01(int ID, int n, int SC[2], int *H);/*関数 1*/

const char *name[] = {FNAME(ID_00), FNAME(ID_01)};
const int SCT[2][2] = {{5,  0},
                       {10, 2}}; /*点数表*/

int main(void) {
    int i, ii, j, k, rh[2];
    int *h; //int h[2][N];
    int sc[2] = {0, 0};
    FILE *LOG;
    char LOG_File[100];
    int (*player[])(int, int, int [2], int *) = {ID_00, ID_01};
    int (*play[2])(int, int, int [2], int *);
    setbuf(stderr, NULL);

    // 乱数を使いたい時に備えて初期化
    // srand((unsigned int)time(NULL)); 毎回変わる乱数
    srand((unsigned int) 19720117L); // 決まった乱数

    //calloc
    h = (int *) calloc(2 * N, sizeof(int));

    /////////////////////////////////////////
    sprintf(LOG_File, "LOG_%s_%s", name[0], name[1]);

    LOG = fopen(LOG_File, "w");

    play[0] = player[0];
    play[1] = player[1];

    for (k = 0; k < 2; k++) {
        sc[k] = 0;
    }

    for (j = 0; j < N; j++) {
        for (k = 0; k < 2; k++) {
            rh[k] = (*play[k])(k, j, sc, h);
        }

        for (k = 0; k < 2; k++) {
            *(h + (2 * j) + k) = rh[k];
            sc[k] += SCT[rh[k]][rh[k ^ 1]];
        }

        fprintf(
                LOG,
                "Turn %3d,h: %d %d, sc:%3d %3d,total: %3d %3d\n",
                j + 1, *(h + (2 * j)), *(h + (2 * j) + 1),
                SCT[*(h + (2 * j))][*(h + (2 * j) + 1)],
                SCT[*(h + (2 * j) + 1)][*(h + (2 * j))], sc[0], sc[1]
        );
    }

    fprintf(LOG, " %s : %s .\n", name[i], name[ii]);
    fprintf(LOG, "score %d : %d . %d\n", sc[0], sc[1], sc[0] + sc[1]);
    printf(" %s : %s .\n", name[i], name[ii]);
    printf("score %d : %d . %d\n", sc[0], sc[1], sc[0] + sc[1]);
    fclose(LOG);
    fprintf(stderr, "\n THE END\n");

    /////////////////////////////////////////

    free(h);
    return 0;
}

///////////////////////////////////////////////
///////////////////////////////////////////////
/* 提出するのは以下の部分にある関数部分(どちらか1つ) */
///////////////////////////////////////////////
///////////////////////////////////////////////

int p_0(int ID, int n, int SC[2], int *H) /*関数 0*/ {
    int t;
    if (ID == 0) {
        t = rand() & 1;
    }

    if (ID == 1) {
        t = (rand() >> 1) & 1;
    }
    return t;
}

int p_1(int ID, int n, int SC[2], int *H) /*関数 1*/ {
    int t;
    if (ID == 0) {
        t = rand() & 1;
    }
    if (ID == 1) {
        t = (rand() >> 1) & 1;
    }
    return t;
}