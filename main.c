#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>

typedef struct deck{
    char cards[5];
    char *hand;
}Deck;

void print_char_array(char *arr, size_t size);
Deck pull(Deck *my_deck, int *count);
//Falta almacenar en el archivo (funcion para save, stop)
void save(Deck *my_deck, int *count);
void load();
int stop();

int main() {

    int count = 5;

    printf("Hello, welcome to the Deck Emulator :)\n");

    char numbers[] = {'K','Q','J','A', 10};

    srand(time(NULL));

    for (int i = count - 1; i >= 0; --i){
        //generate a random number [0, n-1]
        int j = rand() % (i+1);

        //swap the last element with element at random index
        int temp = numbers[i];
        numbers[i] = numbers[j];
        numbers[j] = temp;
    }

    Deck mi_deck;
    mi_deck.cards[0] = numbers[0];
    mi_deck.cards[1] = numbers[1];
    mi_deck.cards[2] = numbers[2];
    mi_deck.cards[3] = numbers[3];
    mi_deck.cards[4] = numbers[4];


    print_char_array(mi_deck.cards, count);
    //save(&mi_deck, &count);
    while(count > 0){
        pull(&mi_deck, &count);
    }
    printf("Your deck is empty. The game is over\n");

    return 0;
}

void print_char_array(char *arr, size_t size) {
    if (size == 0) {
        printf("[] ");
    } else {
        putchar('[');
        for (int i = 0; i < size - 1; i++)
            if(arr[i] == 10)
            {
                printf("%d, ", arr[i]);
            }
            else{
                printf("%c, ", arr[i]);
            }
        if(arr[size - 1] == 10){
            printf("%d] ", arr[size - 1]);
        }else{
            printf("%c] ", arr[size - 1]);
        }

    }
}

Deck pull(Deck *my_deck, int *count)
{
    int size = strlen(my_deck->cards);
    char temp[2];

    my_deck->hand = my_deck->cards[*count- 1];

    if(my_deck->hand == 10){
        printf("Your current card is: <%d>", my_deck->hand);
    }else{
        printf("Your current card is: <%c>", my_deck->hand);
    }


    printf("\nWhat do you want to do with your current card?\n");
    printf("If you want to take it back to the top of the deck -> t\n"
           "If you want to take to take it back to the bottom of the deck -> b\n"
           "If you want to discard your current card -> d\n");

    char choose = (fgetc(stdin));
    fgetc(stdin);
    //*count -= 1;
    switch (choose) {
        case ('t'):
            //printf("<%c>\n", my_deck->hand);
            my_deck->cards[*count-1] = my_deck->hand;
            print_char_array(my_deck->cards, *count);
            save(my_deck, count);
            break;

        case ('b'):
            temp[0] = my_deck->cards[*count - 1];
            //printf("<%c>\n", my_deck->hand);
            for(int i = *count - 1; i > 0; i--)
            {
                my_deck->cards[i] = my_deck->cards[i-1];
            }
            my_deck->cards[0] = temp[0];
            print_char_array(my_deck->cards, *count);
            printf("\n");
            save(my_deck, count);
            break;

        case ('d'):
            my_deck->hand = ' ';
            print_char_array(my_deck->cards, *count - 1);
            *count -= 1;
            save(my_deck, count);
            break;

        case ('s'):
            save(my_deck, count);
            printf("Saved!\n");
            exit(0);

        case ('e'):
            stop();
            break;

        default:
            printf("Try again \n");
            fgetc(stdin);
            fgetc(stdin);
            print_char_array(my_deck->cards, *count);
            break;
    }
}

void save(Deck *my_deck, int *count){
    FILE *fptr;
    fptr = fopen("..\\Deck", "a+");
    if(fptr == NULL){
        printf("ERROR");
    }
    for(int i = 0; i < *count; i++){
        if(my_deck->cards[i] < 65)
        {
            fprintf(fptr, "%d ", my_deck->cards[i]);
        }
        else{
            fprintf(fptr, "%c ", my_deck->cards[i]);
        }
    }
    if(my_deck->hand == 10){
        fprintf(fptr, "<%d>\n", my_deck->hand);

    }else{
        fprintf(fptr, "<%c>\n", my_deck->hand);
    }
}

void load(){
    FILE *fptr;
    fptr = fopen("..\\Deck", "r+");
    if(fptr == NULL){
        printf("There's not a game saved before");
    }
}
int stop(){
    exit(0);
}
