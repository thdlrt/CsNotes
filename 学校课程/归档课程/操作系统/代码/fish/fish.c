#include "thread.h"
#include "thread-sync.h"

#define LENGTH(arr) (sizeof(arr) / sizeof(arr[0]))

enum { A = 1, B, C, D, E, F, };

struct rule {
  int from, ch, to;
} rules[] = {
    {A, '<', B},
    {B, '>', C},
    {C, '<', D},
    {A, '>', E},
    {E, '<', F},
    {F, '>', D},
    {D, '_', A},
};

int current = A;

mutex_t lk = MUTEX_INIT();
cond_t cv = COND_INIT();

int next(char ch) {
    for (int i = 0; i < LENGTH(rules); i++) {
        struct rule *rule = &rules[i];
        if (rule->from == current && rule->ch == ch) {
          return rule->to;
        }
    }
    return 0;
}

static int can_print(char ch) {
    return next(ch) != 0;
}

const char roles[] = ".<<<<<>>>>___";

void fish_thread(int id) {
    char role = roles[id];
    while (1) {
        mutex_lock(&lk);
        while (!can_print(ch)) {
            cond_wait(&cv, &lk);
        }
        putchar(role); 
        current = next(ch);
        cond_broadcast(&cv);
        mutex_unlock(&lk);
    }
}

int main() {
    setbuf(stdout, NULL);
    for (int i = 0; i < strlen(roles); i++)
        create(fish_thread);
}
