#include<iostream>
#include<math.h>
#include<stdlib.h>

using namespace std;

const int _maxByte = 6;
const int _binSize = 8 * _maxByte;    //!!6 bytes

int _zeroBin[_binSize];    //!! Numero Binario de valor 0
int _unitaryBin[_binSize];   //!! Numero Binario de valor 1

int* somaBin(int binaryA[], int binaryB[]);
int* subBin(int binaryA[], int binaryB[]);
int* multBin(int binaryA[], int binaryB[]);
int* divBin(int binaryA[], int binaryB[], int resto[]);//!O resto é retornado
int* fatBin(int binary[]);

void showBinary(int binary[], int numByte);

void zerarBinary(int* binary);
void maxBinary(int* binary);

int compBinary(int binaryA[], int binaryB[]);//! retorna 1 se A>B; 0 se A==B; -1 A<B

int main()
{
    zerarBinary(_zeroBin);
    zerarBinary(_unitaryBin);
    _unitaryBin[0] = 1;

    int i;
    int binA[_binSize], binB[_binSize], *result, resto[_binSize];
    char operador = ' ';
    int menu;

    zerarBinary(binA);
    zerarBinary(binB);
    zerarBinary(resto);
    //!
    while(1){
        cout << "A = {";
        showBinary(binA, 1);
        cout << "};\n";
        cout << "B = {";
        showBinary(binB, 1);
        cout << "};\n";

        cout << "\n";
        cout << "RESULTADO = ";
        switch(operador){
        case '+':
            cout << "(SOMA) A + B = {";
            result = somaBin(binA, binB);
            showBinary(result, 1);
            break;
        case '-':
            cout << "(SUBTRACAO) A - B = {";
            if(compBinary(binA, binB)!=-1){
                result = subBin(binA, binB);
                showBinary(result, 1);
            } else{
                cout << "_B maior que A, resultado NEGATIVO_";
            }
            break;
        case '*':
            cout << "(MULTIPLICACAO) A * B = {";
            result = multBin(binA, binB);
            showBinary(result, 1);
            break;
        case '/':
            cout << "(DIVISAO) A / B = {";
            if(compBinary(binB, _zeroBin)!=0){
                result = divBin(binA, binB, resto);
                showBinary(result, 1);
                cout << "};\n            ";
                cout << "(RESTO) A % B = {";
                showBinary(resto, 1);
            } else{
                cout << "_B igual a 0, resultado INDEFINIDO_";
            }
            break;
        case '!':
            cout << "(FATORIAL) A! = {";
            result = fatBin(binA);
            showBinary(result, _maxByte);
            cout << "};\n            ";
            cout << "(FATORIAL) B! = {";
            result = fatBin(binB);
            showBinary(result, _maxByte);
            break;
        default:
            cout << "{";
        }
        cout << "};\n\n";

        cout << "1. Insira A;\n";
        cout << "2. Insira B;\n";
        cout << "3. Realizar Operacao;\n";
        cout << "0. SAIR";
        cout << "\nOpcao: ";
        cin >> menu;

        //!!!!!!!!!!!
        system("cls");

        switch(menu){
        case 1:
            cout << "Insira um binario equivalente a um 4 bits separados por espaco:\nEx.: 0 0 0 1\n";

            zerarBinary(binA);
            for(i=3; i>=0; i--){
                cin >> binA[i];
            }
            break;
        case 2:
            cout << "Insira um binario equivalente a um 4 bits separados por espaco:\nEx.: 0 0 0 1\n";

            zerarBinary(binB);
            for(i=3; i>=0; i--){
                cin >> binB[i];
            }
            break;
        case 3:
            cout << "Insira a operacao:(+, -, *, /, !):\n";
            cin >> operador;

            break;
        case 0:
            delete[] result;
            return 0;
        }
        //!!!!!!!!!!!
        system("cls");
    }
}

