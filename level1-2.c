#include <stdio.h>
int main(void)
{	
	int total_money,current_money,input_money;
	input_money=current_money=0;
	printf("请您输入所购买货物的总金额：");
	scanf("%d",&total_money);
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
	printf("找您%d元",change);
	
	return 0;   	
}