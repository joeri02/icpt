#include <stdio.h>

int main() {
    float getal1, getal2;
    float som, verschil, product;

    printf("Voer het eerste getal in: ");
    scanf("%f", &getal1);

    printf("Voer het tweede getal in: ");
    scanf("%f", &getal2);

    som = getal1 + getal2;
    verschil = getal1 - getal2;
    product = getal1 * getal2;

    printf("\nResultaten:\n");
    printf("Som: %.2f + %.2f = %.2f\n", getal1, getal2, som);
    printf("Verschil: %.2f - %.2f = %.2f\n", getal1, getal2, verschil);
    printf("Product: %.2f * %.2f = %.2f\n", getal1, getal2, product);

    return 0;
}
