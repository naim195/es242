#include <stdio.h>

typedef char Cube[6][4];
Cube cube;

void init_cube(char face[6][4])
{
    for(int i=0;i<6;i++)
    {
        for(int j=0;j<4;j++)
        {
            cube[i][j]=face[i][j];
        }
    }
}

int main()
{
    char face[6][4];
    printf("Enter the colours in order for faces 1 to 6\nfaces 1 to 3 will br F,U,R respectively\n");
    for(int i=0;i<6;i++)
    {
        scanf(" %[^\n]s",face[i]);
        printf("\n");        
    }    

    init_cube(face);

    


    return 1;
}