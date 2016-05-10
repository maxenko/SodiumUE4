#include "SodiumUE4PrivatePCH.h"
#include "../Public/SodiumUE4BlueprintInterface.h"
#include "SodiumUE4.h"
#include "Base64.h"

USodiumUE4PluginBPLibrary::USodiumUE4PluginBPLibrary(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{

}

bool USodiumUE4PluginBPLibrary::SodiumTest() {
	return FSodiumUE4Module::Get().Test();
}

TArray<uint8> USodiumUE4PluginBPLibrary::RandomBytes(int32 len){
	TArray<uint8> ret;
	ret.SetNum(len);
	FSodiumUE4Module::Get().RandomBytes(ret.GetData(), len);
	return ret;
}

TArray<uint8> USodiumUE4PluginBPLibrary::Nonce() {
	return RandomBytes(FSodiumUE4Module::Get().GetMacBytes());
}

void USodiumUE4PluginBPLibrary::GenerateKeyPair(TArray<uint8>& publicKey, TArray<uint8>& privateKey) {
	auto sodium = FSodiumUE4Module::Get();
	sodium.GenerateKeyPair(publicKey, privateKey);
}

void USodiumUE4PluginBPLibrary::EncryptString(FString s, TArray<uint8> publicKey, TArray<uint8>& encrypted, bool& success) {

	auto sodium = FSodiumUE4Module::Get();

	TArray<uint8> data;
	std::string _s(TCHAR_TO_UTF8(*s));
	data.Append((unsigned char *)_s.data(), _s.size());
	encrypted.SetNum(_s.size() + sodium.GetBoxSealBytes());

	auto msg = sodium.Encrypt(encrypted, data, publicKey);

	if (msg == -1) {
		encrypted.Empty();
		success = false;
	} else {
		success = true;
	}
}

void USodiumUE4PluginBPLibrary::DecryptString(TArray<uint8> encrypted, TArray<uint8> publicKey, TArray<uint8> privateKey, FString& decrypted, bool& success) {

	auto sodium = FSodiumUE4Module::Get();

	auto decryptedContainerSize = encrypted.Num() - sodium.GetBoxSealBytes();

	TArray<uint8> _decrypted;

	// preemptively terminate the string
	_decrypted.SetNum(decryptedContainerSize+1);
	_decrypted[decryptedContainerSize] = 0; 

	auto msg = sodium.Decrypt(_decrypted, encrypted, publicKey, privateKey);
	
	if(msg == -1){
		success = false;
	} else {
		decrypted = FString(UTF8_TO_TCHAR(_decrypted.GetData()));
		success = true;
	}
}

FString USodiumUE4PluginBPLibrary::ToBase64(TArray<uint8> data) {
	return FBase64::Encode(data);
}

FString USodiumUE4PluginBPLibrary::ToBase64S(FString data) {
	return FBase64::Encode(data);
}

TArray<uint8> USodiumUE4PluginBPLibrary::FromBase64(FString data, bool& success) {
	TArray<uint8> dest;
	success = FBase64::Decode(data, dest);
	return dest;
}

FString USodiumUE4PluginBPLibrary::FromBase64S(FString data, bool& success) {
	FString dest;
	success = FBase64::Decode(data, dest);
	return dest;
}

void USodiumUE4PluginBPLibrary::Encrypt(TArray<uint8> data, TArray<uint8> publicKey, TArray<uint8>& encrypted, bool& success) {
	auto sodium = FSodiumUE4Module::Get();
	success = sodium.Encrypt(encrypted, data, publicKey) == 0 ? true : false;
}

void USodiumUE4PluginBPLibrary::Decrypt(TArray<uint8> encrypted, TArray<uint8> publicKey, TArray<uint8> privateKey, TArray<uint8>& decrypted, bool& success) {
	auto sodium = FSodiumUE4Module::Get();
	success = sodium.Decrypt(decrypted, encrypted, publicKey, privateKey) == 0 ? true : false;
}

void USodiumUE4PluginBPLibrary::EncryptAuthenticated(TArray<uint8> data, TArray<uint8> publicKey, TArray<uint8> privateKey, TArray<uint8> nonce, TArray<uint8>& encrypted, bool& success) {
	auto sodium = FSodiumUE4Module::Get();
	success = sodium.EncryptAuthenticated(encrypted, data, nonce, publicKey, privateKey) == 0 ? true : false;
}

void USodiumUE4PluginBPLibrary::DecryptAuthenticated(TArray<uint8> encrypted, TArray<uint8> publicKey, TArray<uint8> privateKey, TArray<uint8> nonce, TArray<uint8>& decrypted, bool& success) {
	auto sodium = FSodiumUE4Module::Get();
	success = sodium.DecryptAuthenticated(decrypted, encrypted, nonce, publicKey, privateKey) == 0 ? true : false;
}