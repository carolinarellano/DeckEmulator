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
//Falta implementar la funcion para almacenar en el archivo (funcion para save, stop) [Supongo que va desde el main]

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

    //mi_deck.hand = mi_deck.cards[count - 1];

    print_char_array(mi_deck.cards, count);
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
            if(arr[i] < 65)
            {
                printf("%d, ", arr[i]);
            }
            else{
                printf("%c, ", arr[i]);
            }
        printf("%c] ", arr[size - 1]);
    }
}

Deck pull(Deck *my_deck, int *count)
{
    int size = strlen(my_deck->cards);
    char temp[2];

    my_deck->hand = my_deck->cards[*count- 1];

    printf("Your current card is: <%c>", my_deck->hand);

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
            break;

        case ('d'):
            my_deck->hand = ' ';
            print_char_array(my_deck->cards, *count - 1);
            *count -= 1;
            break;

        default:
            printf("Try again \n");
            fgetc(stdin);
            fgetc(stdin);
            print_char_array(my_deck->cards, *count);
    }
}