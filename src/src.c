#include <stdlib.h>
#include <stdio.h>

int menu() {
    int op;

    system("cls");
    printf("* * * *    MENU    * * * *\n\n");
    printf("1 - Criptografar\n");
    printf("2 - Descriptografar\n");
    printf("Escolha uma opcao: ");
    scanf("%d", &op);

    return op;
}

int main() {
    FILE *fonte, *novo; //Ponteiros dos arquivos

    char ch, ch2;       //Variaveis para a leitura e transcrição dos caracteres presentes nos arquivos
    int ascii, temp;    //Variaveis para a manipulação dos caracteres

    int chave, op;      //Variaveis para a interação do usuario

    chave = 0;
    op = 0;

    fonte = fopen("origem.txt", "r");       //Abertura dos arquivos
    novo = fopen("saida.txt", "w");

    op = menu();

    switch (op) {                           //Como o programa efetua dois tipos de operação, tem um switch case para escolher elas

        case 1:                             //Codificador
            system("cls");
            printf("* * * *    Criptografar    * * * *\n\n");

            printf("Insira a chave da codificacao de 0 a 26:\n");
            scanf("%d", &chave);            //Coleta da chave da codificação de cesar

            if (chave >= 0 && chave <= 26) {                    //Validação da chave
                while ((ch = getc(fonte)) != EOF) {             //While para percorrer todo o documento txt
                    //printf("%c", ch);                         essa linha servia apenas para debug

                    ascii = ch;                                 //Salva o caractere atual do arquivo em uma váriavel tipo int, dessa forma convertendo para ASCII
                    temp = ascii + chave;                       //depois é feito uma soma da chave com o valor ASCII para realizar a conversão

                    if ((ascii != 32) && ((temp >= 65 && temp <= 90) || (temp >= 97 && temp <= 122))) {     //Para a conversão ser feita corretamente, é necessário checar se a soma não sai do intervalo referente ao alfabeto
                        ascii = temp;                           //Caso ela não sair, ele faz a conversão direta de ASCII para caractere e coloca no novo txt
                        ch2 = ascii;
                        fputc(ch2, novo);

                    } else if ((ascii >= 65 && ascii <= 90) || (ascii >= 97 && ascii <= 122)) {

                        if (ascii >= 65 && ascii <= 90) {       //Caso contrário, é realizado uma verificação para saber se é maiusculo ou minusculo para percorrer o conjunto certo do inicio
                            ascii = 65 + (temp - ascii);
                        }
                        if (ascii >= 97 && temp <= 123) {
                            ascii = 97 + (temp - ascii);
                        }

                        ch2 = ascii;                            //E só ai que é introduzido no txt
                        fputc(ch2, novo);
                    } else {                                    //Por fim, se o caractere não for uma letra, ele não realiza a conversão
                        ch2 = ascii;
                        fputc(ch2, novo);
                    }
                }
                printf("Arquivo criptografado com sucesso!");
            } else {
                printf("Erro ao tentar criptografar...\nNumero de codificacao invalido!");
            }
            printf("\n\n");
            system("pause");
            break;

        case 2:                             //Descodificador
            system("cls");
            printf("* * * *    Descriptografar    * * * *\n\n");    //Aqui a lógica é a mesma do caso anterior, a diferença é que ao invés de avançar para a direita ele volta para a esquerda.

            printf("Insira a chave da codificacao de 0 a 26:\n");
            scanf("%d", &chave);

            if (chave >= 0 && chave <= 26) {
                while ((ch = getc(fonte)) != EOF) {
                    //printf("%c", ch);                 Linha de debug

                    ascii = ch;
                    temp = ascii - chave;                           //Esta é a diferença do caso anterior, ao invés de realizar uma soma do ASCII com a chave é feito uma subtração

                    if ((ascii != 32) && ((temp >= 65 && temp <= 90) || (temp >= 97 && temp <= 122))) {
                        ascii = temp;
                        ch2 = ascii;
                        fputc(ch2, novo);

                    } else if ((ascii >= 65 && ascii <= 90) || (ascii >= 97 && ascii <= 122)) {

                        if (ascii >= 65 && ascii <= 90) {
                            ascii = 90 + (temp - ascii);            //Por tanto, os caracteres vão retroceder ao invés de avançar
                        }
                        if (ascii >= 97 && temp <= 123) {
                            ascii = 123 + (temp - ascii);
                        }

                        ch2 = ascii;
                        fputc(ch2, novo);
                    } else {
                        ch2 = ascii;
                        fputc(ch2, novo);
                    }
                }
                printf("Arquivo descriptografado com sucesso!");

            } else {
                printf("Erro ao tentar descriptografar...\nNumero de codificacao invalido!");

            }

            printf("\n\n");
            system("pause");
            break;
    }

    fclose(fonte);                  //Para finalizar, os arquivos são fechados.
    fclose(novo);
    return 0;
}