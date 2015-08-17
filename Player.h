#ifndef _PLAYER_H
#define _PLAYER_H

#include <map>

/*
 ласс Gamer ответственнен за координаты игрока и количество совершЄнных ходов
*/

class Gamer
{
private:
	int PlayerX;
	int PlayerY;
	long int stepcounter;

public:
	Gamer(std::map<char, int>& settings){
		PlayerX=settings['x'];
		PlayerY=settings['y'];
		stepcounter=settings['s'];
	}

	//  онструктор копировани€
	Gamer(const Gamer &copy);

	// вывод позиции игрока
int getPlayerY(){return PlayerY;}
int getPlayerX(){return PlayerX;}
long int getEscapeTime(){return stepcounter;}

	// vvod
void setPlayerY(int Y){PlayerY=Y;}
void setPlayerX(int X){PlayerX=X;}
void setEscapeTime(long int length){stepcounter=length;}

friend std::ostream& operator <<( std::ostream& stream, Gamer& clsobj){
	stream<<
	"x= "<<clsobj.PlayerX<<std::endl<<
	"y= "<<clsobj.PlayerY<<std::endl<<
	"s= "<<clsobj.stepcounter<<std::endl;
	return stream;
}
};



#endif