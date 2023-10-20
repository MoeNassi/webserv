NAME = server

C_NAME = client

CPP = c++

CFLAGS = -Wall -Wextra -Werror -std=c++98 -g -fsanitize=address

SRC = server.cpp

C_SRC = client.cpp

OBJ = $(SRC:.cpp=.o)

C_OBJ = $(C_SRC:.cpp=.o)

WHITE = \033[1;37m

HEADER = server.hpp

C_HEADER = client.hpp

all : $(NAME) $(C_NAME)

$(NAME) : $(OBJ) $(HEADER)
	@echo "${WHITE}COMPILING ${END}"
	@$(CPP) $(CFLAGS) $(OBJ) -o $(NAME)

$(C_NAME) : $(C_OBJ) $(C_HEADER)
	@echo "${WHITE}COMPILING ${END}"
	@$(CPP) $(CFLAGS) $(C_OBJ) -o $(C_NAME)

%.o : %.cpp $(HEADER)
	@echo "${WHITE}LINKING ${END}"
	@$(CPP) $(CFLAGS) $(CPPFLAGS) -c $< -o $@

clean :
	@echo "${WHITE}removing object files ${END}"
	@rm -rf $(OBJ) $(C_OBJ)

fclean : clean
	@echo "${WHITE}removing executable ${END}"
	@rm -rf $(NAME) $(C_NAME)

re : fclean all

.PHONY : clean fclean re