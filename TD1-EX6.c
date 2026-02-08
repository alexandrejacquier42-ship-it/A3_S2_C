#include <stdio.h>
#include <stdlib.h>
#include <string.h>
 
int len(char *str) {
    int longueur = 0;
    while (str[longueur] != '\0') { 
        longueur++;
    }
    return longueur;
}
 
int cpy (char *str, char *copy){
    int i = 0;
    while (str[i] != '\0') {
        copy[i] = str[i];
        i++;
    }
    copy[i] = '\0';
}
 
int palindrome (char *str){
    char inv[len(str)+1];
    for (int i = 0; i<len(str); i++){
        inv[i] = str[len(str)-1-i];
    }
    inv[len(str)] = '\0';
    if (strcmp(inv, str) == 0) {
        return 1;
    }
    else {
        return 0;
    }
}
int main() {
    char str[100];
    char copy[100];
 
    printf("Entrer une chaine de caractere : ");
    scanf("%s", str);
 
    printf("La longueur de la chaine est : %d\n", len(str));
 
    cpy(str, copy);
    printf("La copie de la chaine est : %s\n", copy);
 
    if (palindrome(str) == 1) {
        printf("La chaine est un palindrome.\n");
    } else {
        printf("La chaine n'est pas un palindrome.\n");
    }
 
    return 0;
}