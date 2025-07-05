#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <time.h>
#include <string.h>

uint32_t w, z;

// Android sistem zamanı ile tohum al
void seed_rng() {
    z = time(NULL);
    w = z ^ 0x5DEECE66D;
}

// Marsaglia'nın 96-bit RNG'si (MWC tipi)
uint32_t marsaglia_rand() {
    z = 36969 * (z & 0xFFFF) + (z >> 16);
    w = 18000 * (w & 0xFFFF) + (w >> 16);
    return (z << 16) + w;
}

// 1-90 arasında tekrar etmeyen 6 sayı üret
void generate_column(int col_index) {
    int numbers[91] = {0}; // 0-90 için
    int selected[6];
    int count = 0;

    while (count < 6) {
        int num = marsaglia_rand() % 90 + 1;
        if (!numbers[num]) {
            numbers[num] = 1;
            selected[count++] = num;
        }
    }

    // Küçükten büyüğe sırala
    for (int i = 0; i < 5; i++) {
        for (int j = i + 1; j < 6; j++) {
            if (selected[i] > selected[j]) {
                int tmp = selected[i];
                selected[i] = selected[j];
                selected[j] = tmp;
            }
        }
    }

    printf("%c  ", 'A' + col_index);
    for (int i = 0; i < 6; i++) {
        if (selected[i] < 10)
            printf("0%d ", selected[i]);
        else
            printf("%d ", selected[i]);
    }
    printf("\n");
}

int main() {
    int kolon_sayisi = 3; // sabit sayı (scanf yerine)
    seed_rng();
    printf("--- Sayısal Loto 6/90 ---\n");
    for (int i = 0; i < kolon_sayisi; i++) {
        generate_column(i);
    }
    printf("-------------------------------\n");
    return 0;
}
