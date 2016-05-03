#include <vector>

// import directive

using namespace std;

__declspec(dllimport) int LoadSodium();
__declspec(dllimport) int SodiumGenerateKeyPair(unsigned char *pk, unsigned char *sk);
__declspec(dllimport) string SodiumEncryptString(string str, vector<unsigned char> &pk);
__declspec(dllimport) string SodiumDecryptString(string str, vector<unsigned char> &pk, vector<unsigned char> &sk);

__declspec(dllimport) bool SodiumTest();