#include "database.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "hashSet.h"

hashSet *pnatTable;
hashSet *toTable;
hashSet *tcTable;
hashSet *ghadTable;
hashSet *pggaTable;

void initDatabase() {
    pnatTable = newHashSet(11);
    toTable = newHashSet(11);
    tcTable = newHashSet(11);
    ghadTable = newHashSet(11);
    pggaTable = newHashSet(11);
}

void freeDatabase() {
    freeHashSet(pnatTable);
    freeHashSet(toTable);
    freeHashSet(tcTable);
    freeHashSet(ghadTable);
    freeHashSet(pggaTable);
}

bool isWildcardOrMatch(char *para, char *val) {
    return strcmp(para, "*") == 0 || strcmp(para, val) == 0;
}

bool isIntWildcardOrMatch(char *para, int val) {
    if (strcmp(para, "*") == 0) { return true; }
    int i = atoi(para); // atoi is ASCII to int
    return i == val;
}

char *createPNATKey(int playerID) {
    char *key = malloc(sizeof(char) * 20);
    sprintf(key, "%d", playerID);
    return key;
}

char *createTOKey(char *team) {
    char *key = strdup(team);
    return key;
}

char *createTCKey(char *team) {
    char *key = strdup(team);
    return key;
}

char *createGHADKey(int gameNum) {
    char *key = malloc(sizeof(char) * 20);
    sprintf(key, "%d", gameNum);
    return key;
}

char *createPGGAKey(int playerID) {
    char *key = malloc(sizeof(char) * 20);
    sprintf(key, "%d", playerID);
    return key;
}

void insertPNAT(int playerID, char* name, int age, char* team) {
    PNAT *pnat = malloc(sizeof(PNAT));
    pnat->playerID = playerID;
    pnat->name = strdup(name);
    pnat->age = age;
    pnat->team = strdup(team);

    char *key = createPNATKey(playerID);
    insert(pnatTable, key, pnat);
    free(key);
}

void deletePNAT(char* playerID, char* name, char* age, char* team) {
    bool found = false;
    for (int i = 0; i < pnatTable->size; i++) {
        entry *e = pnatTable->table[i];
        entry *prev = NULL;

        while (e != NULL) {
            PNAT *pnat = e->value;
            entry *next = e->next;
            if (isIntWildcardOrMatch(playerID, pnat->playerID) && isWildcardOrMatch(name, pnat->name) && isIntWildcardOrMatch(age, pnat->age) && isWildcardOrMatch(team, pnat->team)) {
                found = true;
                if (prev == NULL) {
                    pnatTable->table[i] = next;
                } else {
                    prev->next = next;
                }
                free(pnat->name);
                free(pnat->team);
                free(pnat);
                e = next;
            } else {
                prev = e;
                e = next;
            }
        }
    }
    if (!found) { printf("Not found in PNAT Table.\n"); }
}

void lookupPNAT(char* playerID, char* name, char* age, char* team) {
    bool found = false;
    for (int i = 0; i < pnatTable->size; i++) {
        entry *e = pnatTable->table[i];
        while (e != NULL) {
            PNAT *pnat = e->value;
            if (isIntWildcardOrMatch(playerID, pnat->playerID) && isWildcardOrMatch(name, pnat->name) && isIntWildcardOrMatch(age, pnat->age) && isWildcardOrMatch(team, pnat->team)) {
                printf("Found in PNAT: Player ID: %d, Name: %s, Age: %d, Team: %s\n", pnat->playerID, pnat->name, pnat->age, pnat->team);
                found = true;
            }
            e = e->next;
        }
    }

    if (!found) {
        printf("Not found in PNAT table.\n");
    }
}

void printPNATTable() {
    printf("PNAT Table:\n");
    for (int i = 0; i < pnatTable->size; i++) {
        entry *e = pnatTable->table[i];
        while (e != NULL) {
            PNAT *pnat = e->value;
            printf("PNAT: Player ID: %d, Name: %s, Age: %d, Team: %s\n", pnat->playerID, pnat->name, pnat->age, pnat->team);
            e = e->next;
        }
    }
}

void insertTO(char* team, char* owner) {
    TO *to = malloc(sizeof(TO));
    to->team = strdup(team);
    to->owner = strdup(owner);

    char *key = createTOKey(team);
    insert(toTable, key, to);
    free(key);
}

