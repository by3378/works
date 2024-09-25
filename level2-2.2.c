#include <stdio.h>
#include <stdbool.h>
#include <ctype.h>
#include <string.h>
#define CHANNELMAX 5
#define PRICEMAX 10
#define NUMBERMAX 50
#define BACK "BACK"
#define END "END"

struct cha_nnel{
	char type;
	int channel;
	int price;
	int number;
};//摆放时一个货物通道的各参数
struct CHA_NNEL{
	char TYPE;
	int CHANNEL;
	int NUMBER;
};//购买时一个货物通道的各参数

int s_gets(char * , int );//去掉fgets()存储在字符串中的换行符，并检查输入长度
char * TOUPPER(char * );  //将字符串中的字母转写为大写字母

int goods_input(struct cha_nnel ptr[]);//货物摆放部分   

int goods_output_all(const struct cha_nnel ptr[]);//展示所有的货物
void goods_output_line(int ,int ,char ,int );  //展示一个通道的货物

int goods_buy(struct CHA_NNEL PTR[],struct cha_nnel ptr[],int * );//货物购买部分   
void input_and_change_function(int );//投币与找零

int get_choice(void);//选择是否继续购买

int main(void)
{
    struct cha_nnel seller[CHANNELMAX];//定义结构数组seller,其中每个元素代表一次货物摆放
    for(int i=0;i<CHANNELMAX;i++)
        seller[i] = (struct cha_nnel){'#',0,0,0};  //初始化，便于之后比较

    goods_input(seller);//货物摆放部分 
	
    int check=goods_output_all(seller);//存货展示
	
	if (check==0)
	    return 0;       //无存货时不进入购买流程
	
	struct CHA_NNEL SELLER[CHANNELMAX];//定义结构数组SELLER,其中每个元素代表一次货物购买
    for(int i=0;i<CHANNELMAX;i++)
        SELLER[i] = (struct CHA_NNEL){'#',0,0};  //初始化，便于之后比较
	
	int choice;
	do
	{
		//货物购买部分   
	    int total_money=0;
	    goods_buy(SELLER,seller,&total_money);
		printf("需支付金额是：%d元\n",total_money);
	
	    //付款部分
	    if(total_money!=0)
		    input_and_change_function(total_money);	
	    else
	        puts("您未选择货物。");	
	        
	    check=goods_output_all(seller);//检查并展示存货 
	    
	    if(check==1)//有存货
	        choice=get_choice();//选择是否继续购买
	    else 
	        return 0;//无存货则直接结束
	
	}while(choice);
	
	return 0;
	
}



int s_gets(char * st, int n )
//去掉fgets()存储在字符串中的换行符，并检查输入长度
{
    char * ret_val;
    char * find;
	while(1)
	{
		ret_val = fgets(st, n, stdin);
        if (ret_val)                       // ret_val != NULL
        {
            find = strchr(st, '\n');       // 使用strchr()查找换行符。如果该函数发现了换行符，将返回该换行符的地址
            if (find)                      // 如果地址不是 NULL,
            {
		        *find = '\0';              // 将换行符改为空字符
		        return 1;                  //结束函数
		    }               
        }
		else
        {
        	while (getchar() != '\n')
                continue;              //处理输入行中剩余的字符
			puts("您的输入过长，请重新输入：");//防止超出数组
			continue;                       
		}    
    }
}
char * TOUPPER(char * st)//将字符串中的字母转写为大写字母
{
	for(char * p=st; *p!='\0';p++)
	{
		if (isalpha(*p)==1)
			*p=toupper(*p);
	}
	return st;
}



