//test    缺少：同货物不同价格的检查机制；通道数重复检查机制;用户未输入空格的情况
#include <stdio.h>
#define MAX 5
#define PRICEMAX 10
int purchase(int*price,int*number,int*channel,char*type,int*total_money);
void goods_output_line(int channel,int number,char type,int price);
void input_and_change_function(int totalmoney);
int goods_output_all(int*channel,int*number,char*type,int*price);
int main(void)
{
    char type[MAX];//货物种类
	int channel[MAX]; int price[MAX]; int number[MAX];//通道标号，货物单价，货物个数
	
    int i,check;
    int count,step;
    count=step=0;//回退次数，步数
    printf("请依次输入货物种类(大写字母)，通道标号（正整数），货物单价（正整数），货物个数（正整数），使用空格分隔：\n");
	printf("输入END以结束货物摆放\n");
	printf("输入BACK以撤回操作（您最多可以连续撤回三次）\n");
	for(i=0;i<MAX;i++)
	{	
		while(1)
		{
			check = scanf(" %c %d %d %d",type+i,channel+i,price+i,number+i);
		    if(type[i] == 'E'&&check==1)
		    {
		    	printf("所有货物摆放结束！\n");
				while(getchar()!='\n');
				count=step=0;
				goto end;
			}
		    if(type[i] == 'B' && check==1 && step>0 && count<3)
		    {
		    	i--;
				type[i]='#',channel[i]=price[i]=number[i]=0;
		    	printf("已回退至上一步。\n");
				count++;
				step--;
				while(getchar()!='\n');
				continue;
			}
			if( check!=4 || channel[i] * price[i] * number[i] <= 0 || channel[i] >= MAX || price[i]>=PRICEMAX )
		    {
		    	printf("输入不合要求，请重新输入\n");
                while(getchar()!='\n');
			}
			else
			{
				printf("%d通道货物摆放成功！\n",channel[i]); 
				step++;
				count=0;
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
	
	int total_money=0;
    purchase(price,number,channel,type,&total_money);	
	printf("需支付金额是：%d元\n",total_money);    	
	if(total_money!=0)
		input_and_change_function(total_money);	
	else
	    printf("您未选择货物。\n");	
	
	return 0;
	
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
    char TYPE[MAX];//购买的货物种类
	int CHANNEL[MAX]; int PRICE[MAX]; int NUMBER[MAX];//购买的通道标号，货物单价，货物个数
	
    int i,check,p;
    int count,step;
    count=step=0;//回退次数，步数
    printf("请依次输入要购买的货物种类(大写字母)，通道标号（正整数），货物个数（正整数），使用空格分隔：\n");
	printf("输入END以结束货物挑选\n");
	printf("输入BACK以撤回操作（您最多可以连续撤回三次）\n");

	for(i=0;i<MAX;i++)
	{	
		while(1)
		{
			TYPE[i]='#',CHANNEL[i]=NUMBER[i]=0;
			check = scanf(" %c %d %d",TYPE+i,CHANNEL+i,NUMBER+i);
		    if(TYPE[i] == 'E'&&check==1)
		    {
		    	printf("所有货物挑选结束！\n");
				while(getchar()!='\n');
				count=step=0;
				return 0;
			}
		    if(TYPE[i] == 'B' && check==1 && step>0 && count<3)
		    {
		    	i--;
				number[p]+=NUMBER[i];
                *total_money -= NUMBER[i]*price[p];	
				TYPE[i]='#',CHANNEL[i]=NUMBER[i]=0;
		    	printf("已回退至上一步。\n");
				count++;
				step--;
				
				while(getchar()!='\n');
				continue;
			}
			if( CHANNEL[i] <= 0 || CHANNEL[i] >= MAX || NUMBER[i]<=0 )
		    {
		    	printf("输入不合要求，请重新输入\n");
                while(getchar()!='\n');
			}
			else//数据格式正确
			{
				p=0;
				while(channel[p]!=CHANNEL[i]&&p<MAX)
                    p++;
			//找到输入CHANNEL对应的编号p
		        if(p>4)
		        {
		            printf("此通道无货物，请重新输入：\n");
			    	continue;
			    }		        
		        else if(type[p]!=TYPE[i])
		        {
		    	    printf("与实际货物摆放不符,请重新输入。\n");
				    continue;
		    	}
		        else if(number[p]<NUMBER[i])
		        {
		        	printf("抱歉，货物数量不足，请重新输入：\n");
		    		continue;
		    	}
				else
				{
					printf("单次货物挑选成功！您还可以继续挑选。\n"); 
				    step++;
				    count=0;
	 
					number[p]-=NUMBER[i];
                    *total_money += NUMBER[i]*price[p];	
					printf("目前金额：%d\n",*total_money);
					break;
				}
			}       
        }
    }    
}



void input_and_change_function(int total_money)//投币与找零
{
	int current_money = 0;
	int change,check,i;
	int count,step;
	char input_money[50];//最多投币次数
	check=i=0;
	count=step=0;
	printf("请开始投币（只接受1元、2元、5元）:\n");
    printf("输入BACK以撤回操作（您最多可以连续撤回三次）\n");
	while(current_money<total_money)
	    {
	    	
			check=scanf(" %d",&input_money[i]);
	        if(check==0&&step>0&&count<3)
			{
				input_money[i]=0;
				printf("已回退至上一步。\n");
				count++;
				step--;
				i--;
			    current_money-=input_money[i];
				while(getchar()!='\n');
				continue;
				
			}
			if(input_money[i]!=1 && input_money[i]!=2 && input_money[i]!=5 )
			{
			    printf("抱歉，我们只接受1元、2元、5元,请重新投币。\n");
			    input_money[i]= 0;
			}
			current_money+=input_money[i];
	        if(current_money<total_money)
		    {
			    printf("投入%d元。\n",input_money[i]);
				printf("请继续投币:\n");
				count=0;
				step++;	
				i++;
			}
			else
		    {
			    printf("金额足够！开始找零：\n");
			    change=current_money-total_money;
	            printf("找您%d元\n",change);
			}
		}
}