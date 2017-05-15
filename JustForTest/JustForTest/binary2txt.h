/*	函数实现读取二进制文件并转换为十进制文件的功能	*/
//生成随机数据并以二进制形式存入binarydata.dat文件中
void generateBinary();

//从二进制文件inputfname.dat中读取数据并转换为十进制txt文件
void binary2txt(char* inputfname,char* outputfname);