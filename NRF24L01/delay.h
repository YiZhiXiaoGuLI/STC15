#define uint unsigned int
//1us��ʱ����
void delay_us(uint a)
{
	while(a--);
}
//1MS��ʱ����
void delay_ms(uint a)
{
	while(a--)
	{
		delay_us(1000);
	}
}