#include "support.h"

void support::initWindow()
{
	this->videoMode.height = 600;
	this->videoMode.width = 800;
	this->window = new sf::RenderWindow(this->videoMode, "Awwab", sf::Style::Titlebar | sf::Style::Close);
	this->window->setFramerateLimit(60);
}

void support::initVariables()
{
	this->keyHeld1 = false;
	this->keyHeld2 = false;
	this->ht[0] = 0.5f;
	this->ht[1] = 0.6f;
	this->ht[2] = 0.7f;
	this->ht[3] = 0.8f;
	this->ht2[0] = 0.4f;
	this->ht2[1] = 0.5f;
	this->ht2[2] = 0.6f;
	this->ht3[0] = 0.25f;
	this->ht3[1] = 0.75f;
	this->ht4[0] = 0.7f;
	this->ht4[1] = 0.8f;
	this->index = 0,this->index2 = 0,this->index3 = 0, this->index4 = 1;
}

void support::initFonts()
{
	if (this->font.loadFromFile("fonts/Raleway-bold.ttf"))
	{
		std::cout << "ERROR:GAME::::INITFONTS::Failed to load font" << "\n";
	}
}
void support::initText()
{
	this->uiText.setFont(this->font);
	this->uiText.setCharacterSize(24);
	this->uiText.setFillColor(sf::Color::White);
	this->uiText.setString("NONE");
}

support::support()
{
	this->initWindow();
	this->initFonts();
	this->initText();
	this->initVariables();
}

support::~support()
{
	delete this->window;
}

//Accessors
const bool support::running() const
{
	return this->window->isOpen();
}

void support::pollEvents()
{
	//Event polling
	while (this->window->pollEvent(this->eevee))
	{
		switch (this->eevee.type)
		{
		case sf::Event::Closed:
			this->window->close();
			break;
		case sf::Event::KeyPressed:
			if (this->eevee.key.code == sf::Keyboard::Escape)
			{
				this->window->close();
				break;
			}
		}
	}
}

int support::retscreen()
{
	std::cout << this->eevee.key.code <<" " << this->index << std::endl;
	if (this->index == 0 && this->eevee.key.code == sf::Keyboard::Enter)
	{
		std::cout << "hello1\n";
		return 1;
	}
	else if(this->eevee.key.code == sf::Keyboard::Backspace)
	{
		std::cout << "hello2\n";
		return 1;
	}
	else if (this->index == 1 && sf::Keyboard::isKeyPressed(sf::Keyboard::Enter))
	{
		std::cout << "hello3\n";
		return 2;
	}
	else if (this->index == 2 && sf::Keyboard::isKeyPressed(sf::Keyboard::Enter))
	{
		std::cout << "hello4\n";
		return 3;
	}
	else if (this->index == 3 && sf::Keyboard::isKeyPressed(sf::Keyboard::Enter))
	{
		std::cout << "hello5\n";
		return 4;
	}
	else if (this->index == 0 && sf::Keyboard::isKeyPressed(sf::Keyboard::Enter))
	{
		std::cout << "hellogame\n";
		return 5;
	}
	else 
	{
		std::cout << "hello6\n";
		return 1;
	}
}

