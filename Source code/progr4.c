#include <stdio.h>
#include <errno.h> 
#include <string.h> 
#include <stdlib.h>

int main()
{
    int no_of_routers,i,j,k,l,count,path_cost,cost;
    int cost_matrix[100][100],flag[100],cost_from_src[100],path[100];
    char first_node,src_router;
    char path_taken[100];
    char file_name[100];
    FILE * filePointer;
    printf("OSPF Link-State (LS) Routing:\n-----------------------------");
    printf("\nEnter the number of routers: ");
    scanf("%d",&no_of_routers);
    printf("\nEnter filename with cost matrix values: ");
    scanf("%s",file_name);
    filePointer = fopen(file_name,"r");
    if(filePointer==NULL)
    {
        printf("\nerror: %s: %s",strerror(errno),file_name);
        exit(-1);
    }
    i=0;

    while(i<no_of_routers)
    {
        j=0;
        while(j<no_of_routers)
	{
            fscanf(filePointer,"%d",&cost);
            cost_matrix[i][j]=cost;
            j++;
        }
        i++;
    }
    fclose(filePointer);
    printf("\nEnter character representation of first node: ");
    scanf(" %c",&first_node);
    printf("\nEnter the source router: ");
    scanf(" %c",&src_router);
    
    
    /*printf("\nEnter the cost_matrix: ");
    i=0;
    while(i<no_of_routers){
        j=0;
        while(j<no_of_routers){
            scanf("%d",&cost_matrix[i][j]);
            j++;
        }
        i++;
    }*/
    
    
    i=0;
    while(i<no_of_routers)
    {
        j=0;
        while(j<no_of_routers)
	{
            if(cost_matrix[i][j]<0)
	    {
                cost_matrix[i][j]=1000;
            }
            j++;
        }
        i++;
    }
    i=0;
    while(i<no_of_routers)
    {
        flag[i]=0;
        path[i]=src_router-first_node;
        cost_from_src[i]=cost_matrix[src_router-first_node][i];
        i++;
    }
    flag[src_router-first_node]=1;
    i=0;
    while(i<no_of_routers)
    {
        path_cost=1000;
        j=0;
        while(j<no_of_routers)
	{
            if(!flag[j])
	    {
                if(cost_from_src[j]<path_cost)
		{
                    k=j;
                    path_cost=cost_from_src[j];
                }
            }
            j++;
        }
        flag[k]=1;
        j=0;
        while(j<no_of_routers)
	{
            if(!flag[j])
	    {
                if(path_cost+cost_matrix[k][j]<cost_from_src[j])
		{
                    cost_from_src[j]=path_cost+cost_matrix[k][j];
                    path[j]=k;
                }
            }
            j++;
        }
        i++;
    }
    i=0;
    while(i<no_of_routers)
    {
        printf("\n%c ==> %c :",src_router,first_node+i);
        printf("\npath cost : %d",cost_from_src[i]);
        printf("\npath taken: ");
        count=0;
        k=0;
        j=i;
        while(j!=src_router-first_node)
	{
            path_taken[k]=first_node+path[j];
            j=path[j];
            k++;
        }
        path_taken[k]='/';
        l=0;
        while(l<no_of_routers)
	{
            if(path_taken[l]=='/')
	    {
                break;
            }
            count++;
            l++;
        }
        l=count-1;
        while(l>=0)
	{
            printf("%c",path_taken[l]);
            printf(" --> ");
            l--;
        }
        printf("%c",first_node+i);
        i++;
    }
    return 0;
}

