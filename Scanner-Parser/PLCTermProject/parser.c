#include "reference.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

FILE* in_fp, * fopen();

int CodeLine = 1;
int nodeNumber = 1;
int value = 0;			// Value for ID only


struct node {
	int NodeNumber;
	int RuleInUse;
	int alternative;
	int id_val;
	struct node * branchOne;		// Left branch
	struct node * branchTwo;		// Right Branch
	struct node * branchThree;		// Middle Branch
};


struct node* newNode(int NodeNumber, int rule, int alt, int value) {
	struct node* node = (struct node*)malloc(sizeof(struct node));
	node->NodeNumber = NodeNumber;
	node->RuleInUse = rule;
	node->alternative = alt;
	node->id_val = value;
	
	node->branchOne = NULL;
	node->branchTwo = NULL;
	node->branchThree = NULL;

	return (node);
};

struct node* currentNode;
struct node* root;


//tree to keep track of nodes

//struct node* currentNode = root->first;

/* global declarations */
/* variables */

void parse()
{
	if ((in_fp = fopen("myinput.txt", "r")) == NULL)
		printf("error - cannot open myinput.txt \n");
	else
	{
		getChar();
		lex();
		if (strcmp(lexeme, "program") == 0)
		{
			root = newNode(nodeNumber++, 1, 1, 0);

			currentNode = root;
			lex();

			do
			{

				if (strcmp(lexeme, "begin") != 0)
				{
					//currentNode = root->first;
					decl_sec();
				}
				else
				{
					//root->branchTwo = newNode(nodeNumber++, 1, 0, 0);
					currentNode = root;					// Done with Declaration side, move back to start and go down the right side now
					lex();
					stmt_sec();
				}

			} while (strcmp(lexeme, "end"));
		}
		else
		{
			printf("this program is not a valid program! Missing program keyword!\n");
			exit(-1);				// Used to exit program for error
		}

		lex();
		if (nextToken == TERMINATE)
		{
			lex();
			if (nextToken != EOF)
			{
				printf("Error, expecting end of file at Line %d!", CodeLine);
				exit(-1);
			}
			else
			{
				printf("Node #\tRule#\tBranch1\tBranch2\tBranch3\tAlternative #\t Id/Int Value\n");
				printf("----------------------------------------------------------------------\n");
				printTable(root);
			}
		} 
		else
		{
			printf("Error, missing terminate keyword: ' ; ' at Line %d!", CodeLine);
			exit(-1);
		}

		
	}
}

void decl_sec()
{
	push(currentNode, 2, 1, 0);
	decl();
	while (strcmp(lexeme, "begin") != 0)
	{
		currentNode = root->branchOne;
		//push(currentNode, 2, 2, 0);
		decl();
	}
	
}

void decl()

{
	
	push(currentNode,3,1, 0);
	id_list();
	if(nextToken == DECLARE)
	{
		lex();
		if (strcmp(lexeme, "int") != 0)
		{
			printf("Error, expecting type declaration: int at Line %d!", CodeLine);
			exit(-1);
		}
		else
		{
			lex();
			if (nextToken != TERMINATE)
			{
				printf("Error, missing terminate keyword: ' ; ' at Line %d!", CodeLine);
				exit(-1);
			}
		}
		
	}
	else
	{
		printf("Error, expecting a declaration: ' : ' at Line %d!", CodeLine);
		exit(-1);
	}
	lex();
}

void id_list()
{	
	push(currentNode, 4, 1, 0);
	id();

	while (nextToken == COMMA)
	{
		push(currentNode, 4, 2, 0);
		lex();
		id();
	}

}

void id()
{


	if (nextToken == IDENT)
	{
		if (strcmp(lexeme, "a") == 0)
		{
			value = 1;
		}
		else if (strcmp(lexeme, "b") == 0)
		{
			value = 2;
		}
		else if (strcmp(lexeme, "c") == 0)
		{
			value = 3;
		}
		else if (strcmp(lexeme, "d") == 0)
		{
			value = 4;
		}
		else if (strcmp(lexeme, "e") == 0)
		{
			value = 5;
		}
		else if (strcmp(lexeme, "f") == 0)
		{
			value = 6;
		}
		else if (strcmp(lexeme, "g") == 0)
		{
			value = 7;
		}
		else if (strcmp(lexeme, "h") == 0)
		{
			value = 8;
		}
		else if (strcmp(lexeme, "i") == 0)
		{
			value = 9;
		}
		else if (strcmp(lexeme, "j") == 0)
		{
			value = 10;
		}
		else if (strcmp(lexeme, "k") == 0)
		{
			value = 11;

		}
		else if (strcmp(lexeme, "l") == 0)
		{
			value = 12;

		}
		else if (strcmp(lexeme, "m") == 0)
		{
			value = 13;

		}
		else if (strcmp(lexeme, "n") == 0)
		{
			value = 14;

		}
		else if (strcmp(lexeme, "o") == 0)
		{
			value = 15;

		}
		else if (strcmp(lexeme, "p") == 0)
		{
			value = 16;

		}
		else if (strcmp(lexeme, "q") == 0)
		{
			value = 17;

		}
		else if (strcmp(lexeme, "r") == 0)
		{
			value = 18;

		}
		else if (strcmp(lexeme, "s") == 0)
		{
			value = 19;

		}
		else if (strcmp(lexeme, "t") == 0)
		{
			value = 20;

		}
		else if (strcmp(lexeme, "u") == 0)
		{
			value = 21;

		}
		else if (strcmp(lexeme, "v") == 0)
		{
			value = 22;

		}
		else if (strcmp(lexeme, "w") == 0)
		{
			value = 23;

		}
		else if (strcmp(lexeme, "x") == 0)
		{
			value = 24;

		}
		else if (strcmp(lexeme, "y") == 0)
		{
			value = 25;

		}
		else
		{
			value = 26;
		}
		push(currentNode, 5, 0, value);
		lex();
		
	}
	else
	{
		printf("Error, unable to parse ID, unknown ID identifier: ' %s ' at Line %d!",lexeme, CodeLine);
		exit(-1);
	}
}

