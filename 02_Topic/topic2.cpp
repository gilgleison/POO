#include <iostream>
#include <vector>
#include <sstream>
#include <string>

using namespace std;


struct Passageiro{
    string nome;
    string idade;

    Passageiro(string nome = "joãozinho",string idade = "32"){
        this->nome = nome;
        this->idade = idade;
    }    

    string toString(){
        stringstream ss;
        ss << this->nome << ":" << this->idade;
        return ss.str();
    }
};

struct Topic{
    vector<Passageiro*> poltrona; 
    int qtd,pref;
    string idoso = "60";

    Topic(int qtd = 0, int pref = 0):    
        poltrona(qtd, nullptr)
    {    
          this->qtd = qtd;
          this->pref = pref;
    }

    ~Topic(){
        for(Passageiro *pass : poltrona){
            delete(pass);
        }
    }

    
    bool in(string nome, string idade){
        
        Passageiro *pass;
        pass = new Passageiro(nome, idade);
       
        if(pass->idade >= idoso){
            for(int i = 0;i<qtd; i++){

                if(poltrona[i] != nullptr && pass->nome == poltrona[i]->nome){
                    cout<<"fail: você ja está na topic"<<endl;
                    return false;
                }

                if(i < pref && poltrona[i] == nullptr){
                    poltrona[i]=pass;
                    return true;                   
                }                           
                else

                    if(i >= pref && poltrona[i] == nullptr){
                        poltrona[i]=pass;
                        return true;                                          
                    }
                       
            }
            
        }
            
        else 
            if(pass->idade < idoso){
                for(int i=pref;i<qtd;i++){
                    if(poltrona[i] != nullptr && pass->nome == poltrona[i]->nome)
                    return false;

                    if(i >= pref && poltrona[i] == nullptr){
                        poltrona[i]=pass;
                        return true;    
                    }

                }  
                for(int i=0;i<pref;i++){
                    if(i < pref && poltrona[i] == nullptr){
                        poltrona[i]=pass;
                        return true;
                    }
                }    
            }   

        return false;
    }
    
    
    bool out(string nome){  
        for(int i=0;i<qtd;i++){ 
            if(poltrona[i] != nullptr && poltrona[i]->nome == nome){
                delete(poltrona[i]);
                poltrona[i] = nullptr;
                return true;
            }
        }

        return false;
    }

     string toString(){
        stringstream ss;
        ss << "[";
        for(int i=0;i<qtd;i++){
            if(poltrona[i] == nullptr)
                if(i<pref)
                    ss << " @ ";
                else 
                    ss << " = ";
            else
                ss << poltrona[i]->toString() << " ";            
        }
        ss << "]";
        return ss.str();
    }

};

int main(){
    Topic topic;
    string op;
    while(true){
        cin>>op;
        if(op == "show") cout << topic.toString() << endl; 
        else if(op == "init"){ 
            int qtd,pref;
            cin>>qtd>>pref;
            topic = Topic(qtd,pref);
        }
        else if(op == "in"){ 
            string nome,idade;
            cin>>nome>>idade;
            if(topic.in(nome, idade))
                cout<<"Ok"<<endl;
            else
                cout<<"fail"<<endl;
        }
        else if(op == "out"){ 
            string nome;
            cin>>nome;
            if(topic.out(nome))
                cout<<"Ok"<<endl;
            else 
                cout<<"fail: você não está na topic"<<endl;
        }
        else if(op == "help") 
            cout<<"init_qtdPoltronas_qtdPreferenciais;in_nome_idade;out_nome;show;end;"<<endl;
        else if(op == "end") 
            break;   
        else 
            cout<<"essa opção não existe"<<endl;
    }

    return 0;
}
