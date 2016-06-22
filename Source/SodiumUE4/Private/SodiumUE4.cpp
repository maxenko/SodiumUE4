// Copyright 1998-2016 Epic Games, Inc. All Rights Reserved.

#include "SodiumUE4PrivatePCH.h"
#include "Core.h"
#include "ModuleManager.h"
#include "IPluginManager.h"

#if PLATFORM_WINDOWS
    #include "../../ThirdParty/SodiumUE4Library/SodiumUE4.h"
#endif // PLATFORM_WINDOWS

#define LOCTEXT_NAMESPACE "FSodiumUE4Module"

void FSodiumUE4Module::StartupModule()
{
	// This code will execute after your module is loaded into memory; the exact timing is specified in the .uplugin file per-module

	// Get the base directory of this plugin
	FString BaseDir = IPluginManager::Get().FindPlugin("SodiumUE4")->GetBaseDir();

	// Add on the relative location of the third party dll and load it
	FString LibraryPath;
#if PLATFORM_WINDOWS
	// LibraryPath = FPaths::Combine(*BaseDir, TEXT("Binaries/ThirdParty/SodiumUE4Library/Win64/libsodiumUE4.dll"));
	LibraryPath = FPaths::Combine(*BaseDir, TEXT("Source/ThirdParty/SodiumUE4Library/x64/Release/libsodiumUE4.dll"));

	libsodiumUE4Handle = !LibraryPath.IsEmpty() ? FPlatformProcess::GetDllHandle(*LibraryPath) : nullptr;

	if (libsodiumUE4Handle)
	{
		// load sodium
		int loadMsg = LoadSodium();
		if (loadMsg < 0) {
			UE_LOG(LogInit, Warning, TEXT("Sodium library failed to load."));
		} else {
			UE_LOG(LogInit, Log, TEXT("Sodium dll library successfully loaded."));

			bool sodiumTestPassed = SodiumTest();
			if(sodiumTestPassed){
				UE_LOG(LogInit, Log, TEXT("Sodium dll library test pass status: passed."));
			}else{
				UE_LOG(LogInit, Warning, TEXT("Sodium dll library test pass status: failed."));
			}
			
			// check if module is loaded into UE
			if (FSodiumUE4Module::IsAvailable()) {
				UE_LOG(LogInit, Log, TEXT("Sodium plugin successfully loaded."));
			} else {
				UE_LOG(LogInit, Warning, TEXT("Sodium plugin failed to load."));
			}
		}
	}
	else
#endif // PLATFORM_WINDOWS
	{
		FMessageDialog::Open(EAppMsgType::Ok, LOCTEXT("ThirdPartyLibraryError", "Failed to load sodium-ue4."));
	}
}

void FSodiumUE4Module::ShutdownModule()
{
	// This function may be called during shutdown to clean up your module.  For modules that support dynamic reloading,
	// we call this function before unloading the module.

	// Free the dll handle
	FPlatformProcess::FreeDllHandle(libsodiumUE4Handle);
	libsodiumUE4Handle = nullptr;
}

//////////////////////////////////////////////////////////////////////////
// Sodium API
//////////////////////////////////////////////////////////////////////////

int FSodiumUE4Module::GetPublicKeyBytes() {
	return SodiumGetPublicKeyBytes();
}

int FSodiumUE4Module::GetSecretKeyBytes() {
	return SodiumGetSecretKeyBytes();
}

int FSodiumUE4Module::GetBoxSealBytes() {
	return SodiumGetBoxSealBytes();
}

int FSodiumUE4Module::GetNonceBytes() {
	return SodiumGetNonceBytes();
}

int FSodiumUE4Module::GetMacBytes() {
	return SodiumGetMacBytes();
}

void FSodiumUE4Module::GenerateKeyPair(TArray<uint8>& publicKey, TArray<uint8>& secretKey) {
	auto sodium = FSodiumUE4Module::Get();

	// allocate space for key
	publicKey.SetNum(sodium.GetPublicKeyBytes());
	secretKey.SetNum(sodium.GetSecretKeyBytes());

	// generate key
	SodiumGenerateKeyPair(publicKey.GetData(), secretKey.GetData());
}

void FSodiumUE4Module::RandomBytes(unsigned char* bytes, size_t len) {
	SodiumRandomBytes(bytes, len);
}

int FSodiumUE4Module::Encrypt(TArray<uint8>& encrypted, TArray<uint8>& data, TArray<uint8>& publicKey) {
	encrypted.SetNum(data.Num() + this->GetBoxSealBytes());
	return SodiumEncrypt(encrypted.GetData(), data.GetData(), data.Num(), publicKey.GetData());
}

int FSodiumUE4Module::Decrypt(TArray<uint8>& decrypted, TArray<uint8>& encrypted, TArray<uint8>& publicKey, TArray<uint8>& privateKey) {
	decrypted.SetNum(encrypted.Num() - this->GetBoxSealBytes());
	return SodiumDecrypt(decrypted.GetData(), encrypted.GetData(), encrypted.Num(), publicKey.GetData(), privateKey.GetData());
}

int FSodiumUE4Module::EncryptAuthenticated(TArray<uint8>& encrypted, TArray<uint8>& data, TArray<uint8>& nonce, TArray<uint8>& publicKey, TArray<uint8>& privateKey) {
	encrypted.SetNum(data.Num() + this->GetMacBytes());
	return SodiumEncryptAuth(encrypted.GetData(), data.GetData(), data.Num(), nonce.GetData(), publicKey.GetData(), privateKey.GetData());
}

int FSodiumUE4Module::DecryptAuthenticated(TArray<uint8>& decrypted, TArray<uint8>& encrypted, TArray<uint8>& nonce, TArray<uint8>& publicKey, TArray<uint8>& privateKey) {
	decrypted.SetNum(encrypted.Num() - this->GetMacBytes());
	return SodiumDecryptAuth(decrypted.GetData(), encrypted.GetData(), encrypted.Num(), nonce.GetData(), publicKey.GetData(), privateKey.GetData());
}

bool FSodiumUE4Module::Test() {
	return SodiumTest();
}

#undef LOCTEXT_NAMESPACE
	
IMPLEMENT_MODULE(FSodiumUE4Module, SodiumUE4)
