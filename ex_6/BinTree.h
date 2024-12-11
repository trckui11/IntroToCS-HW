/******************************************
*Student name: Arbel Feldman
*Student ID: 216303990
*Exercise name: ex_6
*Submit username: feldmaaf
******************************************/

#ifndef EX_6_BINTREE_H
#define EX_6_BINTREE_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_STRING 11
#define AGE_PER_ITERATION 20
#define LEADER_FREE_AGE 80
#define DIE_AGE 120
#define MALE 'M'
#define FEMALE 'F'
#define LEADER "Moshe"
#define TRUE 1
#define FALSE 0

typedef struct BinTree {
    int id;
    char* name;
    int age;
    char gender;
    void (*task)(void* val);
    void* action;
    struct BinTree* left;
    struct BinTree* right;
    // I added a parent field for easy access to it:
    struct BinTree* parent;
} BinTree;

void generic_function(BinTree* root, void(*task)(void*));
int generic_int_function(BinTree* root, int(*task)(void*));

BinTree* createChild();
void addChild(BinTree* root, BinTree* child);

void child_task(void* val);
void moshe_task(void* val);

int increaseAge(void* root);

int removeChild(BinTree* child);
int throwToNile(void* root);

void childTaskPreorder(void* root);
void childTaskInorder(void* root);
void childTaskPostorder(void* root);

int findMoshe(void* root);

void printPreorder(void* root);
void printInorder(void* root);
void printPostorder(void* root);

int sizeAllJews(void* root);
int sizeAllMales(void* root);
int sizeAllFemales(void* root);

int checkDieAge(void* root);

void freeIsrael(void* root);

//EX_6_BINTREE_H
#endif