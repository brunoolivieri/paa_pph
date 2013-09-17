#ifndef PPH_H
#define PPH_H

#define TRUE 1
#define FALSE 0

#include <vector>
#include <fstream>
#include <iostream>
#include <chrono> ///gcc -std=gnu++0x

typedef std::chrono::milliseconds milliseconds;

using namespace std;

typedef struct par{
    unsigned a;
    unsigned b;
    float razao;
    par(unsigned a) : a(a){};
    par(unsigned a,unsigned b,float razao) : a(a),b(b),razao(razao){};
}parOrdenado;

class PPH
{
    public:
        /// Nome do arquivo de entrada e vetor onde será armazenado a entrada
        PPH(const char * fileName,std::vector<parOrdenado> &input);
        /// Restaura todos atributos para os estados iniciais após a leitura da entrada
        void restauraEstadoInicial();
        /// Retorna do polinômio de entrada
        unsigned getGrau();
        /// Escreve no arquivo de texto os pares ordenados que maximizam o PPH
        void writeOutput(const char * estrategia,milliseconds time,unsigned iteracoes);
        /// Verifica se par ordenado na posição pos deve entrar na conta do PPH
        unsigned inserePar(parOrdenado par);
        /// Retorna a razão atual do PPH
        float getRazao();
        /// Verifica se todos pares de S satisfazem o lema
        unsigned validaLema();
    protected:
    private:
        unsigned grau;
	unsigned grau_original;
        const char * nomeArquivo;
        std::vector<parOrdenado> resultado;
        unsigned numerador,denominador;
};

#endif // PPH_H
