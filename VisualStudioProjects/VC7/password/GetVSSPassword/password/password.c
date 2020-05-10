void envsspasswd(char * passwd,char * enpasswd,int len)
{
    const char incstr[15]="BrianDavidHarry";
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
    printf("%02x",b);
}



int devsspasswd(char enp[4],char * dnp)
{
    const char incstr[15]="BrianDavidHarry";
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
                Sleep(100);
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
                    
                    if((e^0x96)>='0' && (e^0x96)<='Z') 
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
