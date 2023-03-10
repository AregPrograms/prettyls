CC=g++

all:
	@$(CC) prettyls.cpp -o "dist/pls" -O2
	@cp "dist/pls" "dist/ls"
	@printf "\033[34m[ SUDO ]\033[0m \033[34msudo\033[0m access might be requested to write to /usr/bin\n"
	@sudo cp "dist/pls" /usr/bin