int goods_input(struct cha_nnel ptr[])//货物摆放部分   
{
	puts("请依次输入货物种类(一个大写字母)，通道标号（正整数1至5），货物单价（小于十的正整数），货物个数（小于50的正整数），使用空格分隔：");
	puts("输入END以结束货物摆放");
	puts("输入BACK以撤回操作（您最多可以连续撤回三次）");
		
	char temp[20]; //声明一个数组以临时存放输入结果，20应当是足够大的  使用缓存数组理应不会有非法输入留在输入行
	int count=0;          //回退次数
    for(int i=0;i<CHANNELMAX;)
    {
        while(1)
    	{
	        s_gets(temp,20);        //最多读入19个字符，给用户留下多输入几个空格的空间，又防止超出数组
	    	
			if ( strcmp(TOUPPER(temp),BACK)==0 && count<3 && i>0 )  //输入BACK，回退次数小于3，且非退无可退   
	        {
	        	count++;  
	        	ptr[--i] = (struct cha_nnel){'#',0,0,0};//重置上次输入,防止用户直接输入END       
	        	puts("已回退至上一步。");
	        	puts("请重新输入。");
	        	continue;
         	}    
	        if ( strcmp(TOUPPER(temp),BACK)==0 && count>=3 && i==0 )
        	{
	        	puts("不能再退了，我也是有底线的哦。");
	        	puts("请重新输入。");                  //直接覆写temp
	        	continue;
         	}    
	        if ( strcmp(TOUPPER(temp),END)==0 )
	        {
	        	puts("您已完成货物摆放。");
	         	return 0;
	    	}   
	
	    	int check= sscanf(temp," %c %d %d %d",&ptr[i].type,&ptr[i].channel,&ptr[i].price,&ptr[i].number); 
            //将temp里的数据格式化输入seller的一个元素中,并进行输入项检查
        	if(check==4 && (ptr[i].channel>0 && ptr[i].channel<=CHANNELMAX) 
    		            && (ptr[i].price<PRICEMAX && ptr[i].price>0) 
						&& (ptr[i].number<=NUMBERMAX && ptr[i].number>0)     )
        	{
    	    	bool bad_input=false,same_channel=false;
				int p;
				for(p=0;p<i;p++)
    	    	    {
					   if(ptr[p].type==ptr[i].type && ptr[p].price!=ptr[i].price)  //同物不同价
    	    	        {
    	    	            puts("您输入的相同货物价格不同，请重新输入。");
							bad_input=true;	
						}
					    else if(ptr[p].channel==ptr[i].channel && ptr[p].type!=ptr[i].type) //相同通道不同货物
					    {
					    	printf("%d通道已经有%c货物，您不能在同一个通道中放不同的货物。\n",ptr[p].channel,ptr[p].type);
					    	bad_input=true;
						}
						else if(ptr[p].channel==ptr[i].channel && ptr[p].type==ptr[i].type)
						{
							same_channel=true;  //相同通道继续放置相同货物，则累加
							break; //不递增p
						}
					}
				
				if(bad_input)
				    continue;
				else
				{
					if(same_channel)
					{
						ptr[p].number+=ptr[i].number;  //增加数量
						printf("您已向%d通道继续放入了%d个%c货物。此步不计为一次完整操作，不在回退涉及的范围之内。\n",ptr[i].channel,ptr[i].number,ptr[i].type);  
						ptr[i].type='#';  ptr[i].number=ptr[i].price=ptr[i].channel=0;
						count=0;          //重置回退次数
						continue;       //覆写ptr[i]  
					}
					else
					{
					    printf("您已将货物放入%d通道。\n",ptr[i].channel);
    	    	        i++;              //序号递增
                        count=0;          //重置回退次数
                        break;
					}
				}
        	}
        	else //超出范围或输入格式错误
        	{
    	    	puts("您的输入不合要求，请重新输入：");   
	    	    continue;  //直接覆写temp
			}
		}	
    } 	
}



int goods_output_all(const struct cha_nnel ptr[])   //展示所有的货物
{
	puts("现在售货机的存货情况是：");
	if(ptr[0].type=='#')
	{
	    printf("无货物。\n");
		return 0;	//结束函数
	}
	for(int p=1;p<=CHANNELMAX;p++)
	{
	    for(int i=0;i<CHANNELMAX;i++)
	    {
			if( ptr[i].channel==p && ptr[i].type!='#' && ptr[i].number!=0)//找到p通道所对应的序号i
	            goods_output_line(ptr[i].channel,ptr[i].number,ptr[i].type,ptr[i].price);
		}           
	}
	return 1;  //有存货
}
void goods_output_line(int channel,int number,char type,int price)   //展示一个通道的货物
{
	printf("%d: ",channel);
	for(int i=0;i<number;i++)
	    printf("%c",type);
	printf(" %d\n",price);
}



