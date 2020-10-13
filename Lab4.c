#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

char* read_file(char *);
void write_file(char *, char *);
void make_rand_key(int, char*);
void encrypt(char*, char*, char*);
void decrypt(char*, char*, char*);

int main()
{
		srand(time(NULL));
		
		int input;

		printf("Encrypt a file:	1\nDecrypt a file:	2\nExit:      	3\nEnter a choice: ");
		scanf("%d", &input);

		switch(input){

			case 1:
				encrypt("test.txt", "cipher_key.txt","encryption_result.txt");
				break;

			case 2:
				decrypt("cipher_key.txt", "encryption_result.txt", "decrypted.txt");
				break;

			default:
				return 0;
		}

		return 0;
}

void encrypt(char* clear_file, char* key_file, char* cipher_file){

	char* clear_string = read_file(clear_file);

	int length = strlen(clear_string);

	char* key = (char*)malloc(length*sizeof(char));
	char* cipher_text = (char*)malloc(length*sizeof(char));

	make_rand_key(length, key);

	int i;
	for(i = 0; i < length; i++){
		cipher_text[i] = clear_string[i] ^ key[i]; 		
	}
	
	write_file(cipher_text, cipher_file);
	write_file(key, key_file);
	
	printf("\nGenerated key: %s\n", key);
	printf("Encrypted text: %s\n", cipher_text);
}

void decrypt(char* key_file, char* cipher_file, char* clear_file){

	char* encrypted_string = read_file(cipher_file);

	char* key = read_file(key_file);
	int length = strlen(encrypted_string);

	char* decrypted_string = (char*)malloc(length*sizeof(char));
	
	int i;
	for(i = 0; i < length; i++){
		decrypted_string[i] = encrypted_string[i] ^ key[i];
	}

	write_file(decrypted_string, clear_file);

	printf("\nText to decrypt: %s\n", encrypted_string);
	printf("\nDecrypted text: %s\n", decrypted_string);
}

char* read_file(char *file_name)
{
    FILE *fp = fopen(file_name, "r");

    if (fp == NULL)
    {
        printf("File not found");
    }

    fseek(fp, 0L, SEEK_END);

		long int size = ftell(fp);

    char *string = (char *)malloc(size * sizeof(char));

    rewind(fp);

    fread(string, sizeof(char), size, fp);

    fclose(fp);

		return string;
}

void write_file(char *string, char *file_name)
{

    FILE *fp = fopen(file_name, "w");

    fwrite(string, sizeof(char), strlen(string), fp);

    fclose(fp);
}

void make_rand_key(int length, char* key){
	int i;	
	for(i = 0; i < length; i++){
		key[i] = (char)(rand()%(122-33))+33;
	}

}
