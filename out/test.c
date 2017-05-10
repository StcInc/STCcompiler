int sum (int x, int y) {
    return x + y;
}

int main () {
    int a = 20;
    for (int i = 0; i < 20; ++i) {
        if (i < a) {
            a = a - 1;
        }
        else {
            a++;
        }
    }
    while (a > 0) {
        a = a - 1;
    }
    do {
        a = a + 1;
    } while (a < 10);
    a = sum(5, 10);
    return 0;
}
