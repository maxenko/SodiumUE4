#include <Windows.h>
#include <sodium.h>

#include <vector>

using namespace std;

__declspec(dllexport) int LoadSodium(){
	return sodium_init();
}

__declspec(dllexport) void SodiumRandomBytes(unsigned char *bytes, size_t len) {
	randombytes_buf(bytes, len);
}

__declspec(dllexport) int SodiumGetPublicKeyBytes() {
	return crypto_box_PUBLICKEYBYTES;
}

__declspec(dllexport) int SodiumGetSecretKeyBytes() {
	return crypto_box_SECRETKEYBYTES;
}

__declspec(dllexport) int SodiumGetBoxSealBytes() {
	return crypto_box_SEALBYTES;
}

__declspec(dllexport) int SodiumGetNonceBytes() {
	return crypto_box_NONCEBYTES;
}

__declspec(dllexport) int SodiumGetMacBytes() {
	return crypto_box_MACBYTES;
}

__declspec(dllexport) int SodiumGenerateKeyPair(unsigned char *pk, unsigned char *sk) {
	return crypto_box_keypair(pk, sk);
}

__declspec(dllexport) int SodiumEncrypt(unsigned char *to, unsigned char *data, size_t data_len, unsigned char *pk) {
	return crypto_box_seal(to, data, data_len, pk);
}

__declspec(dllexport) int SodiumDecrypt(unsigned char *decrypted, unsigned char *encrypted, size_t len, unsigned char *pk, unsigned char *sk) {
	return crypto_box_seal_open(decrypted, encrypted, len, pk, sk);
}

__declspec(dllexport) int SodiumEncryptAuth(unsigned char *to, unsigned char *data, size_t data_len, unsigned char *nonce, unsigned char *pk, unsigned char *sk) {
	return crypto_box_easy(to, data, data_len, nonce, pk, sk);
}

__declspec(dllexport) int SodiumDecryptAuth(unsigned char *decrypted, unsigned char *encrypted, size_t len, unsigned char *nonce, unsigned char *pk, unsigned char *sk) {
	return crypto_box_open_easy(decrypted, encrypted, len, nonce, pk, sk);
}

__declspec(dllexport) bool SodiumTest() {

	vector<unsigned char> pk_test(crypto_box_PUBLICKEYBYTES);
	vector<unsigned char> sk_test(crypto_box_SECRETKEYBYTES);
	auto msgKeys = SodiumGenerateKeyPair(pk_test.data(), sk_test.data());

	// generate random data
	vector<unsigned char> nonce(512);
	randombytes_buf(nonce.data(), nonce.size());

	// encrypt random data
	vector<unsigned char> ciphed(crypto_box_SEALBYTES + nonce.size());
	auto msgEncrypted = crypto_box_seal(ciphed.data(), nonce.data(), nonce.size(), pk_test.data());

	// decrypt
	vector<unsigned char> deciphed(ciphed.size() - crypto_box_SEALBYTES);
	auto msgDecrypted = crypto_box_seal_open(deciphed.data(), ciphed.data(), ciphed.size(), pk_test.data(), sk_test.data());

	auto isEqual = deciphed == nonce;

	bool randomBytesPass = msgKeys == msgEncrypted == msgDecrypted == 0 && isEqual;

	/*
	string toEncrypt = "I am a unique snowflake.";
	string encrypted = SodiumEncryptString(toEncrypt, pk_test);

	bool stringEncryptDecryptPass = (toEncrypt.compare(SodiumDecryptString(encrypted, pk_test, sk_test)) == 0);
	*/

	return randomBytesPass;
}