CC = g++ 
CFLAGS = -g -Wall 

main :  src/main.o particle.o 
		cd src/ && $(CC) $(CCFLAGS) -o main main.o particle.o && mv main ../ 

main.o :  src/main.cpp src/particle.h 
		cd src/ && $(CC) $(CCFLAGS) -c main.cpp particle.h 

particle.o : src/particle.cpp src/particle.h
			cd src/ && $(CC) $(CCFLAGS) -c particle.cpp particle.h 
clean : 
		rm src/*.o && rm src/*.gch