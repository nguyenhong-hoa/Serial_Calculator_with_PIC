#include "16F877A.h"
#use    delay(crystal=20M)
#use    rs232(UART1)
#define Enter 13
#define Plus '+'
#define Minus '-'
#define Multiply '*'
#define Divide '/'
#define Exponent '^'
#define Factorial '!'

int a=0,b=0,sign1=0,sign2=0,skip=0;
char          MyKey;
signed long   Op1, Op2,Key,Sign,mul,i;
unsigned char msg1[] = " CALCULATOR PROGRAM";
unsigned char msg2[] = " Enter First Number: ";
unsigned char msg3[] = " Enter Second Number: ";
unsigned char msg4[] = " Enter Operation: ";
unsigned char msg5[] = " Result = ";

void Newline() {
putc(0x0D); 
putc(0x0A); 
} 

void baoloi(){
   Newline();
   printf("Co loi trong qua trinh nhap! Moi nhan RESET va nhap lai");
   while(1)
      {output_toggle(PIN_B0);
       delay_ms(500);}
}

void checkdata(int data){
   if (!(((data >= '0')&& (data <= '9'))||(data == '?')||(data == 'f')||(data == '%')||(data=='+')||(data=='-')||(data=='*')||(data=='/')||(data=='^')||(data=='!')||(data==13)||(data=='h')||(data=='e')||(data=='p')||(data=='b')||(data=='u')))
       baoloi();
}


#int_RDA
void isrtran(){
   a=1;
   b= getc();
   checkdata(b);
}

void Text_To_Usart(unsigned char *m) {
unsigned char i;
     i = 0;
     while(m[i] != 0) 
        {putc(m[i]);
         i++;}
}

void snt() {
for (i=2;i<Op1;i++)
    if (Op1 % i == 0)
        mul=1;
if ((sign1==1) || (mul==1))
    printf("Khong phai so nguyen to !");
else 
    printf("La so nguyen to");}


void main()
{  set_tris_C(0xC0);
   setup_uart(9600);
   enable_interrupts(int_RDA);
   enable_interrupts(global);
   
again: for(;;) {
         a=0;
         skip=0;
         sign1=0;
         sign2=0;
         MyKey = 0;
         Op1 = 0;
         Op2 = 0;
         Newline();
         Newline();
         Text_To_Usart(msg1);
         Newline();
         Newline();
         Text_To_Usart(msg2);

         while(1){
            if(a==1){
               MyKey=b;
               if(MyKey == Enter)
                  {a=0;
                   break;}
               putc(MyKey);
               if ((MyKey >= '0')&& (MyKey <= '9')) {
                   Key = MyKey - '0';
                   Op1 = 10*Op1 + Key;}
               if (MyKey == '-') {
                   sign1=1;
                   if (Op1 !=0)
                        baoloi();}
               a=0;
               if (Mykey=='h') {
                  Newline();
                  Text_To_Usart(msg5);
                  printf("%lf",6.62);
                  putc('e');
                  putc('-');
                  printf("%d",34);
                  goto again;}
               else
                  if (Mykey=='p') {
                     Newline();
                     Text_To_Usart(msg5);
                     printf("%lf",3.14);
                     goto again;}
                  else    
                     if (Mykey=='e'){
                        Newline();
                        Text_To_Usart(msg5);
                        printf("%lf",2.72);
                        goto again;}
               }}

         Newline();
         Text_To_Usart(msg4);
         while(1) {
            if(a==1) {
               MyKey=b;
               if(MyKey == Enter) {
                  a=0;
                  break;}
         putc(MyKey);
         Sign = MyKey;
         a=0;
         if ((Sign == '!') || (Sign == 'f')||(Sign=='?'))
            skip=1;
         }}

         Newline();
         if (skip==0){
         Text_To_Usart(msg3);
         while(1) {
            if(a==1) {
               MyKey=b;
               if(MyKey == Enter) {
                  a=0;
                  break;}
            putc(MyKey);
            if ((MyKey >= '0')&& (MyKey <= '9')) {
               Key = MyKey - '0';
               Op2= 10*Op2+ Key;}
            if (MyKey == '-') {
               sign2=1;
               if (Op2 !=0)
                 baoloi(); }
            a=0;
          }}}
          
         Newline();
         Text_To_Usart(msg5);

         switch(Sign) {
            case Plus:
               if (SIGN1==1)
                  if (sign2==1) {
                     putc('-');
                     printf("%ld",Op1+Op2);}
                  else 
                     printf("%ld",Op2-Op1);
               else
                  if (sign2 == 1) {
                     printf("%ld",Op1-Op2);}
                  else 
                     printf("%ld",Op1+Op2);
         break;



         case Minus:
              if (SIGN1==1)
                  if (sign2==1) {
                      printf("%ld",Op2-Op1);}
                  else {  
                      putc('-');
                      printf("%ld",Op2+Op1);}
               else
                  if (sign2 == 1) {
                     printf("%ld",Op1+Op2);}
                  else 
                     printf("%ld",Op1-Op2);
         break;

         case Multiply:
               if (SIGN1==1)
                  if (sign2==1) {
                      printf("%ld",Op1*Op2);}
                  else {
                      putc('-');
                      printf("%ld",Op2*Op1);}
               else
                  if (sign2 == 1) {  
                     putc('-');
                     printf("%ld",Op1*Op2);}
                  else 
                     printf("%ld",Op1*Op2);
         break;

         case Divide:
            if (Op2==0) baoloi();
            if ((SIGN1-SIGN2)!=0) 
                 putc('-');
            mul=Op1/Op2;
            printf("%ld",mul);
            putc('.');
            if (((10*(Op1-mul*Op2))/Op2) == 0) 
               putc('0');
            Op1=100*(Op1-mul*Op2);
            mul=Op1/Op2;
            printf("%ld",mul);
         break;

         case Exponent:
            if ((sign1 == 1) && (Op2 % 2 ==1)) 
               putc('-');
            mul = 1;
         for (i=1;i<=Op2;i++)
            mul=mul*Op1;
         if (sign2==0)
            printf("%ld",mul);
         else
            if (mul==1) 
               printf("%ld",mul);
            else {
               mul=100/mul;
               putc('0'); putc('.');
               printf("%ld",mul);}
         break;

         case Factorial:
         if (sign1==1) 
              baoloi();
         mul = Op1;
         for (i=1;i<Op1;i++)
               mul=mul*(Op1-i);
         printf("%ld",mul);     
         break;
         
         case 'b':
         for (i=1;i<65536;i++)
            if ((i % Op1 ==0) && (i % Op2 ==0))
               {printf("%ld",i);
               break;}
         break;
         
         case 'u':
         for (i=1;i<=Op1;i++)
            if ((Op1 % i == 0) && (Op2 % i ==0))
               mul=i;
         printf("%ld",mul);
         break;
         
         case '%':
         if ((sign1==1) || (sign2==1))
            baoloi();
         printf("%ld",Op1 % Op2);
         break;
         
         case 'f':
         if (sign1==1)
            printf("%d",-1);
         else
            putc('1');
         for (i=2;i<=Op1;i++)
            if (Op1 % i == 0)
             { Op1 = Op1/i;
               printf("x%ld",i);
               i=1;}
         break;
         
         case '?':
         mul=0;
         snt();
         break;
         
         default: baoloi();
}}}
