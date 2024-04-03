#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <ctype.h>
#include <stdlib.h> // atoi �Լ��� ����ϱ� ���� �߰�

/* ���� ���� */
char lexeme[100];
char nextChar;
int lexLen;
int token;
int nextToken;
int charClass;
FILE* in_fp, * fopen();

/* �Լ� ����� */
void addChar();
void getChar();
void getNonBlank();
int lookup(char ch);
int lex();
int lookup(char ch);

/* ���� ������ ��ū �ڵ� */
#define LETTER 0
#define DIGIT 1
#define UNKNOWN 99

#define INT_LIT 10
#define IDENT 11
#define ASSIGN_OP 20
#define ADD_OP 21
#define SUB_OP 22
#define MULT_OP 23
#define DIV_OP 24
#define LEFT_PAREN 25
#define RIGHT_PAREN 26


int lookup(char ch) {
    switch (ch) {
    case '(':
        addChar();
        nextToken = LEFT_PAREN;
        break;
    case ')':
        addChar();
        nextToken = RIGHT_PAREN;
        break;
    case '+':
        addChar();
        nextToken = ADD_OP;
        break;
    case '-':
        addChar();
        nextToken = SUB_OP;
        break;
    case '*':
        addChar();
        nextToken = MULT_OP;
        break;
    case '/':
        addChar();
        nextToken = DIV_OP;
        break;
    default:
        addChar();
        nextToken = EOF;
        break;
    }
    return nextToken;
}

/* ���� �м��� */
int lex() {
    lexLen = 0;
    getNonBlank();
    switch (charClass) {
    case LETTER:
        addChar();
        getChar();
        while (charClass == LETTER || charClass == DIGIT) {
            addChar();
            getChar();
        }
        nextToken = IDENT;
        break;
    case DIGIT:
        addChar();
        getChar();
        while (charClass == DIGIT) {
            addChar();
            getChar();
        }
        nextToken = INT_LIT;
        break;
    case UNKNOWN:
        lookup(nextChar);
        getChar();
        break;
    case EOF:
        nextToken = EOF;
        lexeme[0] = 'E';
        lexeme[1] = 'O';
        lexeme[2] = 'F';
        lexeme[3] = 0;
        break;
    }
    printf("Next token is: %d, Next lexeme is %s\n", nextToken, lexeme);
    return nextToken;
}


/* ���� �м��� */
int expr();
int term();
int factor();

int expr() {
    int value = term();
    while (nextToken == ADD_OP || nextToken == SUB_OP) {
        int op = nextToken;
        lex(); // ������ ���� ��ū���� �̵�
        if (op == ADD_OP) {
            value += term();
        }
        else {
            value -= term();
        }
    }
    return value;
}

int term() {
    int value = factor();
    while (nextToken == MULT_OP || nextToken == DIV_OP) {
        int op = nextToken;
        lex(); // ������ ���� ��ū���� �̵�
        if (op == MULT_OP) {
            value *= factor();
        }
        else {
            value /= factor();
        }
    }
    return value;
}

int factor() {
    int value = 0;
    if (nextToken == INT_LIT) {
        value = atoi(lexeme);
        lex(); // ���� ���� ��ū���� �̵�
    }
    else if (nextToken == LEFT_PAREN) {
        lex(); // ��ȣ �� ǥ���� ó��
        value = expr();
        if (nextToken == RIGHT_PAREN) {
            lex(); // �ݴ� ��ȣ ���� ��ū���� �̵�
        }
        else {
            printf("Error: Missing right parenthesis.\n");
        }
    }
    else {
        printf("Error: Unrecognized token %d\n", nextToken);
        lex(); // ���� �߻� �� ���� ��ū���� �̵��Ͽ� ��� ����
    }
    return value;
}



/* �߰��� �Լ� ���� */
void addChar() {
    if (lexLen <= 98) {
        lexeme[lexLen++] = nextChar;
        lexeme[lexLen] = 0;
    }
    else
        printf("Error - lexeme is too long \n");
}

void getChar() {
    if ((nextChar = getc(in_fp)) != EOF) {
        if (isalpha(nextChar))
            charClass = LETTER;
        else if (isdigit(nextChar))
            charClass = DIGIT;
        else
            charClass = UNKNOWN;
    }
    else
        charClass = EOF;
}

void getNonBlank() {
    while (isspace(nextChar))
        getChar();
}

/* main �Լ� */
int main() {
    if ((in_fp = fopen("front.in", "r")) == NULL)
        printf("ERROR - cannot open front.in \n");
    else {
        getChar();
        do {
            lex();
            int result = expr();
            printf("Result = %d\n", result);
        } while (nextToken != EOF);
    }
    return 0;
}