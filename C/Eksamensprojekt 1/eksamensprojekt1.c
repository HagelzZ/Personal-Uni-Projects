/*
Author: Alexander "HagelzZ" Hagelberg
        https://github.com/HagelzZ
*/
#include <stdio.h>
#include <math.h>

void scan_data(char *operator, double *operand){
    printf("Indtast operator: ");
    scanf(" %c", operator);

    /* Tjekker om operatoren er binær, unær eller ugyldig */
    if(*operator == '+' || *operator == '-' || *operator == '*' || *operator == '/' || *operator == '^') {
        printf("Indtast operand: ");
        scanf(" %lf", operand);
    } else if(*operator == '#' || *operator == '%' || *operator == '!' || *operator == 'q') {
        *operand = 0;
    } else {
        printf("Ugyldig operator!\n");
    }
};

void do_next_op(char operator, double operand, double *akkumulator){
    /* Switch funktion der skifter udregningsmetode afhængig af hvad der ligger i 'operator' variablen */
    switch (operator){
        case '+':
            *akkumulator += operand;
            break;
        case '-':
            *akkumulator -= operand;
            break;
        case '*':
            *akkumulator *= operand;
            break;
        case '/':
            if(operand != 0){
                *akkumulator /= operand;
            } else {
                printf("Kan ikke dividere med 0\n");
            };
            break;
        case '^':
            if(*akkumulator != 0){
                *akkumulator = pow(*akkumulator, operand);
            } else {
                printf("Dette giver ikke mening, da 0 * X giver 0\n");
            };
            break;
        case '#':
            if (*akkumulator > 0) {
                *akkumulator = sqrt(*akkumulator);
            } else {
                printf("Kan ikke finde kvadratroden af 0 og negative tal\n");
            };
            break;
        case '%':
            *akkumulator = -*akkumulator;
            break;
        case '!':
            if(*akkumulator != 0){
                *akkumulator = 1 / *akkumulator;
            } else {
                printf("Kan ikke dividere med 0\n");
            };
            break;
        default:
            break;
    }
};

double run_calculator() {
    double akkumulator = 0.0;
    char operator;
    double operand;
    int c; /* Udefineret integer der bruges til en senere funktion */
    
    /* Looper scan_data() og do_next_op() indtil brugeren indtaster 'q' for at afslutte */
    while(operator != 'q'){
        printf("Resultat indtil videre: %.3lf\n", akkumulator);

        /* Kalder scan_data-funktionen for at tage imod bruger-input til udregningerne */
        scan_data(&operator, &operand);

        /* Udfører udregninger baseret på indhold af 'operand' og 'operator' variablerne */
        do_next_op(operator, operand, &akkumulator);
        
        /*
        While-lykke der bruges til at rydde bufferen ved at tage eventuelle "afventende inputs"
        og tjekke hvorvidt det ikke er lig med newline OG 'EOF' som indikerer End Of File
        Dette var nødvendigt siden der var probelemer med en tidligere version af programmet
        hvor den kun nogle gange brugte rigtige input og andre gange "ghost inputs" som jeg kalder dem:)
        */
        while ((c = getchar()) != '\n' && c != EOF) { }
    }
    /* Returnerer til 'main()' funktionen med værdien gemt i 'akkumulator' variablen */
    return akkumulator;
}

int main(){
    printf("\nVelkommen til den akkumulative regnemaskine!\n"
    "Du kan bruge foelgende operatorere:\n\n"
    "Binaere operatorere:\n"
    "+   for addition af akkumulatoren med operanden\n"
    "-   for subtraktionaf akkumulatoren med operanden\n"
    "*   for multiplikation af akkumulatoren med operanden\n"
    "/   for division af akkumulatoren med operanden\n"
    "^   for potensoploeftning af akkumulatoren med operanden\n\n"
    "Unaere operatorere:\n"
    "#   for kvadratroden af akkumulatoren\n"
    "%%   for at vende fortegnet af akkumulatoren\n"
    "!   for at dividere 1 med akkumulatoren\n"
    "q   for at afslutte med slutresultatet\n\n");

    /* Kalder 'run_calculator()' funktionen og returnerer 'akkumulator' til 'resultat' variablen */
    double resultat = run_calculator();

    printf("\nEndeligt resultat: %.3lf\n", resultat);
    return 0;
};
