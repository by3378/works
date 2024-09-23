//1-3不再输入金额的版本，并更新一些对误操作的处理,对投币找零进行了优化
#include <stdio.h>
#include <stdbool.h>
void input_and_change_function(int total_money);
int purchase(int price,int*number,int channel,char type,int*total_money);
int goods_output(int channel,int number,char type,int price);
int main(void)
{
	char type;
	int channel,price,number,check;
	printf("请依次输入货物种类(大写字母)，通道标号（正整数），货物单价（正整数），货物个数（正整数）:\n");
	check = scanf(" %c %d %d %d",&type,&channel,&price,&number);
	while(check!=4 )
	{
		printf("货物摆放不合要求，请重新摆放\n");
		printf("请依次输入货物种类(大写字母)，通道标号（正整数），货物单价（正整数），货物个数（正整数）:\n");
		while(getchar()!='\n')
		    continue;
		check = scanf(" %c %d %d %d",&type,&channel,&price,&number);
        
	}

    goods_output(channel,number,type,price);
	
    int total_money;
	int re_turn = purchase(price,&number,channel,type,&total_money);
    while(re_turn)
        {
			input_and_change_function(total_money);
			goods_output(channel,number,type,price);
			re_turn = purchase(price,&number,channel,type,&total_money);
		}//重复购买

	return 0;   
	
}


//确认货物摆放的好办法是数组，留到下一个版本实现

int goods_output(int channel,int number,char type,int price)
{
   	if(number == 0)
    {
	    printf("%d通道的%c货物已售罄。",channel,type);
		return 0;
    }
	printf("现在售货机的存货情况是：\n");
	printf("%d: ",channel);
	int i;
	for(i=0;i<number;i++)
	    printf("%c",type);
	printf(" %d\n",price);
	return 1;
}



int purchase(int price,int*number,int channel,char type,int*total_money)//实现单次购买
{
	int CHANNEL,NUMBER,check;
	char TYPE;
	
	printf("请依次输入要购买的货物种类，它所处的通道标号以及购买数量，输入3个q以放弃购买:\n");
	check = scanf(" %c %d %d",&TYPE,&CHANNEL,&NUMBER);
	
	while(check != 3)
		{
			if(TYPE=='q')
			{
				printf("您已放弃购买，再见\n");
				return 0;
			}		
			else
			{
			    printf("输入格式错误，请重新输入\n");
			    printf("请依次输入要购买的货物种类，它所处的通道标号以及购买数量，输入3个q以放弃购买:\n");
			   	while(getchar()!='\n')
		            continue;
				check = scanf(" %c %d %d",&TYPE,&CHANNEL,&NUMBER);	
			}
		}

	while(check == 3)
	    {   
			if(TYPE!=type || CHANNEL !=channel)
	        {
	        	printf("输入与实际货物摆放不符,请重新输入。\n");
			    printf("请依次输入要购买的货物种类，它所处的通道标号以及购买数量，输入3个q以放弃购买:\n");
				while(getchar()!='\n')
		            continue;
				check = scanf(" %c %d %d",&TYPE,&CHANNEL,&NUMBER);
			    if(TYPE=='q')
			    {
				printf("您已放弃购买，再见");
				return 0;
			    }		
			}
			
			else if(NUMBER>*number)
            {
            	printf("抱歉，售货机中只有%d个%c货物\n",*number,type);
    	    	printf("请重新输入\n");
    	    	printf("请依次输入要购买的货物种类，它所处的通道标号以及购买数量，输入3个q以放弃购买：\n");
	            	while(getchar()!='\n')
		            continue;
				check = scanf(" %c %d %d",&TYPE,&CHANNEL,&NUMBER);
	            if(TYPE=='q')
			    {
				    printf("您已放弃购买，再见");
				    return 0;
				}
			}
			
			else 
	    	{
                *number-=NUMBER;
                *total_money = NUMBER*price;
				return 1;
	    	}
	    	
		}
	
    return 0;
}



void input_and_change_function(int total_money)//投币与找零
{
	int current_money = 0;
	int input_money,change;
	printf("请开始投币（只接受1元、2元、5元）:");
    while(current_money<total_money)
	    {
	    	scanf("%d",&input_money);
	        if(input_money!=1 && input_money!=2 && input_money!=5 )
			    {
			    	printf("抱歉，我们只接受1元、2元、5元\n");
			    	input_money = 0;
				}
			current_money+=input_money;
	        if(current_money<total_money)
			    printf("请继续投币:");
			else
		    {
			    printf("金额足够！开始找零：\n");
			    change=current_money-total_money;
	            printf("找您%d元\n",change);
			}
		}

}