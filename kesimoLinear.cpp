#include <iostream>
#include <vector>
#include <algorithm>
#include "PPH.hpp"

using namespace std;


vector<parOrdenado> partition(vector<parOrdenado> &val, float chave){
    vector<parOrdenado> lDireito; //Lado Direito da chave
    unsigned i;

    for(i=0; i<val.size();i++){
        if(val[i].razao>chave){
            lDireito.push_back(val[i]);
        }
    }

    return lDireito;
}

parOrdenado encontraMediana(vector<parOrdenado> vec){
    parOrdenado median = vec[(vec.size()/2)];
    return median;
}

parOrdenado encontraMedianaDasMedianas(vector<vector<parOrdenado> > values){
    vector<parOrdenado> medians;

    for (unsigned i = 0; i < values.size(); i++) {
        parOrdenado m = encontraMediana(values[i]);
        medians.push_back(m);
    }

    return encontraMediana(medians);
}

float selectionByMedianOfMedians(const vector<parOrdenado> values,unsigned pos){

    vector<vector<parOrdenado> > vec2D;
    ///Divide a entrada em grupos de tamanho 5
    unsigned count = 0;
    while (count != values.size()) {
        int countRow = 0;
        vector<parOrdenado> row;

        while ((countRow < 5) && (count < values.size())) {
            row.push_back(values[count]);
            count++; //Aumenta o número total de elementos do vetor já visitado
            countRow++; //Garante que seja dividido em grupos de 5
        }
        vec2D.push_back(row);
    }

    /*cout<<endl<<endl<<"Printing 2D vector : "<<endl;
    for (unsigned i = 0; i < vec2D.size(); i++) {
        for (unsigned j = 0; j < vec2D[i].size(); j++) {
            cout<<vec2D[i][j].razao<<" ";
        }
        cout<<endl;
    }
    cout<<endl;*/
    ///Calcula a Mediana das Medianas
    parOrdenado medianaDaMediana = encontraMedianaDasMedianas(vec2D);
    //cout<<"Mediana da Mediana : "<<medianaDaMediana.razao<<endl;

    ///Divide a entrada em dois grupos:
    ///Maiores que a mediana
    ///Menores que a mediana
    vector<parOrdenado> L1, L2;

    for (unsigned i = 0; i < vec2D.size(); i++) {
        for (unsigned j = 0; j < vec2D[i].size(); j++) {
            if (vec2D[i][j].razao > medianaDaMediana.razao) {
                L1.push_back(vec2D[i][j]);
            }else if (vec2D[i][j].razao < medianaDaMediana.razao){
                L2.push_back(vec2D[i][j]);
            }
        }
    }

    /*cout<<endl<<"Imprimir vetor L1 : "<<endl;
    for (int i = 0; i < L1.size(); i++) {
        cout<<L1[i].razao<<" ";
    }

    cout<<endl<<"Imprimir vetor L2 : "<<endl;
    for (int i = 0; i < L2.size(); i++) {
        cout<<L2[i].razao<<" ";
    }*/

    if ((pos - 1) == L1.size()) {
        return medianaDaMediana.razao;
    }else if (pos <= L1.size()) {
        return selectionByMedianOfMedians(L1, pos);
    }else{
        return selectionByMedianOfMedians(L2, pos-((int)L1.size())-1);
    }
}
