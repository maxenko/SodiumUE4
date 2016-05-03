#include <Windows.h>
#include <sodium.h>

#include <vector>

using namespace std;

__declspec(dllexport) int LoadSodium(){
	return sodium_init();
}


__declspec(dllexport) int SodiumGenerateKeyPairVec(vector<unsigned char> &pk, vector<unsigned char> &sk) {
	pk.resize(crypto_box_PUBLICKEYBYTES);
	sk.resize(crypto_box_SECRETKEYBYTES);
	return crypto_box_keypair(pk.data(), sk.data());
}

__declspec(dllexport) int SodiumGenerateKeyPair(unsigned char *pk, unsigned char *sk) {
	return crypto_box_keypair(pk, sk);
}

__declspec(dllexport) string SodiumEncryptString(string str, vector<unsigned char> &pk) {

	vector<unsigned char> ciphed(str.size() + crypto_box_SEALBYTES);
	auto msg = crypto_box_seal(ciphed.data(), (unsigned char*)str.data(), str.size(), pk.data());

	if (msg != 0) {
		return "";
	}
	else {
		string ret(ciphed.begin(), ciphed.end());
		return ret;
	}
}

__declspec(dllexport) string SodiumDecryptString(string str, vector<unsigned char> &pk, vector<unsigned char> &sk) {
	vector<unsigned char> deciphed(str.size() - crypto_box_SEALBYTES);
	auto msg = crypto_box_seal_open(deciphed.data(), (unsigned char*)str.data(), str.size(), pk.data(), sk.data());
	if (msg != 0) {
		return "";
	}
	else {
		string ret(deciphed.begin(), deciphed.end());
		return ret;
	}
}

__declspec(dllexport) bool SodiumTest() {

	vector<unsigned char> pk_test(0);
	vector<unsigned char> sk_test(0);
	auto msgKeys = SodiumGenerateKeyPairVec(pk_test, sk_test);

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

	string toEncrypt = "I am a unique snowflake.";
	string encrypted = SodiumEncryptString(toEncrypt, pk_test);

	bool stringEncryptDecryptPass = (toEncrypt.compare(SodiumDecryptString(encrypted, pk_test, sk_test)) == 0);

	return randomBytesPass && stringEncryptDecryptPass;
}