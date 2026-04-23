#include <stdio.h>
#include <string.h>
#include <stdlib.h>

struct Employee
{
    int id;
    float hourlyPay;
    int hoursWorked;
    float weeklySalary;
};

void runProblem3()
{
    char words[1000][51];
    int wordCount = 0;
    char result[1000][51];
    int resultCount = 0;

    FILE *f = fopen("input.txt", "r");
    if (f == NULL)
    {
        printf("cant find input.txt\n");
        return;
    }
    while (wordCount < 1000 && fscanf(f, "%50s", words[wordCount]) != EOF)
    {
        wordCount++;
    }
    fclose(f);

    if (wordCount > 0)
    {
        strcpy(result[0], words[0]);
        resultCount = 1;
        char lastChar = words[0][strlen(words[0]) - 1];
        int i;
        for (i = 1; i < wordCount; i++)
        {
            if (words[i][0] == lastChar)
            {
                strcpy(result[resultCount], words[i]);
                resultCount++;
                lastChar = words[i][strlen(words[i]) - 1];
            }
        }
        FILE *bin = fopen("output.bin", "wb");
        for (i = 0; i < resultCount; i++)
        {
            fwrite(result[i], strlen(result[i]), 1, bin);
            if (i < resultCount - 1)
            {
                char s = ' ';
                fwrite(&s, 1, 1, bin);
            }
        }
        fclose(bin);
        printf("linked words saved to output.bin\n");
    }
}

void runProblem4()
{
    char filename[100];
    int key;
    printf("filename to encode:");
    scanf("%99s", filename);
    printf("key 2-10:");
    scanf("%d", &key);
    FILE *in = fopen(filename, "r");
    FILE *out = fopen("encoded.txt", "w");
    if (in != NULL && out != NULL)
    {
        int c;
        while ((c = fgetc(in)) != EOF)
        {
            fputc(c + key, out);
        }
        fclose(in);
        fclose(out);
        printf("done encoded.txt created\n");
    }
}

void runProblem5()
{
    char word[] = "concatenation";
    int len = strlen(word);
    char disp[100];
    int i, found = 0, guesses = 0;
    for (i = 0; i < len; i++) disp[i] = '_';
    disp[len] = '\0';
    while (found < len)
    {
        printf("word: %s letter:", disp);
        char l;
        scanf(" %c", &l);
        guesses++;
        for (i = 0; i < len; i++)
        {
            if (word[i] == l && disp[i] == '_')
            {
                disp[i] = l;
                found++;
            }
        }
    }
    printf("win word was %s\n", word);
}

void runProblem6()
{
    char w1[100], w2[100];
    int c1[256] = {0}, c2[256] = {0}, i;
    printf("word 1:");
    scanf("%99s", w1);
    printf("word 2:");
    scanf("%99s", w2);
    if (strlen(w1) == strlen(w2))
    {
        for (i = 0; w1[i]; i++) c1[(unsigned char)w1[i]]++;
        for (i = 0; w2[i]; i++) c2[(unsigned char)w2[i]]++;
        for (i = 0; i < 256; i++)
        {
            if (c1[i] != c2[i])
            {
                printf("no\n");
                return;
            }
        }
        printf("yes anagram\n");
    }
    else
    {
        printf("no\n");
    }
}

void runProblem7()
{
    FILE *f = fopen("employees.dat", "ab+");
    struct Employee emp;
    printf("id:");
    scanf("%d", &emp.id);
    printf("pay:");
    scanf("%f", &emp.hourlyPay);
    printf("hours:");
    scanf("%d", &emp.hoursWorked);
    float p = emp.hoursWorked <= 40 ? emp.hoursWorked * emp.hourlyPay : (40 * emp.hourlyPay) + (emp.hoursWorked - 40) * emp.hourlyPay * 1.5f;
    emp.weeklySalary = p * 0.9635f;
    fwrite(&emp, sizeof(struct Employee), 1, f);
    fclose(f);
    printf("employee added\n");
}

int main()
{
    int choice;
    while (1)
    {
        printf("\n--- MENU ---\n3. word link\n4. encode\n5. hangman\n6. anagram\n7. employee\n0. exit\nchoice:");
        if (scanf("%d", &choice) != 1) break;
        if (choice == 0) break;
        if (choice == 3) runProblem3();
        else if (choice == 4) runProblem4();
        else if (choice == 5) runProblem5();
        else if (choice == 6) runProblem6();
        else if (choice == 7) runProblem7();
    }
    return 0;
}
