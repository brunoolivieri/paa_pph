#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <chrono> ///gcc -std=gnu++0x
#include "mergesort.hpp"
#include "PPH.hpp"
#include "kesimoLinear.hpp"

using namespace std;

vector<parOrdenado> elementos;

typedef std::chrono::high_resolution_clock Clock;
typedef std::chrono::milliseconds milliseconds;

std::chrono::milliseconds refTime(5000);   // Rodar pelo menos 5 segundos
Clock::time_point t0,t1;
milliseconds tBruteForce,tMergeSort,tLinear,tBestPivot;

void bruteForce(PPH &pph,vector<parOrdenado> &vElementos){
    unsigned last = vElementos.size();

     while(last!=0){
        unsigned max = 0;

        for(unsigned i=1;i<last;i++){
            if(vElementos[i].razao>vElementos[max].razao){
                max = i;
            }
        }

        pph.inserePar(vElementos[max]);
        parOrdenado temp = vElementos[last-1];
        vElementos[last-1] = vElementos[max];
        vElementos[max] = temp;
        last--;
    }
    /*for(unsigned i=0;i<elementos.size();i++){
        /// Se o par for inserido
        if(pph.inserePar(elementos[i])){
            pph.validaLema(); ///Verifica se todos elementos de S satisfaz o lema
        }
    }*/
}

void ordenando(PPH &pph){
    elementos = mergesortvector(elementos);
    unsigned entrou = TRUE;
    for (unsigned i = 0; i < elementos.size(); ++i)
    {
        entrou = pph.inserePar(elementos[i]);
        if(!entrou)
            i = elementos.size();
    }
}

void kesimo(PPH &pph,vector<parOrdenado> &vElementos){
    float elem = selectionByMedianOfMedians(vElementos,vElementos.size()/2);
    for(unsigned i=0; i<vElementos.size();i++){
        if(vElementos[i].razao > elem){
            pph.inserePar(vElementos[i]);
        }
    }
}

void melhorPivot(PPH &pph,vector<parOrdenado> &vElementos){
    vector<parOrdenado> lDireito = partition(vElementos,pph.getRazao());
    unsigned posMax;
    while(!lDireito.empty()){

        posMax = 0;

        for(unsigned i=1;i<lDireito.size();i++){
            if(lDireito[posMax].razao<lDireito[i].razao){
                posMax = i;
            }
        }

        pph.inserePar(lDireito[posMax]);
        ///Exclui elemento que entrou
        lDireito[posMax] = lDireito.back();
        lDireito.pop_back();
        partition(lDireito,pph.getRazao());
    }
}

int main(int argc,char ** argv)
{
    vector<parOrdenado> vElmCopia;
    unsigned iteracoes = 0;

    if(argc<3){
        printf("Informe uma estrategia e pelo menos um arquivo de entrada\n");
        exit(0);
    }

    for(int i = 2; i<argc;i++){
        printf("Arquivo de Entrada %s \n",argv[i]);
        /// Faz a leitura da entrada e já coloca a0/bo no conjunto de saída
        PPH pph(argv[i],elementos);
        vector<parOrdenado> copiaElementos(elementos);
        switch((int)(argv[1][0] - '0')){
            case 0:{ //Força Bruta
                printf("Algoritmo de Forca Bruta selecionado \n");
                t0 = Clock::now(); ///Marca Início de Tempo
                do{
                    iteracoes++;
                    pph.restauraEstadoInicial();
                    bruteForce(pph,copiaElementos);
                    t1 = Clock::now(); ///Marca Fim de Tempo
                    tBruteForce = std::chrono::duration_cast<std::chrono::milliseconds>(t1 - t0);
                }while(tBruteForce<refTime);
                pph.writeOutput("Força Bruta",tBruteForce,iteracoes);
                break;
             }case 1:{
                //Merge Sort
                printf("Algoritmo de Ordenacao Selecionado \n");
                t0 = Clock::now(); ///Marca Início de Tempo Tempo
                do{
                    iteracoes++;
                    pph.restauraEstadoInicial();
                    ordenando(pph);
                    t1 = Clock::now(); ///Marca Fim de Tempo
                    tMergeSort = std::chrono::duration_cast<std::chrono::milliseconds>(t1 - t0);
                }while(tMergeSort<refTime);
                pph.writeOutput("Merge Sort",tMergeSort,iteracoes);
                break;
            }case 2:{
                printf("Algoritmo do Kesimo Selecionado");
                t0 = Clock::now(); ///Marca Tempo
                do{
                    iteracoes++;
                    pph.restauraEstadoInicial();
                    kesimo(pph,copiaElementos);
                    t1 = Clock::now(); ///Marca Fim de Tempo
                    tLinear = std::chrono::duration_cast<std::chrono::milliseconds>(t1 - t0);
                }while(tLinear<refTime);
                 pph.writeOutput("Kesimo Linear Modificado",tLinear,iteracoes);
                break;
            }case 3:{
                // Questao 4
                printf("Algoritmo do Piviot Pre-estabelecido \n");
                t0 = Clock::now(); ///Marca Tempo
                do{
                    iteracoes++;
                    pph.restauraEstadoInicial();
                    melhorPivot(pph,copiaElementos);
                    t1 = Clock::now(); ///Marca Fim de Tempo
                    tBestPivot = std::chrono::duration_cast<std::chrono::milliseconds>(t1 - t0);
                }while(tBestPivot<refTime);
                pph.writeOutput("Best Pivot",tBestPivot,iteracoes);
                break;
            }default:
                printf("Numero do algoritmo selecionado invalido\n");
                printf("Algoritmo: 0 (zero): O(n^2) \n");
                printf("Algoritmo: 1 (um): O(nlogn) \n");
                printf("Algoritmo: 2 (dois): O(n) \n");
                printf("Algoritmo: 3 (tres): Quarta questao \n");
        }

    }
}
