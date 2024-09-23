//将前两个等级串联起来，并支持重复购买
#include <stdio.h>
void input_and_change_function(int total_money);
int purchase(int price,int*number,char type);
int main(void)
{
	char type;//货物种类
	int channel,price,number;//通道标号，货物单价，货物个数
	printf("请依次输入货物种类，通道标号，货物单价，货物个数(使用空格分隔):\n");
	scanf(" %c %d %d %d",&type,&channel,&price,&number);
	
	printf("您摆放的结果是：\n");
	printf("%d: ",channel);
	int i;
	for(i=0;i<number;i++)
	    printf("%c",type);
	printf(" %d\n",price);
	
    int re_turn = purchase(price,&number,type);
    while(re_turn)
        {
			input_and_change_function(re_turn);
	        printf("还剩余%d个%c货物\n",number,type);
			re_turn = purchase(price,&number,type);
		}//重复购买
    


	return 0;   
	
	
}






int purchase(int price,int*number,char type)//实现单次购买
{
	int total_money = 0;
	printf("请您输入所购买货物的总金额(输入q以放弃购买)：");
	int check = scanf("%d",&total_money);
	while(check == 1)
	    {
            if(total_money>price * (*number))
            {
            	printf("抱歉，售货机中只有%d个%c货物\n",*number,type);
    	    	printf("请您重新输入所购买货物的总金额(输入q以放弃购买)：");
            	check = scanf("%d",&total_money);
			}
			else 
	    	{
				int buy_number = total_money/price;
                *number-=buy_number;
                return total_money;
	    	}
	    	
		}
	
    return 0;
}




void input_and_change_function(int total_money)//投币与找零
{
	int current_money = 0;
	int input_money = 0;
	printf("请开始投币（只接受1元、2元、5元）:");
    while(current_money<total_money)
	    {
	    	scanf("%d",&input_money);
	        current_money+=input_money;
	        if(current_money<total_money)
			    printf("请继续投币:");
			else
			    printf("金额足够！开始找零：\n");
		}
	int change=current_money-total_money;
	printf("找您%d元\n",change);
	
}