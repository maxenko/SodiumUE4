#pragma once

#include "ModuleManager.h"
#include "../ThirdParty/libsodium/src/libsodium/include/sodium.h"

class FSodiumUE4Module : public IModuleInterface
{
public:

	////////////////////////////
	// IModuleInterface implementation
	////////////////////////////

	virtual void StartupModule() override;
	virtual void ShutdownModule() override;

	void GenerateKeyPair(TArray<uint8>& publicKey, TArray<uint8>& secretKey);
	TArray<uint8> GenerateKey();

	int GetPublicKeyBytes() { return crypto_box_PUBLICKEYBYTES; }
	int GetSecretKeyBytes() { return crypto_box_SECRETKEYBYTES; }
	int GetBoxSealBytes() { return crypto_box_SEALBYTES; }
	int GetMacBytes(){ return crypto_box_MACBYTES; }
	int GetMacBytesSymmetric() { return crypto_secretbox_MACBYTES; }

	int GetAssymetricNonceLen() { return crypto_box_NONCEBYTES; }
	int GetSymmetricNonceLen() { return crypto_secretbox_NONCEBYTES; }

	void RandomBytes(unsigned char* bytes, size_t len);

	int Encrypt(TArray<uint8>& encrypted, TArray<uint8>& data, TArray<uint8>& publicKey);
	int Decrypt(TArray<uint8>& decrypted, TArray<uint8>& encrypted, TArray<uint8>& publicKey, TArray<uint8>& privateKey);

	int EncryptAuthenticated(TArray<uint8>& encrypted, TArray<uint8>& data, TArray<uint8>& nonce, TArray<uint8>& publicKey, TArray<uint8>& privateKey);
	int DecryptAuthenticated(TArray<uint8>& decrypted, TArray<uint8>& encrypted, TArray<uint8>& nonce, TArray<uint8>& publicKey, TArray<uint8>& privateKey);


	int EncryptSymmetric(TArray<uint8>& encrypted, TArray<uint8>& data, TArray<uint8>& nonce, TArray<uint8>& key);
	int DecryptSymmetric(TArray<uint8>& decrypted, TArray<uint8>& encrypted, TArray<uint8>& nonce, TArray<uint8>& key);

	static inline FSodiumUE4Module& Get() {
		return FModuleManager::LoadModuleChecked<FSodiumUE4Module>("SodiumUE4"); // name should be the same as directory of the plugin in /Plugins
	}

	static inline bool IsAvailable() {
		return FModuleManager::Get().IsModuleLoaded("SodiumUE4");
	}

private:
	/** Handle to the test dll we will load */
	//void* libsodiumUE4Handle;
};