void stmt_sec()
{
	push(currentNode, 6, 1, 0);
	stmt();
	while (strcmp(lexeme, "else") != 0 && strcmp(lexeme, "end") != 0)
	{
		currentNode = root->branchTwo;
		push(currentNode, 6, 2, 0);
		stmt();
	}
}

void stmt()
{
	
	if (nextToken == IDENT)
	{
		push(currentNode, 7, 1, 0);
		assign();
	}
		
	else if (nextToken == RESERVED_WORD)
	{
		if (strcmp(lexeme, "if") == 0)
		{
			push(currentNode, 7, 2, 0);
			ifstmt();
		}
		else if (strcmp(lexeme, "while") == 0)
		{
			push(currentNode, 7, 3, 0);
			whilestmt();
		}
		else if (strcmp(lexeme, "input") == 0)
		{
			push(currentNode, 7, 4, 0);
			inputstmt();
		}
		else if (strcmp(lexeme, "output") == 0)
		{
			push(currentNode, 7, 5, 0);
			outputstmt();
		}
		else
		{
			printf("Error, unable to parse statement, unknown reserved word: ' %s ' at Line %d!", lexeme, CodeLine);
			exit(-1);
		}
	}
	else
	{
		printf("Error, unable to parse statement, unknown statement type: ' %s ' at Line %d!", lexeme, CodeLine);
		exit(-1);
	}
	
}

void assign()
{
	push(currentNode, 8, 1, 0);
	id();
	if (nextToken == ASSIGN_OP)
	{
		lex();
		expr();
	}
	else
	{
		printf("Error, inappropriate assignment of variable, need this ' := ' at Line %d!", CodeLine);
		exit(-1);
	}
	if (nextToken != TERMINATE)
	{
		printf("Error, missing terminate keyword: ' ; ' at Line %d!", CodeLine);
		exit(-1);
	}
	//CodeLine++;
	lex();

}

void inputstmt()
{
	push(currentNode, 11, 1, 0);
	lex();
	id_list();
	if (nextToken != TERMINATE)
	{
		printf("Error, missing terminate keyword: ' ; ' at Line %d!", CodeLine);
		exit(-1);
	}
	//CodeLine++;
	lex();
}

void whilestmt()
{
	push(currentNode, 10, 1, 0);
	lex();
	comp();
	if (strcmp(lexeme, "loop") == 0)
	{
		lex();
		stmt_sec();
		if (strcmp(lexeme, "end") == 0)
		{
			lex();
			if (strcmp(lexeme, "loop") != 0)
			{
				printf("Error, missing reserved_word: ' loop ' at Line %d!", CodeLine);
				exit(-1);
			}

		}
	}
	else
	{
		printf("Error, missing reserved_word: ' loop ' at Line %d!", CodeLine);
		exit(-1);
	}
	lex();
	if (nextToken != TERMINATE)
	{
		printf("Error, missing terminate keyword: ' ; ' at Line %d!", CodeLine);
		exit(-1);
	}
	//CodeLine++;
	lex();
}

void outputstmt()
{
	push(currentNode, 12, 1, 0);
	lex();
	id_list();
	if (nextToken != TERMINATE)
	{
		printf("Error, missing terminate keyword: ' ; ' at Line %d!", CodeLine);
		exit(-1);
	}
	//CodeLine++;
	lex();
}
 

void expr()
{
	push(currentNode, 13, 1, 0);
	factor();
	while (nextToken == ADD_OP || nextToken == SUB_OP)
	{
		lex();
		expr();
	}

}

void factor()
{
	push(currentNode, 14, 1, 0);
	operand();
	while (nextToken == MULT_OP)
	{
		lex();
		factor();
	}
}

void operand()
{
	push(currentNode, 15, 1, 0);
	if (nextToken == INT_LIT)
		INT();
	else if (nextToken == IDENT)
		id();
	else if (nextToken == LEFT_PAREN)
	{
		lex();
		expr();
		if (nextToken == RIGHT_PAREN)
		{
			lex();
		}
		else
		{
			printf("Error, missing type declaration: ')' at Line %d!", CodeLine);
			exit(-1);
		}
	}
	else
	{
		printf("Error, unable to parse operation, unknown type identifier: ' %s ' at Line %d!", lexeme, CodeLine);
		exit(-1);
	}
}

