#ifndef ANALYZE_C
#define ANALYZE_C

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "gtutil.c"

// 比較関数
int compare(const void *a, const void *b) {
    int l = *((const int *) a);
    int r = *((const int *) b);

    return (r - l);
}

// 得点表から p、q、r、s の大小関係を解析し、大きい順に並び替える関数
void analyze_and_sort_scores(const int score_table[2][2], char *result) {
    int p = get_score_of(score_table, 'p');
    int q = get_score_of(score_table, 'q');
    int r = get_score_of(score_table, 'r');
    int s = get_score_of(score_table, 's');

    int scores[4][2] = {
            {p, 'p'},
            {q, 'q'},
            {r, 'r'},
            {s, 's'}
    };

    qsort(scores, 4, sizeof(scores[0]), compare);

    // 結果を出力
    for (int i = 0; i < 4; i++) {
        if (i > 0 && scores[i][0] == scores[i - 1][0]) {
            strcat(result, "=");
            strcat(result, (char *) &scores[i][1]);
        } else {
            if (i != 0) {
                strcat(result, ">");
            }
            strcat(result, (char *) &scores[i][1]);
        }
    }
}

// テスト
int main() {
    int score_table[2][2] = {
            {1, 1},
            {1, 1}
    }; // 例: q=3, s=0, p=5, r=1

    char result[8] = "";
    analyze_and_sort_scores(score_table, result);

    printf("%s\n", result); // p>q=r>s
}


#endif //ANALYZE_C
