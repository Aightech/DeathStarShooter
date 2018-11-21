#include <stdio.h>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include "guilib.h"
#include "cgilib.h"
#include "joystick.h"
#include "mbdlib.h"
#include <iostream>
#include "joystick.h"
#include <string>



int main()
{
       Pantilt pantilt = {80,80,40,140,40,100,0.3};
       initPantilt(&pantilt);
  cJoystick js;
  GUI gui;
  int flag;
  Camera cam;
  struct _CGI afterEffect;
  Patatoide patate;
  Texture texture;
  unsigned char pixels[W*H*4];
  cam.frameNumber = 0;
  initGUI(&gui);
  createMenu(&gui);
  init_mask(&afterEffect);
  patate.moy = 1500;
  int nb_points = 0;
  //Pantilt pantilt = {80,80,40,140,40,100,0.3};
  //initPantilt();
  if(!init_cam(&cam))
    {
      printf("Erreur lors de l'ouverture de la caméra\n");
      return 0;
    }
  else
    {
      afterEffect.DeathStar = cvLoadImage("./images/death-star-v.jpg", CV_LOAD_IMAGE_COLOR );/*On charge l'image de l'étoile de la mort*/
      if(!afterEffect.DeathStar)
	{
	  printf("Erreur lors de l'ouverture de l'étoile de la mort !! Mais que fait Anakin ??\n");
	}
      
      afterEffect.Explosion = cvLoadImage("./images/explosion.jpg", CV_LOAD_IMAGE_COLOR); /* On charge l'image de l'étoile de la mort */

      /*Création du mask permettant d'enlever le fond du cockpit*/

      while(gui.window.isOpen())
	{
	  Event event;
	  while(gui.window.pollEvent(event))
	    {
	      if(event.type == Event::Closed)
		gui.window.close();
	    }
              
	  switch(gui.display)
	    {
	    case 0:
	      {
		gui.selected+=(js.joystickValue(1)>10000)?0.06:0;
		gui.selected+=(js.joystickValue(1)<-10000)?-0.06:0;
		
		if(js.buttonPressed(0)>0)
		  {
		    switch((int)gui.selected%3)
		      {
		      case 0:
			gui.display=1;
			createMenu(&gui);
			break;
                                          
		      case 1:
			break;
                                          
		      case 2:
			gui.window.close();
			break;
		      }
		  }
		  usleep(100000);
		updateGUI(&gui);
		
	      }
	      break;
	    case 1:
	      {
	      if(js.buttonPressed(1)>0)
	      {
	              gui.display=0;
	              usleep(100000);
	              createMenu(&gui);
	       }
		gui.selected+=(js.joystickValue(0)>10000)?0.06:0;
		gui.selected+=(js.joystickValue(0)<-10000)?-0.06:0;
		if(js.buttonPressed(0)>0)
		  {
		    gui.starship=(int)gui.selected%3;
		    printf("starship: %d\n",gui.starship);
		    afterEffect.Cockpit = init_cockpit(gui.starship);/* Initialisations liées à l'image du cockpit */
		    printf("depth: %d\n",afterEffect.Cockpit->depth);
		    create_mask(&afterEffect, 0, 0, 0);
		    gui.display=2;
		    createMenu(&gui);
		    usleep(100000);
		  }
		updateGUI(&gui);
	      }
	      break;
	    case 2:
	      {
                           
		gui.window.clear(Color(48,48,48));
		//Texture texture;
                            
		gui.textureImages.create(W, H); 
                            
		unsigned char pixels[W*H*4];

		for(int i = 0; i < W*H*4; i += 4) {
		  pixels[i] = 0; // obviously, assign the values you need here to form your color
		  pixels[i+1] = 0;
		  pixels[i+2] = 0;
		  pixels[i+3] = 255;
		}

		gui.textureImages.update(pixels);
		//Sprite sprite;
		gui.cam.setTexture(gui.textureImages);// Setting the texture for the sprites
		//gui.cam.setPosition(Vector2f(55,100));
                 updateGUI(&gui);           
		gui.window.draw(gui.cam);
		gui.window.display();//updateGUI(&gui);

		/*cam.frame = cvQueryFrame(cam.cap);
		if(!cam.frame)
		  {
		    printf("Erreur lors de l'acquisition de l'image\n");
		    break;
		  }

		//On créé nos images que l'on va utiliser

		cam.HSV = cvCreateImage(cvGetSize(cam.frame), 8, 3);
		cam.threshed = cvCreateImage(cvGetSize(cam.frame), 8, 1);

		//On passe de l'espace BGR à l'espace HSV. On stocke l'image dans edges_HSV

		cvCvtColor(cam.frame, cam.HSV, CV_BGR2HSV);

		//On binarise l'image edges_HSV en la seuillant avec des bornes basses et hautes (pour garder uniquement le bleu)

		cvInRangeS(cam.HSV, cam.lowerBound, cam.higherBound, cam.threshed);

		//EROSION

		cvErode(cam.threshed, cam.threshed, cam.elem, 1);

		//Calcul du centre de l'image et du nombre moyen de pixels détectés faire focntion qui retourne struc centre

		calcul_patate(&patate, &cam, 0.1);

		insert_image(&afterEffect, &cam, &patate, 1);//On insère l'étoile de la mort

		if(js.buttonPressed(0)>0)    
		  flag = 1;
		
		if(flag == 1)
		  {
		    laser(cam.frame, cam.frameNumber);
		    cam.frameNumber++;
		    if(cam.frameNumber == 10)
		      {
			cam.frameNumber = 0;	
			flag = 0;
*/
			if(isTouched(patate))
			{
			                     nb_points++;
						insert_image(&afterEffect, &cam, &patate, 2);// On insère l'explosion 
					//usleep(500000);

		      }
		  }
		  }
		  if(js.buttonPressed(5)>0)
	             {
	                     if(abs(patate.centre.x-cam.cols/2)>10)
                            {
                                   pantilt.posM1+=(patate.centre.x-cam.cols/2)*-0.01*pantilt.ease;
                                   pantilt.posM1=(pantilt.posM1>pantilt.minM1)?pantilt.posM1:pantilt.minM1;
                                   pantilt.posM1=(pantilt.posM1<pantilt.maxM1)?pantilt.posM1:pantilt.maxM1;
                            }
                            if(abs(patate.centre.y-cam.rows/2)>10)
                            {
                                   pantilt.posM2+=(patate.centre.y-cam.rows/2)*0.01*pantilt.ease;
                                   pantilt.posM2=(pantilt.posM2>pantilt.minM2)?pantilt.posM2:pantilt.minM2;
                                   pantilt.posM2=(pantilt.posM2<pantilt.maxM2)?pantilt.posM2:pantilt.maxM2;
                            }
                            movePantilt(&pantilt);
                            //printf("hey\n");
	              }  
	      

		insert_image(&afterEffect, &cam, &patate, 0);// On insère le cockpit 
              
                    
		gui.textureImages.create(W, H); 
                            
		unsigned char pixels[W*H*4];
              int j=0;
		for(int i = 0; i < W*H*3; i += 3) {
		  pixels[i+j] = cam.frame->imageData[i+2]; // obviously, assign the values you need here to form your color
		  pixels[i+j+1] = cam.frame->imageData[i + 1];
		  pixels[i+j+2] = cam.frame->imageData[i ];
		  pixels[i+j+3] = 255;
		  j++;
		}

		gui.textureImages.update(pixels,W,H,0,0);
		//Sprite sprite;
		gui.cam.setTexture(gui.textureImages);// Setting the texture for the sprites
		//gui.cam.setPosition(Vector2f(55,100));
                 updateGUI(&gui);           
		gui.window.draw(gui.cam);
		gui.window.display();//updateGUI(&gui);


		release_boucle(&afterEffect, &cam);
		if(cvWaitKey(27) != -1)
		  break;
	      }
	      break;
	    }
              
	  
	}
      release_final(&cam, &afterEffect);
    }
  return 0;
}
