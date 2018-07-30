//
// Created by liushan on 18-7-28.
//

#ifndef EXERCISE_FILM2_H
#define EXERCISE_FILM2_H
void film2(unsigned long);
#define NAME_SIZE 45

struct film {
    char name[NAME_SIZE];
    int rating;
    struct film * next;
};

#endif //EXERCISE_FILM2_H
