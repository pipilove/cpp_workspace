//Test class Set
#include <iostream>
#include <stdio.h>
#include "Set.h"

void menu(){				//人机交互菜单
	std::cout<< std::endl;
	std::cout<< "a.  Show the elements of two sets";
	std::cout<< std::endl;
	std::cout<< "b.  Determine whether the set is empty";
	std::cout<< std::endl;
	std::cout<< "c.  Returns the number of elements";
	std::cout<< std::endl;
	std::cout<< "d.  Empties the set";
	std::cout<< std::endl;
	std::cout<< "e.  Put a new element into the set";
	std::cout<< std::endl;
	std::cout<< "f.  Delete a element from the set";
	std::cout<< std::endl;
	std::cout<< "g.  Determine whether the element belongs to the set";
	std::cout<< std::endl;
	std::cout<< "h.  Determine whether the set is contained in the set";
	std::cout<< std::endl;
	std::cout<< "i.  Determine whether sets are equal";
	std::cout<< std::endl;
	std::cout<< "j.  Find the union of two sets";
	std::cout<< std::endl;
	std::cout<< "k. Find the intersection of two sets";
	std::cout<< std::endl;
	std::cout<< "l. Find the difference of two sets";
	std::cout<< std::endl;
	std::cout<< "m. Return to the Main Menu";
	std::cout<< std::endl;
	std::cout<< "n. Quit the program";
	std::cout<< std::endl;
}

