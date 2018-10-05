#include <iostream>
#include <sstream>
#include <map>
#include <vector>
#include <algorithm>

using namespace std;

class Aluno{
    string matricula;
    string curso;
    string nome;
public:
    Aluno(string matricula = " ", string curso=" ", string nome=" "){
        this->matricula = matricula;
        this->curso = curso;
        this->nome = nome;
    }

    string toString(){
        stringstream ss;
        ss << "[" << this->matricula << ":" << this->curso <<":" << this->nome<<"]";
        return ss.str();
    }

};


class  Professor{
    string nome;
    string siape;
    string nivel;    
public:

    Professor(string nome = " ", string siape= " ", string nivel=" "){
        this->nome = nome;
        this->siape = siape;
        this->nivel = nivel;
    }

    string toString(){
        stringstream ss;
        ss << "[" << this->nome << ":" << this->siape <<":"<< this->nivel<<"]";
        return ss.str();
    }


};

class Disciplina{
    string codigo;
    string curso;
    string nome;
public:
    Disciplina(string codigo = " ", string curso=" ", string nome=" "){
        this->codigo = codigo;
        this->curso = curso;
        this->nome = nome;
    }

    string toString(){
        stringstream ss;
        ss << "[" << this->codigo << ":" << this->curso <<":" << this->nome<<"]";
        return ss.str();
    }

};

template<typename T>

class Repositorio{
    map<string,T> data;
public:
    void add(string chave, T elem){
        auto it = data.find(chave);
        if( it == data.end()){
            data.insert(make_pair(chave,elem));
        }
        else throw "ja existe";
    }

    void rm(string chave){
        auto it = data.find(chave);
        if( it != data.end()){
            data.erase(chave);
        }else throw "não existe";
    }

    string get(string chave){
        for(auto par : data){
            if(par.first == chave){
                return par.second.toString();
            }
        }
        throw "não existe";
    }

    string toString(){
        stringstream ss;
        for(auto par : data){
            ss << par.second.toString()<<endl;
        }
        return ss.str();
    }

};


struct Controller{
    Repositorio<Aluno>repA;
    Repositorio<Professor>repP;
    Repositorio<Disciplina>repD;
    
    string shell(string line){
        stringstream ss(line);
        stringstream saida;
        string op;
        ss >> op;
        // aluno
        if(op=="addAlu"){
            string matricula;
            string curso, nome;
            ss >> matricula >> curso >> nome;
            repA.add(matricula, Aluno(matricula,curso,nome));
        }
        else if(op == "rmAlu"){
            string matricula;
            ss >> matricula;
            repA.rm(matricula);
        }
        else if(op == "getAlu"){
            string matricula;
            ss >> matricula;
            saida << repA.get(matricula)<<endl;
        }
        else if(op == "showAlu"){
            saida << repA.toString();
        }
        // professor
        else if(op=="addPro"){
            string nome, siape, nivel;
            ss >> nome >> siape >> nivel;
            repP.add(nome, Professor(nome,siape,nivel));
        }
        else if(op == "rmPro"){
            string nome;
            ss >> nome;
            repP.rm(nome);
        }
        else if(op == "getPro"){
            string nome;
            ss >> nome;
            saida << repP.get(nome)<<endl;
        }
        else if(op == "showPro"){
            saida << repP.toString();
        }
        // disciplina
        else if(op=="addDis"){
            string codigo, curso, nome;
            ss >> codigo >> curso >> nome; 
            repD.add(codigo, Disciplina(codigo,curso,nome));
        }
        else if(op == "rmDis"){
            string codigo;
            ss >> codigo;
            repD.rm(codigo);
        }
        else if(op == "getDis"){
            string codigo;
            ss >> codigo;
            saida << repD.get(codigo)<<endl;
        }
        else if(op == "showDis"){
            saida << repD.toString();
        }

        return saida.str();
    }

    void exec(){      
        while(true){
            string line;
            getline(cin,line);
            if(line == "end")
                break;
            try{    
                cout<<shell(line);
            }catch(const char *e){
                cout<<e<<endl;
            }

        }
    }

};

int main(){

    Controller control;
    control.exec();

    return 0;
}