#include <iostream>
#include <sstream>
#include <vector>
using namespace std;


class Contato{

    string nome;
    string num;

    public:

    Contato(string nome = "vazio",string num = "-"){
        this->nome = nome;
        this->num  = num;
    }

    string toString(){
        stringstream ss;
        ss <<this->nome << ":"<< this->num;
        return ss.str();
    }

    static bool validate(string num){
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
};  

struct Agenda{
    vector<Contato*> contato;
    string nome;

    Agenda(string nome="vazio"){
        this->nome = nome;        
    }

    bool add(string nome, string num){
        if(Contato::validate(num)){
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

    bool update(string line){
        stringstream entrada(line);
        string nome;
        string num;
        string atualiza;
        while(entrada>>atualiza){
            stringstream ss;                    
            for(int i=0;i < (int)atualiza.size();i++ ) if(atualiza[i] == ':') atualiza[i] = ' ';
            ss << atualiza; 
            ss >> nome;
            ss >> num;
            if(add(nome,num));                    
        }

        return true;
    }

};

struct Control{
    
    Agenda agenda;

    string shell(string line){
        stringstream entrada(line);
        stringstream saida;
        string op;
        entrada >> op;

        if(op == "init"){
            string nome;
            entrada>>nome;               
            agenda = Agenda(nome);
            saida << "ok";
        }
        else if(op == "show") saida << agenda.toString();
        else if(op == "add"){
            string nome;
            string num;
            entrada>>nome;
            entrada>>num;
            if(agenda.add(nome,num))
                saida <<"ok";
            else
                saida <<"fail: numero invalido";             
            }
        else if(op == "rm"){
                int posRm;
                entrada>>posRm;
                if(agenda.rm(posRm))
                    saida <<"ok";
                else
                    saida <<"fail: indice incorreto";                 
                }
        else if(op == "help")
                saida << "init_nome;add_id_num;rm_indice;show;update_nome_label:numero";
        
        else if(op == "update"){
                string nome;
                entrada>>nome;
                agenda = Agenda(nome);

                if(agenda.update(line)) saida<<"ok";
            }
        return saida.str();
    }

    void exec(){
        string line;
        while(true){
            getline(cin,line);
            if(line == "end")
                break;
            cout << shell(line)<<endl;
        }  
    }

};

int main(){

    Control control;
    control.exec();
    
    return 0;

}