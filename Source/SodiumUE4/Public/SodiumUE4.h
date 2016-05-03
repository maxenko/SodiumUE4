// Copyright 1998-2016 Epic Games, Inc. All Rights Reserved.

#pragma once

#include "ModuleManager.h"
#include <string>
#include <vector>

using namespace std;

class FSodiumUE4Module : public IModuleInterface
{
public:

	////////////////////////////
	// IModuleInterface implementation
	////////////////////////////

	virtual void StartupModule() override;
	virtual void ShutdownModule() override;

	void GenerateKeyPair(vector<unsigned char> &pk, vector<unsigned char> &sk);

	static inline FSodiumUE4Module& Get(){
		return FModuleManager::LoadModuleChecked<FSodiumUE4Module>("SodiumUE4"); // name should be the same as directory of the plugin in /Plugins
	}

	static inline bool IsAvailable() {
		return FModuleManager::Get().IsModuleLoaded("SodiumUE4");
	}
	
private:
	/** Handle to the test dll we will load */
	void*	libsodiumUE4Handle;
};