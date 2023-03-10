CC=g++

linux:
	@$(CC) prettyls.cpp -o "dist/pls" -O2
	@cp "dist/pls" "dist/ls"

macos:
	@$(CC) prettyls.cpp -o "dist/pls" -O2
	@cp "dist/pls" "dist/ls"

add_path_linux:
	@echo "export PATH=$$PWD/dist:$$PATH" >> ~/.bashrc

add_path_macos:
	@echo "export PATH=$$PWD/dist:$$PATH" >> ~/.bash_profile

