#include <stdio.h>
#include <stdlib.h>
#include "conta.h"

void insere_5_funcionarios(FILE *out) {
    printf("Inserindo 5 funcionários no arquivo...");

    Conta *f1 = cont(1,3123,300);
    salva(f1, out);
    free(f1);
    Conta *f2 = cont(2,3123,200);
    salva(f2, out);
    free(f2);
    Conta *f3 = cont(3,3123,100);
    salva(f3, out);
    free(f3);
    Conta *f4 = cont(4,3123,400);
    salva(f4, out);
    free(f4);
    Conta *f5 = cont(5,3123,40);
    salva(f5, out);
    free(f5);
}

void le_funcionarios(FILE *in) {
    printf("\n\nLendo contas do arquivo...\n\n");
    rewind(in);
    Conta *f;
    while ((f = le(in)) != NULL) {
        imprime(f);
        free(f);
    }
}

void le_segundo_funcionario(FILE *in) {
    printf("\n\nLendo segunda conta do arquivo...\n\n");
    //tamanho() indica quantos bytes vamos pular, o que aqui é igual ao tamanho de um registro
    //(vamos pular o primeiro e nos posicionar no início do segundo)
    //** ATENÇÃO: não usar sizeof(Conta), pois ele pode retornar valor maior que o tamanho ocupado em disco,
    //            devido a alinhamento automático (ver https://en.wikipedia.org/wiki/Data_structure_alignment))
    //SEEK_SET indica o início do arquivo
    //ao final, o cursor estará posicionado em 0 + tamanho() +1
    fseek(in, tamanho(), SEEK_SET);
    Conta *f = le(in);
    if (f != NULL) {
        imprime(f);
        free(f);
    }
}

void adiciona_funcionario(FILE *in) {
    printf("\n\nAdicionando funcionário no final do arquivo...\n\n");
    //pula 5 registros para posicionar no início do final do arquivo
    fseek(in, tamanho() * 5, SEEK_SET);
    Conta *f = cont(6,3123,400.00);
    salva(f, in);
    free(f);

    //lê funcionário que acabou de ser gravado
    //posiciona novamente o cursor no início desse registro
    fseek(in, tamanho() * 5, SEEK_SET);
    Conta *f6 = le(in);
    if (f6 != NULL) {
        imprime(f6);
        free(f6);
    }
}

void sobrescreve_quarto_funcionario(FILE *in) {
    printf("\n\nSobrescrevendo quarto funcionário do arquivo...\n\n");
    //pula primeiros 3 registros para posicionar no início do quarto registro
    fseek(in, tamanho() * 3, SEEK_SET);
    Conta *f4 = cont(7,3123,400.00);
    salva(f4, in);
    free(f4);

    //lê funcionário que acabou de ser gravado
    //posiciona novamente o cursor no início desse registro
    fseek(in, tamanho() * 3, SEEK_SET);
    Conta *f = le(in);
    if (f != NULL) {
        imprime(f);
        free(f);
    }
}

int main(int argc, char** argv) {
    //declara ponteiro para arquivo
    FILE *out;
    //abre arquivo
    if ((out = fopen("funcionario.dat", "w+b")) == NULL) {
        printf("Erro ao abrir arquivo\n");
        exit(1);
    }
    else {
        //insere funcionários
        insere_5_funcionarios(out);
        //volta ao início do arquivo e lê os funcionários inseridos
        le_funcionarios(out);
        //volta ao início do arquivo e lê o segundo funcionário
        //le_segundo_funcionario(out);
        //grava mais um funcionário no final do arquivo
        //adiciona_funcionario(out);
        //sobrescreve quarto funcionário
        //sobrescreve_quarto_funcionario(out);
        //lendo o arquivo todo novamente
        //le_funcionarios(out);
        
        //fecha arquivo
        fclose(out);    
    }
}

