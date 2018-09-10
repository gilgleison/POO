#include <iostream>
#include <sstream>
#include <vector>
using namespace std;


struct Contato{

    string nome;
    string num;

    Contato(string nome = "vazio",string num = "-"){
        this->nome = nome;
        this->num  = num;
    }

    string toString(){
        stringstream ss;
        ss <<this->nome << ":"<< this->num;
        return ss.str();
    }
};  

struct Agenda{
    vector<Contato*> contato;
    string nome;

    Agenda(string nome="vazio"){
        this->nome = nome;        
    }

    bool add(string nome, string num){
        if(validate(num)){
            contato.push_back(new Contato(nome,num));
            return true;
        }
        return false;
    }
    
    bool rm(int posRm){
        if(posRm>(int)contato.size())
            return false;
        contato.erase(contato.begin() + posRm);        
        return true;
    }

    bool validate(string num){
        string comp = "0123456789().";
        int cont = 0;
        int abriu=0,fechou=0,contNum=0;
        for(int i=0; i<(int) num.size();i++ ){
            for(int j=0;j<(int)comp.size();j++){
                if(num[i]==comp[j]){
                    if(num[i]=='(') abriu++;
                    else if(num[i]==')') fechou++;
                    else if(num[i]=='.');                    
                    else contNum++;
                    cont++; 
                    break;
                }

            }

        }
        if(cont==(int)num.size() && abriu==fechou && contNum >= 1)
            return true;
        else return false;
    }

     string toString(){
        stringstream ss;
        ss << nome << "=> ";
        for(int i=0; i < (int) contato.size();i++){
            ss <<"[";
            ss << i <<":"<<contato[i]->toString();
            ss << "]";
        }
        return ss.str();
    }

};

struct Control{
    
    Agenda agenda;

    string shell(string op){
        stringstream saida;
        if(op == "init"){
            string nome;
            cin>>nome;               
            agenda = Agenda(nome);
            saida << "ok";
        }
        else if(op == "show") saida << agenda.toString();
        else if(op == "add"){
            string nome;
            string num;
            cin>>nome>>num;
            if(agenda.add(nome,num))
                saida <<"ok";
            else
                saida <<"fail: numero invalido";             
            }
        else if(op == "rm"){
                int posRm;
                cin>>posRm;
                if(agenda.rm(posRm))
                    saida <<"ok";
                else
                    saida <<"fail: indice incorreto";                 
                }
        else if(op == "help")
                saida << "init_nome;add_id_num;rm_indice;show;";

        return saida.str();
    }

    void exec(){
        string op;
        while(true){
            cin >> op;
            if(op == "end")
                break;
            cout << shell(op)<<endl;
        }  
    }

};

int main(){

    Control control;
    control.exec();
    
    return 0;

}