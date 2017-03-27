// Copyright 1998-2016 Epic Games, Inc. All Rights Reserved.

//#include <vector>

#include "SodiumUE4PrivatePCH.h"
#include "Core.h"
#include "ModuleManager.h"
#include "Interfaces/IPluginManager.h"
#include "../ThirdParty/libsodium/src/libsodium/include/sodium.h"

#if PLATFORM_WINDOWS
//#include "../../ThirdParty/SodiumUE4Library/SodiumUE4.h"
#endif // PLATFORM_WINDOWS

#define LOCTEXT_NAMESPACE "FSodiumUE4Module"

void FSodiumUE4Module::StartupModule()
{
	sodium_init();
}

void FSodiumUE4Module::ShutdownModule()
{
}

//////////////////////////////////////////////////////////////////////////
// Sodium API
//////////////////////////////////////////////////////////////////////////

int FSodiumUE4Module::GetPublicKeyBytes() {
	//return SodiumGetPublicKeyBytes();
	return crypto_box_PUBLICKEYBYTES;
}

int FSodiumUE4Module::GetSecretKeyBytes() {
	return crypto_box_SECRETKEYBYTES;
	//return SodiumGetSecretKeyBytes();
}

int FSodiumUE4Module::GetBoxSealBytes() {
	return crypto_box_SEALBYTES;
	//return SodiumGetBoxSealBytes();
}

int FSodiumUE4Module::GetNonceBytes() {
	return crypto_box_NONCEBYTES;
	//return SodiumGetNonceBytes();
}

int FSodiumUE4Module::GetMacBytes() {
	return crypto_box_MACBYTES;
	//return SodiumGetMacBytes();
}

void FSodiumUE4Module::GenerateKeyPair(TArray<uint8>& publicKey, TArray<uint8>& secretKey) {
	auto sodium = FSodiumUE4Module::Get();

	// allocate space for key
	publicKey.SetNum(sodium.GetPublicKeyBytes());
	secretKey.SetNum(sodium.GetSecretKeyBytes());

	// generate key
	//SodiumGenerateKeyPair(publicKey.GetData(), secretKey.GetData());
	crypto_box_keypair(publicKey.GetData(), secretKey.GetData());
}

void FSodiumUE4Module::RandomBytes(unsigned char* bytes, size_t len) {
	//SodiumRandomBytes(bytes, len);
	randombytes_buf(bytes, len);
}

int FSodiumUE4Module::Encrypt(TArray<uint8>& encrypted, TArray<uint8>& data, TArray<uint8>& publicKey) {
	encrypted.SetNum(data.Num() + this->GetBoxSealBytes());
	//return SodiumEncrypt(encrypted.GetData(), data.GetData(), data.Num(), publicKey.GetData());
	return crypto_box_seal(encrypted.GetData(), data.GetData(), data.Num(), publicKey.GetData());
}

int FSodiumUE4Module::Decrypt(TArray<uint8>& decrypted, TArray<uint8>& encrypted, TArray<uint8>& publicKey, TArray<uint8>& privateKey) {
	decrypted.SetNum(encrypted.Num() - this->GetBoxSealBytes());
	//return SodiumDecrypt(decrypted.GetData(), encrypted.GetData(), encrypted.Num(), publicKey.GetData(), privateKey.GetData());
	return crypto_box_seal_open(decrypted.GetData(), encrypted.GetData(), encrypted.Num(), publicKey.GetData(), privateKey.GetData());

}

int FSodiumUE4Module::EncryptAuthenticated(TArray<uint8>& encrypted, TArray<uint8>& data, TArray<uint8>& nonce, TArray<uint8>& publicKey, TArray<uint8>& privateKey) {
	encrypted.SetNum(data.Num() + this->GetMacBytes());
	//return SodiumEncryptAuth(encrypted.GetData(), data.GetData(), data.Num(), nonce.GetData(), publicKey.GetData(), privateKey.GetData());
	return crypto_box_easy(encrypted.GetData(), data.GetData(), data.Num(), nonce.GetData(), publicKey.GetData(), privateKey.GetData());

}

int FSodiumUE4Module::DecryptAuthenticated(TArray<uint8>& decrypted, TArray<uint8>& encrypted, TArray<uint8>& nonce, TArray<uint8>& publicKey, TArray<uint8>& privateKey) {
	decrypted.SetNum(encrypted.Num() - this->GetMacBytes());
	//return SodiumDecryptAuth(decrypted.GetData(), encrypted.GetData(), encrypted.Num(), nonce.GetData(), publicKey.GetData(), privateKey.GetData());
	return crypto_box_open_easy(decrypted.GetData(), encrypted.GetData(), encrypted.Num(), nonce.GetData(), publicKey.GetData(), privateKey.GetData());

}

#undef LOCTEXT_NAMESPACE

IMPLEMENT_MODULE(FSodiumUE4Module, SodiumUE4)
