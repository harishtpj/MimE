NAME = mime
INCL = includes
SRC = smtp.c
CC = gcc

smtp: $(SRC)
	@$(CC) -o $(NAME) -I$(INCL) $(SRC)
	@echo "--> Completed Building SMTP Server"

run: smtp
	@echo "--> Running SMTP Server"
	@./mime

clean:
	@rm -f $(NAME) *.o
	@echo "--> Cleaned Directory"