int __main(){
	menu();
	
	for (; true;){
		
		char c = 0;
		Set s1;
		Set s2;


			std::cout<<"Please choose the operation:"<<std::endl;
			std::cin>> c;
			getchar();

			switch(c){
			case 'a': case 'A':{		//不区分大小写，展示集合Set_1,Set_2中的元素
				std::cout<< std::endl;
				std::cout<< "\tSet_1 = ";
				s1.ShowElement();
				std::cout<< std::endl;
				std::cout<< "\tSet_2 = ";
				s2.ShowElement();
				std::cout<< std::endl;

				std::cout<< "Press ENTER to continue.";
				getchar();
				break;
					  }

			case 'b': case 'B':{		//判断集合Set_1,Set_2是否为空
				std::cout<< std::endl;
				std::cout<< ((s1.IsEmpt())? "\t\tSet_1 is Empty!": "\t\tSet_1 is not Empty.");
				std::cout<< std::endl;
				std::cout<< ((s2.IsEmpt())? "\t\tSet_2 is Empty!": "\t\tSet_2 is not Empty.");
				std::cout<< std::endl;

				std::cout<< "Press ENTER to continue.";
				getchar();
				break;
					  }

			case 'c': case 'C':{		//查看集合Set_1,Set_2中元素的多少
				std::cout<< std::endl;
				std::cout<< "\t\tThere are  "<< s1.size()<< "  element(s) in Set_1.";
				std::cout<< std::endl;
				std::cout<< "\t\tThere are  "<< s2.size()<< "  element(s) in Set_2.";
				std::cout<< std::endl;

				std::cout<< "Press ENTER to continue.";
				getchar();
				break;
					  }

			case 'd': case 'D':{		//选择集合Set_1或者Set_2，并清除
				
				
				std::cout<< "Choose the Set you want to clear:\t1. Set_1\t2.Set_2\t\t3.Back";
				std::cout<< std::endl;

				char _s;
				std::cin>> _s;
				getchar();

				switch(_s){
				case '1':
					s1.clear();
					std::cout<< "\t\tSet_1 have been cleared!";
					break;

				case '2':
					s2.clear();
					std::cout<< "\t\tSet_2 have been cleared!";
					break;

				case '3':
					break;

				default:
					std::cout<< std::endl;
					std::cout<< "Error!";
				}

				std::cout<< "Press ENTER to continue.";
				getchar();
				break;
					  }

			case 'e': case 'E':{                        //选择集合Set_1或者Set_2，并插入新元素_e
				
				
				std::cout<< "Choose the Set you want add into:\t1. Set_1\t2.Set_2\t\t3.Back";

				char s;
				std::cin>> s;
				getchar();

				int _e;
				switch(s){
				case '1':{
					
					
					std::cout<< "Please input the Number you want to add into  Set_1:";
					std::cout<< std::endl;

					std::cin>> _e;
					getchar();
					s1.insert(_e);
					std::cout<< "\t\tSet_1 = ";
					s1.ShowElement();
					break;
						 }

				case '2':{
					
					
					std::cout<< "Please input the Number you want to add into  Set_2:";
					std::cout<< std::endl;

					std::cin>> _e;
					getchar();
					s2.insert(_e);
					std::cout<< "\t\tSet_2 = ";
					s2.ShowElement();
					break;
						 }

				case '3':
					break;

				default:
					std::cout<< std::endl;
					std::cout<< "Error!";
				}

				std::cout<< "Press ENTER to continue.";
				getchar();
				break;
					   }

			case 'f': case 'F':{		//选择集合Set_1或者Set_2，并从中删除一个元素_e
				
				
				std::cout<< "Choose the Set you want delete from:\t1. Set_1\t2.Set_2\t\t3.Back";
				std::cout<< std::endl;

				char s;
				std::cin>> s;
				getchar();

				int _e;
				switch(s){
				case '1':{
					
					
					std::cout<< "Please input the Number you want to delete from  Set_1:";
					std::cout<< std::endl;

					std::cin>> _e;
					getchar();
					s1.deleteElement(_e);
					std::cout<< std::endl;
					std::cout<< "\t\tSet_1 = ";
					s1.ShowElement();
					break;
						 }

				case '2':{
					
					
					std::cout<< "Please input the Number you want to delete from  Set_2:";
					std::cout<< std::endl;

					std::cin>> _e;
					getchar();
					s2.deleteElement(_e);
					std::cout<< std::endl;
					std::cout<< "\t\tSet_2 = ";
					s2.ShowElement();
					break;
						 }

				case '3':
					break;

				default:
					std::cout<< std::endl;
					std::cout<< "Error!";

				}

				std::cout<< "Press ENTER to continue.";
				getchar();
				break;
					  }

			case 'g': case 'G':{                        //判断集合Set_1，Set_2是否包含某元素
				
				
				std::cout<< "Please intput the number you want :"<< std::endl;

				int _e;
				std::cin>> _e;
				getchar();
				std::cout<< ((s1.IsElement(_e))? "\t\tThe number is in Set_1.": "\t\tThe number is NOT in Set_1.");
				std::cout<< std::endl;
				std::cout<< ((s2.IsElement(_e))? "\t\tThe number is in Set_2.": "\t\tThe number is NOT in Set_2.");

				std::cout<< "Press ENTER to continue.";
				getchar();
				break;
					  }


			case 'h': case 'H':{                        //判断集合Set_1（Set_2）是否包含Set_2（Set_1）
				std::cout<< std::endl;
				std::cout<< ((s2.IsSubset(s1))? "\t\tSet_1 is a subset of Set_2.": "\t\tSet_1 is NOT a subset of Set_2.");
				std::cout<< std::endl;
				std::cout<< ((s1.IsSubset(s2))? "\t\tSet_2 is a subset of Set_1.": "\t\tSet_2 is NOT a subset of Set_1.");
				std::cout<< std::endl;

				std::cout<< "Press ENTER to continue.";
				getchar();
				break;
					  }


			case 'i': case 'I':{                        //判断集合Set_1，Set_2是否相等
				std::cout<< std::endl;
				std::cout<< ((s1.IsEqual(s2))? "\t\tSet_1 is equal with Set_2.": "\t\tSet_1 is NOT equal with Set_2.");
				std::cout<< std::endl;

				std::cout<< "Press ENTER to continue.";
				getchar();
				break;
					  }


			case 'j': case 'J':{                        //求集合Set_1，Set_2的交集
				std::cout<< std::endl;
				std::cout<< "Set_1 Union Set_2 is:";
				std::cout<< std::endl;
				std::cout<< "";
				s1.Union(s2).ShowElement();
				std::cout<< std::endl;

				std::cout<< "Press ENTER to continue.";
				getchar();
				break;
					  }


			case 'k': case 'K':{                        //求集合Set_1，Set_2的并集
				std::cout<< std::endl;
				std::cout<< "Set_1 Intersection Set_2 is:";
				std::cout<< std::endl;
				std::cout<< "";
				s1.intersection(s2).ShowElement();
				std::cout<< std::endl;

				std::cout<< "Press ENTER to continue.";
				getchar();
				break;
					  }


			case 'l': case 'L':{                        //求集合Set_1，Set_2的差集
				std::cout<< std::endl;
				std::cout<< "Set_1 Difference Set_2 is:";
				std::cout<< "\t";
				s1.difference(s2).ShowElement();
				std::cout<< std::endl;
				std::cout<< "Set_2 Difference Set_1 is:";
				std::cout<< "\t";
				s2.difference(s1).ShowElement();
				std::cout<< std::endl;

				std::cout<< "Press ENTER to continue.";
				getchar();
				break;
					  }



			case 'n': case 'N':{                        //推出程序
				
				std::cout<< std::endl;;
				return 0;
				break;
					  }


			default:{                        //输入错误
				std::cout<< std::endl;
				std::cout<< "Error!"<< std::endl;
				std::cout<< "Press ENTER to continue..."<< std::endl;
				getchar();
				break;
					}
			}
	}

};