int goods_buy(struct CHA_NNEL PTR[],struct cha_nnel ptr[],int * total_money)//货物购买部分   
{
	puts("请依次输入货物种类(一个大写字母)，通道标号（正整数1至5），货物个数（小于50的正整数），使用空格分隔：");
	puts("输入END以结束货物挑选");
	puts("输入BACK以撤回操作（您最多可以连续撤回三次）");
		
	char temp[20]; //声明一个数组以临时存放输入结果，20应当是足够大的
	int count=0;   //回退次数
    int p;         //SELLER编号
	for(int i=0;i<CHANNELMAX;)//seller编号
    {
        while(1)
    	{
	        s_gets(temp,20);        //最多读入19个字符，给用户留下多输入几个空格的空间，又防止数组过小
	    	
			if ( strcmp(TOUPPER(temp),BACK)==0 && count<3 && i>0 )  //输入BACK，回退次数小于3，且非退无可退   
	        {
	        	count++;  
	        	
				p=0;
				while(ptr[p].channel!=PTR[--i].CHANNEL && p<CHANNELMAX)
                    p++;			//递减i，找到上一次输入的CHANNEL在seller中对应的编号p
				
				ptr[p].number+=PTR[i].NUMBER;
                *total_money -= PTR[i].NUMBER*ptr[p].price;	//还原货物数量与金额
				
				PTR[i] = (struct CHA_NNEL){'#',0,0};//重置上次输入结果,防止用户直接输入END       
				
				puts("已回退至上一步。");
				printf("目前金额：%d\n",*total_money);
	        	puts("请重新输入。");
        		continue;
         	}    
	        if ( strcmp(TOUPPER(temp),BACK)==0 && count>=3 && i==0 )
        	{
	        	puts("不能再退了，我也是有底线的哦。");
	        	puts("请重新输入。");                  //直接覆写temp
	        	continue;
         	}    
	        if ( strcmp(TOUPPER(temp),END)==0 )
	        {
	        	puts("您已完成货物挑选。");
	         	return 0;
	    	}   
	
	    	int check= sscanf(temp," %c %d %d",&PTR[i].TYPE,&PTR[i].CHANNEL,&PTR[i].NUMBER); 
            //将temp里的数据格式化输入seller的一个元素中,并进行输入项检查
        	if(check==3 && (PTR[i].CHANNEL>0 && PTR[i].CHANNEL<=CHANNELMAX) 
    		            && (PTR[i].NUMBER<=NUMBERMAX && PTR[i].NUMBER>0)    )//数据格式正确
        	{
    	    	p=0;
				while(ptr[p].channel!=PTR[i].CHANNEL && p<CHANNELMAX)
                    p++;			//找到输入的CHANNEL在seller中对应的编号p
				
				if(p>CHANNELMAX-1 || ptr[p].type!=PTR[i].TYPE)   //没找到对应的p或找到了但货物不对
		        {
		    	    puts("与实际货物摆放不符,请重新输入。");
			    	continue;
			    }		        
		        else if(ptr[p].number<PTR[i].NUMBER)
		        {
		        	puts("抱歉，货物数量不足，请重新输入：");
		    		continue;
		    	}
				else
				{
					puts("单次货物挑选成功！您还可以继续挑选。"); 
				    count=0;  //重置回退次数
				    ptr[p].number-=PTR[i].NUMBER;  //更新货物数量
                    *total_money += PTR[i].NUMBER*ptr[p].price;	  //金额累加
					printf("目前金额：%d\n",*total_money);
					i++;      //seller序号递增
					break;
		        }
	    	}
        	else
        	{
    	    	puts("您的输入不合要求，请重新输入：");   
	    	    continue;
        	}	
	    }	
    } 	
}



void input_and_change_function(int total_money)//投币与找零
{
	puts("请开始投币（只接受1元、2元、5元）:");
    puts("输入BACK以撤回操作（您最多可以连续撤回三次）");
	
	char temp[10]; //声明一个数组以临时存放输入结果，10应当是足够大的
	int input_money[50];//存放投币结果
	
    int i=0,count=0;     //input_money数组序号;回退步数
    int current_money=0;
	while(current_money<total_money)
    {
	    s_gets(temp,10);        //最多读入9个字符，给用户留下多输入几个空格的空间，又防止数组过小
	    	
		if ( strcmp(TOUPPER(temp),BACK)==0 && count<3 && i>0 )  //输入BACK，回退次数小于3，且非退无可退   
	    {
	        count++;    
	        current_money-=input_money[--i];   //还原金额
	        input_money[i] = 0;  //重置上次输入   
			puts("已回退至上一步。");
	        puts("请重新输入。");
	        continue;
        }    
	    if ( strcmp(TOUPPER(temp),BACK)==0 && count>=3 && i==0 )
        {
	        puts("不能再退了，我也是有底线的哦。");
	        puts("请重新输入。");                  //直接覆写temp
	       	continue;
        }    
	
	    int check = sscanf(temp," %d",&input_money[i]); 
        //将temp里的数据格式化输入input的一个元素中,并进行输入项检查
        if(check==1 && ( input_money[i]==1 || input_money[i]==2 || input_money[i]==5 ) )
       	{
    	    current_money+=input_money[i];   //累加金额
			printf("投入%d元。\n",input_money[i]);
    	   	i++;              //序号递增
            count=0;          //重置回退次数
			continue;
        }
       	else
        {
    	    puts("抱歉，我们只接受1元、2元、5元,请重新投币。");   
	    	continue;
        }	
	}	 

    puts("金额足够！开始找零：");
	int change=current_money-total_money;
	printf("找您%d元\n",change);
} 	



int get_choice(void)//选择是否继续购买
{
	char response;
	puts("是否继续购买？");
	puts("若要继续，请输入Y；若要结束，请输入N:");
    do{
		response = toupper(getchar());   	
		if(response=='N')
    	{
    		puts("谢谢购买，再见。");
    		return 0;
		}
		else if(response=='Y')
		{
			puts("您选择了继续购买。");
			while(getchar()!='\n');   //清空输入行
			return 1;
		}
		else
		{
			puts("抱歉，我只理解Y和N。");
			while(getchar()!='\n');
		}
	}while(1);
}	