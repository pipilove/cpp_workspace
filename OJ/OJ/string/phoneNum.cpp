/****************************************************************************/
/*	POJ����ʼ�4.3 ���� 487-3279�������ĵ绰����2974\1002	ƤƤ 2014-7-4 */
/****************************************************************************/
#include <iostream>
#include <string>
#include <map>
using namespace std;

#define PHONE_LEN 9

int compare(const void * elem1, const void * elem2){
	return strcmp( (char*)elem1, (char*)elem2 );
}

//map��ռ�úܴ��ڴ棡��һ��mapԪ��*3��int�����ã���
void phoneNum(){
	int count;
	scanf("%d", &count);
	map<string, int> phone;
	map<string, int>::iterator phoneIt;

	string str;
	while(count--){
		cin>>str;
		for(int i = 0; i < str.length(); i++){
			if( isalpha(str[i]) ){
				if( str[i] > 'R')
					str[i] = (str[i] - 'B') / 3 + 50;
				else
					str[i] = (str[i] - 'A') / 3 + 50;
			}
		}
		for(int i = 0; i < str.length(); i++){		//����ͬʱ����
			if( str[i] == '-' ){
				str.replace(i, 1, "");				//str.length()��1��
				i--;
			}
		}
		str.insert(3, "-");
		/*for(phoneIt = phone.begin(); phoneIt != phone.end(); phoneIt++){//�ᳬʱ������
		if( phoneIt->first == str){
		phoneIt->second ++;
		break;
		}
		}
		if( phoneIt == phone.end() )
		phone[str] =  1;*/		
		phone[str]++;								//�����ڻ��Զ��������ҳ�ֵΪ0
	}

	bool flag = true;
	for(phoneIt = phone.begin(); phoneIt != phone.end(); phoneIt++){
		if( phoneIt->second > 1){
			printf("%s %d\n", phoneIt->first.c_str(), phoneIt->second);
			flag = false;
			//cout<<phoneIt->first<<" "<<phoneIt->second<<endl;
		}
	}
	if(flag)
		printf("No duplicates.\n");
}

void phoneNum1(){
	int count;
	int i,char_i;
	scanf("%d", &count);
	char str[80];							//С�˻�runtime error
	char phone[100000][PHONE_LEN];

	/*	��ʽ��	*/
	for(int str_i = 0; str_i < count; str_i++){
		char_i = 0;
		scanf("%s", str);
		for(i = 0; str[i] != 0; i++){		//�����
			if(str[i] == '-')
				continue;
			if( char_i == 3)
				phone[str_i][char_i++] = '-';
			if( isalpha(str[i]) ){
				if(str[i] <= 'R')
					phone[str_i][char_i++] = (str[i] - 'A') / 3 +50;//Ҳ��ͨ�����
				else
					phone[str_i][char_i++] = (str[i] - 'B') / 3 +50;
			}else{
				phone[str_i][char_i++] = str[i];
			}
		}
		phone[str_i][char_i] = 0;			//�ַ���ĩβ��0	<=>'\0'
	}

	/*	����		*/
	qsort(phone, count, PHONE_LEN, compare);

	/*	ͳ��		*/
	int j;
	bool no_duplicates = true;
	for(i = 0; i < count; ){
		for(j = i + 1; j < count; j++){
			if( strcmp((char*)phone[i], (char*)phone[j]) )
				break;
		}
		if(j - i > 1){
			printf("%s %d\n", phone[i], j - i);
			no_duplicates = false;
		}
		i = j;
	}
	if(no_duplicates)
		printf("No duplicates.\n");
}

int __549836main(){
	//phoneNum();
	phoneNum1();
	return 0;
}