void deleteTO(char* team, char* owner) {
    bool found = false;
    for (int i = 0; i < toTable->size; i++) {
        entry *e = toTable->table[i];
        entry *prev = NULL;

        while (e != NULL) {
            entry *next = e->next;
            TO *to = e->value;
            if (isWildcardOrMatch(team, to->team) && isWildcardOrMatch(owner, to->owner)) {
                found = true;
                if (prev == NULL) {
                    toTable->table[i] = next;
                } else {
                    prev->next = next;
                }
                free(to->team);
                free(to->owner);
                free(to);
                e = next;
            } else {
                prev = e;
                e = next;
            }

        }
    }
    if (!found) { printf("Not found in TO Table.\n"); }
}

void lookupTO(char* team, char* owner) {
    bool found = false;
    for (int i = 0; i < toTable->size; i++) {
        entry *e = toTable->table[i];
        while (e != NULL) {
            TO *to = e->value;
            if (isWildcardOrMatch(team, to->team) && isWildcardOrMatch(owner, to->owner)) {
                printf("Found in TO: Team: %s, Owner: %s\n", to->team, to->owner);
                found = true;
            }
            e = e->next;
        }
    }

    if (!found) {
        printf("Not found in TO table.\n");
    }
}

void printTOTable() {
    printf("TO Table:\n");
    for (int i = 0; i < toTable->size; i++) {
        entry *e = toTable->table[i];
        while (e != NULL) {
            TO *to = e->value;
            printf("TO: Team: %s, Owner: %s\n", to->team, to->owner);
            e = e->next;
        }
    }
}

void insertTC(char* team, char* city) {
    TC *tc = malloc(sizeof(TC));
    tc->team = strdup(team);
    tc->city = strdup(city);

    char *key = createTCKey(team);
    insert(tcTable, key, tc);
    free(key);
}

void deleteTC(char* team, char* city) {
    bool found = false;
    for (int i = 0; i < tcTable->size; i++) {
        entry *e = tcTable->table[i];
        entry *prev = NULL;

        while (e != NULL) {
            TC *tc = e->value;
            entry *next = e->next;
            if (isWildcardOrMatch(team, tc->team) && isWildcardOrMatch(city, tc->city)) {
                found = true;
                if (prev == NULL) {
                    toTable->table[i] = next;
                } else {
                    prev->next = next;
                }
                free(tc->team);
                free(tc->city);
                free(tc);
                e = next;
            } else {
                prev = e;
                e = next;
            }
        }
    }
    if (!found) { printf("Not found in TC Table.\n"); }
}

void lookupTC(char* team, char* city) {
    bool found = false;
    for (int i = 0; i < tcTable->size; i++) {
        entry *e = tcTable->table[i];
        while (e != NULL) {
            TC *tc = e->value;
            if (isWildcardOrMatch(team, tc->team) && isWildcardOrMatch(city, tc->city)) {
                printf("Found in TC: Team: %s, City: %s\n", tc->team, tc->city);
                found = true;
            }
            e = e->next;
        }
    }

    if (!found) {
        printf("Not found in TC table.\n");
    }
}

void printTCTable() {
    printf("TC Table:\n");
    for (int i = 0; i < tcTable->size; i++) {
        entry *e = tcTable->table[i];
        while (e != NULL) {
            TC *tc = e->value;
            printf("TC: Team: %s, City: %s\n", tc->team, tc->city);
            e = e->next;
        }
    }
}

void insertGHAD(int gameNum, char* homeTeam, char* awayTeam, char* date) {
    GHAD *ghad = malloc(sizeof(GHAD));
    ghad->gameNum = gameNum;
    ghad->homeTeam = strdup(homeTeam);
    ghad->awayTeam = strdup(awayTeam);
    ghad->date = strdup(date);

    char *key = createGHADKey(gameNum);
    insert(ghadTable, key, ghad);
    free(key);
}

void deleteGHAD(char* gameNum, char* homeTeam, char* awayTeam, char* date) {
    bool found = false;
    for (int i = 0; i < ghadTable->size; i++) {
        entry *e = ghadTable->table[i];
        entry *prev = NULL;

        while (e != NULL) {
            GHAD *ghad = e->value;
            entry *next = e->next;
            if (isIntWildcardOrMatch(gameNum, ghad->gameNum) && isWildcardOrMatch(homeTeam, ghad->homeTeam) && isWildcardOrMatch(awayTeam, ghad->awayTeam) && isWildcardOrMatch(date, ghad->date)) {
                found = true;
                if (prev == NULL) {
                    ghadTable->table[i] = next;
                } else {
                    prev->next = next;
                }
                free(ghad->homeTeam);
                free(ghad->awayTeam);
                free(ghad->date);
                free(ghad);
                e = next;
            } else {
                prev = e;
                e = next;
            }
        }
    }
    if (!found) { printf("Not found in GHAD Table.\n"); }
}

