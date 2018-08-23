#include<iostream>
#include<string>

using namespace std;

struct Carro{
    int qtd_pessoas;
    int max_pessoas;
    float tanque;
    int max_tanque;
    float rodado;

    void show(){
        cout<<"Quantidade de pessoas no carro:" <<qtd_pessoas << "\n" << "Litros de Gasolina no tanque:"<<tanque<<"\n" <<"km rodados:"<<rodado<<endl; 

    }

    void embarcar(){
        if(qtd_pessoas == max_pessoas)
            cout<<"não foi possivel embarcar, carro cheio"<<endl;
        else{
            qtd_pessoas++;
            cout<<"embarcado com sucesso"<<endl;
        }
    }

    void desembarcar(){
        if(qtd_pessoas > 0){ 
            qtd_pessoas--;
            cout<<"desembarcado com sucesso"<<endl;
        }
        else cout<<"não há pessoas para desembarcar"<<endl;
    }

    void abastecer(float litros){
        float abastecido = max_tanque - tanque;
        tanque += litros;
        if(tanque > max_tanque){   
            tanque = max_tanque;
            cout<<"você tentou abastecer mais do que cabe no tanque, foi abastecido apenas :"<< abastecido <<endl;
        }
    }

    void andar(float kms){
        float pode_andar = ((tanque*10) - kms);
        if(qtd_pessoas > 0 && pode_andar >= 0){
            tanque -= (kms/10);
            rodado += kms;
        }
        else if(qtd_pessoas==0)
            cout<<"esse carro não pode andar sozinho"<<endl;
        else if(pode_andar < 0 )
            cout<<"o carro não tem combustivel suficiente"<<endl;

    }



};

int main(){
    Carro car = {0,2,0,10,0};
    string op;

    while(1){
    cin >> op;

        if(op=="show") 
            car.show();
        else if(op=="embarcar") 
            car.embarcar();
        else if(op=="abastecer"){
            float litros;
            cin>>litros;
            car.abastecer(litros);
        }
        else if(op=="desembarcar") 
            car.desembarcar();

        else if(op=="andar") {
            float kms;
            cin>>kms;
            car.andar(kms);
        }
        else if(op=="help") 
            cout<<"show;embarcar;desembarcar;abastecer_litros;andar_km;sair;"<<endl;
       else if(op=="sair")
            break;
        else 
            cout<<"essa opção não existe"<<endl;

    }
    return 0;
}