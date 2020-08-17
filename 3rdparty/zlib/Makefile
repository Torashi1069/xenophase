OUT = out/gcc-release
TMP = $(OUT)/tmp
SRCS = $(wildcard *.c)
OBJS = $(addprefix $(TMP)/, $(SRCS:.c=.o))

all: libz

clean:
	rm -rf $(OUT)

libz: $(OUT) $(TMP) $(OUT)/libz.lib

$(OUT):
	mkdir -p $(OUT)

$(TMP):
	mkdir -p $(TMP)

$(OUT)/libz.lib: $(OBJS)
	ar -rcs $(OUT)/libz.lib $(OBJS)

$(TMP)/%.o: %.c
	gcc -c $< -o $@ -g -O3