void lookupGHAD(char* gameNum, char* homeTeam, char* awayTeam, char* date) {
    bool found = false;
    for (int i = 0; i < ghadTable->size; i++) {
        entry *e = ghadTable->table[i];
        while (e != NULL) {
            GHAD *ghad = e->value;
            if (isIntWildcardOrMatch(gameNum, ghad->gameNum) && isWildcardOrMatch(homeTeam, ghad->homeTeam) && isWildcardOrMatch(awayTeam, ghad->awayTeam) && isWildcardOrMatch(date, ghad->date)) {
                printf("Found in GHAD: gameNum: %d, Home Team: %s, Away Team: %s, Date: %s\n", ghad->gameNum, ghad->homeTeam, ghad->awayTeam, ghad->date);
                found = true;
            }
            e = e->next;
        }
    }

    if (!found) {
        printf("Not found in GHAD table.\n");
    }
}

void printGHADTable() {
    printf("GHAD Table:\n");
    for (int i = 0; i < ghadTable->size; i++) {
        entry *e = ghadTable->table[i];
        while (e != NULL) {
            GHAD *ghad = e->value;
            printf("GHAD: gameNum: %d, Home Team: %s, Away Team: %s, Date: %s\n", ghad->gameNum, ghad->homeTeam, ghad->awayTeam, ghad->date);
            e = e->next;
        }
    }
}

void insertPGGA(int playerID, int gameNum, int goals, int assists) {
    PGGA *pgga = malloc(sizeof(PGGA));
    pgga->gameNum = gameNum;
    pgga->playerID = playerID;
    pgga->goals = goals;
    pgga->assists = assists;

    char *key = createPGGAKey(playerID);
    insert(pggaTable, key, pgga);
    free(key);
}

void deletePGGA(char* playerID, char* gameNum, char* goals, char* assists) {
    bool found = false;
    for (int i = 0; i < pggaTable->size; i++) {
        entry *e = pggaTable->table[i];
        entry *prev = NULL;

        while (e != NULL) {
            PGGA *pgga = e->value;
            entry *next = e->next;
            if (isIntWildcardOrMatch(gameNum, pgga->gameNum) && isIntWildcardOrMatch(playerID, pgga->playerID) && isIntWildcardOrMatch(goals, pgga->goals) && isIntWildcardOrMatch(assists, pgga->assists)) {
                found = true;
                if (prev == NULL) {
                    pggaTable->table[i] = next;
                } else {
                    prev->next = next;
                }
                free(pgga);
                e = next;
            } else {
                prev = e;
                e = next;
            }
        }
    }
    if (!found) { printf("Not found in PGGA Table.\n"); }
}

void lookupPGGA(char* playerID, char* gameNum, char* goals, char* assists) {
    bool found = false;
    for (int i = 0; i < pggaTable->size; i++) {
        entry *e = pggaTable->table[i];
        while (e != NULL) {
            PGGA *pgga = e->value;
            if (isIntWildcardOrMatch(gameNum, pgga->gameNum) && isIntWildcardOrMatch(playerID, pgga->playerID) && isIntWildcardOrMatch(goals, pgga->goals) && isIntWildcardOrMatch(assists, pgga->assists)) {
                printf("Found in PGGA: Player ID: %d, gameNum: %d, Goals: %d, Assists: %d\n", pgga->playerID, pgga->gameNum, pgga->goals, pgga->assists);
                found = true;
            }
            e = e->next;
        }
    }

    if (!found) {
        printf("Not found in PGGA table.\n");
    }
}

void printPGGATable() {
    printf("PGGA Table:\n");
    for (int i = 0; i < pggaTable->size; i++) {
        entry *e = pggaTable->table[i];
        while (e != NULL) {
            PGGA *pgga = e->value;
            printf("PGGA: Player ID: %d, gameNum: %d, Goals: %d, Assists: %d\n", pgga->playerID, pgga->gameNum, pgga->goals, pgga->assists);
            e = e->next;
        }
    }
}

