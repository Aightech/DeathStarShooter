CC=gcc
CFLAGS=-W -Wall -ansi -pedantic -I/usr/include/opencv -g  
LDFLAGS=/usr/lib/x86_64-linux-gnu/libopencv_calib3d.so /usr/lib/x86_64-linux-gnu/libopencv_contrib.so /usr/lib/x86_64-linux-gnu/libopencv_core.so /usr/lib/x86_64-linux-gnu/libopencv_features2d.so /usr/lib/x86_64-linux-gnu/libopencv_flann.so /usr/lib/x86_64-linux-gnu/libopencv_gpu.so /usr/lib/x86_64-linux-gnu/libopencv_highgui.so /usr/lib/x86_64-linux-gnu/libopencv_imgproc.so /usr/lib/x86_64-linux-gnu/libopencv_legacy.so /usr/lib/x86_64-linux-gnu/libopencv_ml.so /usr/lib/x86_64-linux-gnu/libopencv_objdetect.so /usr/lib/x86_64-linux-gnu/libopencv_ocl.so /usr/lib/x86_64-linux-gnu/libopencv_photo.so /usr/lib/x86_64-linux-gnu/libopencv_stitching.so /usr/lib/x86_64-linux-gnu/libopencv_superres.so /usr/lib/x86_64-linux-gnu/libopencv_ts.so /usr/lib/x86_64-linux-gnu/libopencv_video.so /usr/lib/x86_64-linux-gnu/libopencv_videostab.so -lopencv_calib3d -lopencv_contrib -lopencv_core -lopencv_features2d -lopencv_flann -lopencv_gpu -lopencv_highgui -lopencv_imgproc -lopencv_legacy -lopencv_ml -lopencv_objdetect -lopencv_ocl -lopencv_photo -lopencv_stitching -lopencv_superres -lopencv_ts -lopencv_video -lopencv_videostab  
EXEC=shooter
all:$(EXEC)
shooter: shooter.o cgilib.o
	$(CC) -o $@ $^ $(LDFLAGS)
shooter.o: shooter.c struct.h cgilib.h
	$(CC) -o $@ -c $< $(CFLAGS) $(LDFLAGS)
cgilib.o: cgilib.c struct.h
	$(CC) -o $@ -c $< $(CFLAGS) $(LDFLAGS)
clean:
	rm -rf *.o
mrproper: clean
	rm -rf $(EXEC)

