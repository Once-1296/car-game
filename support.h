#pragma once
#include<iostream>
#include<vector>
#include<string>
#include<cstring>
#include<ctime>
#include<sstream>
#include<fstream>
#include"SFML/Audio.hpp"
#include"SFML/Graphics.hpp"
#include"SFML/Network.hpp"
#include"SFML/System.hpp"
#include"SFML/Window.hpp"
class opcar
{
public:
	std::vector<sf::RectangleShape>opcars;
};
class optruck
{
public:
	std::vector<sf::RectangleShape>optrucks;
};
class opvan
{
public:
	std::vector<sf::RectangleShape>opvans;
};
class support
{
private:
	//variables
	//window
	sf::RenderWindow* window;
	sf::Event eevee;
	sf::VideoMode videoMode;
	//Resources
	sf::Font font;
	//Text
	sf::Text uiText, uiTextgame;
	std::vector<sf::Text> uiTexts1,uiTexts2;
	//variables
	sf::FloatRect rc;
	sf::RectangleShape rect,rectpause,recths;
	std::vector<sf::RectangleShape> usercar;
	sf::RectangleShape block;
	sf::RectangleShape wheel;
	sf::RectangleShape carwindow;
	std::vector<sf::RectangleShape> borders;
	std::vector<sf::RectangleShape> lane1;
	std::vector<sf::RectangleShape> lane2;
	std::vector<sf::RectangleShape> lane3;
	std::vector<sf::RectangleShape> lane4;
	std::vector<sf::RectangleShape> opcarset;
	std::vector<sf::RectangleShape> optruckset;
	std::vector<sf::RectangleShape> opvanset;
	std::vector<opcar> opcarfin;
	opcar objopcar;
	optruck objoptruck;
	opvan objopvan;
	std::vector<optruck> optruckfin;
	std::vector<opvan> opvanfin;
	sf::RectangleShape border;
	sf::RectangleShape strip;
	sf::RectangleShape pointbox;
	int index,index2,index3,index4,lanenum;
	int points;
	int lap;
	float opcarspeed, opcartimerincr;
	float optruckspeed, optrucktimerincr;
	float opvanspeed, opvantimerincr;
	float striptimer,striptimermax;
	float opvehictimer, opvehictimermax,opvehictimerincr;
	int maxopvehic,prevvehicindex;
	double rowstate,ceiling,floor;
	float ht[4],ht2[3],ht3[2],ht4[2];
	bool keyHeld1,keyHeld2;
	void initWindow();
	void initVariables();
	void initFonts();
	void initText();
public:
	support();//Constructor
	virtual ~support();//Destructor
	//Accessors
	const bool running() const;
	void pollEvents();
	int retscreen();
	void update();
	void updateObjects();
	void updateObjects2();
	void screentitle();
	void screenopt();
	void screenhs();
	void clearhs();
	void updateObjects4();
	void screenng();
	void initGameState();
	void pausescreen();
	void updateObjects3();
	void exitgame();
	void continuegame();
	void initDecor();
	void spawnstrips();
	void updatestrips();
	void initopvehicles();
	void initgameText();
	void initgamevariables();
	int checkGameState();
	void spawnopcar(int n);
	void spawnoptruck(int n);
	void spawnopvan(int n);
	void updateopcar(float n);
	void updateoptruck(float n);
	void updateopvan(float n);
	void updateopvehicles();
	void initUserCar();
	void moveUsercar();
	void updateScores();
	void updatePoints();
	void screencontrol();
	void updateText1(int scrnum);
	void render();
	void render2();
	void renderObjects(sf::RenderTarget& target);
	void renderText(sf::RenderTarget& target);
	void renderUserCar(sf::RenderTarget& target);
};

