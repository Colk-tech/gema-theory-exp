#ifndef STRATEGY_C
#define STRATEGY_C

#include <stdlib.h>

#include "gtutil.c"

#define COOPERATE 0
#define DEFECT 1

// しっぺ返し戦略
int tit_for_tat(int ID, int n, int SC[2], int *H) {
    // 最初は協調を選択する
    if (n == 0) {
        return COOPERATE;
    }

    // else
    int oid = get_opponent_id(ID);
    int opponent_last_move = get_history_of(H, oid, n);
    return opponent_last_move;
}

// 逆しっぺ返し
int reverse_tit_for_tat(int ID, int n, int SC[2], int *H) {
    // 最初は裏切りを選択する
    if (n == 0) {
        return DEFECT;
    }

    // else
    int oid = get_opponent_id(ID);
    int opponent_last_move = get_history_of(H, oid, n);
    return opponent_last_move;
}

// 堪忍袋戦略
int tit_for_two_tats(int ID, int n, int SC[2], int *H) {
    // 最初は協調を選択する
    if (n == 0) {
        return COOPERATE;
    }

    // else
    int oid = get_opponent_id(ID);

    int opponent_last_move = get_history_of(H, oid, n);
    int opponent_move_before_last = get_history_of(H, oid, n - 1);

    // 前回の相手の手と前々回の相手の手が裏切りなら裏切る
    if (opponent_last_move == DEFECT && opponent_move_before_last == DEFECT) {
        return DEFECT;
    }

    // else
    return COOPERATE;
}

// フリードマン戦略
int friedman(int ID, int n, int SC[2], int *H) {
    // 最初は協調を選択する
    if (n == 0) {
        return COOPERATE;
    }

    int oid = get_opponent_id(ID);

    // 過去に 1 回でも裏切りがあるなら裏切る
    for (int i = 0; i < n; i++) {
        if (get_history_of(H, oid, i) == DEFECT) {
            return DEFECT;
        }
    }

    // else
    return COOPERATE;
}

// ヨッス戦略
int joss(int ID, int n, int SC[2], int *H) {
    if (n == 0) return COOPERATE;

    int oid = get_opponent_id(ID);
    int opponent_last_move = get_history_of(H, oid, n - 1);

    if (opponent_last_move == DEFECT) {
        return DEFECT;
    }

    // else
    // 90% の確率で協調、10% の確率で裏切り
    return (rand() % 10 < 9) ? COOPERATE : DEFECT;
}


// テュロック戦略
int tullock(int ID, int n, int SC[2], int *H) {
    // 最初の 10 回は協調を選択する
    if (n <= 10) {
        return COOPERATE;
    }

    int oid = get_opponent_id(ID);

    int cooperate_count = 0;
    for (int i = 0; i < 10; i++) {
        if (get_history_of(H, oid, i) == COOPERATE) {
            cooperate_count++;
        }
    }

    double cooperate_probability = ((double) cooperate_count / 10) - 0.1;

    // 最初の 10 回の間に相手が協調を選んだ頻度より 10 % 低い確率で協調を選ぶ
    return (rand() / (RAND_MAX + 1.0)) < cooperate_probability ? COOPERATE : DEFECT;
}

// デービス戦略
int davis(int ID, int n, int SC[2], int *H) {
    // 最初の 10 回は協調を選択する
    if (n <= 10) {
        return COOPERATE;
    }

    int oid = get_opponent_id(ID);

    // 1 ~ 10 回の中で 1 回でも裏切りがあるなら裏切る
    for (int i = 0; i < 10; i++) {
        if (get_history_of(H, oid, i) == DEFECT) {
            return DEFECT;
        }
    }

    return COOPERATE;
}

// でたらめ戦略
int random_strategy(int ID, int n, int SC[2], int *H) {
    return rand() % 2;
}

// 悪人戦略
int all_d(int ID, int n, int SC[2], int *H) {
    return DEFECT;
}

// 善人戦略
int all_c(int ID, int n, int SC[2], int *H) {
    return COOPERATE;
}

#endif //STRATEGY_C
