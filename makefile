CXX = g++
CFLAGS = -Wall -Wextra -Werror
DEBUG = -g
OBJS = main.o string.o tree.o food.o
NAME = menu

make: $(OBJS)
	$(CXX) $(CFLAGS) -o $(NAME) $(OBJS)

debug: $(OBJS)
	$(CXX) $(CFLAGS) $(DEBUG) -o $(NAME) $(OBJS)

clear: $(OBJS)
	rm -rvf $(OBJS) $(NAME)

clean: $(OBJS)
	rm -rvf $(NAME)