void addAppendixA() {
    initDatabase();

    // PNAT
    insertPNAT(8547, "R. Long", 28, "Freeze");
    insertPNAT(6292, "I. Perez", 20, "Freeze");
    insertPNAT(1596, "D. Gray", 33, "Freeze");
    insertPNAT(3445, "A. Patel", 18, "Amerks");
    insertPNAT(4055, "I. Perez", 34, "Bears");
    insertPNAT(3211, "D. Gray", 18, "Amerks");

    // TO
    insertTO("Dogs", "C. Long");
    insertTO("Freeze", "J. Nguyen");
    insertTO("Amerks", "I. Price");
    insertTO("Chill", "J. Nguyen");
    insertTO("Bears", "L. Allen");
    insertTO("Edge", "I. Price");

    // TC
    insertTC("Dogs", "Binghamton");
    insertTC("Freeze", "Albany");
    insertTC("Amerks", "Rochester");
    insertTC("Chill", "Syracuse");
    insertTC("Bears", "Buffalo");
    insertTC("Edge", "Utica");

    // GHAD
    insertGHAD(904, "Edge", "Freeze", "Feb 17");
    insertGHAD(663, "Freeze", "Bears", "Mar 14");
    insertGHAD(501, "Edge", "Amerks", "Nov 28");
    insertGHAD(461, "Amerks", "Freeze", "Dec 14");
    insertGHAD(252, "Freeze", "Bears", "Jan 20");

    // PGGA
    insertPGGA(1596, 904, 2, 1);
    insertPGGA(6292, 663, 1, 0);
    insertPGGA(8547, 663, 2, 1);
    insertPGGA(3211, 501, 1, 2);
    insertPGGA(4055, 252, 2, 1);
}

void findGoalsPartA(int gameNum, char* name) {
    for (int i = 0; i < pnatTable->size; i++) {
        entry *t = pnatTable->table[i];
        while (t != NULL) {
            PNAT *pnat = t->value;
            if (strcmp(name, pnat->name) == 0) {
                int playerID = pnat->playerID;
                for (int j = 0; j < pggaTable->size; j++) {
                    entry *s = pggaTable->table[j];
                    while (s != NULL) {
                        PGGA *pgga = s->value;
                        if (playerID == pgga->playerID && gameNum == pgga->gameNum) {
                            printf("In game %d, %s scored %d goals.\n", gameNum, name, pgga->goals);
                            return;
                        }
                        s = s->next;
                    }
                }
            }
            t = t->next;
        }
    }
    printf("There is no record of %s in game %d.\n", name, gameNum);
}

void findGoalsPartB(char *name, char *city) {
    bool anyFound = false;
    for (int i = 0; i < pnatTable->size; i++) {
        entry *t = pnatTable->table[i];
        while (t != NULL) {
            PNAT *pnat = t->value;
            if (strcmp(pnat->name, name) == 0) {
                int playerID = pnat->playerID;
                int goals = 0;
                bool found = false;
                for (int j = 0; j < pggaTable->size; j++) {
                    entry *s = pggaTable->table[j];
                    while (s != NULL) {
                        PGGA *pgga = s->value;
                        if (pgga->playerID == playerID) {
                            bool gameMatched = false;
                            for (int k = 0; k < ghadTable->size && !gameMatched; k++) {
                                entry *u = ghadTable->table[k];
                                while (u != NULL && !gameMatched) {
                                    GHAD *ghad = u->value;
                                    if (pgga->gameNum == ghad->gameNum) {
                                        for (int l = 0; l < tcTable->size && !gameMatched; l++) {
                                            entry *v = tcTable->table[l];
                                            while (v != NULL && !gameMatched) {
                                                TC *tc = v->value;
                                                if (strcmp(ghad->homeTeam, tc->team) == 0 && strcmp(tc->city, city) == 0) {
                                                    goals += pgga->goals;
                                                    found = true;
                                                    gameMatched = true;
                                                }
                                                v = v->next;
                                            }
                                        }
                                    }
                                    u = u->next;
                                }
                            }
                        }
                        s = s->next;
                    }
                }
                if (found) {
                    printf("%s (ID: %d) scored %d goals playing in %s\n", name, playerID, goals, city);
                    anyFound = true;
                }
            }
            t = t->next;
        }
    }
    if (!anyFound) {
        printf("There is no record of %s playing in %s.\n", name, city);
    }
}

