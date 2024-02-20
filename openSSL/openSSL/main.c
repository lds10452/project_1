#define _CRT_SECURE_NO_WARNINGS
#include "openssl/md5.h"		// md5 ͷ�ļ�
#include "openssl/sha.h"
#include "openssl/hmac.h"
#include "openssl/aes.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void getMD5(const char* str)
{
	unsigned char md[MD5_DIGEST_LENGTH] = { 0 };
	unsigned char result[MD5_DIGEST_LENGTH * 2 + 1] = { 0 };
	// ��һ�ַ�ʽ
	//MD5_CTX ctx;
	//// ��ʼ��
	//MD5_Init(&ctx);
	//// �������
	//MD5_Update(&ctx, str, strlen(str));
	//// ������
	//MD5_Final(md, &ctx);

	// �ڶ��ַ�ʽ
	MD5(str, strlen(str), md);

	for (int i = 0; i < 16; ++i)
	{
		sprintf(&result[i * 2], "%02x", md[i]);
	}
	printf("md5 value: %s\n", result);
}

void getSHA1(const char* str)
{
	unsigned char md[SHA_DIGEST_LENGTH];
	unsigned char result[SHA_DIGEST_LENGTH * 2 + 1];
	SHA1(str, strlen(str), md);
	for (int i = 0; i < SHA_DIGEST_LENGTH; ++i)
	{
		sprintf(&result[i * 2], "%02x", md[i]);
	}
	printf("sha1 value: %s\n", result);
}

void getHmac()
{
	char key[] = "mysecretkey";
	char data[] = "Hello, HMAC!";
	unsigned char result[EVP_MAX_MD_SIZE];
	unsigned int result_length;

	//�ʺ��������Ƚϴ�
	HMAC_CTX* ctx = HMAC_CTX_new();
	HMAC_Init_ex(ctx, key, strlen(key), EVP_sha256(), NULL);
	HMAC_Update(ctx, (unsigned char*)data, strlen(data));
	HMAC_Final(ctx, result, &result_length);
	HMAC_CTX_free(ctx);

	//�ʺ��������Ƚ���
	//HMAC(EVP_sha256(), key, strlen(key), data, strlen(data), result, &result_length);

	printf("HMAC-SHA256: ");
	for (int i = 0; i < result_length; i++) {
		printf("%02x", result[i]);
	}
	printf("\n");
}

void AES()
{
	unsigned char userKey[AES_BLOCK_SIZE];
	unsigned char* data = (unsigned char*)malloc(AES_BLOCK_SIZE * 3);
	unsigned char* encrypto = (unsigned char*)malloc(AES_BLOCK_SIZE * 3);
	unsigned char* decrypt = (unsigned char*)malloc(AES_BLOCK_SIZE * 3);
	AES_KEY key;

	memcpy(userKey, "zheshiopensslexq", 16);
	memset((void*)data, 'p', AES_BLOCK_SIZE * 3);
	memset((void*)encrypto, 0, AES_BLOCK_SIZE * 3);
	memset((void*)decrypt, 0, AES_BLOCK_SIZE * 3);

	//���ü���key����Կ����
	//������AES�����Ǹ���S�н����ֽ��滻�ģ����ԭ�ĺ����ĸ��ֽ�һһ��Ӧ��С��ͬ
	AES_set_encrypt_key((const unsigned char*)userKey, AES_BLOCK_SIZE * 8, &key);

	int len = 0;
	//ѭ�����ܣ� ÿ�μ��ܳ�����AES_BLOCK_SIZE���ȵ�����
	while (len < AES_BLOCK_SIZE * 3)
	{
		AES_encrypt(data + len, encrypto + len, &key);
		len += AES_BLOCK_SIZE;
	}

	//���ý���key����Կ����
	AES_set_decrypt_key((const unsigned char*)userKey, AES_BLOCK_SIZE * 8, &key);

	len = 0;
	//ѭ������
	//ÿ������16�ֽڣ����16�ֽڣ����������Ҫ���
	while (len < AES_BLOCK_SIZE * 3)
	{
		AES_decrypt(encrypto + len, decrypt + len, &key);
		len += AES_BLOCK_SIZE;
	}

	//���ܺ���Ԫ�����Ƿ�һ��
	if (memcmp(decrypt, data, AES_BLOCK_SIZE * 3) == 0)
	{
		printf("test success\n");
	}
	else
	{
		printf("test failed\n");
	}
}

int main()
{
	getMD5("hello, md5");
	getSHA1("���, ����");
	getHmac();
	AES();
	system("pause");
	return 0;
}