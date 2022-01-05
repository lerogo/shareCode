1. 系统能够编译，内核模块、用户程序均正常。
   本机单独make（非mips环境）app能够正常运行和内核能够正常加载（insmod）
2. 文件夹“题目2”、“题目3”中编译好的系统是一样的。
   若作为内核模块，内核集成到了“/lib/modules/kernel/drivers/hellohhlkernel”下面，否则集成到了整体系统里面了。
   其中app在/bin/hellohhl