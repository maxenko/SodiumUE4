#include <vector>

// import directive

using namespace std;

__declspec(dllimport) int LoadSodium();
__declspec(dllimport) int SodiumGetPublicKeyBytes();
__declspec(dllimport) int SodiumGetSecretKeyBytes();
__declspec(dllimport) int SodiumGetBoxSealBytes();
__declspec(dllimport) void SodiumRandomBytes(unsigned char *bytes, size_t len);
__declspec(dllimport) int SodiumGenerateKeyPair(unsigned char *pk, unsigned char *sk);
__declspec(dllimport) int SodiumEncrypt(unsigned char* to, unsigned char *data, size_t data_len, unsigned char *pk);
__declspec(dllimport) int SodiumDecrypt(unsigned char *encrypted, size_t len, unsigned char *decrypted, unsigned char *pk, unsigned char *sk);

__declspec(dllimport) bool SodiumTest();