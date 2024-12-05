/*
Author: Alexander "HagelzZ" Hagelberg - CCT1 [Gr.9]
        https://github.com/HagelzZ
*/
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define ROUNDS 15  // Antal runder i spillet
#define MAX_DICE 20  // Maksimum antal terninger

// Funktion til at slå med flere terninger
void roll_multiple_dice(int dice[], int N) {
    for (int i = 0; i < N; i++) {
        dice[i] = rand() % 6 + 1;
    }
}

// Funktion til at udskrive terningerne
void print_dice(int dice[], int N) {
    for (int i = 0; i < N; i++) {
        printf("%d ", dice[i]);
    }
}

// Funktion til at tælle antal af en given værdi
int count_value(int dice[], int N, int value) {
    int count = 0;
    for (int i = 0; i < N; i++) {
        if (dice[i] == value) {
            count++;
        }
    }
    return count;
}

// Funktion til at beregne den bedste score for de første 6 runder
int score_single_number(int dice[], int N, int number) {
    int count = count_value(dice, N, number);
    return count * number; 
}

// Funktion til at beregne point for et One Pair
int score_one_pair(int dice[], int N) {
    int max_pair = 0;
    for (int i = 1; i <= 6; i++) {
        if (count_value(dice, N, i) >= 2 && i * 2 > max_pair) {
            max_pair = i * 2;
        }
    }
    return max_pair;
}

// Funktion til at beregne point for to One Pair
int score_two_pair(int dice[], int N) {
    int first_pair = 0, second_pair = 0;
    for (int i = 6; i >= 1; i--) {
        if (count_value(dice, N, i) >= 2) {
            if (first_pair == 0) {
                first_pair = i * 2;
            } else {
                second_pair = i * 2;
                return first_pair + second_pair;
            }
        }
    }
    return 0;
}

// Funktion til at beregne point for tre ens
int score_three_of_a_kind(int dice[], int N) {
    for (int i = 6; i >= 1; i--) {
        if (count_value(dice, N, i) >= 3) {
            return i * 3;
        }
    }
    return 0;
}

// Funktion til at beregne point for fire ens
int score_four_of_a_kind(int dice[], int N) {
    for (int i = 6; i >= 1; i--) {
        if (count_value(dice, N, i) >= 4) {
            return i * 4;
        }
    }
    return 0;
}

// Funktion til at beregne point for lille (1-5)
int score_small_straight(int dice[], int N) {
    int required[] = {1, 2, 3, 4, 5};
    for (int i = 0; i < 5; i++) {
        if (count_value(dice, N, required[i]) == 0) {
            return 0;
        }
    }
    return 15;
}

// Funktion til at beregne point for stor (2-6)
int score_large_straight(int dice[], int N) {
    int required[] = {2, 3, 4, 5, 6};
    for (int i = 0; i < 5; i++) {
        if (count_value(dice, N, required[i]) == 0) {
            return 0;
        }
    }
    return 20;
}

// Funktion til at beregne point for fuld hus
int score_full_house(int dice[], int N) {
    int three_of_a_kind = 0, pair = 0;
    for (int i = 1; i <= 6; i++) {
        if (count_value(dice, N, i) >= 3) {
            three_of_a_kind = i * 3;
        }
    }
    for (int i = 1; i <= 6; i++) {
        if (count_value(dice, N, i) >= 2 && i * 2 != three_of_a_kind) {
            pair = i * 2;
        }
    }
    return (three_of_a_kind && pair) ? (three_of_a_kind + pair) : 0;
}

// Funktion til at beregne point for chance (sum af de 5 højeste terninger)
int score_chance(int dice[], int N) {
    int sum = 0;
    for (int i = 0; i < N; i++) {
        sum += dice[i];
    }
    return sum;
}

// Funktion til at beregne point for Yatzy (5 ens)
int score_yatzy(int dice[], int N) {
    for (int i = 1; i <= 6; i++) {
        if (count_value(dice, N, i) == 5) {
            return 50;
        }
    }
    return 0;
}

