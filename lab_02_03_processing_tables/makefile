# Мой основной makefile

# Определение переменных
EXE_NAME := app.exe
SRC_DIR := ./src
OUT_DIR := ./out
INC_DIR := ./inc

# Настройки компиляции
CC := gcc
CFLAGS := -std=gnu99 -O0 -I $(INC_DIR) -Werror -Wall -pedantic -Wfloat-conversion -Wfloat-equal -Wvla -Wextra # Флаги компиляции по умоланию
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
.PHONY : clean release debug asan msan ubsan 
clean:
	$(RM) *.exe $(OUT_DIR)/*.o *.o *.out $(OUT_DIR)/*.gcno $(OUT_DIR)/*.gcda $(OUT_DIR)/*.d *.gcov

# Цель build release
release: CFLAGS += -DNDEBUG -g0
release: $(EXE_NAME)

# Цель build debug
debug: CFLAGS += -g3 -O0
debug: $(EXE_NAME)


# Цель build asan
asan: CC = clang
asan: CFLAGS += -g -fno-omit-frame-pointer -fsanitize=address
asan: LDFLAGS := -fsanitize=address
asan: $(EXE_NAME)

# Цель build msan
msan: CC = clang
msan: CFLAGS += -g -fPIE -fno-omit-frame-pointer -fsanitize=memory
msan: LDFLAGS := -fsanitize=memory -pie
msan: $(EXE_NAME)

# Цель build ubsan
ubsan: CC = clang
ubsan: CFLAGS += -fno-omit-frame-pointer -fsanitize=undefined -g
ubsan: LDFLAGS := -fsanitize=undefined
ubsan: $(EXE_NAME)
