#include <stdio.h>
#include <memory.h>
#include <windows.h>

typedef unsigned short WORD;

WORD envsspasswd(char * passwd,int len)
{
    const char incstr[16]="BrianDavidHarry";
    char passwd1[200];
    int i;
    WORD a;
    WORD b;
    if(len>15)
        return 0;
    memcpy(passwd1,passwd,len);
    memcpy(passwd1+len,incstr,15-len);
    passwd1[15]=0;
    len = 15;
    b = 0;
    a = 0;
    for(i=0;i<len;i++)
    {
        a =  passwd1[i]; 
        a = a ^ 0x96;
        a = a*(i+1);
        b += a;
    }
    //printf("%i",b);
	return b;
}

WORD getincstr(int len)
{
	const char incstr[16]="BrianDavidHarry";
	char in[200];
	if(len>15)
		return 0;
	memcpy(in+len, incstr, 15-len);
	in[15]=0;
	int i, a , b=0;
    i = len;
	for(i;i<15;i++)
    {
        a =  in[i]; 
        a = a ^ 0x96;
        a = a*(i+1);
        b += a;
    }
	return b;
}

WORD envsspasswd1(char * passwd,int len, WORD incstr1)
{
    const char incstr[16]="BrianDavidHarry";
    char passwd1[200];
    int i;
    WORD a;
    WORD b;
    if(len>15)
        return 0;
    //memcpy(passwd1,passwd,len);
    //memcpy(passwd1+len,incstr,15-len);
    //passwd1[15]=0;
    //len = 15;
    b = 0;//incstr1;
    //a = 0;
    for(i=0;i<len;i++)
    {
        a =  passwd[i]; 
        a = a ^ 0x96;
        a = a*(i+1);
        b += a;
    }
    //printf("%i",b);
	return b+incstr1;
}

int hextoint(char c)
{
	if(c < 'a')
	{
		return c - '0';
	}
	else
	{
		return c - 'a' + 10;
	}
}

bool jinwei(char*enp, int i)
{
	if(enp[i] < '0')
	{
		enp[i] = '0';
		return false;
	}
	/*
	if(enp[i] == '9')
		{
			enp[i]='A';
			return false;
		}*/
	
	if(enp[i] >= 'z')
	{
		enp[i] = '0';
		return true;
	}
	else
	{
		enp[i]++;
		return false;
	}
}

bool setpasswd(char*enp, int i, int j)
{
     if(jinwei(enp,i))
	 {
		 if(i < j)
			return setpasswd(enp, i+1, j);
		 else
			return false;
	 }
	 return true;
}

int g_len=0;
bool GetPasswd(char*enp, int i)
{
	static int ii=0;
		if(ii > g_len)
		{
		ii=0;
			return false;
		}
		ii++;
	
	return setpasswd(enp,0,i);
}

bool baoli()
{
	char enp[5]="6d5c", enpstring[100];
	WORD enpasswd;
	memset(enpstring, 0, 100);
	g_len=('z' - '0')*('z' - '0');
	enpasswd = hextoint(enp[2])*16*16*16+hextoint(enp[3])*16*16+hextoint(enp[0])*16+hextoint(enp[1]);

	int i = 10;
	memset(enpstring, '0', i);
	while(i<100)
	{
		WORD w=getincstr(i);
		while(GetPasswd(enpstring,i))
		{
			//if(enpasswd == envsspasswd1(enpstring, i, w))
			if(enpasswd == envsspasswd(enpstring, i))
			{
				printf("ÃÜÂë:%s\n", enpstring);
				return TRUE;
			}
			printf("%s\n", enpstring);
		}
		i++;
	}
	return true;
}

int devsspasswd(char enp[4],char * dnp)
{
    const char incstr[16]="BrianDavidHarry";
    int i;
    int j;
    int k;
    long c1;
    long c2;
    long c4;
    int c3;
	
    WORD a;
    WORD b;
    WORD c;
    WORD d;
    WORD e;
    int num;
	
    a = hextoint(enp[2])*16*16*16+hextoint(enp[3])*16*16+hextoint(enp[0])*16+hextoint(enp[1]);
    c3 = 'Z'-'0'+1;
	
    for(i=0;i<15;i++)
    {
        dnp[i]=0;
        b =0;
        for(j=0;j<15-i;j++)
        {
            c = incstr[j]; 
            c = c ^ 0x96;
            c = c*(j+1+i);
		    b += c;
        }
        if(i==0 && b==a)
        {
            printf("password is null\n");
            return 0;
        }
        d = a - b;
        num = 0;
        c2 = 1;
        for(j=0;j<i;j++)
        {
            num = num+j+1;
            c2 = c3*c2;
        }
        if(num>0)
        {
            c1 = 0;            
            if((d/num)>154 && (d/num)<250)
            {
                memset(dnp,'0',i);
                //Sleep(100);
                do{
                    c4 = 1;
                    for(j=1;j<i-1;j++)
                    {
                        c4 = c4 * c3;
                        if(c1%c4==0)
                            dnp[j]='0';
                        else
                        {
                            dnp[j]++;
                            break;
                        }
                    }
                    b = 0;
                    for(k=1;k<i;k++)
                    {
                        c = dnp[k]; 
                        c = c ^ 0x96;
                        c = c*(k+1);
                        b += c;
                    }
                    e=d-b;    
					//printf("%c\n",e);
                    //if((e^0x96)>=0x20 && (e^0x96)<=0x7f) 
                    if((e^0x96)>='0' && (e^0x96)<='z') 
                    {
                        dnp[0]=(e^0x96);
                        printf("%s\n",dnp);
                        return i;
                    }
                    c1++;
                }while(c1<c2);                
            }
        }
    }
    return 0;    
}

void main()
{
	baoli();
	return;
	char enp [5]= "ba5d";
			char devp[100];
	//char pd[]="KL12356";
	//char epd[100];
	//int nLen =sizeof(pd);
	//	//envsspasswd(pd, epd, nLen);
	//
	//	//printf("%02x\n", epd);
		devsspasswd(enp,devp);
	//	//printf("%s\n",devp);
	
}
