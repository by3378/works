#include <stdio.h>
int main(void)
{
	char type;//货物种类
	int channel,price,number;//通道标号，货物单价，货物个数
	printf("请依次输入货物种类，通道标号，货物单价，货物个数(使用空格分隔):\n");
	scanf("%c %d %d %d",&type,&channel,&price,&number);
	
	printf("您摆放的结果是：\n");
	printf("%d: ",channel);
	int i;
	for(i=0;i<number;i++)
	    printf("%c",type);
	printf(" %d\n",price);
	
	return 0;   
	
	
}