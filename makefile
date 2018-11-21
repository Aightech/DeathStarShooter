
# options de compilation
CC =g++ -std=c++11
CCFLAGS = -Wall -Wno-switch -I/usr/include/opencv -g 
LDFLAGS = -lsfml-graphics -lsfml-window -lsfml-system -lpthread `pkg-config --cflags --libs opencv` #/usr/lib/x86_64-linux-gnu/libopencv_calib3d.so /usr/lib/x86_64-linux-gnu/libopencv_contrib.so /usr/lib/x86_64-linux-gnu/libopencv_core.so /usr/lib/x86_64-linux-gnu/libopencv_features2d.so /usr/lib/x86_64-linux-gnu/libopencv_flann.so /usr/lib/x86_64-linux-gnu/libopencv_gpu.so /usr/lib/x86_64-linux-gnu/libopencv_highgui.so /usr/lib/x86_64-linux-gnu/libopencv_imgproc.so /usr/lib/x86_64-linux-gnu/libopencv_legacy.so /usr/lib/x86_64-linux-gnu/libopencv_ml.so /usr/lib/x86_64-linux-gnu/libopencv_objdetect.so /usr/lib/x86_64-linux-gnu/libopencv_ocl.so /usr/lib/x86_64-linux-gnu/libopencv_photo.so /usr/lib/x86_64-linux-gnu/libopencv_stitching.so /usr/lib/x86_64-linux-gnu/libopencv_superres.so /usr/lib/x86_64-linux-gnu/libopencv_ts.so /usr/lib/x86_64-linux-gnu/libopencv_video.so /usr/lib/x86_64-linux-gnu/libopencv_videostab.so -lopencv_calib3d -lopencv_contrib -lopencv_core -lopencv_features2d -lopencv_flann -lopencv_gpu -lopencv_highgui -lopencv_imgproc -lopencv_legacy -lopencv_ml -lopencv_objdetect -lopencv_ocl -lopencv_photo -lopencv_stitching -lopencv_superres -lopencv_ts -lopencv_video -lopencv_videostab  


# fichiers du projet
SRC = shooter.c guilib.c cgilib.c mbdlib.c joystick.c
OBJ = $(SRC:.c=.o)
EXEC = shooter


# règle initiale
all: $(EXEC) clean

# dépendance des .h
shooter.o: guilib.h cgilib.h struct.h mbdlib.h
guilib.o: guilib.h struct.h
cgilib.o: cgilib.h struct.h
mbdlib.o: mbdlib.h struct.h
joystick.o: joystick.h

# règles de compilation
%.o: %.c
	$(CC) $(CCFLAGS) -o $@ -c $<
	
# règles d'édition de liens
$(EXEC): $(OBJ)
	$(CC) -o $@ $^ $(LDFLAGS)

# règles supplémentaires
clean:
	@rm -rf *.o
rmproper:
	rm -rf $(EXEC) *.o
