#ifndef GTUTIL_C
#define GTUTIL_C

int get_history_of(const int *H, int ID, int round) {
    return *(H + 2 * (round - 1) + ID);
}

int get_opponent_id(int my_id) {
    return my_id ^ 1;
}

int get_score_of(const int score_table[2][2], const char alphabet) {
    switch (alphabet) {
        case 'q':
            // 協力協力
            return score_table[0][0];
        case 's':
            // 協力裏切り
            return score_table[0][1];
        case 'p':
            // 裏切り協力
            return score_table[1][0];
        case 'r':
            // 裏切り裏切り
            return score_table[1][1];
        default:
            return -1; // 不明なアルファベット
    }
}

#endif //GTUTIL_C
