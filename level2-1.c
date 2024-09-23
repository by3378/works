//test    缺少：同货物不同价格的检查机制；通道数重复检查机制;用户未输入空格的情况
#include <stdio.h>
#define MAX 5
#define PRICEMAX 10
int purchase(int*price,int*number,int*channel,char*type,int*total_money);
void goods_output_line(int channel,int number,char type,int price);
void input_and_change_function(int totalmoney);
int goods_output_all(int*channel,int*number,char*type,int*price);
int get_choice(void);
int main(void)
{
    char type[MAX];//货物种类
	int channel[MAX]; int price[MAX]; int number[MAX];//通道标号，货物单价，货物个数
	
    int i,check;
    printf("请依次输入货物种类(大写字母)，通道标号（正整数），货物单价（正整数），货物个数（正整数），使用空格分隔：\n");
	printf("(输入4个#以结束货物摆放)：\n");	
	for(i=0;i<MAX;i++)
	{	
		while(1)
		{
			check = scanf(" %c %d %d %d",type+i,channel+i,price+i,number+i);
		    if(type[i] == '#')
		    {
		    	printf("所有货物摆放结束！\n");
				while(getchar()!='\n');
				goto end;
			}
		    else if( check!=4 || channel[i] * price[i] * number[i] <= 0 || channel[i] >= MAX || price[i]>=PRICEMAX )
		    {
		    	printf("货物摆放不合要求，请重新摆放\n");
                while(getchar()!='\n');
			}
			else
			{
				printf("%d通道货物摆放成功！\n",channel[i]); 
				break;
			}       
        }
    }    
	end:
    //货物摆放部分结束    
	for(;i<MAX;i++)
	{
		price[i]=channel[i]=number[i]=0;
		type[i]='#';
	}
	//更新数组空白部分
		goods_output_all(channel,number,type,price);
    //存货展示
	int total_money;
	int re_turn;
	int choice = 1;
	while(choice)
	{
        total_money=0;
		printf("请依次输入要购买的货物种类，它所处的通道标号以及购买数量，输入3个#以结束:\n");
        do{
			re_turn=purchase(price,number,channel,type,&total_money);
		}while(re_turn);
	    
		if(total_money!=0)
		    input_and_change_function(total_money);	
	    else
	        printf("您未选择货物。\n");

		choice=get_choice();	
	}
	
	return 0;
	
}



int get_choice(void)
{
	while(getchar()!='\n');
	char response;
	printf("是否继续购买？\n");
	printf("若要继续，请输入y；若要结束，请输入n:\n");
    do{
		response = getchar();   	
    	if(response=='n')
    	{
    		printf("谢谢购买，再见。\n");
    		return 0;
		}
		else if(response=='y')
		{
			printf("您选择了继续购买。\n");
			while(getchar()!='\n');
			return 1;
		}
		else
		{
			printf("抱歉，我只理解y和n.\n");
			while(getchar()!='\n');
		}
	}while(1);
}


int goods_output_all(int*channel,int*number,char*type,int*price)
{
	printf("现在售货机的存货情况是：\n");
	if(type[0]=='#')
	{
	    printf("无货物。\n");
		return 0;	
	}
	for(int p=1;p<=MAX;p++)
	{
	    for(int i=0;i<MAX;i++)
	    {
			if( channel[i]==p && type[i]!='#' && number[i]!=0)
	            goods_output_line(channel[i],number[i],type[i],price[i]);
		}           
	}
	return 0;
}
void goods_output_line(int channel,int number,char type,int price)
{
	int i;
	printf("%d: ",channel);
	for(i=0;i<number;i++)
	    printf("%c",type);
	printf(" %d\n",price);
}




int purchase(int*price,int*number,int*channel,char*type,int*total_money)//实现单次购买
{
	int CHANNEL,NUMBER,check;
	char TYPE;
//输入检查部分
	while(1)
	{
		//while(getchar()!='\n');为什么??????????????????????????????????????????????????????
		check = scanf(" %c %d %d",&TYPE,&CHANNEL,&NUMBER);
		if(TYPE=='#')
		{
			printf("您已结束货物挑选，接下来请开始付款。\n");
			while(getchar()!='\n');
			return 0;
		}		
		else if(check!=3 || CHANNEL<=0 || NUMBER<=0 || CHANNEL>=MAX )
		{
			printf("输入格式错误，请重新输入\n");
		    while(getchar()!='\n');
			continue;
		}
		else
		{
			int i = 0;
			while(channel[i]!=CHANNEL&&i<MAX)
                i++;
			//找到输入CHANNEL对应的编号i
		    if(i>4)
		    {
		        printf("此通道无货物，请重新输入：\n");
				continue;
			}		        
		    else if(type[i]!=TYPE)
		    {
		    	printf("与实际货物摆放不符,请重新输入。\n");
				continue;
			}
		    else if(number[i]<NUMBER)
		    {
		    	printf("抱歉，货物数量不足，请重新输入：\n");
				continue;
			}
			else
			{
				number[i]-=NUMBER;
                *total_money += NUMBER*price[i];
                return 1;	
			}
		}		
	}
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