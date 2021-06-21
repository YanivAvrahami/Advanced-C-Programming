#ifndef CLIENT_H
#define CLIENT_H

typedef struct _client
{
	char id[9];     // 12345678	
	char phone[12]; // 054-1234567 	
} Client;

typedef struct _short_client
{
	unsigned char short_id[4];
	unsigned char short_phone[5];
} Short_client;


// searches for a client by the client id
char *searchClientByID(Short_client *arrSClient, int n, char *id);

// creates a short client array of size N by requesting data from user
Short_client *createShortClientArr(int n);

// compresses client data to short client
void compressClient(Client *pclient, Short_client *pout);

// decompresses short client data to client
void decompressClient(Short_client *pclient, Client *out);

// compresses N clients data to an array of short client
void compressNClients(int n, Client *arrClient, Short_client *outArrSClient);

// decompresses N short clients data to an array of client
void decompressNSClients(int n, Short_client *arrSClient, Client *outArrClient);

// compresses an id
void compressID(char *id, unsigned char *out);

// decompresses an id
void decompressID(unsigned char *id, char *out);

// compresses a phone 
void compressPhone(char *phone, unsigned char *out);

// decompresses a phone 
void decompressPhone(unsigned char *phone, char *out);

// compresses two chars with max value of 9 into one char
unsigned char compress2CharsTo1(char c1, char c2);

// decompresses one char into two chars
void decompress1CharTo2(unsigned char c, char *pc1, char *pc2);

// prints client
void printClient(Client *pclient);

// prints N clients
void printNClients(int n, Client *arrClient);

// request N clients from user
void requestNClients(int n, Client *out);

// request a client from user
void requestClient(Client *out);

// checks if two ids are equal
bool isEqualCompID(char *id1, char *id2);

#endif