void INT()
{
	push(currentNode, 16, 1, 0);
	lex();
}

void ifstmt()
{
	push(currentNode, 9, 1, 0);
	lex();
	comp();
	if (strcmp(lexeme, "then") == 0)
	{
		//CodeLine++;
		push(currentNode, 9, 1, 0);
		lex();
		stmt_sec();

		if (strcmp(lexeme, "else") == 0)
		{
			//CodeLine++;
			pushThirdBranch(currentNode, 9, 2, 0);
			lex();
			stmt_sec();
		}
		if (strcmp(lexeme, "end") == 0)
		{
			lex();
			if (strcmp(lexeme, "if") != 0)
			{
				printf("Error, missing reserved_word: ' if ' at Line %d!", CodeLine);;
				exit(-1);
			}
			
		} 
		else
		{
			printf("Error, missing reserved_word: ' end ' at Line %d!", CodeLine);
			exit(-1);
		}
	}
	else
	{
		printf("Error, missing reserved_word: ' then ' at Line %d!", CodeLine);
		exit(-1);
	}
	lex();
	if (nextToken != TERMINATE)
	{
		printf("Error, missing terminate keyword: ' ; ' at Line %d!", CodeLine);
		exit(-1);
	}
	//CodeLine++;
	lex();
}

void comp()
{

	if(nextToken == LEFT_PAREN)
	{
		lex();
		operand();
		while (nextToken != RIGHT_PAREN)
		{
			switch (nextToken)
			{
			case EQUALS:
				push(currentNode, 17, 1, 0);
				lex();
				operand();
				break;
			case NOT_EQUAL:
				push(currentNode, 17, 2, 0);
				lex();
				operand();
				break;
			case LESS_THAN:
				push(currentNode, 17, 4, 0);
				lex();
				operand();
				break;
			case GREATER_THAN:
				push(currentNode, 17, 3, 0);
				lex();
				operand();
				break;
			default:
				printf("Error, unable to parse comparison, missing: ' ) ' at Line %d!", CodeLine - 1);
				exit(-1);
			}
		}

	}
	else
	{
		printf("Missing type declaration: ' ( ' at Line %d!", CodeLine);
		exit(-1);
	}
	//CodeLine++;
	lex();
}

//This code section is for handling any declaration statements before we get to begin

void push(struct node* node, int rule, int alt, int value)
{
	if (node == root && root->branchOne == NULL)					// Check if we are at the root
	{
		node->branchOne = newNode(nodeNumber++, rule, alt, value);
		currentNode = node->branchOne;
		return;
	}
	else if(node == root && root->branchTwo == NULL)				// If root has one branch already, move on to the next (Root will not have more than two branches)
	{
		node->branchTwo = newNode(nodeNumber++, rule, alt, value);
		currentNode = node->branchTwo;
		return;
	}
	else															// Else, we are not currently working on the root
	{

		if (node->branchOne == NULL)
		{
			node->branchOne = newNode(nodeNumber++, rule, alt, value);
			if (value == 0)											// Check if this is not an ID node, move to the next branch. Else, just return and do not move ahead
				currentNode = node->branchOne;
			return;
		}
		else if(node->branchTwo == NULL)
		{
			node->branchTwo = newNode(nodeNumber++, rule, alt, value);
			currentNode = node->branchTwo;
			return;
		}
		else
		{
			push(node->branchTwo, rule, alt, value);				// If both branches are in use, we want to advance to the child node's right
		}
	}
}

void pushThirdBranch(struct node* node, int rule, int alt, int value)		// Specific for if-else stateemtn
{
		node->branchThree = newNode(nodeNumber++, rule, alt, value);
		currentNode = node->branchThree;
		return;
}

void printTable(struct node* root) {
 	if (root == NULL) {
		return;
	}

	struct node* PrintNode = root;

	int firstBranch = PrintNode->branchOne == NULL ? 0 : PrintNode->branchOne->NodeNumber;
	int secondBranch = PrintNode->branchTwo == NULL ? 0 : PrintNode->branchTwo->NodeNumber;
	int thirdBranch = PrintNode->branchThree == NULL ? 0 : PrintNode->branchTwo->NodeNumber;

	if(PrintNode-> id_val == 0)
		printf("%d\t%d\t%d\t%d\t%d\t%d\n", PrintNode->NodeNumber, PrintNode->RuleInUse, firstBranch, secondBranch, thirdBranch, PrintNode->alternative);
	else
		printf("%d\t%d\t%d\t%d\t%d\t%d\t\t%d\n", PrintNode->NodeNumber, PrintNode->RuleInUse, firstBranch, secondBranch, thirdBranch, PrintNode->alternative, PrintNode -> id_val);

	printTable(PrintNode->branchOne);
	printTable(PrintNode->branchTwo);
	
	
}