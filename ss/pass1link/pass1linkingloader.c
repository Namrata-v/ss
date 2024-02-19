#include <stdio.h>
#include <string.h>

#define MAX 20

struct estab
{
    char csname[10];
    char extsym[10];
    int address;
    int length;
} es[MAX];

int main()
{
    char input[10], name[10];
    int count = 0, progaddr, csaddr, add, len;
    FILE *fp1, *fp2;

    fp1 = fopen("linkinput.txt", "r");
    fp2 = fopen("loadmap.txt", "w");

    if (fp1 == NULL || fp2 == NULL)
    {
        perror("Error opening file");
        return 1;
    }

    printf("Enter the location where the program has to be loaded: ");
    scanf("%d", &progaddr);

    csaddr = progaddr;

    fprintf(fp2, "CS_NAME\tEXT_SYM_NAME\tADDRESS\tLENGTH\n");
    fprintf(fp2, "--------------------------------------\n");

    fscanf(fp1, "%s", input);

    while (strcmp(input, "END") != 0)
    {
        if (strcmp(input, "H") == 0)
        {
            fscanf(fp1, "%s", name);
            strcpy(es[count].csname, name);
            
            fscanf(fp1, "%d", &add);
            es[count].address = add + csaddr;
            fscanf(fp1, "%d", &len);
            es[count].length = len;

            fprintf(fp2, "%s\t%s\t\t%d\t%d\n", es[count].csname, es[count].extsym, es[count].address, es[count].length);

            count++;
        }
        else if (strcmp(input, "D") == 0)
        {
            fscanf(fp1, "%s", input);

            while (strcmp(input, "R") != 0)
            {
                
                strcpy(es[count].extsym, input);
                fscanf(fp1, "%d", &add);
                es[count].address = add + csaddr;
                es[count].length = 0;

                fprintf(fp2, "%s\t%s\t\t%d\t%d\n", es[count].csname, es[count].extsym, es[count].address, es[count].length);

                count++;
                fscanf(fp1, "%s", input);
            }

            csaddr = csaddr + len;
        }
        else if (strcmp(input, "T") == 0)
        {
            while (strcmp(input, "E") != 0)
                fscanf(fp1, "%s", input);
        }

        fscanf(fp1, "%s", input);
    }

    fprintf(fp2, "--------------------------------------\n");
    fclose(fp1);
    fclose(fp2);

    printf("FINISHED\n");

    // Wait for a key press
    getchar();

    return 0;
}