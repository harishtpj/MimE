NAME = mime
INCL = includes
SRC = smtp.c
CC = gcc

build_smtp: $(SRC)
	@$(CC) -o $(NAME) -I$(INCL) $(SRC)
	@echo "--> Completed Building SMTP Server"

run_smtp: build_smtp
	@echo "--> Running SMTP Server"
	@./mime

test_smtp:
	@echo "--> Testing SMTP Server"
	@python3 test/smtp_clnt.py

clean:
	@rm -f $(NAME) *.o
	@echo "--> Cleaned Directory"