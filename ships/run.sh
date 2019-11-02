CMP=$1

if ! [ -z ${CMP+x} ] ;
  then CMP=g++
fi

# Remove the old *.o
rm ./*.o

# Compile the basics
$CMP -g -Wall -c direction.cpp util.cpp point.cpp gamemode.cpp

# Compile the classes
$CMP -g -c ship.cpp point.cpp direction.cpp

$CMP -g -I ./ -c player.cpp ship.o

$CMP -g -I ./ -c ships.cpp util.o

# Link the files
$CMP -Wall -g -o main ships.o

# Run the code
./main