int* somaBin(int binaryA[], int binaryB[])
{
    int *result;
    int carryOn = 0;
    int bitSoma;
    int i;

    result = new int [_binSize];

    for(i=0; i<_binSize; i++){
        bitSoma = binaryA[i] + binaryB[i] + carryOn;

        switch(bitSoma){
        case 0:
            result[i] = 0;
            carryOn = 0;
            break;
        case 1:
            result[i] = 1;
            carryOn = 0;
            break;
        case 2:
            result[i] = 0;
            carryOn = 1;
            break;
        case 3:
            result[i] = 1;
            carryOn = 1;
            break;
        }
    }

    return result;
}

int* subBin(int binaryA[], int binaryB[])
{
    int *result, *auxBinA;
    int borrowed = 0;
    int bitSub;
    int i;

    auxBinA = new int[_binSize];
    result = new int[_binSize];
    zerarBinary(result);

    for(i=0; i<_binSize; i++)
    {
        auxBinA[i] = binaryA[i];
    }

    for(i=0; i<_binSize; i++){
        if(auxBinA[i]==1 && borrowed==1)
        {
            auxBinA[i] = 0;
            borrowed = 0;
        } else if(auxBinA[i]==0 && borrowed==1) auxBinA[i] = 1;

        bitSub = auxBinA[i] + binaryB[i];

        switch(bitSub){
        case 0:
            result[i] = 0;
            break;
        case 1:
            result[i] = 1;
            if(auxBinA[i] == 0){
                if(auxBinA[i+1]==1) auxBinA[i+1] = 0;
                else borrowed = 1;
            }
            break;
        case 2:
            result[i] = 0;
            break;
        }
    }

    delete[] auxBinA;

    return result;
}

int* multBin(int binaryA[], int binaryB[])
{
    int i;
    int *parcial, *result, *aux, *auxBinB;

    parcial = new int[_binSize];
    zerarBinary(parcial);
    result = parcial;

    aux = new int[_binSize];
    for(i=0; i<_binSize; i++){
        aux[i] = binaryB[i];
    }
    auxBinB = aux;

    while(compBinary(auxBinB, _zeroBin)==1){
        result = somaBin(result, binaryA);

        auxBinB = subBin(auxBinB, _unitaryBin);
    }

    delete[] aux;

    return result;
}

int* divBin(int binaryA[], int binaryB[], int resto[])//!o resto é retornado
{
    int i;
    int *result, *parcial, *auxBinA;

    parcial = new int[_binSize];
    zerarBinary(parcial);
    result = parcial;

    auxBinA = binaryA;

    while(compBinary(binaryA, _zeroBin)==1 && compBinary(auxBinA, binaryB)!=-1){

        auxBinA = subBin(auxBinA, binaryB);

        result = somaBin(result, _unitaryBin);
    }

    for(i=0; i<_binSize; i++)
    {
        resto[i] = auxBinA[i];
    }

    delete[] auxBinA;

    return result;
}

int* fatBin(int binary[])
{
    int i;
    int *result, *parcial, *auxBin;

    parcial = new int[_binSize];
    zerarBinary(parcial);
    parcial[0] = 1;
    result = parcial;//!result aponta para um binario de valor 1

    auxBin = binary;

    while(compBinary(auxBin, _zeroBin)==1){
        result = multBin(result, auxBin);

        auxBin = subBin(auxBin, _unitaryBin);
    }

    delete[] auxBin;

    return result;
}

int compBinary(int binaryA[], int binaryB[])
{
    int i;
    int pesoA=0, pesoB=0;

    for(i=0; i<_binSize; i++){
        if(binaryA[i]==1) pesoA += i+1;
        if(binaryB[i]==1) pesoB += i+1;
    }

    if(pesoA > pesoB) return 1;
    else if(pesoA < pesoB) return -1;
    else return 0;
}

void zerarBinary(int* binary)
{
    int i;

    for(i=0; i<_binSize; i++){
        binary[i] = 0;
    }
}

void maxBinary(int* binary)
{
    int i;

    for(i=0; i<_binSize; i++){
        binary[i] = 1;
    }
}

void showBinary(int binary[], int numByte)
{
    int i;

    for(i=(numByte*8)-1; i>=0; i--){
        cout << binary[i];
        if(i%4==0 && i!=0) cout << " ";
    }

    //cout << "\n";
}