void support::update()
{
	this->pollEvents();
	this->updateText1(retscreen());
}
void support::updateObjects()
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
	{
		if (this->keyHeld1 == false) 
		{
			this->keyHeld1 = true;
			if (this->ht[this->index] < 0.8f)
			{
				this->index += 1;
			}
			else
			{
				this->index = 0;
			}
		}
	}
	else
	{
		this->keyHeld1 = false;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
	{
		if (this->keyHeld2 == false)
		{
			this->keyHeld2 = true;
			if (this->ht[this->index] > 0.5f)
			{
				this->index -= 1;
			}
			else
			{
				this->index = 3;
			}
		}
	}
	else
	{
		this->keyHeld2 = false;
	}
}
void support::updateObjects2()
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
	{
		if (this->keyHeld1 == false)
		{
			this->keyHeld1 = true;
			if (this->ht2[this->index2] < 0.6f)
			{
				this->index2 += 1;
			}
			else
			{
				this->index2 = 0;
			}
		}
	}
	else
	{
		this->keyHeld1 = false;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
	{
		if (this->keyHeld2 == false)
		{
			this->keyHeld2 = true;
			if (this->ht2[this->index2] > 0.4f)
			{
				this->index2 -= 1;
			}
			else
			{
				this->index2 = 2;
			}
		}
	}
	else
	{
		this->keyHeld2 = false;
	}
}
void support::screentitle()
{
	std::stringstream ss;
	this->uiTexts1.clear();
	ss << "ENDLESS CAR HIGHWAY";
	this->uiText.setString(ss.str());
	this->uiText.setCharacterSize(30);
	this->rc = this->uiText.getLocalBounds();
	this->uiText.setOrigin(this->rc.width / 2, this->rc.height / 2);
	this->uiText.setPosition(sf::Vector2f(this->videoMode.width * 0.5f, this->videoMode.height * 0.25f));
	this->uiTexts1.push_back(this->uiText);
	ss.str("");
	ss << "New Game";
	this->uiText.setString(ss.str());
	this->uiText.setCharacterSize(15);
	this->rc = this->uiText.getLocalBounds();
	this->uiText.setOrigin(this->rc.width / 2, this->rc.height / 2);
	this->uiText.setPosition(sf::Vector2f(this->videoMode.width * 0.5f, this->videoMode.height * 0.5f));
	this->uiTexts1.push_back(this->uiText);
	ss.str("");
	ss << "High Scores";
	this->uiText.setString(ss.str());
	this->uiText.setCharacterSize(15);
	this->rc = this->uiText.getLocalBounds();
	this->uiText.setOrigin(this->rc.width / 2, this->rc.height / 2);
	this->uiText.setPosition(sf::Vector2f(this->videoMode.width * 0.5f, this->videoMode.height * 0.6f));
	this->uiTexts1.push_back(this->uiText);
	ss.str("");
	ss << "Options";
	this->uiText.setString(ss.str());
	this->uiText.setCharacterSize(15);
	this->rc = this->uiText.getLocalBounds();
	this->uiText.setOrigin(this->rc.width / 2, this->rc.height / 2);
	this->uiText.setPosition(sf::Vector2f(this->videoMode.width * 0.5f, this->videoMode.height * 0.7f));
	this->uiTexts1.push_back(this->uiText);
	ss.str("");
	ss << "Controls";
	this->uiText.setString(ss.str());
	this->uiText.setCharacterSize(15);
	this->rc = this->uiText.getLocalBounds();
	this->uiText.setOrigin(this->rc.width / 2, this->rc.height / 2);
	this->uiText.setPosition(sf::Vector2f(this->videoMode.width * 0.5f, this->videoMode.height * 0.8f));
	this->uiTexts1.push_back(this->uiText);
	this->updateObjects();
	this->rect.setPosition(sf::Vector2f(0.f, (this->ht[this->index]) * 1.0f * (this->videoMode.height)));
	this->rect.setSize(sf::Vector2f(1.0f * this->videoMode.width, 1.0f * this->rc.getSize().y));
	this->rect.setFillColor(sf::Color::Green);
}
void support::screenopt()
{
	std::stringstream ss;
	this->keyHeld1 = false;
	this->keyHeld2 = false;
	while (this->eevee.key.code != sf::Keyboard::Backspace) 
	{
		this->pollEvents();
		this->uiTexts1.clear();
		ss.str("");
		ss << "Easy";
		this->uiText.setString(ss.str());
		this->uiText.setCharacterSize(20);
		this->rc = this->uiText.getLocalBounds();
		this->uiText.setOrigin(this->rc.width / 2, this->rc.height / 2);
		this->uiText.setPosition(sf::Vector2f(this->videoMode.width * 0.5f, this->videoMode.height * 0.4f));
		this->uiTexts1.push_back(this->uiText);
		ss.str("");
		ss << "Medium";
		this->uiText.setString(ss.str());
		this->uiText.setCharacterSize(20);
		this->rc = this->uiText.getLocalBounds();
		this->uiText.setOrigin(this->rc.width / 2, this->rc.height / 2);
		this->uiText.setPosition(sf::Vector2f(this->videoMode.width * 0.5f, this->videoMode.height * 0.5f));
		this->uiTexts1.push_back(this->uiText);
		ss.str("");
		ss << "Hard";
		this->uiText.setString(ss.str());
		this->uiText.setCharacterSize(20);
		this->rc = this->uiText.getLocalBounds();
		this->uiText.setOrigin(this->rc.width / 2, this->rc.height / 2);
		this->uiText.setPosition(sf::Vector2f(this->videoMode.width * 0.5f, this->videoMode.height * 0.6f));
		this->uiTexts1.push_back(this->uiText);
		std::ifstream file0;
		file0.open("difficulty.txt");
		std::string word;
		getline(file0, word);
		if (word == "Easy")
		{
			this->index2 = 0;
		}
		else if (word == "Medium")
		{
			this->index2 = 1;
		}
		else if (word == "Hard")
		{
			this->index2 = 2;
		}
		else
		{
			this->index2 = 1;
		}
		file0.close();
		this->updateObjects2();
		this->rect.setPosition(sf::Vector2f(0.f, (this->ht2[this->index2]) * 1.0f * (this->videoMode.height)));
		this->rect.setSize(sf::Vector2f(1.0f * this->videoMode.width, 1.0f * this->rc.getSize().y));
		this->rect.setFillColor(sf::Color::Green);
		std::ofstream file;
		file.open("difficulty.txt");
		switch (this->index2)
		{
		case 0:
			file << "Easy";
			break;
		case 1:
			file << "Medium";
			break;
		case 2:
			file << "Hard";
			break;
		default:
			file << "Medium";
			break;
		}
		file.close();
		this->render();
	}

}
void support::screenhs()
{
	std::stringstream ss;
	this->rect.setSize(sf::Vector2f(0.f, 0.f));
	std::string line;
	std::fstream file;
	this->keyHeld1 = false;
	this->keyHeld2 = false;
	while (this->eevee.key.code != sf::Keyboard::Backspace)
	{
		this->pollEvents();
		this->uiTexts1.clear();
		file.open("high scores.txt");
		while (getline(file, line))
		{
			ss << line << "\n";
		}
		this->uiText.setOrigin(0, 0);
		this->uiText.setPosition(0, 0);
		this->uiText.setString(ss.str());
		this->uiText.setCharacterSize(15);
		this->uiTexts1.push_back(this->uiText);
		ss.str("");
		ss << "Clear high scores:";
		this->uiText.setString(ss.str());
		this->uiText.setCharacterSize(36);
		this->rc = this->uiText.getLocalBounds();
		this->uiText.setOrigin(this->rc.width / 2, this->rc.height / 2);
		this->uiText.setPosition(sf::Vector2f(this->videoMode.width * 0.25f, this->videoMode.height * 0.75f));
		this->uiTexts1.push_back(this->uiText);
		ss.str("");
		ss << "Yes";
		this->uiText.setString(ss.str());
		this->uiText.setCharacterSize(18);
		this->rc = this->uiText.getLocalBounds();
		this->uiText.setOrigin(this->rc.width / 2, this->rc.height / 2);
		this->uiText.setPosition(sf::Vector2f(this->videoMode.width * 0.75f, this->videoMode.height * 0.7f));
		this->uiTexts1.push_back(this->uiText);
		ss.str("");
		ss << "No";
		this->uiText.setString(ss.str());
		this->uiText.setCharacterSize(18);
		this->rc = this->uiText.getLocalBounds();
		this->uiText.setOrigin(this->rc.width / 2, this->rc.height / 2);
		this->uiText.setPosition(sf::Vector2f(this->videoMode.width * 0.75f, this->videoMode.height * 0.8f));
		this->uiTexts1.push_back(this->uiText);
		ss.str("");
		this->recths.setSize(sf::Vector2f(this->videoMode.width * 0.5f, this->videoMode.height * 0.1f));
		this->rc = this->recths.getLocalBounds();
		this->recths.setOrigin(this->rc.width / 2, this->rc.height / 2);
		this->recths.setFillColor(sf::Color::Green);
		this->updateObjects4();
		this->recths.setPosition(sf::Vector2f(this->videoMode.width * 0.75f, this->videoMode.height * 1.f * (this->ht4[this->index4])));
		this->render();
		file.close();
	}
	if (this->index4 == 0)
	{
		this->clearhs();
	}
	this->recths.setSize(sf::Vector2f(0.f, 0.f));
	this->index4 = 1;
}
void support::clearhs()
{
	std::ofstream filewrite;
	filewrite.open("high scores.txt");
	filewrite << "Easy\n1.0\n2.0\n3.0\n4.0\n5.0\n";
	filewrite << "Medium\n1.0\n2.0\n3.0\n4.0\n5.0\n";
	filewrite << "Hard\n1.0\n2.0\n3.0\n4.0\n5.0\n";
	filewrite.close();

}
void support::updateObjects4()
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
	{
		if (this->keyHeld1 == false)
		{
			this->keyHeld1 = true;
			if (this->ht4[this->index4] < 0.8f)
			{
				this->index4 += 1;
			}
			else
			{
				this->index4 = 0;
			}
		}
	}
	else
	{
		this->keyHeld1 = false;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
	{
		if (this->keyHeld2 == false)
		{
			this->keyHeld2 = true;
			if (this->ht4[this->index4] > 0.7f)
			{
				this->index4 -= 1;
			}
			else
			{
				this->index4 = 1;
			}
		}
	}
	else
	{
		this->keyHeld2 = false;
	}
}
void support::screenng()
{
	this->initGameState();
	this->initUserCar();
	this->initopvehicles();
	this->initgameText();
	this->initDecor();
	this->initgamevariables();
	this->lane1.clear(), this->lane2.clear(), this->lane3.clear(), this->lane4.clear();
	this->striptimer = this->striptimermax;
	this->keyHeld1 = false, this->keyHeld2 = false;
	while (this->checkGameState())
	{
		this->pollEvents();
		this->index3 = 0;
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
		{
			this->keyHeld1 = false;
			this->keyHeld2 = false;
			while (!sf::Keyboard::isKeyPressed(sf::Keyboard::BackSpace))
			{
				std::cout << "PAUSED\n";
				this->pausescreen();
			}
		}
		std::cout << "NOT PAUSED\n";
		this->updateopvehicles();
		this->moveUsercar();
		this->updatestrips();
		this->render2();
		if (this->index3 > 0)
		{
			this->exitgame();
		}
		else
		{
			this->continuegame();
		}
	}
}

