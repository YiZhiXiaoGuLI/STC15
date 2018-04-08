#define uint unsigned int
//1us延时函数
void delay_us(uint a)
{
	while(a--);
}
//1MS延时函数
void delay_ms(uint a)
{
	while(a--)
	{
		delay_us(1000);
	}
}