#include <iostream>
#include <sstream>
#include <vector>
#include <map>

using namespace std;

class Cliente{
float divida;
string id;
public:
    Cliente(auto id=""){
       this->id = id;
       this->divida = 0;
    }

    void setValue(float valor){
        this->divida += valor;
    }

    int getValeu(){
        return this->divida;

    }

    string getId(){
        return this->id;
    }

    string toString(){
        stringstream ss;
        ss << this->id <<":"<< this->divida;
        return ss.str();
    }

};


class Agiota{
float saldo;
map <string,Cliente> cliente;
vector<Cliente*> extrato;
public:

    Agiota(float saldo = 0){
        if(saldo < 0);
        else this->saldo = saldo;
    }
    

    bool addcli(string line){
        stringstream entrada(line);
        string ident;
        entrada >> ident;
        auto pos = cliente.find(ident);
        if(pos==cliente.end()){
            getline(entrada,line);
            cliente.insert(make_pair(ident, Cliente(line)));
            return true;
        }

        return false;

    }
    

    bool emprestar(string line){
        stringstream entrada(line);
        string nome;
        entrada >> nome;
        float valor;
        entrada>>valor;

        auto pos = cliente.find(nome);
        
        
        if(pos != cliente.end()&&valor<saldo && valor < 0){
            pos->second.setValue(valor);
            saldo+=valor;
            extrato.push_back(new Cliente(nome));
            extrato[((int)extrato.size())-1]->setValue(valor);
            return true;
        } 

        return false;

    }

    bool receber(string line){
        stringstream entrada(line);
        string nome;
        entrada >> nome;
        float valor;
        entrada>>valor;

        auto pos = cliente.find(nome);
        auto comp = pos->second.getValeu() + valor;
        
        if(pos != cliente.end() && comp<=0 && valor > 0){
            pos->second.setValue(valor);
            saldo+=valor;
            extrato.push_back(new Cliente(nome));     
            extrato[((int)extrato.size())-1]->setValue(valor);
            return true;
        } 

        return false;

    }


    bool rm(string nome){
        cliente.erase(nome);
        
        for(int i=((int)extrato.size())-1; i>=0 ; i--){

                if(extrato[i]->getId()==nome){
                    extrato.erase(extrato.begin()+i);
                
                }
            }
    
        return true;

    }

    string filtro(string nome){
        stringstream ss;
        int i=0;
        for(auto aux : extrato){
            if(nome == aux->getId()){
                ss<<"id:"<<i<<" ";
                ss<<"[";
                ss <<aux->toString();
                ss<<"]"<<endl;
               
            }
             i++;
        }

        return ss.str();

    }

    string historico(){
        stringstream ss;
        int i=0;
        for(auto aux : extrato){
            ss<<"id:"<<i<<" ";
            ss<<"[";
            ss <<aux->toString();
            ss<<"]"<<endl;
            i++;
        }

        return ss.str();
    }


    string toString(){
        stringstream ss;
        for(pair<string, Cliente> par : cliente){

            ss <<par.first<<":"<<par.second.toString()<<endl;
           
        }
            ss << "Agiota: "<<saldo<<endl;
        return ss.str();

    }
   

};

struct Controller{
    
    Agiota agiota;

    string shell(string line){
        stringstream entrada(line);
        stringstream saida;
        string op;
        entrada >> op;
        if(op == "init"){
            float valor;
            entrada >> valor;
            agiota = Agiota(valor);
            saida << "ok"<<endl;
        }
        else if(op == "addCli"){
                getline(entrada,line);
                if(agiota.addcli(line)) saida << "ok"<<endl;
                else saida<<"cliente ja existe"<<endl;                
        }
            
        else if(op == "emprestar"){
                getline(entrada,line);
                if(agiota.emprestar(line)) saida<<"ok"<<endl;
                else saida<<"fail"<<endl;

        }
        else if(op == "receber"){
                getline(entrada,line);
                if(agiota.receber(line)) saida<<"ok"<<endl;
                else saida<<"fail"<<endl;

        }
        else if(op == "resumo"){
            saida<<agiota.toString();
                
        }
         else if(op == "historico"){
            saida<<agiota.historico();
                
        }
         else if(op == "filtrar"){
            string nome;
            entrada>>nome;
            saida<<agiota.filtro(nome);
                
        }
         else if(op == "matar"){
            string nome;
            entrada>>nome;
            if(agiota.rm(nome)) saida<<"ok"<<endl;
            else saida<<"cliente não existe"<<endl;
        }
        // else if(op == "help"){
        //     saida<<"init_valor;addCli_id_nome;emprestar_qtdDinheiro;receber_qtdDinheiro;resumo;
        //     historico;filtrar_id;matar_id;"<<endl;                
        // }
        else saida<<"opção não existe"<<endl;


        return saida.str();
    }

    void exec(){
        string line;
        while(true){
            getline(cin,line);
            if(line == "end") break;
            cout << shell(line);
        }
    }


};

int main(){
    Controller control;
    control.exec();
    return 0;
}