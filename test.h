//
// Created by liushan on 19-11-10.
//

#ifndef EXERCISE_TEST_H
#define EXERCISE_TEST_H


struct conninfo {
    int a;
    int b;
    char c;
};


struct runinfo {
    struct conninfo * conn;
    char d;
    int e;
};

void temp_test(void);

#endif //EXERCISE_TEST_H
