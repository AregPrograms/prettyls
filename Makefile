CC=g++
CFLAGS = -O2 -Wall

linux: _warning_suppression
	@$(CC) prettyls.cpp -o "dist/pls" $(CFLAGS)
	@cp "dist/pls" "dist/ls"

macos: _warning_suppression
	@$(CC) prettyls.cpp -o "dist/pls" $(CFLAGS)
	@cp "dist/pls" "dist/ls"

add_path_linux:
	@echo "export PATH=$$PWD/dist:$$PATH" >> ~/.bashrc

add_path_macos:
	@echo "export PATH=$$PWD/dist:$$PATH" >> ~/.bash_profile

_warning_suppression:
ifeq ($(CC), clang++) # will have to include clang as well, but ORs are goofy
	@printf "Building with clang++... (expiremental)\n"
CFLAGS += -Wno-c++17-extensions -std=c++17
else
	@echo Building...
endif
