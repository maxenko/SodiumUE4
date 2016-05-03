#pragma once

//#include "Kismet/BlueprintFunctionLibrary.h"
#include "Engine.h"
#include "SodiumUE4BlueprintInterface.generated.h"

UCLASS()
class USodiumUE4PluginBPLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_UCLASS_BODY()

public:

	UFUNCTION(BlueprintCallable, Category = "Sodium|Utility")
	static bool SodiumTest();

};