NAME = webserv

CPP = c++

CFLAGS = -Wall -Wextra -Werror -std=c++98 -g -fsanitize=address

SRC = server.cpp main.cpp

OBJ = $(SRC:.cpp=.o)

WHITE = \033[1;37m

HEADER = server.hpp

C_HEADER = client.hpp

all : $(NAME)

$(NAME) : $(OBJ) $(HEADER)
	@echo "${WHITE}COMPILING ${END}"
	@$(CPP) $(CFLAGS) $(OBJ) -o $(NAME)

%.o : %.cpp $(HEADER)
	@echo "${WHITE}LINKING ${END}"
	$(CPP) $(CFLAGS) -c $< -o $@

clean :
	@echo "${WHITE}removing object files ${END}"
	@rm -rf $(OBJ)

fclean : clean
	@echo "${WHITE}removing executable ${END}"
	@rm -rf $(NAME)

re : fclean all

.PHONY : clean fclean re