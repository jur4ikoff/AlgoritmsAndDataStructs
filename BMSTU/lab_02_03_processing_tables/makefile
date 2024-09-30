# Мой основной makefile

# Определение переменных
EXE_NAME := app.exe
SRC_DIR := ./src
OUT_DIR := ./out
INC_DIR := ./inc

# Настройки компиляции
CC := gcc
CFLAGS := -std=c99 -I $(INC_DIR) -Werror -Wall -pedantic -Wextra -Wvla
LINK_FLAGS := -lm

# Определение исходных файлов
cfiles := $(wildcard src/*.c)
obj_files := $(addprefix $(OUT_DIR)/, $(notdir $(cfiles:%.c=%.o)))

# Компиляция исходных файлов в объектные
$(OUT_DIR)/%.o : $(SRC_DIR)/%.c
	$(CC) $(CFLAGS) -c $< -o $@

# Компоновка в исполняемый файл
$(EXE_NAME) : $(obj_files)
	$(CC) $(obj_files) -o $@ 

# Обозначение фиктивных целей
.PHONY : clean release debug
clean:
	$(RM) *.exe out/*.o *.o

release: CFLAGS += -DNDEBUG -g0
release: $(EXE_NAME)

debug: CFLAGS += -g3 -Wfloat-conversion -Wfloat-equal
debug: $(EXE_NAME)