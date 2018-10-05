# 01 - Carro


- O que você fez

        No objeto carro temos, variaveis para fazer o controle da quantidade de pessoas no carro e seu limite, a quantidade de combustivel e o limite, e a quantida de quilometros rodados.

        Temos a seguintes funções:

        A funcão void show, onde se mostra as condições do carro, quantidade de pessoas, quantidade de litros no tanque, e quilometros rodados.

        A função void embarcar, onde caso ainda haja espaço no carro um pessoa é embarcada, caso o carro esteja cheio, apenas informamos ao usuario que não pode mais embarcar pessoas, pois o carro está cheio.

        A função void desembarcar, onde apenas checamos a quantidade de pessoas no carro, caso ainda hajam pessoas no caso desembarcamos uma pessoas, caso o carro esteja vazio, o usuario é informado que não há mais ninguém para ser desembarcado.

        A função void abastecer, onde o usuário informa a quantidade de litros que deseja abastecer, caso o tanque esteja cheio nenhum litro é adicionado e é informado que foi abastecido zero litros, caso o tanque não esteja cheio mas ele tenta abastecer mais do que o tanque suporta, ele é informado da quantidade de litros que conseguiu abastecer, até que o tanque enchesse.

        A função void andar, recebe a quantidade de quilometros que o usuario pretende percorrer, e checa
        se ha pelo menos uma pessoa no carro e  se a quantidade de litros que contém o tanque é suficiente para completar a viagem, caso não seja, ou o carro esteja vazio, o usuario é informado e o carro continua parado, caso haja gasolina suficientee pelo menos uma pessoa no carro, a quantidade de quilometros rodados é incrementada e a quantia de litros subtraida, de acordo com a quantidade de quilometros percorridos.

        Na função main, o usuario digita uma entreda de acordo com a funcionalidade que ele deseja usar, para auxiliar temos a função help, onde são mostradas as funcioalidades que ele pode usar, e os seu parametros.

        
- Com quem e como você fez

        fiz o trabalho sozinho tirando como referencia o código da calculadora, para tirar algumas duvidas.
  
- O que aprendeu e sabe fazer

        já havia estudado c++, porém não lembrava de muita coisa, e haviam muitos recursos que eu não tinha utilizado, e o trabalho me possibilitou além de relembrar e reforçar alguns conceitos, aprender algumas coisas, como por exemplo, Não sabia que poderiamos usar funções dentro de uma struct e fazer o uso dela normalmente.
        
- O que tem dificuldade ainda

        as duvidas que eu tinha nessa parte do conteúdo, acabei resolvendo enquanto fazia o trabalho.
        
- Quanto tempo levou pra fazer a atividade

        não sei ao certo, pois além do tempo de implementação do código, fiquei um tempo estudando c++ no site passado pelo professor. mas eu diria que umas 6h ao todo.



        
# 02 - Topic


- O que você fez
        

         Foram usadas duas structs, Topic, e Passageiro, onde Topic faz o uso de um vetor de passageiros para gerenciar as poltronas, na main o usuário escolhe a função que deseja usar e passa os dados nescessarios.

        as funções são:

        init, onde a topic é iniciada, passando a quantidade maxima de poltronas e a quantidade de poltronas preferenciais.

        a função booleana in, onde o usuário passa o nome e idade do passageiro que irá sentar na poltrona, e são feitas checagens para saber em qual poltrona o passageiro irá sentar.

        a função booleana out, onde é passado o nome do passageiro, e ele será deletado do meu vetor.

        a função show, onde é mostrado as status da topic, passageiros que já estão sentados, lugares vazios e etc.

        a função help, onde são mostradas a opções de funções disponiveis ao usuário, e os dados nescessários para ultilizalas, e a função end, que encerra o nosso programa.
      
        
- Com quem e como você fez

        Sozinho, usando o código do cinema como referência.
  
- O que aprendeu e sabe fazer

       Aprendi bastante coisa sobre ponteiros, algumas coisas sobre a função vector, construtor e destrutor.
        
- O que tem dificuldade ainda

        Aprendi como usa, mas ainda não sei bem quando usar stringstream.
        
- Quanto tempo levou pra fazer a atividade

        em torno de 10h ao todo, até entender o código feito pelo professor e criar o meu.


# 03 - Contato


