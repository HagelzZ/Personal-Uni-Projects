/*
Author: Alexander "HagelzZ" Hagelberg - CCT1 [Gr.9]
        https://github.com/HagelzZ
*/
#include <stdio.h>
#include <string.h>

#define NUM_MATCHES 90
#define NUM_TEAMS 12
#define MAX_TEAM_NAME 20

// Struct til at holde kampoplysninger
typedef struct {
    char weekday[4];         // Ugedag (f.eks. "Fre")
    char date[6];            // Dato (f.eks. "19/07")
    char time[6];            // Tidspunkt (f.eks. "18.00")
    char home_team[MAX_TEAM_NAME];   // Hjemmeholdets navn
    char away_team[MAX_TEAM_NAME];   // Udeholdets navn
    int home_goals;          // Mål scoret af hjemmeholdet
    int away_goals;          // Mål scoret mod udeholdet
    int spectators;          // Antal tilskuere
} Match;

// Struct til at holde holdoplysninger
typedef struct {
    char name[MAX_TEAM_NAME];  // Holdets navn
    int points;                // Point i turneringen
    int goals_scored;          // Mål scoret af holdet
    int goals_against;         // Mål scoret mod holdet
    int spectators;            // Samlet antal tilskuere for holdets hjemmebanekampe
} Team;

// Funktion til at finde eller oprette et hold i team_array
int find_or_create_team(Team team_array[], int *num_teams, const char *team_name) {
    for (int i = 0; i < *num_teams; i++) {
        if (strcmp(team_array[i].name, team_name) == 0) {
            return i;
        }
    }
    // Hvis holdet ikke findes, opret det
    strcpy(team_array[*num_teams].name, team_name);
    team_array[*num_teams].points = 0;
    team_array[*num_teams].goals_scored = 0;
    team_array[*num_teams].goals_against = 0;
    team_array[*num_teams].spectators = 0;
    return (*num_teams)++;
}

// Sammenligningsfunktion til qsort for at sortere holdene
int compare(const void *a, const void *b) {
    Team *team_a = (Team *)a;
    Team *team_b = (Team *)b;
    // Sortér først efter point
    if (team_b->points != team_a->points) {
        return team_b->points - team_a->points;
    }
    // Hvis point er ens, sortér efter målforskel
    int goal_diff_a = team_a->goals_scored - team_a->goals_against;
    int goal_diff_b = team_b->goals_scored - team_b->goals_against;
    return goal_diff_b - goal_diff_a;
}

int main() {
    Match matches[NUM_MATCHES];
    Team team_array[NUM_TEAMS] = {0};
    int num_teams = 0;

    // Indlæs kampdata fra fil
    FILE *file = fopen("kampe-2024-2025.txt", "r");
    if (!file) {
        printf("Couldn't open the file.\n");
        return 1;
    }

    for (int i = 0; i < NUM_MATCHES; i++) {
        fscanf(file, "%s %s %s %s - %s %d - %d %d",
               matches[i].weekday, matches[i].date, matches[i].time,
               matches[i].home_team, matches[i].away_team,
               &matches[i].home_goals, &matches[i].away_goals, &matches[i].spectators);
    }
    fclose(file);

    // Bearbejd kampresultater
    for (int i = 0; i < NUM_MATCHES; i++) {
        int home_index = find_or_create_team(team_array, &num_teams, matches[i].home_team);
        int away_index = find_or_create_team(team_array, &num_teams, matches[i].away_team);

        // Opdater mål
        team_array[home_index].goals_scored += matches[i].home_goals;
        team_array[home_index].goals_against += matches[i].away_goals;
        team_array[away_index].goals_scored += matches[i].away_goals;
        team_array[away_index].goals_against += matches[i].home_goals;

        // Opdater tilskuere for hjemmehold
        team_array[home_index].spectators += matches[i].spectators;

        // Opdater point
        if (matches[i].home_goals > matches[i].away_goals) {
            team_array[home_index].points += 3;
        } else if (matches[i].home_goals < matches[i].away_goals) {
            team_array[away_index].points += 3;
        } else {
            team_array[home_index].points += 1;
            team_array[away_index].points += 1;
        }
    }

    // Sortér holdene
    qsort(team_array, num_teams, sizeof(Team), compare);

    // Udskriv stillingen
    printf("%-15s %-15s %-15s %-15s %-15s\n", "Team name", "Points", "Goals scored", "Goals against", "Spectators");
    for (int i = 0; i < num_teams; i++) {
        printf("%-15s %-15d %-15d %-15d %-15d\n",
               team_array[i].name,
               team_array[i].points,
               team_array[i].goals_scored,
               team_array[i].goals_against,
               team_array[i].spectators);
    }

    return 0;
}
