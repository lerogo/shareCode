# -ffunction-sections和 -fdata-sections 将每个函数或符号创建为一个sections
# -fPIC 告诉编译器产生与位置无关代码(Position-Independent Code)
CFLAGS += -ffunction-sections -fdata-sections -fPIC -std=gnu99
# 指示链接器去掉不用的section
LDFLAGS += -Wl,--gc-sections

all : main.o Makefile
	$(CC) -o hellohhl main.o $(LDFLAGS)

main.o : main.c
	$(CC) -c main.c $(CFLAGS)

clean :
	rm -f main.o

clean-all :
	rm -f hellohhl *.o

romfs:
	$(ROMFSINST) hellohhl /bin/hellohhl