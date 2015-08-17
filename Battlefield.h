#ifndef _BATTLEFIELD_H
#define _BATTLEFIELD_H
#include <vector>
#include <string>
#include <fstream>
#include <iostream>
#include "Player.h"

/*
Класс Labir ответственен за хранение карты лабиринта.
Конструктором по умолчанию принимает размеры лабиринта и координаты выхода.
Метод setmap ответственен за заполнение карты лабиринта.
Методы движения игрока по полю moveright, moveleft, moveup, movedown.
Метод theGreateEascape выполняет сравнение координат игрока и выхода.
	В случае совпадения координат возвращает true.
*/

class Labir{
private:
    std::vector<std::vector<int> > Map;
	int Escape[2];
	int row;
	int col;
public:
	// Конструктор
	Labir(std::map<char, int>& settings)
	{
		row = settings['h'];
		col = settings['w'];
		Escape[0]=settings['i'];
		Escape[1]=settings['j'];
	};

	// Конструктор копирования
	Labir(const Labir &copy);

	// Заполнение карты
	void setmap (std::ifstream& inputsourcestream){
		inputsourcestream.beg;
		inputsourcestream.close();
		inputsourcestream.open("ej.map");
		std::string test;
		while(test!="Labirint:"){
			inputsourcestream>>test;
			//getline(inputsourcestream, test);
		}
		if(test=="Labirint:"){
			Map.resize(row);
			for(int i = 0; i < row; ++i){
				Map.at(i).resize(col);
				for(int j = 0; j < col; ++j){
					inputsourcestream>>Map.at(i).at(j);
				}
			}
		}

	};
	 
	bool moveright(Gamer& clsobj){
		if( ((clsobj.getPlayerX()+1) < col) && (Map.at(clsobj.getPlayerY()).at(clsobj.getPlayerX()+1) == 0) ){
			clsobj.setPlayerX(clsobj.getPlayerX()+1);
			clsobj.setEscapeTime(clsobj.getEscapeTime()+1);
			return true;
		}
		else{
			return false;
		}
	};

	bool moveleft(Gamer& clsobj){
		if( ((clsobj.getPlayerX()-1) > -1) && (Map.at(clsobj.getPlayerY()).at(clsobj.getPlayerX()-1) == 0) ){
			clsobj.setPlayerX(clsobj.getPlayerX()-1);
			clsobj.setEscapeTime(clsobj.getEscapeTime()+1);
			return true;
		}
		else{
			return false;
		}
	};

	bool moveup(Gamer& clsobj){
		if( ((clsobj.getPlayerY()-1) > -1) && (Map.at(clsobj.getPlayerY()-1).at(clsobj.getPlayerX()) == 0) ){
			clsobj.setPlayerY(clsobj.getPlayerY()-1);
			clsobj.setEscapeTime(clsobj.getEscapeTime()+1);
			return true;
		}
		else{
			return false;
		}
	};

	bool movedown(Gamer& clsobj){
		if( ((clsobj.getPlayerY()+1) < row) && (Map.at(clsobj.getPlayerY()+1).at(clsobj.getPlayerX()) == 0) ){
			clsobj.setPlayerY(clsobj.getPlayerY()+1);
			clsobj.setEscapeTime(clsobj.getEscapeTime()+1);
			return true;
		}
		else{
			return false;
		}
	};

	void showmap(std::ostream& ost = std::cout){
		for (int i=0; i<row; i++){
			for( int j=0; j<col; j++){
				if(Map.at(i).at(j) == 0){
					ost<<(char) 219;
				}
				else {ost<<(char) 176;}
			}
			ost<<std::endl;

		}
	}


	void minimap(Gamer& clsobj ,std::ostream& ost = std::cout){
            for( int i=-10; i<11 ; i++){
                for(int j =-39; j<40; j++){
					if(i==0 && j==0){ost<<(char) 320;}
					else if( ((clsobj.getPlayerY()+i) < 0) || ((clsobj.getPlayerY()+i) > row-1)) {ost<<(char) 176;}
					else if( ((clsobj.getPlayerX()+j) < 0) || ((clsobj.getPlayerX()+j) > col-1)) {ost<<(char) 176;}
					else if(Map.at(clsobj.getPlayerY()+i).at(clsobj.getPlayerX()+j)==0){
						ost<<(char) 219;
					}
					else { ost<<(char) 177; }
					
					
					
				}
				std::cout<<std::endl;
			}

	};

	bool theGreateEascape(Gamer& clsobj){
		if(clsobj.getPlayerX() ==  Escape[0] && clsobj.getPlayerY() == Escape[1]){
			return true;
		}
		else {return false;}
	}

	//void save(std::ofstream& savestream){
	//	savestream<<row<<" "<<col<<std::endl<<
	//	Player[0]<<" "<<Player[1]<<std::endl<<
	//	Escape[0]<<" "<<Escape[1]<<std::endl<<
	//	stepcounter<<std::endl;
	//	for (int i=0; i<row; i++){
	//		for( int j=0; j<col; j++){
	//			if(Map.at(i).at(j) == 0){
	//				savestream<<0<<" ";
	//			}
	//			else {savestream<<1<<" ";}
	//		}
	//		savestream<<std::endl;
	//	}
	//}


		friend std::ostream& operator <<( std::ostream& stream, Labir& clsobj){
			stream<<
			"h= "<<clsobj.row<<std::endl<<
			"w= "<<clsobj.col<<std::endl<<
			"i= "<<clsobj.Escape[0]<<std::endl<<
			"j= "<<clsobj.Escape[1]<<std::endl<<std::endl<<
			"Labirint:"<<std::endl;

			for (int i=0; i<clsobj.row; i++){
				for( int j=0; j<clsobj.col; j++){
					if(clsobj.Map.at(i).at(j) == 0){
						stream<<0<<" ";
					}
					else {stream<<1<<" ";}
				}
				stream<<std::endl;

			}
			return stream;
		}

};



#endif
