#include <sstream>
#include <vector>
#include <iostream>

using namespace std;


class Tamagotchi{
    int Energy;
    int Hungry;
    int Clean;
    int Diamonds;
    int Age;
    int EnergyMax;
    int HungryMax;
    int CleanMax;
    bool Morto;

public:
    Tamagotchi(int Energy = 0, int Hungry = 0, int Clean = 0):
    Energy(Energy),Hungry(Hungry),Clean(Clean)
    {
        this->HungryMax = Hungry;
        this->EnergyMax = Energy;
        this->CleanMax = Clean;
        this->Morto = false;
        this->Hungry = Hungry;
        this->Energy = Energy;
        this->Clean = Clean;
        this->Diamonds = 0;
        this->Age = 0;
    }

    void play(){

        if(Morto) throw "Morto";

        Energy -= 2;
        Hungry -= 1;
        Clean -= 3;
        Diamonds += 1;
        Age += 1;

        if(Energy < 0) Energy = 0;
        if(Hungry < 0) Hungry = 0;
        if(Clean < 0) Clean = 0; 

        if(Energy <= 0 || Hungry <= 0 || Clean <= 0){

            Morto = true;
            throw "Morto";
        }
    }

    void eat(){
        if(Morto) throw "Morto";

        Energy -= 1;
        Clean -= 2;
        Age += 1;        
        Hungry += 4;

        if(Energy < 0) Energy = 0;
        if(Clean < 0) Clean = 0; 
        if(Hungry>HungryMax)
            Hungry = HungryMax;

        if(Energy <= 0 || Clean <= 0){
            Morto = true;
            throw "Morto";
        }

    }

    void sleep(){

        if(Morto) throw "Morto";
        
        if(Energy == EnergyMax)
            throw "sem sono";

        Energy = EnergyMax;        
        Hungry -= 1;
        if(Hungry < 0) Hungry = 0;

        if(Hungry <= 0){
            Morto = true;
            throw "Morto";
        }

    }

    void clean(){
        if(Morto) throw "Morto";

        Energy -= 3;
        Hungry -= 1;
        Clean = CleanMax;
        Age += 2;

        if(Energy < 0) Energy = 0;
        if(Hungry < 0) Hungry = 0;

        if(Energy <= 0 || Hungry <= 0 || Clean <= 0){
            Morto = true;
            throw "Morto";
        }

    }


    string toString(){
        stringstream ss;

        ss<<"E:"<<this->EnergyMax<<"/"<<this->Energy<<","
        <<" "<<"H:"<<this->HungryMax<<"/"<<this->Hungry<<","
        <<" "<<"C:"<<this->CleanMax<<"/"<<this->Clean<<","
        <<" "<<"D:"<<this->Diamonds<<","<<" "<<"A:"<<this->Age<<endl;

        return ss.str();
    }

};


class Controller{
    Tamagotchi tamagotchi;

public:
    string shell(string line){
        stringstream ss(line);
        stringstream saida;
        string op;
        ss >> op;

        if(op == "init"){
            int energy,hungry,clean;
            ss >> energy >> hungry >> clean;
            tamagotchi = Tamagotchi(energy,hungry,clean); 
        }

        else if(op == "play"){
            tamagotchi.play();
        }
        else if(op == "sleep"){
            tamagotchi.sleep();
        }
        else if(op == "clean"){
            tamagotchi.clean();
        }
        else if(op == "eat"){
            tamagotchi.eat();
        }
         else if(op == "show"){
            saida << tamagotchi.toString();
        }

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
