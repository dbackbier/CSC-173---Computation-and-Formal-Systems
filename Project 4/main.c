#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include "database.h"
#include "hashSet.h"

int main() {
    addAppendixA();

    printf("Initial contents of database:\n");

    printPNATTable();
    printf("\n");

    printTOTable();
    printf("\n");

    printTCTable();
    printf("\n");

    printGHADTable();
    printf("\n");

    printPGGATable();
    printf("\n");

    printf("\nPart 1 - Lookup, insert, and delete operations\n");

    // Part 1
    printf("Performing: lookup(3445, A. Patel, 18, Amerks, PLAYER)\n");
    lookupPNAT("3445", "A. Patel", "18", "Amerks");

    printf("\nPerforming: lookup(*, J. Nguyen, TEAM)\n");
    lookupTO("*", "J. Nguyen");

    printf("\nPerforming: lookup(Dogs, Rochester, CITY)\n");
    lookupTC("Dogs", "Rochester");

    printf("\nPerforming: insert(Giants, Geneseo, CITY)\n");
    insertTC("Giants", "Geneseo");
    printf("Updated ");
    printTCTable();

    printf("\nPerforming: insert(Chill, Syracuse, CITY)\n");
    insertTC("Chill", "Syracuse");
    printf("Updated ");
    printTCTable();

    printf("\nPerforming: delete(Freeze, J. Nguyen, TEAM)\n");
    deleteTO("Freeze", "J. Nguyen");
    printf("Updated ");
    printTOTable();

    printf("\nPerforming: delete(Edge, J. Nguyen, TEAM)\n");
    deleteTO("Edge", "J. Nguyen");
    printf("Updated ");
    printTOTable();

    printf("\nPerforming: delete(*, I. Price, TEAM)\n");
    deleteTO("*", "I. Price");
    printf("Updated ");
    printTOTable();

    // Part 2
    freeDatabase();
    addAppendixA();

    printf("\nPart 2 - Queries\n");

    // (a)
    printf("\n(A) How many goals did 'Name' score in game number 'GameNum'?\n");
    while (true) {
        char name[256];
        printf("Enter the name(enter 'stop' if you wish to stop).\n");
        if (fgets(name, sizeof(name), stdin) == NULL) {
            break;
        }
        name[strcspn(name, "\n")] = '\0';
        if (strcmp(name, "stop") == 0) {
            break;
        }
        int gameNum;
        printf("Enter the game number.\n");
        if (scanf("%d", &gameNum) != 1) {
            break;
        }
        int c;
        while ((c = getchar()) != '\n' && c != EOF);
        findGoalsPartA(gameNum, name);
    }

    // (b)
    printf("\n(B) How many Goals did Name score in games played in City?\n");
    while (true) {
        char name[256];
        printf("Enter the name(enter 'stop' if you wish to stop).\n");
        if (fgets(name, sizeof(name), stdin) == NULL) {
            break;
        }
        name[strcspn(name, "\n")] = '\0';
        if (strcmp(name, "stop") == 0) {
            break;
        }
        char city[256];
        printf("Enter the city.\n");
        if (fgets(city, sizeof(city), stdin) == NULL) {
            break;
        }
        city[strcspn(city, "\n")] = '\0';
        findGoalsPartB(name, city);
    }

    // Part 3
    freeDatabase();
    addAppendixA();

    printf("\nPart 3 - Relational Algebra Operations\n");

    // (1) σTeam=“Amerks”(PLAYER)
    hashSet *selectedRes = newHashSet(11);
    selectedRes = selectByTeam("Amerks", selectedRes);

    printf("1. Selection: Team='Amerks'(PLAYER)\n");
    for (int i = 0; i < selectedRes->size; i++) {
        entry *e = selectedRes->table[i];
        while (e != NULL) {
            SelectedPNAT *selected = e->value;
            printf("Player ID: %d, Name: %s, Age: %d, Team: %s\n", selected->playerID, selected->name, selected->age, selected->team);
            e = e->next;
        }
    }

    printf("\n");

    // (2) πName(σTeam=“Amerks”(PLAYER))
    hashSet *projectedRes = newHashSet(11);
    projectedRes = projectNameByTeam(projectedRes, selectedRes);

    printf("2. Projection: Name(Team='Amerks'(PLAYER))\n");
    for (int i = 0; i < projectedRes->size; i++) {
        entry *e = projectedRes->table[i];
        while (e != NULL) {
            ProjectedName *projected = e->value;
            printf("Name: %s\n", projected->name);
            e = e->next;
        }
    }
    freeHashSet(projectedRes);
    freeHashSet(selectedRes);

    printf("\n");

    // (3) GAME ▷◁HomeTeam=Team CITY
    hashSet *joinRes = newHashSet(11);
    joinRes = joinGAMEandTEAMbyHomeTeamandTeam(joinRes);

    printf("3. Join: GAME HomeTeam=Team CITY\n");
    for (int i = 0; i < joinRes->size; i++) {
        entry *e = joinRes->table[i];
        while (e != NULL) {
            JoinGameAndTeam *joinGameAndTeam = e->value;
            printf("Game: %d, Home Team (Team): %s, Away Team: %s, Date: %s, City: %s\n", joinGameAndTeam->gameNum, joinGameAndTeam->homeTeam, joinGameAndTeam->awayTeam, joinGameAndTeam->date, joinGameAndTeam->city);
            e = e->next;
        }
    }

    printf("\n");

    // (4) πAwayTeam(σCity=“Rochester”(GAME ▷◁HomeTeam=Team CITY))
    // Use Join from (3) for Select
    hashSet *selectCity = newHashSet(11);
    selectCity = selectByCity("Rochester", selectCity, joinRes);

    // Use result from above for projection
    hashSet *projectAwayTeam = newHashSet(11);
    projectAwayTeam = projectByAwayTeam(projectAwayTeam, selectCity);

    printf("4. Projection: AwayTeam(City='Rochester'(GAME HomeTeam=Team CITY))\n");
    for (int i = 0; i < projectAwayTeam->size; i++) {
        entry *e = projectAwayTeam->table[i];
        while (e != NULL) {
            ProjectedAwayTeam *awayTeam = e->value;
            printf("Away Team: %s\n", awayTeam->awayTeam);
            e = e->next;
        }
    }
    freeHashSet(selectCity);
    freeHashSet(projectAwayTeam);
    freeHashSet(joinRes);

    freeDatabase();

    printf("\n");

    return 1;
}
