
#include <iostream>
#include <sstream>
#include <map>
#include <vector>
#include <algorithm>

using namespace std;

class Disciplinas;

class Aluno{
    string id;
    vector <Disciplinas*> vecDisc;
public:

    Aluno(string id):id(id)
    {

    }


    void Matricular(Disciplinas *disc){
        vecDisc.push_back(disc);

    }

    void Desmatricular(string idDisc);

    string getName(){
        return id;
    }

    string toString();

};

class Disciplinas{
    string idDisc;
    vector<Aluno*> vecAlu;
public:
    Disciplinas(string id):idDisc(id)
    {

    }

    void Matricular(Aluno *aluno){
        bool teste = true;
        for(int i=0;i<(int)vecAlu.size();i++){
            if(aluno->getName()== vecAlu[i]->getName())
                teste = false;
        }        
        if(teste){
            aluno->Matricular(this);
            vecAlu.push_back(aluno);
        }
        
    }

    void Desmatricular(string idAluno){
        for(int i=0;i<(int)vecAlu.size();i++){
            if(idAluno == vecAlu[i]->getName()){
                vecAlu[i]->Desmatricular(this->getName());
                vecAlu.erase(vecAlu.begin() + i);
            }
        }   
        
    }

    string getName(){
        return idDisc;
    }
    
    string toString(){
        stringstream ss;
        for(auto aux : vecAlu){
            ss << " "<< aux->getName();
        }
        return ss.str();
    }

};

string Aluno::toString(){
    stringstream ss;
    for(int i=0; i <(int)vecDisc.size();i++){
        ss << " "<< vecDisc[i]->getName();
    }
    return ss.str();
}

void Aluno::Desmatricular(string idDisc){
    for(int i=0;i<(int)vecDisc.size();i++){
        if(idDisc == vecDisc[i]->getName())
            vecDisc.erase(vecDisc.begin() + i);        
    }   
}



template<typename T>
class Repositorio{
    map <string , T> dados;
public:
    void add(string nome, T elem){
        auto it = dados.find(nome);
        if(it == dados.end()){
            dados.insert(make_pair(nome,elem));
        }      
    }

    bool check(string nome){
        auto it = dados.find(nome);
        if(it != dados.end()){
            return true;
        }
        return false;
    }

    T& get(string nome){
        auto it = dados.find(nome);
        return it->second;
    }

    void rm(string nome){ 
        if(dados.find(nome) != dados.end()){
            dados.erase(nome);
        }
    }

    string toString(){
        stringstream ss;
        for(auto par : dados){
            ss << par.first<<" "<<"["<<par.second.toString()<<"]"<<"\n";
        }
        return ss.str();
    }

};

class Controller{
    Repositorio<Aluno> RepAlu;
    Repositorio<Disciplinas> RepDis;
public:
    string shell(string line){
        stringstream saida;
        stringstream ss(line);
        string op;
        ss >> op;

        if(op == "addAlu"){
            while(ss >> op){
                RepAlu.add(op,Aluno(op));
            }
        }

        else if(op == "addDis"){
            while(ss >> op){
                RepDis.add(op,Disciplinas(op));
            }
        }
        else if(op == "show"){
            saida<<"alunos:"<<endl;
            saida<< RepAlu.toString();
            saida<<"disciplinas:"<<endl;
            saida<< RepDis.toString();
        }
        else if(op == "mat"){
            string nome;
            ss >> nome;
            while(ss >> op){
                if(RepDis.check(op)){
                    if(RepAlu.check(nome)){
                        Aluno& alu = RepAlu.get(nome);
                        Disciplinas& dis = RepDis.get(op);
                        dis.Matricular(&alu);
                    }
                }                               
            }
        }
        else if(op == "rmMat"){
            string nome;
            ss >> nome;
            while(ss >> op){
                Disciplinas& dis = RepDis.get(op);
                dis.Desmatricular(nome);
            }
        }
        else if(op == "rmAlu"){
            string nome;
            ss >> nome;
            Aluno& alu = RepAlu.get(nome);
            string disc = alu.toString();
            stringstream aux(disc);

            while(aux >> op){
                Disciplinas& dis = RepDis.get(op);
                dis.Desmatricular(nome);                                         
            }
            RepAlu.rm(nome);
        }
        else throw "está opção não existe";

        return saida.str();

    }

    void exec(){
        string line;
        while(true){
            getline(cin,line);
            if(line == "end")
                break;
            try{
                cout<<shell(line);
            
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