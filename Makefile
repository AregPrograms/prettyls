CC=g++

linux:
	@$(CC) prettyls.cpp -o "dist/pls" -O2

macos:
	@$(CC) prettyls.cpp -o "dist/pls" -O2

add_path_linux:
	@echo "export PATH=$$PWD/dist:$$PATH" >> ~/.bashrc

add_path_macos:
	@echo "export PATH=$$PWD/dist:$$PATH" >> ~/.bash_profile

