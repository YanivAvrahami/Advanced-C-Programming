#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "client.h"
#include "bits.h"
#include "util.h"
#include "arr.h"

char * searchClientByID(Short_client *arrSClient, int n, char *id)
{
	int i, j;
	char idcomp[4];
	char *res;

	res = (char *)malloc(12 * sizeof(char));

	compressID(id, idcomp);

	for (i = 0; i < n; i++) 
	{
		if (isEqualCompID(idcomp, arrSClient[i].short_id))
		{
			decompressPhone(arrSClient[i].short_phone, res);
			return res;
		}
	}
			
	return NULL;
}

Short_client *createShortClientArr (int n)
{
	Client *arrClient;
	Short_client *arrSClient;
	int i;
	int ch;

	arrClient = (Client *)safeMalloc(sizeof(Client), n);
	arrSClient = (Short_client *)safeMalloc(sizeof(Short_client), n);
	
	requestNClients(n, arrClient);

	compressNClients(n, arrClient, arrSClient);

	while (((ch = getchar()) != EOF) && (ch != '\n'));

	free(arrClient);

	return arrSClient;
}





unsigned char compress2CharsTo1(char c1, char c2)
{
	unsigned char res;
	
	res = 0;

	c1 -= '0';
	c2 -= '0';

	c1 <<= 4;

	res = c1 | c2;

	return res;
}

void decompress1CharTo2(unsigned char c, char *pc1, char *pc2)
{
	char c1, c2;
	c1 = c2 = 0;

	c1 = c >> 4;

	c2 = RANGE_BIT_CLEAR(c, unsigned char, 4, 7);

	c1 += '0';
	c2 += '0';

	*pc1 = c1;
	*pc2 = c2;
}


void compressID(char *id, unsigned char *out)
{
	int i;
	int write;
	write = 0;
	
	for (i = 0; i < 8; i += 2)
	{
		out[write] = compress2CharsTo1(id[i], id[i + 1]);
		write++;
	}
}

void decompressID(unsigned char *id, char *out)
{
	int i;
	int write;
	write = 0;

	for (i = 0; i < 4; i++)
	{
		decompress1CharTo2(id[i], &out[write], &out[write + 1]);
		write += 2;
	}

	out[8] = '\0';
}


void compressPhone(char *phone, unsigned char *out)
{
	int i;
	int write;
	write = 0;
	for (i = 0; i < 11; i += 2)
	{
		if (i == 2)
		{
			out[write] = compress2CharsTo1(phone[i], phone[i + 2]);
			i++;
			write++;
		}
		else
		{
			out[write] = compress2CharsTo1(phone[i], phone[i + 1]);
			write++;
		}
		
	}
}

void decompressPhone(unsigned char *phone, char *out)
{
	int i;
	int write;
	write = 0;

	for (i = 0; i < 5; i++)
	{
		if (write == 2)
		{
			decompress1CharTo2(phone[i], &out[write], &out[write + 2]);
			out[write + 1] = '-';
			write += 3;
		}
		else
		{
			decompress1CharTo2(phone[i], &out[write], &out[write + 1]);
			write += 2;
		}
	}

	out[11] = '\0';
}


void compressClient(Client *pclient, Short_client *pout)
{
	compressID(pclient->id, pout->short_id);
	compressPhone(pclient->phone, pout->short_phone);
}

void decompressClient(Short_client *pclient, Client *out)
{
	decompressID(pclient->short_id, out->id);
	decompressPhone(pclient->short_phone, out->phone);
}


void compressNClients(int n, Client *arrClient, Short_client *outArrSClient)
{
	int i;
	for (i = 0; i < n; i++)
		compressClient(&arrClient[i], &outArrSClient[i]);
}

void decompressNSClients(int n, Short_client *arrSClient, Client *outArrClient)
{
	int i;
	for (i = 0; i < n; i++)
		decompressClient(&arrSClient[i], &outArrClient[i]);
}



void requestNClients(int n, Client *out)
{
	int i;
	for (i = 0; i < n; i++)
		requestClient(&out[i]);
}

void requestClient(Client *out)
{
	scanf("%s", out->id);
	scanf("%s", out->phone);
}


void printClient(Client *pclient)
{
	printf("%s\n", pclient->id);
	printf("%s\n", pclient->phone);
	printf("\n");
}

void printNClients(int n, Client *arrClient)
{
	int i;
	for (i = 0; i < n; i++)
		printClient(&arrClient[i]);
}

bool isEqualCompID(char *id1, char *id2)
{
	return isEqualCharArr(id1, id2, 4);
}