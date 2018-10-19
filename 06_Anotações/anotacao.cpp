#include <iostream>
#include <sstream>
#include <map>
#include <vector>
#include <algorithm>

using namespace std;

class Notas{
    string titulo;
    string nota;
public:
    Notas(string titulo, string nota){
        this->nota = nota;
        this->titulo = titulo;
    }

    string toString(){
        stringstream ss;
        ss << "[" << this->titulo << ":" << this->nota << "]"<<endl;
        return ss.str();
    }    
};


class User{
    string nome;
    map<string,Notas> notas;
    string senha;
public:
    User(string nome,string senha){
        this->nome = nome;
        this->senha = senha;
    }

    void addNote(string titulo,string nota){
        auto it = notas.find(titulo);
        if(it != notas.end()) 
            throw"titulo já existe";
        notas.insert(make_pair(titulo,Notas(titulo,nota)));
    }
    
    void changePass(string oldPass, string newPass){
        if(this->senha == oldPass)
            this->senha = newPass;
        else 
            throw "senha errada";
    }

    string getPass(){
        return this->senha;
    }

    void rmNote(string titulo){
        auto it = notas.find(titulo);
        if(it != notas.end()){
            notas.erase(titulo);
        }
        else throw "nota não existe";
    }

    string toString(){
        stringstream ss;
        for(auto par : notas){
            ss << par.second.toString();
        }
        return ss.str();
    }

};


class Sistema{
    map<string,User> users;
    
public:

    void addUser(string nome,string senha){
        auto it = users.find(nome);
        if(it != users.end())
            throw "usuário já existe";
        users.insert(make_pair(nome,User(nome,senha))); 
    }

    User& getUser(string nome){        
        auto it = users.find(nome);
        if(it != users.end()){
            return it->second;
        }    
        throw "usuário não existe";
    }

    string toString(){
        stringstream ss;
        for(auto par : users){
            ss <<"["<< par.first <<"]"<< endl;
        }
        return ss.str();
    }

};


class GerLogin{
    Sistema *sisGerLogin;
    User *logado;
public:
    GerLogin(Sistema *sistem)
    {
        this->sisGerLogin = sistem;
        this->logado = nullptr;    
    }

    void login(string nome, string senha){
        if(logado != nullptr)
            throw "já existe alguém logado";            
        User& aux = sisGerLogin->getUser(nome);
        if(aux.getPass() != senha)
            throw "senha errada";
        logado = &aux;        
    }

    User& getLogado(){
        if(logado == nullptr)
            throw "ningém logado";
        return *logado;
    }

    void logout(){
        if(logado == nullptr)
            throw "ninguém logado";
        logado = nullptr;
    }


};


class Controller{
    Sistema sistemaControl;
    GerLogin gerenciador = GerLogin(&sistemaControl);
public:

    void exec(){
        string line;
        while(true){
            getline(cin,line);
            if(line == "end")
                break;
            try{

                cout<<shell(line);

            }catch(const char *e){
                cout<< e <<endl;

            }
        }
    }

    string shell(string line){
        stringstream ss(line);
        stringstream saida;
        string op;
        ss >> op;

        if(op == "addUser"){
            string nome;
            string senha;
            ss >> nome;
            ss >> senha;
            sistemaControl.addUser(nome,senha);
            saida << "ok"<<endl;
        }
        
        else if(op == "login"){
            string nome;
            string senha;
            ss >> nome;
            ss >> senha;
            gerenciador.login(nome,senha);
            saida << "ok"<<endl;
        }
        else if(op == "logout"){
            gerenciador.logout();
            saida << "ok"<<endl;
        }
        else if(op == "changePass"){
            string oldPass;
            string newPass;
            ss >> oldPass;
            ss >> newPass;
            gerenciador.getLogado().changePass(oldPass,newPass);
            saida << "ok"<<endl;   
        }

        else if(op == "addNote"){
            string titulo;
            string nota;
            ss >> titulo;
            getline(ss,nota);
            gerenciador.getLogado().addNote(titulo,nota);
            saida << "ok"<<endl;   
        }
        else if(op == "showNotes"){          
            saida << gerenciador.getLogado().toString();
        }
        
        else if(op == "rmNote"){          
            string titulo;
            ss >> titulo;
            gerenciador.getLogado().rmNote(titulo);
            saida << "ok"<<endl;
        }

        else if(op == "showUsers"){          
            saida << sistemaControl.toString();
        }

        else saida << "comando não existe"<<endl;
        
        return saida.str();
    }


};




int main(){
Controller control;
control.exec();

}