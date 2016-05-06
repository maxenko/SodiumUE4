#include "SodiumUE4PrivatePCH.h"
#include "../Public/SodiumUE4BlueprintInterface.h"
#include "SodiumUE4.h"
#include <vector>
#include <string>

using namespace std;

USodiumUE4PluginBPLibrary::USodiumUE4PluginBPLibrary(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{

}

bool USodiumUE4PluginBPLibrary::SodiumTest() {
	return FSodiumUE4Module::Get().Test();
}

TArray<uint8> USodiumUE4PluginBPLibrary::RandomBytes(int32 len){
	vector<unsigned char> _bytes(len);
	FSodiumUE4Module::Get().RandomBytes(_bytes.data(), len);

	TArray<uint8> ret;
	ret.Empty();
	ret.Append(_bytes.data(), _bytes.size());

	return ret;
}

void USodiumUE4PluginBPLibrary::GenerateKeyPair(TArray<uint8>& publicKey, TArray<uint8>& secretKey) {
	
	auto sodium = FSodiumUE4Module::Get();
	
	auto pk_len = sodium.GetPublicKeyBytes();
	auto sk_len = sodium.GetPublicKeyBytes();

	vector<unsigned char> _pk(pk_len);
	vector<unsigned char> _sk(sk_len);

	// generate key
	sodium.GenerateKeyPair(_pk.data(), _sk.data());

	publicKey.Empty();
	publicKey.Append(_pk.data(), pk_len);

	secretKey.Empty();
	secretKey.Append(_sk.data(), sk_len);

}

void USodiumUE4PluginBPLibrary::EncryptString(FString s, TArray<uint8> publicKey, TArray<uint8>& encrypted) {

	auto sodium = FSodiumUE4Module::Get();

	string str(TCHAR_TO_UTF8(*s));
	vector<unsigned char> encryptedContainer(str.size() + sodium.GetBoxSealBytes());
	vector<unsigned char> data(str.begin(), str.end());

	auto msg = sodium.Encrypt(encryptedContainer, data.data(), data.size(), publicKey.GetData());

	if (msg > -1) {
		encrypted.Append(encryptedContainer.data(), encryptedContainer.size());
	}
}

void USodiumUE4PluginBPLibrary::DecryptString(TArray<uint8> encrypted, TArray<uint8> publicKey, TArray<uint8> privateKey, FString& decrypted) {

	auto sodium = FSodiumUE4Module::Get();

	auto decryptedContainerSize = encrypted.Num() - sodium.GetBoxSealBytes();
	vector<unsigned char> decryptedContainer(decryptedContainerSize+1); // +1 for null terminator we add manually

	auto msg = sodium.Decrypt(encrypted.GetData(), encrypted.Num(), decryptedContainer, publicKey.GetData(), privateKey.GetData());
	
	decryptedContainer[decryptedContainerSize] = 0; // null terminate the string

	if(msg > -1){
		decrypted = FString(UTF8_TO_TCHAR(decryptedContainer.data()));
	}
}