#include <iostream>
#include <sstream>
#include <map>
#include <vector>
#include <algorithm>

using namespace std;

template<typename K,typename T>

class Repositorio{
    map<K,T> dados;
public:

    void add(K k, T t){
        if(dados.find(k) != dados.end())
            throw k + " já existe";
        dados.insert(make_pair(k,t));
    }

    void rm(K k){
        if(dados.find(k)!=dados.end())
            dados.erase(k);
        else
            throw k + " não existe";
    }

    T& get(K k){
        auto it = dados.find(k);
        if(it != dados.end())
            return it->second;
        else throw k + " não existe";
    }

    string toString(){
        stringstream ss;
        for(auto par : dados){
            ss << par.first;
            ss << par.second.toString();
        }

        return ss.str();
    }

};


class Tweet{
    string name;
    string tweet;
    vector<string>likes;
    int id;
public:
    Tweet(int id, string name, string msg):
    name(name),tweet(msg),id(id)
    {

    }

    void like(string nome){
        for(auto aux : likes){
            if(aux == nome)
                throw nome + " ja deu like";
        }
        likes.push_back(nome);
    }

    int getId(){
        return id;
    }

    string toString(){
        stringstream ss;
        ss << " "<<this->name<<":"<<" "<<this->tweet<<" "<<"{";
        for(auto aux : likes){
            ss <<" "<<aux<<" ";
        }
        ss << "}"<<"\n";

        return ss.str();
    }

};


class User{
    string nome;
    vector<User*> seguidores;
    vector<User*> seguidos;
    vector<Tweet*> Timeline;
    vector<Tweet*> MyTweet;
    int cont = 0;
public:

    User(string nome):nome(nome){
        
    }
    
    void addSeguidor(User *user){
        for(auto aux : seguidores){
            if(user->getName() == aux->getName()){
                throw user->getName() +  " já está seguindo" + this->nome;
            }
        }
        seguidores.push_back(user);
    }

    void Seguir(User *user){
        for(auto aux : seguidos){
            if(user->getName() == aux->getName()){
                throw this->nome + " já está seguindo" + user->getName();
            }
        }
        seguidos.push_back(user);
    }

    void addMyTweet(Tweet *T){
        MyTweet.push_back(T);
    }

    void addTimeline(Tweet *T){
        Timeline.push_back(T);
    }

    string getName(){
        return this->nome;
    }

    string getMT(){
        stringstream ss;
        for(auto aux : MyTweet){
            ss << aux->getId() <<" "<<":"<<aux->toString();
        }
        return ss.str();
    }
    
    string getTL(){
        stringstream ss;
        for(auto aux : Timeline){
            ss << aux->getId() <<" "<<":"<<aux->toString();
        }
        cont = (int)Timeline.size();
        return ss.str();
    }

    vector<User*>& getSeguidores(){
        return seguidores;
    }

    Tweet& getTweet(int id){
        for(auto aux : Timeline){
            if(aux->getId() == id)
                return *aux;
        }

        throw std::to_string(id) + " não esta na sua Timeline";
    }

    string unread(){
        stringstream ss;
        for(int i = cont; i < (int)Timeline.size();i++){
            ss << Timeline[i]->getId() <<" "<<":"<<Timeline[i]->toString();
        }
        cont = (int)Timeline.size();
        return ss.str();
    }


    string toString(){
        stringstream ss;
        ss <<":"<<"\n";
        ss << "Seguidos"<<" "<<"[";
        for(auto aux : seguidos){
            ss<<" "<<aux->getName()<<" ";
        } 
        ss << "]"<<"\n";

        ss << "Seguidores"<<" "<<"[";
        for(auto aux : seguidores){
            ss<<" "<<aux->getName()<<" ";
        } 
        ss << "]"<<"\n";

        return ss.str();
    }
};


class Gerador{
    Repositorio<int,Tweet> *RepTweet;
    int id;    
public:

    Gerador(Repositorio<int,Tweet> *RepTweet):
    RepTweet(RepTweet)
    {
        
    }

    Tweet& newTweet(string name, string msg){
        RepTweet->add(id,Tweet(id,name,msg));
        id++;
        return RepTweet->get(id-1);
    }

};


class Controller{
    
    Repositorio<string,User> RepUser;
    Repositorio<int,Tweet> RepTweet;
    Gerador gerador;

public:    
    Controller():gerador(&RepTweet){

    }

    string shell(string line){
        stringstream ss(line);
        stringstream saida;
        string op;
        ss >> op;

        if(op == "addUser"){
            ss >> op;
            RepUser.add(op,User(op));
            saida << "ok";
        }

        else if(op == "show"){
            saida << RepUser.toString();
        }

        else if(op == "seguir"){
            string nome,nome2;
            ss >> nome;
            ss >> nome2;
            User& user = RepUser.get(nome);
            User& user2 = RepUser.get(nome2);
            user.Seguir(&user2);
            user2.addSeguidor(&user);
            saida << "ok";
        }
        else if(op == "twittar"){
            string nome;
            ss >> nome;
            string msg;
            getline(ss,msg);
            Tweet& T = gerador.newTweet(nome,msg); // tweet postado
            User& user = RepUser.get(nome); // usuário que postou
            user.addMyTweet(&T);    // adicionando aos postados de quem postou
            user.addTimeline(&T); //adicionando a timeline de quem postou

            vector<User*>& aux = user.getSeguidores();  // seguidores

            for(auto data : aux){
                data->addTimeline(&T);  //adicionando a TL de todos os seguidores
            }

            saida << "ok";
        }
        else if(op == "showT"){
            saida << RepTweet.toString();
        }
        else if(op == "myTweets"){
            string nome;
            ss >> nome;
            User& user = RepUser.get(nome);
            saida << user.getMT();
        }
         else if(op == "timeline"){
            string nome;
            ss >> nome;
            User& user = RepUser.get(nome);
            saida << user.getTL();
        }
        else if(op == "like"){
            string nome;
            ss >> nome;
            int id;
            ss >> id;
            User& user = RepUser.get(nome);
            Tweet& T = user.getTweet(id);
            T.like(nome);
            saida << "ok";
        }
        else if(op == "unread"){
            string nome;
            ss >> nome;
            User& user = RepUser.get(nome);
            saida << user.unread();
        }
        else 
            saida << "opção não existe";
        
        return saida.str();
    }

    void exec(){    
        string line;    
        while(true){
            getline(cin,line);
            if(line == "end")
                break;
            try{
                cout<< shell(line)<<endl;
            }catch(string e){
                cout<< e <<endl;
            }

        }
    }

};

int main(){
    Controller control;
    control.exec();

    return 0;
}