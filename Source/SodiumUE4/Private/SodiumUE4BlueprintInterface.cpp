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