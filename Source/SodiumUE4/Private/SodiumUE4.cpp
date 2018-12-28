// Copyright 1998-2016 Epic Games, Inc. All Rights Reserved.

//#include <vector>

#include "SodiumUE4PrivatePCH.h"
#include "Core.h"
#include "ModuleManager.h"
#include "Interfaces/IPluginManager.h"


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

void FSodiumUE4Module::GenerateKeyPair(TArray<uint8>& publicKey, TArray<uint8>& secretKey) {
	auto sodium = FSodiumUE4Module::Get();

	// allocate space for key
	publicKey.SetNum(sodium.GetPublicKeyBytes());
	secretKey.SetNum(sodium.GetSecretKeyBytes());

	// generate key
	crypto_box_keypair(publicKey.GetData(), secretKey.GetData());
}

void FSodiumUE4Module::RandomBytes(unsigned char* bytes, size_t len) {
	randombytes_buf(bytes, len);
}

//////////////////////////////////////////////////////////////////////////
// Asymmetric
//////////////////////////////////////////////////////////////////////////

int FSodiumUE4Module::Encrypt(TArray<uint8>& encrypted, TArray<uint8>& data, TArray<uint8>& publicKey) {
	encrypted.SetNum(data.Num() + crypto_box_SEALBYTES);
	return crypto_box_seal(encrypted.GetData(), data.GetData(), data.Num(), publicKey.GetData());
}

int FSodiumUE4Module::Decrypt(TArray<uint8>& decrypted, TArray<uint8>& encrypted, TArray<uint8>& publicKey, TArray<uint8>& privateKey) {
	decrypted.SetNum(encrypted.Num() - crypto_box_SEALBYTES);
	return crypto_box_seal_open(decrypted.GetData(), encrypted.GetData(), encrypted.Num(), publicKey.GetData(), privateKey.GetData());
}

int FSodiumUE4Module::EncryptAuthenticated(TArray<uint8>& encrypted, TArray<uint8>& data, TArray<uint8>& nonce, TArray<uint8>& publicKey, TArray<uint8>& privateKey) {
	encrypted.SetNum(data.Num() + crypto_box_MACBYTES);
	return crypto_box_easy(encrypted.GetData(), data.GetData(), data.Num(), nonce.GetData(), publicKey.GetData(), privateKey.GetData());
}

int FSodiumUE4Module::DecryptAuthenticated(TArray<uint8>& decrypted, TArray<uint8>& encrypted, TArray<uint8>& nonce, TArray<uint8>& publicKey, TArray<uint8>& privateKey) {
	decrypted.SetNum(encrypted.Num() - crypto_box_MACBYTES);
	return crypto_box_open_easy(decrypted.GetData(), encrypted.GetData(), encrypted.Num(), nonce.GetData(), publicKey.GetData(), privateKey.GetData());
}

//////////////////////////////////////////////////////////////////////////
// Symmetric
//////////////////////////////////////////////////////////////////////////

TArray<uint8> FSodiumUE4Module::GenerateKey() {
	TArray<uint8> key;
	key.SetNum(crypto_secretbox_KEYBYTES);
	crypto_secretbox_keygen(key.GetData());
	return key;
}

int FSodiumUE4Module::EncryptSymmetric(TArray<uint8>& encrypted, TArray<uint8>& data, TArray<uint8>& nonce, TArray<uint8>& key) {
	encrypted.SetNum(data.Num() + crypto_secretbox_MACBYTES);
	return crypto_secretbox_easy(encrypted.GetData(), data.GetData(), data.Num(), nonce.GetData(), key.GetData());
}

int FSodiumUE4Module::DecryptSymmetric(TArray<uint8>& decrypted, TArray<uint8>& encrypted, TArray<uint8>& nonce, TArray<uint8>& key) {
	decrypted.SetNum(decrypted.Num() - crypto_secretbox_MACBYTES);
	return crypto_secretbox_open_easy(decrypted.GetData(), encrypted.GetData(), encrypted.Num(), nonce.GetData(), key.GetData());
}

#undef LOCTEXT_NAMESPACE

IMPLEMENT_MODULE(FSodiumUE4Module, SodiumUE4)