void support::initGameState()
{
	std::ofstream file;
	file.open("gamestate.txt");
	file << "true";
	file.close();
}

void support::pausescreen()
{
	this->pollEvents();
	this->uiTexts2.clear();
	std::stringstream ss;
	ss << "GAME PAUSED. CONTINUE? \n PRESS BACKSPACE";
	this->uiText.setString(ss.str());
	this->uiText.setCharacterSize(30);
	this->rc = this->uiText.getLocalBounds();
	this->uiText.setOrigin(this->rc.width / 2, this->rc.height / 2);
	this->uiText.setPosition(sf::Vector2f(this->videoMode.width * 0.5f, this->videoMode.height * 0.4f));
	this->uiTexts2.push_back(this->uiText);
	ss.str("");
	ss << "Yes";
	this->uiText.setString(ss.str());
	this->uiText.setCharacterSize(24);
	this->rc = this->uiText.getLocalBounds();
	this->uiText.setOrigin(this->rc.width / 2, this->rc.height / 2);
	this->uiText.setPosition(sf::Vector2f(this->videoMode.width * 0.25f, this->videoMode.height * 0.7f));
	this->uiTexts2.push_back(this->uiText);
	ss.str("");
	ss << "No";
	this->uiText.setString(ss.str());
	this->uiText.setCharacterSize(24);
	this->rc = this->uiText.getLocalBounds();
	this->uiText.setOrigin(this->rc.width / 2, this->rc.height / 2);
	this->uiText.setPosition(sf::Vector2f(this->videoMode.width * 0.75f, this->videoMode.height * 0.7f));
	this->uiTexts2.push_back(this->uiText);
	ss.str("");
	this->rectpause.setSize(sf::Vector2f(this->videoMode.width * 0.5f, this->videoMode.height * 0.1f));
	this->rc = this->rectpause.getLocalBounds();
	this->rectpause.setOrigin(this->rc.width / 2, this->rc.height / 2);
	this->rectpause.setFillColor(sf::Color::Green);
	this->updateObjects3();
	this->rectpause.setPosition(sf::Vector2f(this->videoMode.width * 1.f * (this->ht3[this->index3]), this->videoMode.height * 0.7f));
	this->render2();
}

