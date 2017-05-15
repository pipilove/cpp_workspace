#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <cstring>
#include <string>
#include <unistd.h>
#include <sstream>
#include <iostream>

using namespace std;

int k = 0;
const char *s = "3";


int __main() {
    string msg = "1 2\n";
    write(STDIN_FILENO, msg.c_str(), msg.size());

    string str;
    getline(std::cin, str);
    cout << "String: " << str << endl;

//    int size = 10;
//	int *data = new int[size];
//	memset(data, 0, size * sizeof(int));


    // read lines
//	while (NULL != fgets(buff, size, stdin)) {
//		printf("Read line with len: %d\n", strlen(buff));
//		printf("%s", buff);
//	}
//	// free buff
//	free(buff);

    int s1, s2;
    scanf("%d%d", &s1, &s2);
    printf("***%d***\n", s1);
    printf("***%d***", s2);
    return 0;
}