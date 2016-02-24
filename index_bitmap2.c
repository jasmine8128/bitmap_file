#include"stdio.h"
#include"math.h"
char bit[100][33];
int key[100];
int offset[100];
void get_bitmap()
{
    FILE *fp;
    char init;
    int i,j,k,offs;
    i=0;j=0;
    fp=fopen("output_test.txt","r");
    while(1)
    {
        init=fgetc(fp);
        if(init=='1')//'1'-literal
        {

            fgets(bit[i],32,fp);
            bit[i][31]='1';bit[i][32]='\0';
            i++;
            fgetc(fp);
        }
        else if(init=='0')//'0'-Fill
        {

            fgets(bit[i],32,fp);
            bit[i][31]='0';bit[i][32]='\0';
            i++;
            fgetc(fp);
        }
        else if(init=='[')//key and offset
        {

            fscanf(fp,"%d",&offs);
            while(fgetc(fp)!=']')
            {
                key[j]=offs;
                j++;
                fscanf(fp,"%d",&offs);
            }
            key[j]=offs;
            fgetc(fp);
            fgetc(fp);
            j=0;

            fscanf(fp,"%d",&offs);

            while(fgetc(fp)!=']')
            {
                offset[j]=offs;
                j++;
                fscanf(fp,"%d",&offs);
            }

            offset[j]=offs;
            break;
        }

    }
}

void index_bitmap()
{

    printf("Please input the attribute you choose:\n");
    int attr;
    scanf("%d",&attr);
    int size,lie,loca,total;
    size=key[attr];
    lie=offset[attr];
    loca=-1;

    for(int i=0;i<size;i++)
    {
        loca+=1;
        if(bit[lie+i][31]=='1')
        {
            for(int j=0;j<31;j++)
            {
                if(bit[lie+i][j]=='1')
                {
                    printf("lie+i:%d j:%d  ",lie+i,j);
                    printf("%d\n",1+j+loca*31);
                }

            }
        }
        else
        {
            total=0;
            for(int j=30;j>=0;j--)
            {
                if(bit[lie+i][j]=='1')
                {
                    total+=pow(2,30-j);
                }
            }
            loca=loca+total-1;
        }
    }
}
int main()
{
    get_bitmap();
    index_bitmap();
    return 0;

}
