#include <SFML/Graphics.hpp>
#include "struct.h"
#include "cgilib.h"



void initGUI(GUI *gui)
{
       gui->display=0;
       gui->selected=30;
       gui->window.create(VideoMode(winW,winH), "DeathStar Shooter");
       
       gui->textureButton.loadFromFile("./images/button.png");
       gui->textureStarShip[0].loadFromFile("./images/starship1.png");
       gui->textureStarShip[1].loadFromFile("./images/starship2.png");
       gui->textureStarShip[2].loadFromFile("./images/starship3.png");
       

       gui->font.loadFromFile("./fonts/Starjedi.ttf");

       gui->labTitle.setFont(gui->font);
       gui->labTitle.setString("DeathStar Shooter");
       gui->labTitle.setCharacterSize(40);
       gui->labTitle.setStyle(sf::Text::Bold);
       gui->labTitle.setPosition(Vector2f(winW/2-8*30, 65));
       gui->labTitle.setColor(Color(255,232,30));
       
       for(int i=0;i<3;i++)
       {
              gui->buttons[i].setTexture(gui->textureButton);// Setting the texture for the sprites
              gui->buttons[i].setTextureRect(IntRect(0, 0, 137, 50));// Setting space and position for the sprites
              gui->spritesStarship[i].setTexture(gui->textureStarShip[i]);
              gui->spritesStarship[i].setTextureRect(IntRect(0, -40, 180, 180));
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
                            gui->buttons[i].setPosition(Vector2f(winW/2-137/2, 150+100*i));
                     } 
                     
                     char labPlay[]="play";
                     char labOption[]="options";
                     char labQuit[]="quit";
                     char *labelsText[3]={labPlay,labOption,labQuit};
                     for(int i=0;i<3;i++)
                     {
                            gui->labels[i].setString(labelsText[i]);// choix de la chaîne de caractères à affiche
                     }
                     gui->labels[0].setPosition(Vector2f(winW/2-2*14, 162));
                     gui->labels[1].setPosition(Vector2f(winW/2-3.5*14, 262));
                     gui->labels[2].setPosition(Vector2f(winW/2-2*14, 362));
              }
              break;
              case 1:
              {
                     gui->labTitle.setPosition(Vector2f(winW/2-8*30, 5));
                     
                     char lab1[]="starship 1";
                     char lab2[]="starship 2";
                     char lab3[]="starship 3";
                     char *labelsText[3]={lab1,lab2,lab3};
                     for(int i=0;i<3;i++)
                     {
                            gui->spritesStarship[i].setPosition(Vector2f(55+i*200, 150));
                            gui->buttons[i].setPosition(Vector2f(80+i*200, 390));
                            gui->labels[i].setString(labelsText[i]);
                            gui->labels[i].setCharacterSize(18);
                            gui->labels[i].setPosition(Vector2f(95+i*200, 402));
                            
                     }
              }
              break;
              case 2:
              {
                    //gui->cam.setTexture(gui->textureImages);// Setting the texture for the sprites
		     gui->cam.setPosition(Vector2f(30,100));
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
                            gui->window.draw(gui->spritesStarship[i]);
                            gui->window.draw(gui->labels[i]);
                     }
                     
              }
              break;
              case 2:
              {
                    /* for(int i=0;i<3;i++)
                     {
                            gui->buttons[i].setTextureRect(IntRect(((int)gui->selected%3!=i)?0:300, 0, 137, 50));
                            gui->labels[i].setColor(((int)gui->selected%3!=i)?Color(255,255,255):Color(44,171,212));
                            gui->window.draw(gui->buttons[i]);
                            gui->window.draw(gui->labels[i]);
                     }*/
                     //gui->cam.setTexture(gui->textureImages);
                     gui->window.draw(gui->cam);
                     
                     
              }
              break;
       }
       
       gui->window.draw(gui->labTitle);
       gui->window.display();
}
