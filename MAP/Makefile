##########################################
#	Project  : Game Dev		 #
#	Author   : Guillaume `Guss` Dua	 #
#	Location : South Korea		 #
##########################################

CC		=	g++
CFLAGS		=	-g3 -W -Wall -ansi -pedantic ‑‑forceinline -Wunknown-pragmas
LDFLAGS		=	 -lsfml-window -lsfml-graphics -lsfml-system -ldl
EXEC		=	mapLoader
SRC		=	$(wildcard 	./*.cpp					\
					../AEntitySprites.cpp			\
					../Geometry.cpp				\
					../Entity.cpp				\
					../AEntity.cpp				\
					../Collisionable.cpp			\
					../Moveable.cpp				\
					../BEHAVIOURS/IEntityBehaviour.cpp	\
					../AGameObject.cpp			\
					../GameSystem_basic.cpp			\
					../GameSystem.cpp			\
					../BindedEvent.cpp			\
					)
OBJ		=	$(SRC:.cpp=.o)

all:	$(EXEC)

$(EXEC):$(OBJ)
	$(CC) -o $(EXEC) $^ $(LDFLAGS) $(LIBS)


%.o:	%.c
	$(CC) -o $@ -c $< $(CFLAGS)

clean:
	rm -rf  *.o
	rm -f *~
	rm -f *#
	rm -rf  */*.o
	rm -f */*~
	rm -f */*#

fclean:	clean
	rm -f $(EXEC)

re:	fclean all

info_code:
	echo -e `wc -l ./*.cpp ./*.h ./*.hpp`
