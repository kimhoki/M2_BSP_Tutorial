@echo off 
del .\test.bin
echo test.bin�� �����Ǿ����ϴ�.
rem pause

.\objcopy .\CW21_Data\ARM920T_RAM_Debug\ARM920T_RAM_Debug.elf -O binary .\test.bin

echo TEST.BIN�� �ۼ��Ǿ����ϴ�.
rem pause