- O que você fez
        
        
        fiz as funções init(inicializar contato), add(adicionar novo numero ao contato), rm(remover numero do contato), help(opções disponiveis ao usuário), show(mostra o contatos e todos os numeros). 
        
        foram usadas 3 structs, Contato (contém os dados do contato, label e numero), Agenda (contém o nome do contato, e funções para implementação das funcionalidades), Control (contém as funções shell e exec, onde umas faz toda a parte de interação com o usuário e a outra trata de executar as funcionalides). 
        
        
        
- Com quem e como você fez

        Sozinho, ultilizando o conhecimento adquirido com as outras praticas, e alguns conceitos passados em aula.
  
- O que aprendeu e sabe fazer

       Aprendi como fazer um melhor uso da função vector e algumas utilidades, aprimorei os conhecimentos sobre ponteiros e algumas utilidades da biblioteca sstream. 
        
- O que tem dificuldade ainda


        não consegui implementar a função Update, onde os dados do contato seria passado em forma de bloco, e atualizado;
        
- Quanto tempo levou pra fazer a atividade

        6h há 7h, já que tinha aprendido bastante coisa com as práticas passadas e reutilizei boa parte do conhecimento já adquirido.

- Atualização
        

        fiz uma alteração no validate, onde agora ele é static, e fiz o update, pois não tinha conseguido fazer anteriormente, também alterei o para receber os dados em linha, alterei a struct contato para class contato. 



# 04 - Agiota


- O que você fez
        
        
        fiz as funções init(inicializar Agiota), addCli(adicionar novo cliente), matar(remover cliente e todas as transações feitas por ele), resumo(mostrar todos os clientes e o saldo do agiota), historico(mostra todas as transações feitas por todos os clientes), filtrar(mostra as transações feitar por um cliente especifico), emprestar(empresta dinheiro a um cliente), receber(recebe pagamento de um cliente);
        
        foram usadas 3 structs, Cliente (contém os dados do cliente, id e saldo), Agiota (contém o saldo do agiota e implementação das funcionalidades), Controller (contém as funções shell e exec, onde umas faz toda a parte de interação com o usuário e a outra trata de executar as funcionalides). 
        
        
        
- Com quem e como você fez

        Sozinho, ultilizando o conhecimento adquirido com as outras praticas, e alguns conceitos passados em aula algumas vezes consultando a video aula do professor para tirar duvidas.
  
- O que aprendeu e sabe fazer

       Aprendi a fazer um melhor uso da biblioteca sstream e fazer o uso de map, pelo menos a parte basica. 
        
- O que tem dificuldade ainda

        tive dificuldade em trabalhar com a biblioteca sstream, mas com a pratica acabei melhorando o conhecimento. 
        
- Quanto tempo levou pra fazer a atividade

        15h , tive que rever muitos conceitos e aprender coisas novas pra conseguir finalizar o projeto.



# 05 - RepositorioI


- O que você fez
        
        
        addAlu(adicionar novo aluno), rmAlu(remove um aluno passando a matricula), getAlu(pega os dados do aluno passando a matricula), showAlu(mostra todos os alunos),
        addPro(adiociona novo professor), rmPro(remove um professor passando o nome), getPro(pega os dados do professor passando o nome), showPro(mostra todos os professores),
        addDis(adiciona nova disciplina), rmDis(remove uma disciplina passando o codigo), getDis(pega os dados da disciplina passando o codigo), showDis(mostra todas as disciplinas),
        
        foram usadas 2 structs, Repositorio(contem as funções usadas pelas classes), Controller (contém as funções shell e exec, onde umas faz toda a parte de interação com o usuário e a outra trata de executar as funcionalides). e 3 class que são, Aluno, Professor e Disciplina.
        
        
- Com quem e como você fez

        Sozinho, ultilizando o conhecimento adquirido com as outras praticas, e os conceitos de repositorio e mapa passados pelo professor em sala de aula, as vezes consultando o código feito em aula pelo professor, com o intuito de tirar dúvidas.
  
- O que aprendeu e sabe fazer

       Aprofundei um pouco os conhecimentos sobre mapa, e aprendi a fazer o uso de repositorio. 
        
- O que tem dificuldade ainda

        Demorei um pouco a entender o conceito de repositorio, porém, com a pratica consegui entender. 
        
- Quanto tempo levou pra fazer a atividade

        10h , a maioria do tempo foi usada estudando respositorio, para entender como funcionava.