// Funktion til at udregne den samlede score
int calculate_total_score(int scores[], int bonus) {
    int total = bonus;
    for (int i = 0; i < ROUNDS; i++) {
        total += scores[i];
    }
    return total;
}

int main() {
    int N;
    srand(time(NULL));
    while (1) {
        printf("Yatzy with how many dice (a number less than 5 terminates): ");
        scanf("%d", &N);
        if (N < 5) break;

        int dice[MAX_DICE];
        int scores[ROUNDS] = {0};
        int bonus = 0;
        int upper_score = 0;
        
        // Slå med terningerne og udregn point for hver runde
        for (int round = 0; round < ROUNDS; round++) {
            roll_multiple_dice(dice, N);

            switch (round) {
                case 0: 
                    scores[round] = score_single_number(dice, N, 1); 
                    printf("Ones: ", round + 1);
                    print_dice(dice, N);
                    break;
                case 1: 
                    scores[round] = score_single_number(dice, N, 2); 
                    printf("Twos: ", round + 1);
                    print_dice(dice, N);
                    break;
                case 2: 
                    scores[round] = score_single_number(dice, N, 3); 
                    printf("Threes: ", round + 1);
                    print_dice(dice, N);
                    break;
                case 3: 
                    scores[round] = score_single_number(dice, N, 4); 
                    printf("Fours: ", round + 1);
                    print_dice(dice, N);
                    break;
                case 4: 
                    scores[round] = score_single_number(dice, N, 5); 
                    printf("Fives: ", round + 1);
                    print_dice(dice, N);
                    break;
                case 5: 
                    scores[round] = score_single_number(dice, N, 6); 
                    printf("Sixes: ", round + 1);
                    print_dice(dice, N);
                    break;
                case 6: 
                    scores[round] = score_one_pair(dice, N); 
                    printf("One Pair: ", round + 1);
                    print_dice(dice, N);
                    break;
                case 7: 
                    scores[round] = score_two_pair(dice, N); 
                    printf("Two Pair: ", round + 1);
                    print_dice(dice, N);
                    break;
                case 8: 
                    scores[round] = score_three_of_a_kind(dice, N); 
                    printf("Three of a kind: ", round + 1);
                    print_dice(dice, N);
                    break;
                case 9: 
                    scores[round] = score_four_of_a_kind(dice, N); 
                    printf("Four of a kind: ", round + 1);
                    print_dice(dice, N);
                    break;
                case 10: 
                    scores[round] = score_small_straight(dice, N); 
                    printf("Small Straight: ", round + 1);
                    print_dice(dice, N);
                    break;
                case 11: 
                    scores[round] = score_large_straight(dice, N); 
                    printf("Large Straight: ", round + 1);
                    print_dice(dice, N);
                    break;
                case 12: 
                    scores[round] = score_full_house(dice, N); 
                    printf("Full House: ", round + 1);
                    print_dice(dice, N);
                    break;
                case 13: 
                    scores[round] = score_yatzy(dice, N); 
                    printf("Yatzy: ", round + 1);
                    print_dice(dice, N);
                    break;
                case 14:
                    scores[round] = score_chance(dice, N);
                    printf("Chance: ", round + 1);
                    print_dice(dice, N);
                    break;
            }
            printf("-- %d points\n", scores[round]);
        }
        for (int i = 0; i < 6; i++) {
            upper_score += scores[i];
        }
        if (upper_score >= 63) bonus = 50;

        // Udskrivning af scoreboard
        printf("\nScoreboard:\n");
        printf("Ones: %d\nTwos: %d\nThrees: %d\nFours: %d\nFives: %d\nSixes: %d\nBONUS: %d\n\n",
               scores[0], scores[1], scores[2], scores[3], scores[4], scores[5], bonus);
        printf("One Pair: %d\nTwo Pair: %d\nThree of a kind: %d\nFour of a kind: %d\nSmall Straight: %d\nLarge Straight: %d\nFull House: %d\nYatzy: %d\n",
               scores[6], scores[7], scores[8], scores[9], scores[10], scores[11], scores[12], scores[13]);

        printf("TOTAL SCORE: %d\n\n", calculate_total_score(scores, bonus));
    }
    return 0;
}
