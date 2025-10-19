// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "Projekt_UnrealGameMode.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS

void EmptyLinkFunctionForGeneratedCodeProjekt_UnrealGameMode() {}

// ********** Begin Cross Module References ********************************************************
ENGINE_API UClass* Z_Construct_UClass_AGameModeBase();
PROJEKT_UNREAL_API UClass* Z_Construct_UClass_AProjekt_UnrealGameMode();
PROJEKT_UNREAL_API UClass* Z_Construct_UClass_AProjekt_UnrealGameMode_NoRegister();
UPackage* Z_Construct_UPackage__Script_Projekt_Unreal();
// ********** End Cross Module References **********************************************************

// ********** Begin Class AProjekt_UnrealGameMode **************************************************
void AProjekt_UnrealGameMode::StaticRegisterNativesAProjekt_UnrealGameMode()
{
}
FClassRegistrationInfo Z_Registration_Info_UClass_AProjekt_UnrealGameMode;
UClass* AProjekt_UnrealGameMode::GetPrivateStaticClass()
{
	using TClass = AProjekt_UnrealGameMode;
	if (!Z_Registration_Info_UClass_AProjekt_UnrealGameMode.InnerSingleton)
	{
		GetPrivateStaticClassBody(
			StaticPackage(),
			TEXT("Projekt_UnrealGameMode"),
			Z_Registration_Info_UClass_AProjekt_UnrealGameMode.InnerSingleton,
			StaticRegisterNativesAProjekt_UnrealGameMode,
			sizeof(TClass),
			alignof(TClass),
			TClass::StaticClassFlags,
			TClass::StaticClassCastFlags(),
			TClass::StaticConfigName(),
			(UClass::ClassConstructorType)InternalConstructor<TClass>,
			(UClass::ClassVTableHelperCtorCallerType)InternalVTableHelperCtorCaller<TClass>,
			UOBJECT_CPPCLASS_STATICFUNCTIONS_FORCLASS(TClass),
			&TClass::Super::StaticClass,
			&TClass::WithinClass::StaticClass
		);
	}
	return Z_Registration_Info_UClass_AProjekt_UnrealGameMode.InnerSingleton;
}
UClass* Z_Construct_UClass_AProjekt_UnrealGameMode_NoRegister()
{
	return AProjekt_UnrealGameMode::GetPrivateStaticClass();
}
struct Z_Construct_UClass_AProjekt_UnrealGameMode_Statics
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Class_MetaDataParams[] = {
#if !UE_BUILD_SHIPPING
		{ "Comment", "/**\n *  Simple GameMode for a third person game\n */" },
#endif
		{ "HideCategories", "Info Rendering MovementReplication Replication Actor Input Movement Collision Rendering HLOD WorldPartition DataLayers Transformation" },
		{ "IncludePath", "Projekt_UnrealGameMode.h" },
		{ "ModuleRelativePath", "Projekt_UnrealGameMode.h" },
		{ "ShowCategories", "Input|MouseInput Input|TouchInput" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Simple GameMode for a third person game" },
#endif
	};
#endif // WITH_METADATA
	static UObject* (*const DependentSingletons[])();
	static constexpr FCppClassTypeInfoStatic StaticCppClassTypeInfo = {
		TCppClassTypeTraits<AProjekt_UnrealGameMode>::IsAbstract,
	};
	static const UECodeGen_Private::FClassParams ClassParams;
};
UObject* (*const Z_Construct_UClass_AProjekt_UnrealGameMode_Statics::DependentSingletons[])() = {
	(UObject* (*)())Z_Construct_UClass_AGameModeBase,
	(UObject* (*)())Z_Construct_UPackage__Script_Projekt_Unreal,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_AProjekt_UnrealGameMode_Statics::DependentSingletons) < 16);
const UECodeGen_Private::FClassParams Z_Construct_UClass_AProjekt_UnrealGameMode_Statics::ClassParams = {
	&AProjekt_UnrealGameMode::StaticClass,
	"Game",
	&StaticCppClassTypeInfo,
	DependentSingletons,
	nullptr,
	nullptr,
	nullptr,
	UE_ARRAY_COUNT(DependentSingletons),
	0,
	0,
	0,
	0x008003ADu,
	METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UClass_AProjekt_UnrealGameMode_Statics::Class_MetaDataParams), Z_Construct_UClass_AProjekt_UnrealGameMode_Statics::Class_MetaDataParams)
};
UClass* Z_Construct_UClass_AProjekt_UnrealGameMode()
{
	if (!Z_Registration_Info_UClass_AProjekt_UnrealGameMode.OuterSingleton)
	{
		UECodeGen_Private::ConstructUClass(Z_Registration_Info_UClass_AProjekt_UnrealGameMode.OuterSingleton, Z_Construct_UClass_AProjekt_UnrealGameMode_Statics::ClassParams);
	}
	return Z_Registration_Info_UClass_AProjekt_UnrealGameMode.OuterSingleton;
}
DEFINE_VTABLE_PTR_HELPER_CTOR(AProjekt_UnrealGameMode);
AProjekt_UnrealGameMode::~AProjekt_UnrealGameMode() {}
// ********** End Class AProjekt_UnrealGameMode ****************************************************

// ********** Begin Registration *******************************************************************
struct Z_CompiledInDeferFile_FID_Projekt_Unreal_Source_Projekt_Unreal_Projekt_UnrealGameMode_h__Script_Projekt_Unreal_Statics
{
	static constexpr FClassRegisterCompiledInInfo ClassInfo[] = {
		{ Z_Construct_UClass_AProjekt_UnrealGameMode, AProjekt_UnrealGameMode::StaticClass, TEXT("AProjekt_UnrealGameMode"), &Z_Registration_Info_UClass_AProjekt_UnrealGameMode, CONSTRUCT_RELOAD_VERSION_INFO(FClassReloadVersionInfo, sizeof(AProjekt_UnrealGameMode), 3169452975U) },
	};
};
static FRegisterCompiledInInfo Z_CompiledInDeferFile_FID_Projekt_Unreal_Source_Projekt_Unreal_Projekt_UnrealGameMode_h__Script_Projekt_Unreal_1843648929(TEXT("/Script/Projekt_Unreal"),
	Z_CompiledInDeferFile_FID_Projekt_Unreal_Source_Projekt_Unreal_Projekt_UnrealGameMode_h__Script_Projekt_Unreal_Statics::ClassInfo, UE_ARRAY_COUNT(Z_CompiledInDeferFile_FID_Projekt_Unreal_Source_Projekt_Unreal_Projekt_UnrealGameMode_h__Script_Projekt_Unreal_Statics::ClassInfo),
	nullptr, 0,
	nullptr, 0);
// ********** End Registration *********************************************************************

PRAGMA_ENABLE_DEPRECATION_WARNINGS
