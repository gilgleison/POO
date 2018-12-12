#include <iostream>
#include <sstream>
#include <vector>

using namespace std;


class Conta{
    float saldo;
    int numero;
public:
    Conta(int numero = 0){
        this->numero=numero;
        this->saldo=0;
    }

    void setValue(float value = 0){
        this->saldo=value;
    }

    float getValue(){
        return this->saldo;
    }

    int getNum(){
        return this->numero;
    }

    string toString(){
        stringstream ss;
        ss << "conta:"<<this->numero<<" "<<"saldo:"<<this->saldo;
        return ss.str();
    }

};

// struct Extrato{
//     string operação;
//     float valor;
//     float valConta;
// }

struct Caixa{
    
    static bool saque(Conta &conta, float value){
        float var;
        var = conta.getValue();
        var -= value;
        if(var<0) return false;
        conta.setValue(var);
        return true;
    }

    static string saldo(Conta conta){
        return conta.toString();
    }

    static bool deposito(Conta &conta,float value){
        if(value < 0) return false;
        conta.setValue(conta.getValue()+value);
        return true;
    }
};


struct Controller{

    Conta conta;
    
    string shell(string line){
        stringstream ss(line);
        stringstream saida;
        string op;
        ss >> op;

        if(op=="init"){
            int num;
            ss >> num;
            conta = Conta(num);
            saida<<"ok";
        }
        else if(op=="deposito"){
            float valor;
            ss >> valor;
            if(Caixa::deposito(conta,valor))
                saida<<"ok";
            else 
                saida<<"valor invalido";
        }
        else if(op=="saque"){
            float valor;
            ss >> valor;
            if(Caixa::saque(conta,valor))
                saida<<"ok";
            else 
                saida<<"saldo insuficiente";

        }
        else if(op == "show"){
            saida<<Caixa::saldo(conta);

        }

        return saida.str();
    
    }

    void exec(){
        string line;
        while(true){
            getline(cin,line);
            if(line=="end") break;
            cout<<shell(line)<<endl;
        }
        
    }


};

int main(){
    Controller control;
    control.exec();

    return 0;
}
