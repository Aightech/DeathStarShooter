#include <SFML/Graphics.hpp>
#include "struct.h"
#include "cgilib.h"



void initGUI(GUI *gui)
{
       gui->display=0;
       gui->selected=30;
       gui->window.create(VideoMode(600, 500), "DeathStar Shooter");
       
       gui->textureButton.loadFromFile("button.png");

       gui->font.loadFromFile("Starjedi.ttf");

       gui->labTitle.setFont(gui->font);
       gui->labTitle.setString("DeathStar Shooter");
       gui->labTitle.setCharacterSize(40);
       gui->labTitle.setStyle(sf::Text::Bold);
       gui->labTitle.setPosition(Vector2f(50, 65));
       gui->labTitle.setColor(Color(255,232,30));
       
       for(int i=0;i<3;i++)
       {
              gui->buttons[i].setTexture(gui->textureButton);// Setting the texture for the sprites
              gui->buttons[i].setTextureRect(IntRect(0, 0, 137, 50));// Setting space and position for the sprites
              gui->labels[i].setCharacterSize(20);// choix de la taille des caractères
              gui->labels[i].setFont(gui->font);// choix de la police à utiliser
       }
       
}

void createMenu(GUI *gui)
{
       switch(gui->display)
       {
              case 0:
              {
                    // Sprites setting up
                     for(int i=0;i<3;i++)
                     {
                            gui->buttons[i].setTexture(gui->textureButton);// Setting the texture for the sprites
                            gui->buttons[i].setTextureRect(IntRect(0, 0, 137, 50));// Setting space and position for the sprites
                            gui->buttons[i].setPosition(Vector2f(225, 150+100*i));
                     } 
                     
                     char labPlay[]="play";
                     char labOption[]="options";
                     char labQuit[]="quit";
                     char *labelsText[3]={labPlay,labOption,labQuit};
                     for(int i=0;i<3;i++)
                     {
                            gui->labels[i].setString(labelsText[i]);// choix de la chaîne de caractères à affiche
                     }
                     gui->labels[0].setPosition(Vector2f(265, 162));
                     gui->labels[1].setPosition(Vector2f(250, 262));
                     gui->labels[2].setPosition(Vector2f(265, 362));
              }
              break;
              case 1:
              {
                     gui->labTitle.setPosition(Vector2f(50, 5));
                     
                     char lab1[]="starship 1";
                     char lab2[]="starship 2";
                     char lab3[]="starship 3";
                     char *labelsText[3]={lab1,lab2,lab3};
                     for(int i=0;i<3;i++)
                     {
                            gui->buttons[i].setPosition(Vector2f(35+i*200, 430));
                            gui->labels[i].setString(labelsText[i]);
                            gui->labels[i].setCharacterSize(18);
                     }
                    
                     
                     gui->labels[0].setPosition(Vector2f(50, 442));
                     gui->labels[1].setPosition(Vector2f(250, 442));
                     gui->labels[2].setPosition(Vector2f(450, 442));
              }
              break;
       }
}

void updateGUI(GUI *gui)
{
       gui->window.clear(Color(48,48,48));

       // Sprites drawing
       switch(gui->display)
       {
              case 0:
              {
                     for(int i=0;i<3;i++)
                     {
                            gui->buttons[i].setTextureRect(IntRect(((int)gui->selected%3!=i)?0:300, 0, 137, 50));
                            gui->labels[i].setColor(((int)gui->selected%3!=i)?Color(255,255,255):Color(44,171,212));
                            gui->window.draw(gui->buttons[i]);
                            gui->window.draw(gui->labels[i]);
                     }
                     
              }
              break;
              
              case 1:
              {
                     for(int i=0;i<3;i++)
                     {
                            gui->buttons[i].setTextureRect(IntRect(((int)gui->selected%3!=i)?0:300, 0, 137, 50));
                            gui->labels[i].setColor(((int)gui->selected%3!=i)?Color(255,255,255):Color(44,171,212));
                            gui->window.draw(gui->buttons[i]);
                            gui->window.draw(gui->labels[i]);
                     }
                     
              }
              break;
              case 2:
              {
                     for(int i=0;i<3;i++)
                     {
                            gui->buttons[i].setTextureRect(IntRect(((int)gui->selected%3!=i)?0:300, 0, 137, 50));
                            gui->labels[i].setColor(((int)gui->selected%3!=i)?Color(255,255,255):Color(44,171,212));
                            gui->window.draw(gui->buttons[i]);
                            gui->window.draw(gui->labels[i]);
                     }
                     
              }
              break;
       }
       
       gui->window.draw(gui->labTitle);
       gui->window.display();
}
