#include <QCoreApplication>
#include <algorithm>
#include <string>
#include "Battlefield.h"
#include "Player.h"
#include "Exception.h"
using namespace std;

void help (void){
    cout<<"This is Labirints help."<<endl<<endl<<"  Here is a command list:"<<endl
    <<"Type \"moveright\" or \"d\" to move to the right"<<endl
    <<"Type \"moveleft\" or \"d\" to move to the left"<<endl
    <<"Type \"moveup\" or \"d\" to move up"<<endl
    <<"Type \"movedown\" or \"d\" to move down"<<endl
    <<endl
    <<"Type \"showmap\" to see whore map -_0"<<endl
    <<"Type \"save\" to save your progress"
    <<endl
    <<"Type \"exit\" to exit the programm immediately"<<endl
    ;
}

//Парсинг файла данных
void pars(map<char, int>& settings, std::ifstream& inputstream){
    while(!inputstream.eof()){
        char letter, equals;
        inputstream >> letter;
        inputstream >> equals;
        if(equals == '='){
            int value;
            inputstream >> value;
            settings[letter] = value;
        }
    }
    if(settings.size()==0){throw NYException();}
}


int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);


    // Temporary solution
    map<char, int> settings;
    ifstream Input;

    cout<<"Welcome to BladeRunner ver. 0.3.938"<<endl
    <<"Now! Choose your destiny!!!"<<endl<<endl<<"\"new\" to start new game"<<endl<<"\"load\" to load your previous progress"<<endl;
    string cmdline;
    bool actiondone=false;
    while(actiondone!=true){
        cin>>cmdline;
        if(cmdline=="load"){
            Input.open("ej.save");
            if(!Input.is_open()){cout<<"error while openning \"ej.save\"."<<endl;}
            else{
            try{pars(settings, Input);}
            catch(NYException& e){std::cout<<"no values were found in \"ej.save\"."; break;}
            actiondone=true;
            }
            //Input.open("ej.save");
            //if(!Input.is_open()){cout<<"error while openning \"ej.save\"."<<endl;}
            //
            //else{
            //Input>>Player[0]; //OX
            //Input>>Player[1]; //OY
            //Input>>Progress;
            //Input>>row;
            //Input>>col;
            //Input>>Escape[0];
            //Input>>Escape[1];
            //actiondone=true;
            //}
        }
        if(cmdline=="new"){
            Input.open("ej.map");
            if(!Input.is_open()){cout<<"error while openning \"ej.map\"."<<endl;}
            else{
            try{pars(settings, Input);}
            catch(NYException& e){cout<<"no values were found in \"ej.map\"."; break;}
            actiondone=true;
            }
            //Input.open("ej.map");
            //if(!Input.is_open()){cout<<"error while openning \"ej.map\"."<<endl;}
            //
            //else{
            //Input>>Player[0]; //OX
            //Input>>Player[1]; //OY
            //Input>>row;
            //Input>>col;
            //Input>>Escape[0];
            //Input>>Escape[1];
            //actiondone=true;
            //}
        }

        if(actiondone==false){
        cout<<"There is an error. It may be coused by incorrect comand or file error."<<endl<<
        "please, try again: ";
        }
    }

    Gamer ClassPlayer(settings);
    Labir Labirint(settings);
    Labirint.setmap(Input);
    Input.close();

    // the end of Temporary solution

    help();
    Labirint.minimap(ClassPlayer);
    cout<<"X: "<<ClassPlayer.getPlayerX()<<" Y: "<<ClassPlayer.getPlayerY()<<endl;

    //
    while(Labirint.theGreateEascape(ClassPlayer)!=true){
        actiondone = false; // if some command was inputted
        cin>>cmdline;

        if(cmdline == "exit"){
            return 1;
        }

        //beginning of move-block
        if(cmdline == "moveright" || cmdline == "d" ){
            if(Labirint.moveright(ClassPlayer) == true){
                system("cls");
                Labirint.minimap(ClassPlayer);
                cout<<"X: "<<ClassPlayer.getPlayerX()<<" Y: "<<ClassPlayer.getPlayerY()<<endl;
            }
            else{
                cout<<"move can't be done"<<endl;
            }
            actiondone = true;
        }

        if(cmdline == "moveleft" || cmdline == "a" ){
            if(Labirint.moveleft(ClassPlayer) == true){
                system("cls");
                Labirint.minimap(ClassPlayer);
                cout<<"X: "<<ClassPlayer.getPlayerX()<<" Y: "<<ClassPlayer.getPlayerY()<<endl;
            }
            else{
                cout<<"move can't be done"<<endl;
            }
            actiondone = true;
        }

        if(cmdline == "moveup" || cmdline == "w" ){
            if(Labirint.moveup(ClassPlayer) == true){
                system("cls");
                Labirint.minimap(ClassPlayer);
                cout<<"X: "<<ClassPlayer.getPlayerX()<<" Y: "<<ClassPlayer.getPlayerY()<<endl;
            }
            else{
                cout<<"move can't be done"<<endl;
            }
            actiondone = true;
        }

        if(cmdline == "movedown" || cmdline == "s" ){
            if(Labirint.movedown(ClassPlayer) == true){
                system("cls");
                Labirint.minimap(ClassPlayer);
                cout<<"X: "<<ClassPlayer.getPlayerX()<<" Y: "<<ClassPlayer.getPlayerY()<<endl;
            }
            else{
                cout<<"move can't be done"<<endl;
            }
            actiondone = true;
        }
        //end of move-block

        if(cmdline == "showmap"){
            Labirint.showmap();
            actiondone = true;
        }


        if(cmdline == "showposition"){
            cout<<"X: "<<ClassPlayer.getPlayerX()<<" Y: "<<ClassPlayer.getPlayerY()<<endl;
            actiondone = true;
        }

        if(cmdline=="save"){
            ofstream savestream("ej.save");
            if(savestream.is_open()){
            savestream<<ClassPlayer;
            savestream<<Labirint;
            cout<<"Your game has been saved"<<endl;
            }
            else{cout<<"Save file error"<<endl;}
            actiondone = true;
        }

        if(cmdline == "help"){
            help();
            actiondone = true;
        }

        if(actiondone == false){
        cout<<"Incorrect command"<<endl;
        }
    }
    //system("cls");
    Labirint.showmap();
    cout<<"You have successfuly escaped in "<<ClassPlayer.getEscapeTime()<<" steps"<<endl;

    return a.exec();
}
