#ifndef PROJECT_4_DATABASE_H
#define PROJECT_4_DATABASE_H

#include "hashSet.h"

extern void initDatabase();
extern void freeDatabase();

typedef struct { // player
    int playerID;
    char* name;
    int age;
    char* team;
} PNAT;

extern void insertPNAT(int playerID, char* name, int age, char* team);
extern void deletePNAT(char* playerID, char* name, char* age, char* team);
extern void lookupPNAT(char* playerID, char* name, char* age, char* team);
extern void printPNATTable();

typedef struct { // team
    char* team;
    char* owner;
} TO;

extern void insertTO(char* team, char* owner);
extern void deleteTO(char* team, char* owner);
extern void lookupTO(char* team, char* owner);
extern void printTOTable();

typedef struct { // city
    char* team;
    char* city;
} TC;

extern void insertTC(char* team, char* city);
extern void deleteTC(char* team, char* city);
extern void lookupTC(char* team, char* city);
extern void printTCTable();

typedef struct { // game
    int gameNum;
    char* homeTeam;
    char* awayTeam;
    char* date;
} GHAD;

extern void insertGHAD(int gameNum, char* homeTeam, char* awayTeam, char* date);
extern void deleteGHAD(char* gameNum, char* homeTeam, char* awayTeam, char* date);
extern void lookupGHAD(char* gameNum, char* homeTeam, char* awayTeam, char* date);
extern void printGHADTable();

typedef struct { // scoring
    int playerID;
    int gameNum;
    int goals;
    int assists;
} PGGA;

extern void insertPGGA(int playerID, int gameNum, int goals, int assists);
extern void deletePGGA(char* playerID, char* gameNum, char* goals, char* assists);
extern void lookupPGGA(char* playerID, char* gameNum, char* goals, char* assists);
extern void printPGGATable();

extern void addAppendixA();

extern void findGoalsPartA(int gameNum, char *name);
extern void findGoalsPartB(char *name, char *city);

typedef struct {
    int playerID;
    char* name;
    int age;
    char* team;
} SelectedPNAT;

typedef struct {
    char *name;
} ProjectedName;

typedef struct {
    int gameNum;
    char* homeTeam;
    char* awayTeam;
    char* date;
    char* city;
} JoinGameAndTeam;

typedef struct {
    int gameNum;
    char *team; // same as home team
    char *awayTeam;
    char *date;
    char *city;
} SelectedGHADC;

typedef struct {
    char *awayTeam;
} ProjectedAwayTeam;

extern hashSet *selectByTeam(char *team, hashSet *selectedRes);
extern hashSet *projectNameByTeam(hashSet *projectedRes, hashSet *selectedRes);
extern hashSet *joinGAMEandTEAMbyHomeTeamandTeam(hashSet *joinRes);
extern hashSet *projectByAwayTeam(hashSet *projectedRes, hashSet *selectedRes);
extern hashSet *selectByCity(char *city, hashSet *selectedRes, hashSet *ghadcTable);

#endif //PROJECT_4_DATABASE_H