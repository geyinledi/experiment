#include <stdio.h>
int main()
{
    int n,sum=0,i,k;
    while(scanf("%d",&n)!=EOF&&n!=0)
    {
        int a[n];
        for(i=0;i<n;i++)
            scanf("%d",&a[i]);
        for(i=0;i<n;i++)
        {
            k=a[i]/100+a[i]%100/50+(a[i]%100-a[i]%100/50*50)/10+a[i]%10/5+(a[i]%10-a[i]%10/5*5)/2+(a[i]%10-a[i]%10/5*5)%2;
            sum=sum+k;
        }
        printf("%d\n",sum);
        sum=0;
    }
    return 0;
}
