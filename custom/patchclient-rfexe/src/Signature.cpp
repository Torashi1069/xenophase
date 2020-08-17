#include "Signature.h"
#include <openssl/bio.h>
#include <openssl/evp.h>
#include <openssl/pem.h>


bool Signature::Sign(const char* pem_privkey, const std::vector<char>& data, std::vector<char>& out_signature)
{
	BIO* bio = BIO_new_mem_buf(const_cast<char*>(pem_privkey), strlen(pem_privkey));
	if( bio == NULL )
		return false;

	EVP_PKEY* key = PEM_read_bio_PrivateKey(bio, NULL, NULL, NULL);
	BIO_free(bio);
	if( key == NULL )
		return false;

	EVP_MD_CTX ctx;
	EVP_MD_CTX_init(&ctx);

	EVP_DigestSignInit(&ctx, NULL, EVP_sha1(), NULL, key);

	EVP_DigestSignUpdate(&ctx, &data.front(), data.size());

	unsigned int s = 0;
	EVP_DigestSignFinal(&ctx, NULL, &s);

	out_signature.resize(s);
	EVP_DigestSignFinal(&ctx, (unsigned char*)&out_signature.front(), &s);
	out_signature.resize(s);

	EVP_MD_CTX_cleanup(&ctx);
	EVP_PKEY_free(key);
	return true;
}


bool Signature::Verify(const char* pem_pubkey, const std::vector<char>& data, const std::vector<char>& signature)
{
	BIO* bio = BIO_new_mem_buf(const_cast<char*>(pem_pubkey), strlen(pem_pubkey));
	if( bio == NULL )
		return false;

	EVP_PKEY* key = PEM_read_bio_PUBKEY(bio, NULL, NULL, NULL);
	BIO_free(bio);
	if( key == NULL )
		return false;

	EVP_MD_CTX ctx;
	EVP_MD_CTX_init(&ctx);

	EVP_DigestVerifyInit(&ctx, NULL, EVP_sha1(), NULL, key);
	EVP_DigestVerifyUpdate(&ctx, &data.front(), data.size());
	int result = EVP_DigestVerifyFinal(&ctx, (unsigned char*)&signature.front(), signature.size());

	EVP_MD_CTX_cleanup(&ctx);
	EVP_PKEY_free(key);

	if( result == 1 )
		return true; // correct
	else
	if( result == 0 )
		return false; // wrong
	else
	if( result == -1 )
		return false; // error

	return false; // ???
}
