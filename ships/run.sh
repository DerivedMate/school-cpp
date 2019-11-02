# Remove the old *.o
rm ./*.o

# Compile the basics
g++ -g -Wall -c direction.cpp util.cpp point.cpp gamemode.cpp

# Compile the classes
g++ -g -c ship.cpp point.cpp direction.cpp

g++ -g -I ./ -c player.cpp ship.o

g++ -g -I ./ -c ships.cpp util.o

# Link the files
g++ -Wall -g -o main ships.o

# Run the code
# ./main