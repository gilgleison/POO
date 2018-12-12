#include <iostream>
#include <sstream>
#include <vector>
#include <map>
using namespace std;

template<typename K,typename T>
class Repositorio{
    map<K,T> dados;
public:

    void add(K k, T t){
        dados.insert(make_pair(k,t));
    }
    
    void rm(K posRm){
        auto it = dados.find(posRm);
        if(it != dados.end()){
            dados.erase(posRm);
        }
        else
            throw "Não existe";
    }

    T& get(K k){
        auto it = dados.find(k);
        if(it != dados.end()){
            return it->second;
        }
        else throw "não existe";
    }   

    string toString(){
        stringstream ss;
        for(auto aux : dados){
            ss << aux.first;
            ss << aux.second.toString();
        }
        return ss.str();
    }

};



class Contato{

    string nome;
    string num;

    public:

    Contato(string nome = "vazio",string num = "-"){
        this->nome = nome;
        this->num  = num;
    }

    string getNum(){
        return this->num;
    }

    string getNome(){
        return this->nome;
    }

    string toString(){
        stringstream ss;
        ss << ":";
        ss <<"["<<this->nome << ":"<< this->num<<"]";
        ss << "\n";
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

class Agenda{
Repositorio<int,Contato>contatos;
int cont;
public:

    Agenda():cont(0){

    }

    void add(string nome, string num){
        if(Contato::validate(num)){
            contatos.add(cont,Contato(nome,num));
            cont++;   
        }
    }

    void rm(int posRm){
        contatos.rm(posRm);
    }

    string toString(){
        stringstream ss;
        ss<< ":"<<"\n";
        ss << contatos.toString();      
        return ss.str();
    }

};


class Control{
    
    Repositorio<string,Agenda>agenda;
    
public:
    string shell(string line){
        stringstream entrada(line);
        stringstream saida;
        string op;
        entrada >> op;

        if(op == "show") 
            saida << agenda.toString();

        else if(op == "addNum"){            
            string nome;
            string num;
            entrada >> nome;
            Agenda& data = agenda.get(nome);
            while(entrada >> nome){
                entrada >> num;
                data.add(nome,num);                
            }
            
            saida <<"ok";                       
        }
        else if(op == "rmNum"){
            entrada >> op;
            Agenda& data = agenda.get(op);
            int posRm;
            while(entrada>>posRm){
                data.rm(posRm);         
            }
            saida <<"ok";        
        }

        else if(op == "addContato"){
            while(entrada >> op){
                agenda.add(op,Agenda());
            }
            saida <<"ok";
        }
        else if(op == "rmContato"){
            while(entrada >> op){
                agenda.rm(op);
            }
            saida <<"ok";
        }
        
        else 
            throw "comando não existe";
        
        return saida.str();
    }

    void exec(){
        string line;
        while(true){
            getline(cin,line);
            if(line == "end")
                break;
            try{
            cout << shell(line)<<endl;
            }catch(const char *e){
                cout << e <<endl;
            }
        }  
    }

};

int main(){

    Control control;
    control.exec();

    // Agenda agenda;
    // string op;
    // while(true){
    //     cin >> op;
    //     if(op == "init"){
    //         string nome;
    //         cin>>nome;
    //         agenda = Agenda(nome);
    //     }
    //     else if(op == "show") cout<<agenda.toString()<<endl;
    //     else if(op == "add"){
    //         string nome;
    //         string num;
    //         cin>>nome>>num;
    //         if(agenda.add(nome,num))
    //             cout<<"ok"<<endl;
    //         else
    //             cout<<"fail: numero invalido"<<endl;             
    //     }
    //      else 
    //         if(op == "rm"){
    //             int posRm;
    //             cin>>posRm;
    //             if(agenda.rm(posRm))
    //                 cout<<"ok"<<endl;
    //             else
    //                 cout<<"fail: indice incorreto"<<endl;                 
    //         }


    // }
    
    return 0;

}