hashSet *selectByTeam(char *team, hashSet *selectedRes) {
    for (int i = 0; i < pnatTable->size; i++) {
        entry *t = pnatTable->table[i];
        while (t != NULL) {
            PNAT *pnat = t->value;
            if (strcmp(pnat->team, team) == 0) {
                SelectedPNAT *selectedPNAT = malloc(sizeof(SelectedPNAT));
                selectedPNAT->playerID = pnat->playerID;
                selectedPNAT->name = strdup(pnat->name);
                selectedPNAT->age = pnat->age;
                selectedPNAT->team = strdup(pnat->team);

                char *key = createPNATKey(selectedPNAT->playerID);
                insert(selectedRes, key, selectedPNAT);
                free(key);
            }
            t = t->next;
        }
    }
    return selectedRes;
}

hashSet *projectNameByTeam(hashSet *projectedRes, hashSet *selectedRes) {
    for (int i = 0; i < selectedRes->size; i++) {
        entry *e = selectedRes->table[i];
        while (e != NULL) {
            SelectedPNAT *selectedPNAT = e->value;
            ProjectedName *projectedName = malloc(sizeof(ProjectedName));
            projectedName->name = strdup(selectedPNAT->name);
            insert(projectedRes, projectedName->name, projectedName);
            e = e->next;
        }
    }
    return projectedRes;
}

// join between GHAD and TC
hashSet *joinGAMEandTEAMbyHomeTeamandTeam(hashSet *joinRes) {
    for (int i = 0; i < ghadTable->size; i++) {
        entry *t = ghadTable->table[i];
        while (t != NULL) {
            GHAD *ghad = t->value;
            for (int j = 0; j < tcTable->size; j++) {
                entry *s = tcTable->table[j];
                while (s != NULL) {
                    TC *tc = s->value;
                    if (strcmp(ghad->homeTeam, tc->team) == 0) {
                        JoinGameAndTeam *joinGameAndTeam = malloc(sizeof(JoinGameAndTeam));
                        joinGameAndTeam->gameNum = ghad->gameNum;
                        joinGameAndTeam->homeTeam = strdup(ghad->homeTeam);
                        joinGameAndTeam->awayTeam = strdup(ghad->awayTeam);
                        joinGameAndTeam->date = strdup(ghad->date);
                        joinGameAndTeam->city = strdup(tc->city);

                        char *key = malloc(sizeof(char) * 20);
                        sprintf(key, "%d", joinGameAndTeam->gameNum);
                        insert(joinRes, key, joinGameAndTeam);
                        free(key);
                    }
                    s = s->next;
                }
            }
            t = t->next;
        }
    }
    return joinRes;
}

hashSet *projectByAwayTeam(hashSet *projectedRes, hashSet *selectedRes) {
    for (int i = 0; i < selectedRes->size; i++) {
        entry *e = selectedRes->table[i];
        while (e != NULL) {
            SelectedGHADC *selectedGHADC = e->value;
            ProjectedAwayTeam *projectedAwayTeam = malloc(sizeof(ProjectedAwayTeam));
            projectedAwayTeam->awayTeam = strdup(selectedGHADC->awayTeam);
            insert(projectedRes, projectedAwayTeam->awayTeam, projectedAwayTeam);
            e = e->next;
        }
    }
    return projectedRes;
}

hashSet *selectByCity(char *city, hashSet *selectedRes, hashSet *ghadcTable) {
    for (int i = 0; i < ghadcTable->size; i++) {
        entry *t = ghadcTable->table[i];
        while (t != NULL) {
            JoinGameAndTeam *ghadc = t->value;
            if (strcmp(ghadc->city, city) == 0) {
                SelectedGHADC *selectedGHADC = malloc(sizeof(SelectedGHADC));
                selectedGHADC->gameNum = ghadc->gameNum;
                selectedGHADC->team = strdup(ghadc->homeTeam);
                selectedGHADC->awayTeam = strdup(ghadc->awayTeam);
                selectedGHADC->date = strdup(ghadc->date);
                selectedGHADC->city = strdup(city);

                char *key = createPNATKey(selectedGHADC->gameNum);
                insert(selectedRes, key, selectedGHADC);
                free(key);
            }
            t = t->next;
        }
    }
    return selectedRes;
}