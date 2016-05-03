#include "SodiumUE4PrivatePCH.h"
#include "../Public/SodiumUE4BlueprintInterface.h"
#include "SodiumUE4.h"

USodiumUE4PluginBPLibrary::USodiumUE4PluginBPLibrary(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{

}

bool USodiumUE4PluginBPLibrary::SodiumTest() {
	return FSodiumUE4Module::Get().Test();
}

TArray<uint8> USodiumUE4PluginBPLibrary::RandomBytes(int len){
	return TArray <uint8>();
}

void USodiumUE4PluginBPLibrary::GenerateKeyPair(TArray<uint8>& publicKey, TArray<uint8>& secretKey) {
	
	// generate key
	unsigned char pk[32U];
	unsigned char sk[32U];
	
	auto module = FSodiumUE4Module::Get();

	module.Test();
	module.GenerateKeyPair(pk, sk);



	publicKey.Empty();
	publicKey.Append(pk, 32U);

	secretKey.Empty();
	secretKey.Append(sk, 32U);

	/*
	for (unsigned char c : pk) {
		//publicKey.Add(1);
	}
	
	for (unsigned char c : sk) {
		//secretKey.Add(2);
	}
	*/
	return;
}
