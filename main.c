#include <stdio.h>
#include <stdlib.h>
#include<string.h>

typedef struct NODE{
char data;
struct NODE *n;
}st;
st *push(st *top, char c)
{

    st *new_node = (st *)malloc(sizeof(st));
    new_node->data = c;
    new_node->n = NULL;
    if (top == NULL)
        top = new_node;

    else
    {
        new_node->n = top;
        top = new_node;
    }

    return top;
}

st *pop(st *top)
{
    st *temp = top;
    top = top->n;
    free(temp);
    return top;
}
char *string_rev(char a[20], char rev[])
{
    int l = strlen(a);
    int j = 0;

    for (int i = l - 1; i >= 0; i--)
    {
        rev[j] = a[i];
        j++;
    }
    rev[j] = '\0';
    return rev;
}

int isEmpty(st *top)
{
    if (top == NULL)
        return 1;
    else
        return 0;
}
char readTop(st *top)
{
    return top->data;
}
void display(st *top)

{
    st *temp = top;
    while (temp)
    {
        printf("|  %c  |\n", temp->data);
        temp = temp->n;
    }
}

int Isdigit(char token)
{
    if (token >= '0' && token <= '9')
        return 1;
    else
        return 0;
}

int presedence(char token)
{

    switch (token)
    {
    case '(':
        return 0;
    case ')':
        return 0;
    case '+':
        return 1;
    case '-':
        return 1;
    case '*':
        return 2;
    case '/':
        return 2;
    }
    return -1;

}

char *infix_to_postfix(char infix[20], char postfix[20])
{

    int i, j = 0;
    char token;
    st *top = NULL;
    for (i = 0; infix[i] != '\0'; i++)
    {
        token = infix[i];
        if (token == '(')
        {
            top = push(top, token);
        }
        else if (Isdigit(token))
        {
            postfix[j] = token;
            j++;
        }

        else if (token == ')')
        {

            while (readTop(top) != '(')
            {
                char x = readTop(top);
                postfix[j] = x;
                j++;

                top = pop(top);
            }
            top = pop(top);
        }

        else
        {
            while (!isEmpty(top) &&
                   presedence(token) <= presedence(readTop(top)))
            {


                postfix[j] = readTop(top);
                j++;
                top = pop(top);
            }

            top = push(top, token);
        }
    }
    while (!isEmpty(top))
    {
        postfix[j] = readTop(top);
        j++;
        top = pop(top);
    }
    postfix[j] = '\0';
    return postfix;
}

void infix_to_prefix(char infix[], char prefix[])
{
    char rev_infix[20];
    int l = strlen(infix);
    int j = 0;
    char rev[20];
    for (int i = l - 1; i >= 0; i--)
    {
        if (infix[i] == '(')
            rev_infix[j] = ')';
        else if (infix[i] == ')')
            rev_infix[j] = '(';
        else
            rev_infix[j] = infix[i];
        j++;
    }
    rev_infix[j] = '\0';
    
    printf("%s  ", string_rev(prefix, rev));
}

int eval_postfix(char postfix[20])
{
    st *top = NULL;
    int i = 0;
    char token, x;
    for (i = 0; postfix[i] != '\0'; i++)


    {
        token = postfix[i];
        if (Isdigit(token))
        {
            top = push(top, token - 48);
        }
        else

        {
            int op1, op2;

            op2 = readTop(top);
            top = pop(top);
            op1 = readTop(top);
            top = pop(top);
            switch (token)
            {

            case '+':
                x = op1 + op2;
                break;
            case '-':
                x = op1 - op2;
                break;
            case '*':
                x = op1 * op2;
                break;
            case '/':
                x = op1 / op2;
                break;
            }
            top = push(top, x);
        }
    }
    x = readTop(top);
    top = pop(top);
    return x;
}

int eval_prefix(char prefix[20])
{
    char prefix_rev[20];
    strcpy(prefix_rev, string_rev(prefix, prefix_rev));

    st *top = NULL;
    int i = 0;
    char token, x;
    for (i = 0; prefix_rev[i] != '\0'; i++)
    {
        token = prefix_rev[i];
        if (Isdigit(token))
        {
            top = push(top, token - 48);
        }
        else
        {
            int op1, op2;
            op1 = readTop(top);

            top = pop(top);
            op2 = readTop(top);
            top = pop(top);
            switch (token)
            {
            case '+':
                x = op1 + op2;
                break;
            case '-':
                x = op1 - op2;
                break;
            case '*':
                x = op1 * op2;
                break;
            case '/':
                x = op1 / op2;
                break;
            }
            top = push(top, x);
        }
    }


    x = readTop(top);
    top = pop(top);
    return x;
}


int main(void) {
  char pof[50],inf[50],pref[50];
  int ch=0;
  while(ch!=5)
{
    printf("\nEnter operation you want to perform using stack \n1.Infix to Postfix operation \n2.Infix to Prefix opretion \n3.Postfix Evaluation \n4.Prefix Evaluation \n5.Exit\n ");
    scanf("%d",&ch);
    switch(ch){
      case 1:

      printf("\nEnter infix Expression");
      scanf("%s",inf);
      printf("%s",infix_to_postfix(inf,pof));
      break;

      case 2:


      printf("\nEnter  infix  expression  ");
            scanf("%s", inf);
            infix_to_prefix(inf, pref);
            break;

      case 3:

      printf("\nEnter  postfix  expression  ");
            scanf("%s", pof);
            printf("\nans=  %d  ", eval_postfix(pof));
            break;

      case 4:

                printf("\nEnter  prefix  expression  ");
            scanf("%s", pref);
            printf("ans=  %d  ", eval_prefix(pref));
            break;
      
      case 5:
      break;

    }
  }

  return 0;

}

