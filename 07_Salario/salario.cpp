#include <iostream>
#include <sstream>
#include <map>
#include <vector>
#include <algorithm>

using namespace std;

class Funcionario{

string nome;
    int max_diarias;
    int diarias;
    int bonus;

public:

    Funcionario(string nome,int max){
        this->nome = nome;
        this->max_diarias = max;
    }

    virtual void setBonus(int bonus){
        this->bonus = bonus;

    }

    virtual void addDiaria(){
        this->diarias += 1;
        if(this->diarias > this->max_diarias){
            this->diarias = this->max_diarias;
            throw "não pode mais receber diarias";
        }
    }

    virtual string toString() = 0;
     
    virtual string getNome(){
        return this->nome;
    }

    virtual int getDiarias(){
        return this->diarias;
    }

    virtual int getBonus(){
        return this->bonus;
    }


};


class Professor : public Funcionario{
    char classe;
    int salario;
public:
    Professor(string nome, char classe) : 
    Funcionario(nome,2),classe(classe){

        if(classe == 'a'||classe == 'A')
            this->salario = 3000;
        else if(classe == 'b'||classe == 'B')
            this->salario = 5000;
        else if(classe == 'c'||classe == 'C')
            this->salario = 7000;
        else if(classe == 'd'||classe == 'D')
            this->salario = 9000;
        else if(classe == 'e'||classe == 'E')
            this->salario = 11000;
    }

    virtual int calcSalario(){
        return this->salario + (getDiarias() * 100) + getBonus();
        
    }


    virtual string toString(){
        stringstream ss;
        ss <<"Professor"<<" "<<getNome()<<" "<<"classe:"<<" "<<this->classe<<"\n"<<"Salário:"<<" "<<calcSalario();
        return ss.str();
    }

};



class STA : public Funcionario{
    int nivel;
    int salario = 3000;
public:
    STA(string nome, int nivel):
    Funcionario(nome,1),nivel(nivel)
    { 

    }

    virtual  int calcSalario(){
        return salario + (nivel * 300) + (getDiarias() * 100) + getBonus();
    }

    virtual string toString(){
        stringstream ss;
        ss <<"STA"<<" "<<getNome()<<" "<<"Nivel:"<<" "<<this->nivel<<"\n"<<"Salario:"<<" "<<calcSalario();
        return ss.str();
    }

};


class Terceirizado : public Funcionario{
    int horas_trab;
    bool insalubre;
public:

    Terceirizado(string nome, int horas,bool insalubre):
    Funcionario(nome,0),horas_trab(horas),insalubre(insalubre)
    {

    }

    virtual int calcSalario(){
        if(this->insalubre)
            return (4 * this->horas_trab) + 500 + getBonus();
        else return 4 * horas_trab;
    }

    virtual string toString(){
        stringstream ss;
        ss <<"Terceirizado"<<" "<<getNome()<<" "<<this->horas_trab<<" "<<this->insalubre<<"\n"<<"Salário:"<<" "<<calcSalario();
        return ss.str();
    }

};


template<typename T>

struct Repositorio{
    map <string, T> dados;

    void addFuncionario(string nome, T elem){
        auto it = dados.find(nome);
        if(it == dados.end()){
            dados.insert(make_pair(nome,elem));
        }
        else throw "Funcionário já existe";
    }

    void rmFuncionario(string nome){
        auto it = dados.find(nome);
        if(it != dados.end()){
            dados.erase(nome);
        }
        else throw "Funcionário já existe";

    }

    string toString(string nome){
        stringstream ss;
        for(auto par : dados){
            if(par.first == nome){
                ss << par.second->toString();
                return ss.str();
            }               
        }
        throw "funcionario não existe";

    }
    
    void addDiaria(string nome){
        auto it = dados.find(nome);
        if(it != dados.end()){
            it->second->addDiaria();
        }
        else throw "funcionário não existe";
    }

    void setBonus(int bonus){
        bonus = bonus/dados.size();
        for(auto& par : dados){
            par.second->setBonus(bonus);
        }
    }
    

};



class Controller{
    Repositorio<Funcionario*> Rep;
public:
    string shell(string line){
        stringstream ss(line);
        stringstream saida;
        string op;
        ss >> op;

        //adicionar funcionarios
        if(op == "addProf"){
            string nome;
            char c;
            ss >> nome;
            ss >> c;
            if(c == 'a'||c == 'A'||c == 'b'||c == 'B'||c == 'c'||c == 'C'||c == 'd'||c == 'D'||c == 'e'||c == 'E'){
            Rep.addFuncionario(nome,new Professor(nome,c));
            saida << "ok";
            } 
            else throw "classe inválida";

        }
        else if(op == "addSta"){
            string nome;
            int nivel;
            ss >> nome;
            ss >> nivel;
            Rep.addFuncionario(nome,new STA(nome,nivel));
            saida << "ok";
        }
        else if(op == "addTer"){
            string nome;
            int horas;
            bool insalubre;
            string var;
            ss >> nome;
            ss >> horas;
            ss >> var;
            if(var == "sim") 
                insalubre = true;
            else 
                insalubre = false;

            Rep.addFuncionario(nome,new Terceirizado(nome,horas,insalubre));
            saida << "ok";
        }
        
        //remover funcionarios
        else if(op == "rm"){
            string nome;
            ss >> nome;
            Rep.rmFuncionario(nome);
            saida << "ok";
        }


        // Show funcionarios

        else if(op == "show"){
            string nome;
            ss >> nome;
            saida << Rep.toString(nome);
        }

        //Adicionar diarias
        else if(op == "addDiaria"){
            string nome;
            ss >> nome;
            Rep.addDiaria(nome);
            saida <<"ok";
        }

        // SetBonus
        else if(op == "setBonus"){
            int bonus;
            ss >> bonus;
            Rep.setBonus(bonus);
            saida <<"ok";
        }
        else saida << "opção invalida";

        return saida.str();
    }

    void exec(){
        string line;
        while(true){
            getline(cin,line);
            if(line == "end")
                break;
            try{
                cout<<shell(line)<<endl;
            
            }catch(const char * e){
                cout<< e << endl;
            }

        }
        
    }


};


int main(){
    Controller control;
    control.exec();
    
    return 0;
}