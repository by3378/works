#include <stdio.h>
#include <stdlib.h>
#define filename "money.txt"
int main(void)
{	
	FILE * fp;
    if ((fp = fopen(filename, "r")) == NULL)
    {
        printf("读取%s文件失败。\n", filename);
        exit(EXIT_FAILURE);
    }
	
	
	int total_money,current_money,input_money;
	input_money=current_money=0;

	fscanf(fp," %d",&total_money);
	printf("所购买货物的总金额是%d元。\n",total_money);
	

    while(current_money<total_money)
	    {
			int check=fscanf(fp," %d",&input_money);
	        if(input_money==1 || input_money==2 || input_money==5)
			{
				current_money+=input_money;
				printf("投入%d元。\n",input_money);
				input_money=0;
			}
			else if(check==1)
            {
            	printf("我们只接受1元、2元、5元,%d是无效输入。\n",input_money);
            	input_money=0;
			}  
			
			if(feof(fp) && current_money<total_money)
            {
                puts("您未投入足够的金额，接下来请手动投币。");	
				break;
	     	}  	   
		}
	while(current_money<total_money)
	{
		scanf(" %d",&input_money);
	    if(input_money==1 || input_money==2 || input_money==5)
		{
			current_money+=input_money;
			printf("投入%d元:\n",input_money);
		}
		else
            printf("我们只接受1元、2元、5元,%d是无效输入。\n",input_money);
		}
		
	printf("金额足够！开始找零：\n");
	int change=current_money-total_money;
	printf("找您%d元\n",change);
	
	return 0;   	
}