void support::updateObjects3()
{
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
		{
			if (this->keyHeld1 == false)
			{
				this->keyHeld1 = true;
				if (this->ht3[this->index3] < 0.75f)
				{
					this->index3 += 1;
				}
				else
				{
					this->index3 = 0;
				}
			}
		}
		else
		{
			this->keyHeld1 = false;
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
		{
			if (this->keyHeld2 == false)
			{
				this->keyHeld2 = true;
				if (this->ht3[this->index3] > 0.25f)
				{
					this->index3 -= 1;
				}
				else
				{
					this->index3 = 1;
				}
			}
		}
		else
		{
			this->keyHeld2 = false;
		}
}

void support::exitgame()
{
	std::ofstream fileexit;
	fileexit.open("gamestate.txt");
	fileexit << "false";
	fileexit.close();
	this->updateScores();
	this->uiTexts2.clear();
	this->rectpause.setSize(sf::Vector2f(0.f, 0.f));
}

void support::continuegame()
{
	this->index3 = 0;
	this->uiTexts2.clear();
	this->rectpause.setSize(sf::Vector2f(0.f, 0.f));
}

void support::initDecor()
{
	this->border.setSize(sf::Vector2f(50.f, this->videoMode.height * 1.f));
	this->border.setFillColor(sf::Color::Green);
	this->border.setPosition(sf::Vector2f(0.f, 0.f));
	this->borders.push_back(this->border);
	this->border.setPosition(sf::Vector2f(750.f, 0.f));
	this->borders.push_back(this->border);
	this->border.setSize(sf::Vector2f(1.f, this->videoMode.height * 1.f));
	this->border.setPosition(sf::Vector2f(225.f, 0.f));
	this->borders.push_back(this->border);
	this->border.setPosition(sf::Vector2f(400.f, 0.f));
	this->borders.push_back(this->border);
	this->border.setPosition(sf::Vector2f(575.f, 0.f));
	this->borders.push_back(this->border);
}

void support::spawnstrips()
{
	this->strip.setSize(sf::Vector2f(20.f, this->videoMode.height * 0.3f));
	this->rc = this->strip.getLocalBounds();
	this->strip.setOrigin(0.f, rc.height);
	this->strip.setPosition(sf::Vector2f(127.5f, 0));
	this->lane1.push_back(this->strip);
	this->strip.move(175.f, 0.f);
	this->lane2.push_back(this->strip);
	this->strip.move(175.f, 0.f);
	this->lane3.push_back(this->strip);	
	this->strip.move(175.f, 0.f);
	this->lane4.push_back(this->strip);
}

void support::updatestrips()
{
	if (this->striptimer >= this->striptimermax)
	{
		this->spawnstrips();
		this->striptimer = 0.f;
	}
	else
	{
		this->striptimer += 1.f;
	}
	for (int i = 0; i < this->lane1.size(); i++)
	{
		this->lane1[i].move(0.f, 1.f);
		if (this->lane1[i].getPosition().y > (this->window->getSize().y + this->lane1[i].getSize().y))
		{
			this->lane1.erase(this->lane1.begin() + i);
		}
	}
	for (int i = 0; i < this->lane2.size(); i++)
	{
		this->lane2[i].move(0.f, 1.f);
		if (this->lane2[i].getPosition().y > (this->window->getSize().y + this->lane2[i].getSize().y))
		{
			this->lane2.erase(this->lane2.begin() + i);
		}
	}
	for (int i = 0; i < this->lane3.size(); i++)
	{
		this->lane3[i].move(0.f, 1.f);
		if (this->lane3[i].getPosition().y > (this->window->getSize().y + this->lane3[i].getSize().y))
		{
			this->lane3.erase(this->lane3.begin() + i);
		}
	}
	for (int i = 0; i < this->lane4.size(); i++)
	{
		this->lane4[i].move(0.f, 1.f);
		if (this->lane4[i].getPosition().y > (this->window->getSize().y + this->lane4[i].getSize().y))
		{
			this->lane4.erase(this->lane4.begin() + i);
		}
	}
}

void support::initopvehicles()
{
	this->opcarfin.clear();
	this->optruckfin.clear();
	this->opvanfin.clear();
	this->striptimermax = 200.f;
	this->points = 0;
	this->opvehictimermax = 3000.f;
	this->maxopvehic = 3;
	this->opvehictimer = 0.f;
}

void support::initgameText()
{
	this->uiTextgame.setFont(this->font);
	this->uiTextgame.setCharacterSize(15);
	this->uiTextgame.setPosition(sf::Vector2f(0.f, 0.f));
	this->uiTextgame.setOrigin(0, 0);
	this->uiTextgame.setFillColor(sf::Color::Black);
	this->rc = this->uiTextgame.getLocalBounds();
	this->pointbox.setSize(sf::Vector2f(50.f, 40.f));
	this->pointbox.setFillColor(sf::Color::White);
	this->pointbox.setPosition(sf::Vector2f(0.f, 0.f));
}

void support::initgamevariables()
{
	std::ifstream file;
	this->lap = 0;
	file.open("difficulty.txt");
	std::string word;
	getline(file, word);
	this->opvehictimerincr = 5.f;
	this->prevvehicindex = 3;
	if (word == "Easy")
	{
		this->optruckspeed = 0.8f;
		this->optrucktimerincr = 0.08f;
		this->opvanspeed = 1.f;
		this->opvantimerincr = 0.1f;
		this->opcarspeed = 1.2f;
		this->opcartimerincr = 0.12f;
	}
	else if (word == "Medium")
	{
		this->optruckspeed = 1.6f;
		this->optrucktimerincr = 0.16f;
		this->opvanspeed = 2.f;
		this->opvantimerincr = 0.2f;
		this->opcarspeed = 2.4f;
		this->opcartimerincr = 0.24f;
	}
	else if (word == "Hard")
	{
		this->optruckspeed = 2.4f;
		this->optrucktimerincr = 0.24f;
		this->opvanspeed = 3.2f;
		this->opvantimerincr = 0.32f;
		this->opcarspeed = 3.6f;
		this->opcartimerincr = 0.36f;
	}
	else
	{
		this->optruckspeed = 1.f;
		this->optrucktimerincr = 0.1f;
		this->opvanspeed = 1.2f;
		this->opvantimerincr = 0.12f;
		this->opcarspeed = 1.4f;
		this->opcartimerincr = 0.14f;
	}
}

int support::checkGameState()
{
	std::ifstream file;
	file.open("gamestate.txt");
	std::string word;
	getline(file, word);
	file.close();
	if (word == "true")
	{
		return 1;
	}
	return 0;
}

void support::spawnopcar(int n)
{
	this->opcarset.clear();
	this->objopcar.opcars.clear();
	this->block.setSize(sf::Vector2f((this->videoMode.width - 100.f) * 0.05f, (this->videoMode.height) * 0.1f));
	this->block.setFillColor(sf::Color::Red);
	this->rc = this->block.getLocalBounds();
	this->block.setOrigin(this->rc.width / 2, this->rc.height / 2);
	this->block.setPosition(sf::Vector2f((50.f) + (((2*n) + 1)*87.5f), 0.f - (this->rc.height/2)));
	this->wheel.setSize(sf::Vector2f(this->block.getSize().x / 8.f, this->block.getSize().y / 8.f));
	this->rc = this->wheel.getLocalBounds();
	this->wheel.setOrigin(this->rc.width / 2, this->rc.height / 2);
	this->wheel.setFillColor(sf::Color::Yellow);
	this->wheel.setPosition(sf::Vector2f(this->block.getPosition().x + (this->block.getSize().x * 0.5f),
		this->block.getPosition().y + (this->block.getSize().y * 0.5f)));
	this->opcarset.push_back(this->wheel);
	this->wheel.setPosition(sf::Vector2f(this->block.getPosition().x + (this->block.getSize().x * 0.5f),
		this->block.getPosition().y - (this->block.getSize().y * 0.5f)));
	this->opcarset.push_back(this->wheel);
	this->wheel.setPosition(sf::Vector2f(this->block.getPosition().x - (this->block.getSize().x * 0.5f),
		this->block.getPosition().y + (this->block.getSize().y * 0.5f)));
	this->opcarset.push_back(this->wheel);
	this->wheel.setPosition(sf::Vector2f(this->block.getPosition().x - (this->block.getSize().x * 0.5f),
		this->block.getPosition().y - (this->block.getSize().y * 0.5f)));
	this->opcarset.push_back(this->wheel);
	this->opcarset.push_back(this->block);
	this->carwindow.setSize(sf::Vector2f(this->block.getSize().x * 0.6f, this->block.getSize().y * 0.2f));
	this->carwindow.setFillColor(sf::Color::Blue);
	this->rc = this->carwindow.getLocalBounds();
	this->carwindow.setOrigin(this->rc.width / 2, this->rc.height / 2);
	this->carwindow.setPosition(sf::Vector2f(this->block.getPosition().x * 1.f, this->block.getPosition().y + this->rc.height * 1.f));
	this->opcarset.push_back(this->carwindow);
	for (auto& e : this->opcarset)
	{
		this->objopcar.opcars.push_back(e);
	}
	this->opcarfin.push_back(this->objopcar);
}
void support::spawnoptruck(int n)
{
	this->optruckset.clear();
	this->objoptruck.optrucks.clear();
	this->block.setSize(sf::Vector2f((this->videoMode.width - 100.f) * 0.07f, (this->videoMode.height) * 0.15f));
	this->block.setFillColor(sf::Color::Blue);
	this->rc = this->block.getLocalBounds();
	this->block.setOrigin(this->rc.width / 2, this->rc.height / 2);
	this->block.setPosition(sf::Vector2f((50.f) + (((2 * n) + 1) * 87.5f), 0.f - (this->rc.height * 0.7f)));
	this->wheel.setSize(sf::Vector2f(this->block.getSize().x / 4.f, this->block.getSize().y / 4.f));
	this->rc = this->wheel.getLocalBounds();
	this->wheel.setOrigin(this->rc.width / 2, this->rc.height / 2);
	this->wheel.setFillColor(sf::Color::Green);
	this->wheel.setPosition(sf::Vector2f(this->block.getPosition().x + (this->block.getSize().x * 0.5f),
		this->block.getPosition().y + (this->block.getSize().y * 0.5f)));
	this->optruckset.push_back(this->wheel);
	this->wheel.setPosition(sf::Vector2f(this->block.getPosition().x + (this->block.getSize().x * 0.5f),
		this->block.getPosition().y - (this->block.getSize().y * 0.5f)));
	this->optruckset.push_back(this->wheel);
	this->wheel.setPosition(sf::Vector2f(this->block.getPosition().x - (this->block.getSize().x * 0.5f),
		this->block.getPosition().y + (this->block.getSize().y * 0.5f)));
	this->optruckset.push_back(this->wheel);
	this->wheel.setPosition(sf::Vector2f(this->block.getPosition().x - (this->block.getSize().x * 0.5f),
		this->block.getPosition().y - (this->block.getSize().y * 0.5f)));
	this->optruckset.push_back(this->wheel);
	this->optruckset.push_back(this->block);
	this->carwindow.setSize(sf::Vector2f(this->block.getSize().x * 1.2f, this->block.getSize().y * 0.4f));
	this->carwindow.setFillColor(sf::Color::Red);
	this->rc = this->carwindow.getLocalBounds();
	this->carwindow.setOrigin(this->rc.width / 2, this->rc.height / 2);
	this->carwindow.setPosition(sf::Vector2f(this->block.getPosition().x * 1.f, this->block.getPosition().y + (this->block.getSize().y * 0.5f) + (this->rc.height * 0.5f)));
	this->wheel.setPosition(sf::Vector2f(this->carwindow.getPosition().x - (this->carwindow.getSize().x * 0.5f),
		this->carwindow.getPosition().y + (this->carwindow.getSize().y * 0.5f)));
	this->optruckset.push_back(this->wheel);
	this->wheel.setPosition(sf::Vector2f(this->carwindow.getPosition().x + (this->carwindow.getSize().x * 0.5f),
		this->carwindow.getPosition().y + (this->carwindow.getSize().y * 0.5f)));
	this->optruckset.push_back(this->wheel);
	this->block.setFillColor(sf::Color::Cyan);
	this->block.setSize(sf::Vector2f(this->carwindow.getSize().x * 0.5f, this->carwindow.getSize().y * 0.3f));
	this->rc = this->block.getLocalBounds();
	this->block.setOrigin(this->rc.width / 2, this->rc.height / 2);
	this->block.setPosition(sf::Vector2f(this->carwindow.getPosition().x, this->carwindow.getPosition().y + (this->rc.height/2)));
	this->optruckset.push_back(this->carwindow);
	this->optruckset.push_back(this->block);
	for (auto& e : this->optruckset)
	{
		this->objoptruck.optrucks.push_back(e);
	}
	this->optruckfin.push_back(this->objoptruck);
}

void support::spawnopvan(int n)
{
	this->opvanset.clear();
	this->objopvan.opvans.clear();
	this->block.setSize(sf::Vector2f((this->videoMode.width - 100.f) * 0.05f, (this->videoMode.height) * 0.2f));
	this->block.setFillColor(sf::Color::Cyan);
	this->rc = this->block.getLocalBounds();
	this->block.setOrigin(this->rc.width / 2, this->rc.height / 2);
	this->block.setPosition(sf::Vector2f((50.f) + (((2 * n) + 1) * 87.5f), 0.f - (this->rc.height / 2)));
	this->wheel.setSize(sf::Vector2f(this->block.getSize().x / 6.f, this->block.getSize().y / 6.f));
	this->rc = this->wheel.getLocalBounds();
	this->wheel.setOrigin(this->rc.width / 2, this->rc.height / 2);
	this->wheel.setFillColor(sf::Color::Blue);
	this->wheel.setPosition(sf::Vector2f(this->block.getPosition().x + (this->block.getSize().x * 0.5f),
		this->block.getPosition().y + (this->block.getSize().y * 0.5f)));
	this->opvanset.push_back(this->wheel);
	this->wheel.setPosition(sf::Vector2f(this->block.getPosition().x + (this->block.getSize().x * 0.5f),
		this->block.getPosition().y - (this->block.getSize().y * 0.5f)));
	this->opvanset.push_back(this->wheel);
	this->wheel.setPosition(sf::Vector2f(this->block.getPosition().x - (this->block.getSize().x * 0.5f),
		this->block.getPosition().y + (this->block.getSize().y * 0.5f)));
	this->opvanset.push_back(this->wheel);
	this->wheel.setPosition(sf::Vector2f(this->block.getPosition().x - (this->block.getSize().x * 0.5f),
		this->block.getPosition().y - (this->block.getSize().y * 0.5f)));
	this->opvanset.push_back(this->wheel);
	this->wheel.setPosition(sf::Vector2f(this->block.getPosition().x + (this->block.getSize().x * 0.5f),
		this->block.getPosition().y * 1.f));
	this->opvanset.push_back(this->wheel);
	this->wheel.setPosition(sf::Vector2f(this->block.getPosition().x - (this->block.getSize().x * 0.5f),
		this->block.getPosition().y * 1.f));
	this->opvanset.push_back(this->wheel);
	this->opvanset.push_back(this->block);
	this->carwindow.setSize(sf::Vector2f(this->block.getSize().x * 0.6f, this->block.getSize().y * 0.1f));
	this->carwindow.setFillColor(sf::Color::Blue);
	this->rc = this->carwindow.getLocalBounds();
	this->carwindow.setOrigin(this->rc.width / 2, this->rc.height / 2);
	this->carwindow.setPosition(sf::Vector2f(this->block.getPosition().x * 1.f, this->block.getPosition().y + (this->rc.height * 3.f)));
	this->opvanset.push_back(this->carwindow);
	this->carwindow.setPosition(sf::Vector2f(this->block.getPosition().x * 1.f, this->block.getPosition().y - (this->rc.height * 3.f)));
	this->opvanset.push_back(this->carwindow);
	this->carwindow.setPosition(sf::Vector2f(this->block.getPosition().x * 1.f, this->block.getPosition().y));
	this->opvanset.push_back(this->carwindow);
	for (auto& e : this->opvanset)
	{
		this->objopvan.opvans.push_back(e);
	}
	this->opvanfin.push_back(this->objopvan);
}

void support::updateopcar(float n)
{
	for (int i = 0; i < this->opcarfin.size(); i++)
	{
		if (this->opcarfin[i].opcars[4].getPosition().y > this->videoMode.height + this->opcarfin[i].opcars[4].getSize().y)
		{
			this->points += 20;
			this->lap += 20;
			this->opcarfin.erase(this->opcarfin.begin() + i);
		}
		else
		{
			for (int j = 0; j < this->opcarfin[i].opcars.size(); j++)
			{
				this->opcarfin[i].opcars[j].move(0.f, n * 1.f);
			}
		}
	}
}
void support::updateoptruck(float n)
{
	for (int i = 0; i < this->optruckfin.size(); i++)
	{
		if (this->optruckfin[i].optrucks[4].getPosition().y > this->videoMode.height + this->optruckfin[i].optrucks[4].getSize().y)
		{
			this->points += 50;
			this->lap += 50;
			this->optruckfin.erase(this->optruckfin.begin() + i);
		}
		else
		{
			for (int j = 0; j < this->optruckfin[i].optrucks.size(); j++)
			{
				this->optruckfin[i].optrucks[j].move(0.f, n * 1.f);
			}
		}
	}
}

void support::updateopvan(float n)
{
	for (int i = 0; i < this->opvanfin.size(); i++)
	{
		if (this->opvanfin[i].opvans[4].getPosition().y > this->videoMode.height + this->opvanfin[i].opvans[4].getSize().y)
		{
			this->points += 30;
			this->lap += 30;
			this->opvanfin.erase(this->opvanfin.begin() + i);
		}
		else
		{
			for (int j = 0; j < this->opvanfin[i].opvans.size(); j++)
			{
				this->opvanfin[i].opvans[j].move(0.f, n * 1.f);
			}
		}
	}
}

void support::updateopvehicles()
{
	int somenum = 1,somenum2 = 0;
	std::ifstream file;
	file.open("difficulty.txt");
	std::string word;
	getline(file, word);
	file.close();
	if (this->opcarfin.size() + this->optruckfin.size() + this->opvanfin.size() < this->maxopvehic)
	{
		if (this->opvehictimer >= this->opvehictimermax)
		{
			if (word == "Easy")
			{
				this->opvehictimermax = 937.5f;
			}			
			else if (word == "Medium")
			{
				this->opvehictimermax = 468.75;
			}			
			else if (word == "Hard")
			{
				this->opvehictimermax = 312.5;
			}
			else
			{
				this->opvehictimermax = 468.75;
			}
			somenum = (rand() % 3) + 1;
			do
			{
				somenum2 = (rand() % 4);
			} while (somenum2 == this->prevvehicindex);
			this->prevvehicindex = somenum2;
			switch (somenum)
			{
			case 1:
				this->spawnopcar(somenum2);
				break;
			case 2:
				this->spawnoptruck(somenum2);
				break;
			case 3:
				this->spawnopvan(somenum2);
				break;
			default:
				this->spawnopcar(somenum2);
				break;
			}

			this->opvehictimer = 0.f;
		}
		else
		{
			this->opvehictimer += 5.f;
		}
	}
	if (this->lap > 100)
	{
		this->lap -= 100;
		this->opcarspeed += this->opcartimerincr;
		this->optruckspeed += this->optrucktimerincr;
		this->opvanspeed += this->opvantimerincr;
		this->opvehictimerincr += 0.05f;
	}
	this->updateopcar(this->opcarspeed);
	this->updateoptruck(this->optruckspeed);
	this->updateopvan(this->opvanspeed);
	this->updatePoints();
}

void support::initUserCar()
{
	this->lanenum = 1;
	this->usercar.clear();
	this->block.setSize(sf::Vector2f((this->videoMode.width - 100.f) * 0.05f, (this->videoMode.height)*0.1f));
	this->block.setFillColor(sf::Color::Blue);
	this->rc = this->block.getLocalBounds();
	this->block.setOrigin(this->rc.width / 2, this->rc.height / 2);
	this->block.setPosition(sf::Vector2f(((this->videoMode.width - 100.f) * 0.125f) + 50.f, this->videoMode.height - this->rc.getSize().y));
	this->rowstate = this->block.getPosition().y;
	this->floor = this->videoMode.height - this->rc.getSize().y;
	this->ceiling = this->videoMode.height - this->floor;
	this->wheel.setSize(sf::Vector2f(this->block.getSize().x / 8.f, this->block.getSize().y / 8.f));
	this->rc = this->wheel.getLocalBounds();
	this->wheel.setOrigin(this->rc.width / 2, this->rc.height / 2);
	this->wheel.setFillColor(sf::Color::Red);
	this->wheel.setPosition(sf::Vector2f(this->block.getPosition().x + (this->block.getSize().x * 0.5f),
		this->block.getPosition().y + (this->block.getSize().y * 0.5f)));
	this->usercar.push_back(this->wheel);
	this->wheel.setPosition(sf::Vector2f(this->block.getPosition().x + (this->block.getSize().x * 0.5f),
		this->block.getPosition().y - (this->block.getSize().y * 0.5f)));
	this->usercar.push_back(this->wheel);
	this->wheel.setPosition(sf::Vector2f(this->block.getPosition().x - (this->block.getSize().x * 0.5f),
		this->block.getPosition().y + (this->block.getSize().y * 0.5f)));
	this->usercar.push_back(this->wheel);
	this->wheel.setPosition(sf::Vector2f(this->block.getPosition().x - (this->block.getSize().x * 0.5f),
		this->block.getPosition().y - (this->block.getSize().y * 0.5f)));
	this->usercar.push_back(this->wheel);
	this->usercar.push_back(this->block);
	this->carwindow.setSize(sf::Vector2f(this->block.getSize().x * 0.6f, this->block.getSize().y * 0.2f));
	this->carwindow.setFillColor(sf::Color::Yellow);
	this->rc = this->carwindow.getLocalBounds();
	this->carwindow.setOrigin(this->rc.width / 2, this->rc.height / 2);
	this->carwindow.setPosition(sf::Vector2f(this->block.getPosition().x*1.f,this->block.getPosition().y-this->rc.height*1.f));
	this->usercar.push_back(this->carwindow);
}
void support::moveUsercar()
{
	//std::cout << this->floor << " " << this->ceiling<<std::endl;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) && this->lanenum > 1)
	{
		if (this->keyHeld1 == false) 
		{
			this->keyHeld1 = true;
			this->lanenum--;
			for (int i = 0; i < this->usercar.size(); i++)
			{
				this->usercar[i].move(sf::Vector2f(-175.f, 0.f));
			}
		}
	}
	else
	{
		this->keyHeld1 = false;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) && this->lanenum < 4)
	{
		if (this->keyHeld2 == false)
		{
			this->keyHeld2 = true;
			this->lanenum++;
			for (int i = 0; i < this->usercar.size(); i++)
			{
				this->usercar[i].move(sf::Vector2f(175.f, 0.f));
			}
		}
	}
	else
	{
		this->keyHeld2 = false;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) && this->rowstate > this->ceiling)
	{
		for (int i = 0; i < this->usercar.size(); i++)
		{
			this->rowstate -= (this->videoMode.height * 0.01f)/this->usercar.size();
			this->usercar[i].move(sf::Vector2f(0.f, -1.f * this->videoMode.height * 0.01f));
		}
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down) && this->rowstate < this->floor)
	{
		for (int i = 0; i < this->usercar.size(); i++)
		{
			this->rowstate += (this->videoMode.height * 0.01f) / this->usercar.size();
			this->usercar[i].move(sf::Vector2f(0.f, this->videoMode.height * 0.01f));
		}
	}
	sf::FloatRect temp;
	temp = this->usercar[4].getGlobalBounds();
	std::ofstream file;
	file.open("gamestate.txt");
	bool t1 = false, t2 = false, t3 = false;
	for (int i = 0; i < this->opcarfin.size(); i++)
	{
		if (this->opcarfin[i].opcars[4].getGlobalBounds().intersects(temp))
		{
			t1 = true;
		}
	}
	for (int i = 0; i < this->optruckfin.size(); i++)
	{
		if (this->optruckfin[i].optrucks[4].getGlobalBounds().intersects(temp))
		{
			t2 = true;
		}
	}
	for (int i = 0; i < this->opvanfin.size(); i++)
	{
		if (this->opvanfin[i].opvans[4].getGlobalBounds().intersects(temp))
		{
			t3 = true;
		}
	}
	if (t1 || t2 || t3)
	{
		file << "false";
		this->updateScores();
	}
	else
	{
		file << "true";
	}
}
void support::updateScores()
{
	std::ifstream file;
	std::string difficulty,line,word;
	int scorearr[5] = {0,0,0,0,0};
	std::string lines[18];
	file.open("difficulty.txt");
	getline(file, difficulty);
	file.close();
	file.open("high scores.txt");
	if (difficulty == "Easy")
	{
		getline(file, line);
		for (int i = 0; i < 5; i++)
		{
			getline(file, line);
			std::stringstream obj(line);
			while (getline(obj, word, '.'))
			{
				scorearr[i] = stoi(word);
			}
		}
	}
	else if (difficulty == "Medium")
	{
		for (int i = 0; i < 7; i++)
		{
			getline(file, line);
		}
		for (int i = 0; i < 5; i++)
		{
			getline(file, line);
			std::stringstream obj(line);
			while (getline(obj, word, '.'))
			{
				scorearr[i] = stoi(word);
			}
		}
	}
	else if (difficulty == "Hard")
	{
		for (int i = 0; i < 13; i++)
		{
			getline(file, line);
		}		
		for (int i = 0; i < 5; i++)
		{
			getline(file, line);
			std::stringstream obj(line);
			while (getline(obj, word, '.'))
			{
				scorearr[i] = stoi(word);
			}
		}
	}
	else
	{
		for (int i = 0; i < 7; i++)
		{
			getline(file, line);
		}
		for (int i = 0; i < 5; i++)
		{
			getline(file, line);
			std::stringstream obj(line);
			while (getline(obj, word, ','))
			{
				scorearr[i] = stoi(word);
			}
		}
	}
	//std::cout << "1\n";
	int tempnum = 0, tempnum1 = 0;
	for (int i = 0; i < 5; i++)
	{
		if (this->points > scorearr[i]) 
		{
			tempnum = scorearr[i];
			scorearr[i] = this->points;
			this->points = -1;
		}
		else if(this->points < 0)
		{
			tempnum1 = scorearr[i];
			scorearr[i] = tempnum;
			tempnum = tempnum1;
		}
	}
	//std::cout << "1\n";
	file.seekg(0, std::ios::beg);
	std::string scrarr[5];
	for (int i = 0; i < 5; i++)
	{
		std::string te1 = std::to_string(i + 1),te2 = std::to_string(scorearr[i]);
		scrarr[i] = te1 + "." + te2;
		//std::cout << scrarr[i];
	}
	int index = 0;
	while (getline(file,line))
	{
		lines[index] = line;
		index++;
	}
	if (difficulty == "Easy")
	{
		for (int i = 0; i < 5; i++)
		{
			lines[1 + i] = scrarr[i];
		}
	}
	else if (difficulty == "Medium")
	{
		for (int i = 0; i < 5; i++)
		{
			lines[7 + i] = scrarr[i];
		}
	}
	else if (difficulty == "Hard")
	{
		for (int i = 0; i < 5; i++)
		{
			lines[13 + i] = scrarr[i];
		}
	}
	else
	{
		for (int i = 0; i < 5; i++)
		{
			lines[7 + i] = scrarr[i];
		}
	}
	file.close();
	std::ofstream ofile;
	ofile.open("high scores.txt");
	for (int i = 0; i < 18; i++)
	{
		ofile << lines[i] << "\n";
	}
	ofile.close();
}
void support::updatePoints()
{
	std::stringstream ss;
	ss << "Points:\n" << this->points;
	this->uiTextgame.setString(ss.str());
}
void support::screencontrol()
{
	std::stringstream ss;
	this->rect.setSize(sf::Vector2f(0.f, 0.f));
	std::string line;
	std::fstream file;
	while (this->eevee.key.code != sf::Keyboard::Backspace)
	{
		this->pollEvents();
		this->uiTexts1.clear();
		file.open("controls.txt");
		while (getline(file, line))
		{
			ss << line << "\n";
		}
		this->uiText.setOrigin(0, 0);
		this->uiText.setPosition(0, 0);
		this->uiText.setString(ss.str());
		this->uiText.setCharacterSize(15);
		this->uiTexts1.push_back(this->uiText);
		this->render();
	}
}
void support::updateText1(int scrnum)
{

	switch (scrnum) 
	{
	case 1:
		this->screentitle();
	break;
	case 2:
		this->screenhs();
	break;
	case 3:
		this->screenopt();
	break;
	case 4:
		this->screencontrol();
	break;
	case 5:
		this->screenng();
	break;
	default:
		this->screentitle();
	break;
}
}
void support::renderText(sf::RenderTarget& target)
{
	for (auto& e : this->uiTexts1)
	{
		target.draw(e);
	}
}
void support::renderUserCar(sf::RenderTarget& target)
{
	for (auto& e : this->borders)
	{
		target.draw(e);
	}
	for (auto& e : this->lane1)
	{
		target.draw(e);
	}
	for (auto& e : this->lane2)
	{
		target.draw(e);
	}
	for (auto& e : this->lane3)
	{
		target.draw(e);
	}
	for (auto& e : this->lane4)
	{
		target.draw(e);
	}
	for (int i = 0; i < this->opcarfin.size(); i++)
	{
		for(auto& e : this->opcarfin[i].opcars)
		{
			target.draw(e);
		}
	}
	for (int i = 0; i < this->optruckfin.size(); i++)
	{
		for (auto& e : this->optruckfin[i].optrucks)
		{
			target.draw(e);
		}
	}
	for (int i = 0; i < this->opvanfin.size(); i++)
	{
		for (auto& e : this->opvanfin[i].opvans)
		{
			target.draw(e);
		}
	}
	for (auto& e : this->usercar)
	{
		target.draw(e);
	}
	target.draw(this->pointbox);
	target.draw(this->uiTextgame);
	target.draw(this->rectpause);
	for (auto& e : this->uiTexts2)
	{
		target.draw(e);
	}
}
void support::renderObjects(sf::RenderTarget& target)
{
	target.draw(this->rect);
	target.draw(this->recths);
}

void support::render()
{
	this->window->clear(sf::Color());
	this->renderObjects(*this->window);
	this->renderText(*this->window);
	this->window->display();
}

void support::render2()
{
	this->window->clear(sf::Color());
	this->renderUserCar(*this->window);
	this->window->display();
}


