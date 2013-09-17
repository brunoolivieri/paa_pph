#include "PPH.hpp"
#include <stdio.h>
#include <stdlib.h>
#include <iostream>

PPH::PPH(const char * fileName, std::vector<parOrdenado> &input){
    unsigned element;
    nomeArquivo = fileName;
    FILE * in = fopen(fileName,"r");

    if(!in){
        printf("Nao foi possivel abrir o arquivo %s\n",fileName);
        exit(EXIT_FAILURE);
    }
    fscanf(in,"%d",&grau);
    grau_original = grau;
    fscanf(in,"%d",&numerador);

    //Ler os Ai's
    for(unsigned i=0; i<grau; i++){
        fscanf(in,"%d",&element);
        input.push_back(parOrdenado(element));
    }
    fscanf(in,"%d",&denominador);
    //Ler os Bi's
    for(unsigned i=0; i<grau; i++){
        fscanf(in,"%d",&element);
        input.at(i).b = element;
    }

    //Calcula razao
    for(unsigned i=0; i<grau; i++){
        if(input.at(i).b == 0){
            input[i] = input.back();
            input.pop_back();
            i--;
            grau--;
        } else {
            input.at(i).razao = input.at(i).a / (float)input.at(i).b;
        }
    }
    //Adiciona o a0 e b0 à lista dos elementos que contribuem na maximação
    resultado.push_back(parOrdenado(numerador,denominador,numerador/(float)denominador));
    fclose(in);
}

/// Verifica se todos pares de S satisfazem o lema - exceto a0/b0
/// Retorna a quantidade de elementos que não satisfazem
unsigned PPH::validaLema(){
    float razao;
    unsigned qtd = 0;
    for(unsigned i=1;i<resultado.size();i++)
    {
        razao = (numerador - resultado[i].a) / (float) (denominador - resultado[i].b);
        if(resultado[i].razao<razao)
        {
            /// Incrementa a quantidade de par removidos
            qtd++;
            /// Atualiza os dados sem o elemento
            numerador = numerador - resultado[i].a;
            denominador = denominador - resultado[i].b;
            razao = numerador / (float) denominador;

            ///Remove o elemento
            resultado[i] = resultado.back();
            resultado.pop_back();

            i--; /// Reajusta o ponteiro
        }
    }
    return qtd;
}

unsigned PPH::inserePar(parOrdenado par){
    if( numerador/(float)denominador < par.razao){
        numerador += par.a;
        denominador += par.b;
        resultado.push_back(par);
        return TRUE;
    } else {
        return FALSE;
    }
}

float PPH::getRazao(){
    return numerador/(float)denominador;
}

void PPH::writeOutput(const char * estrategia,milliseconds time,unsigned iteracoes){
    ofstream out;
    out.open("resultados.txt",ofstream::out | ofstream::app);
    //out << "Pares na saída: " << resultado.size() << endl;
    //out << "Razao: " << numerador/(float) denominador << endl;
    //out << "Estratégia;Entrada;tempo(miliseg);Iteracoes;Tempo Medio;R*;S*" << endl;
    out << estrategia << ";" << grau_original << ";" << time.count() << ";" << iteracoes
    << ";" << time.count()/(float)iteracoes << endl;
    out.close();
}

unsigned PPH::getGrau(){
    return grau;
}

/// Restaura todos atributos para os estados iniciais após a leitura da entrada
void PPH::restauraEstadoInicial(){
    parOrdenado backup = resultado[0];
    resultado.clear();
    numerador = backup.a;
    denominador = backup.b;
    resultado.push_back(backup);
}
