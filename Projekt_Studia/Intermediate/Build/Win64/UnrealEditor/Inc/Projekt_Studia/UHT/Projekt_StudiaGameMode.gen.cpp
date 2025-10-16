// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "Projekt_Studia/Projekt_StudiaGameMode.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS

void EmptyLinkFunctionForGeneratedCodeProjekt_StudiaGameMode() {}

// ********** Begin Cross Module References ********************************************************
ENGINE_API UClass* Z_Construct_UClass_AGameModeBase();
PROJEKT_STUDIA_API UClass* Z_Construct_UClass_AProjekt_StudiaGameMode();
PROJEKT_STUDIA_API UClass* Z_Construct_UClass_AProjekt_StudiaGameMode_NoRegister();
UPackage* Z_Construct_UPackage__Script_Projekt_Studia();
// ********** End Cross Module References **********************************************************

// ********** Begin Class AProjekt_StudiaGameMode **************************************************
void AProjekt_StudiaGameMode::StaticRegisterNativesAProjekt_StudiaGameMode()
{
}
FClassRegistrationInfo Z_Registration_Info_UClass_AProjekt_StudiaGameMode;
UClass* AProjekt_StudiaGameMode::GetPrivateStaticClass()
{
	using TClass = AProjekt_StudiaGameMode;
	if (!Z_Registration_Info_UClass_AProjekt_StudiaGameMode.InnerSingleton)
	{
		GetPrivateStaticClassBody(
			StaticPackage(),
			TEXT("Projekt_StudiaGameMode"),
			Z_Registration_Info_UClass_AProjekt_StudiaGameMode.InnerSingleton,
			StaticRegisterNativesAProjekt_StudiaGameMode,
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
	return Z_Registration_Info_UClass_AProjekt_StudiaGameMode.InnerSingleton;
}
UClass* Z_Construct_UClass_AProjekt_StudiaGameMode_NoRegister()
{
	return AProjekt_StudiaGameMode::GetPrivateStaticClass();
}
struct Z_Construct_UClass_AProjekt_StudiaGameMode_Statics
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Class_MetaDataParams[] = {
#if !UE_BUILD_SHIPPING
		{ "Comment", "/**\n *  Simple GameMode for a third person game\n */" },
#endif
		{ "HideCategories", "Info Rendering MovementReplication Replication Actor Input Movement Collision Rendering HLOD WorldPartition DataLayers Transformation" },
		{ "IncludePath", "Projekt_StudiaGameMode.h" },
		{ "ModuleRelativePath", "Projekt_StudiaGameMode.h" },
		{ "ShowCategories", "Input|MouseInput Input|TouchInput" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Simple GameMode for a third person game" },
#endif
	};
#endif // WITH_METADATA
	static UObject* (*const DependentSingletons[])();
	static constexpr FCppClassTypeInfoStatic StaticCppClassTypeInfo = {
		TCppClassTypeTraits<AProjekt_StudiaGameMode>::IsAbstract,
	};
	static const UECodeGen_Private::FClassParams ClassParams;
};
UObject* (*const Z_Construct_UClass_AProjekt_StudiaGameMode_Statics::DependentSingletons[])() = {
	(UObject* (*)())Z_Construct_UClass_AGameModeBase,
	(UObject* (*)())Z_Construct_UPackage__Script_Projekt_Studia,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_AProjekt_StudiaGameMode_Statics::DependentSingletons) < 16);
const UECodeGen_Private::FClassParams Z_Construct_UClass_AProjekt_StudiaGameMode_Statics::ClassParams = {
	&AProjekt_StudiaGameMode::StaticClass,
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
	METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UClass_AProjekt_StudiaGameMode_Statics::Class_MetaDataParams), Z_Construct_UClass_AProjekt_StudiaGameMode_Statics::Class_MetaDataParams)
};
UClass* Z_Construct_UClass_AProjekt_StudiaGameMode()
{
	if (!Z_Registration_Info_UClass_AProjekt_StudiaGameMode.OuterSingleton)
	{
		UECodeGen_Private::ConstructUClass(Z_Registration_Info_UClass_AProjekt_StudiaGameMode.OuterSingleton, Z_Construct_UClass_AProjekt_StudiaGameMode_Statics::ClassParams);
	}
	return Z_Registration_Info_UClass_AProjekt_StudiaGameMode.OuterSingleton;
}
DEFINE_VTABLE_PTR_HELPER_CTOR(AProjekt_StudiaGameMode);
AProjekt_StudiaGameMode::~AProjekt_StudiaGameMode() {}
// ********** End Class AProjekt_StudiaGameMode ****************************************************

// ********** Begin Registration *******************************************************************
struct Z_CompiledInDeferFile_FID_Projekt_Studia_Source_Projekt_Studia_Projekt_StudiaGameMode_h__Script_Projekt_Studia_Statics
{
	static constexpr FClassRegisterCompiledInInfo ClassInfo[] = {
		{ Z_Construct_UClass_AProjekt_StudiaGameMode, AProjekt_StudiaGameMode::StaticClass, TEXT("AProjekt_StudiaGameMode"), &Z_Registration_Info_UClass_AProjekt_StudiaGameMode, CONSTRUCT_RELOAD_VERSION_INFO(FClassReloadVersionInfo, sizeof(AProjekt_StudiaGameMode), 1398805835U) },
	};
};
static FRegisterCompiledInInfo Z_CompiledInDeferFile_FID_Projekt_Studia_Source_Projekt_Studia_Projekt_StudiaGameMode_h__Script_Projekt_Studia_5890886(TEXT("/Script/Projekt_Studia"),
	Z_CompiledInDeferFile_FID_Projekt_Studia_Source_Projekt_Studia_Projekt_StudiaGameMode_h__Script_Projekt_Studia_Statics::ClassInfo, UE_ARRAY_COUNT(Z_CompiledInDeferFile_FID_Projekt_Studia_Source_Projekt_Studia_Projekt_StudiaGameMode_h__Script_Projekt_Studia_Statics::ClassInfo),
	nullptr, 0,
	nullptr, 0);
// ********** End Registration *********************************************************************

PRAGMA_ENABLE_DEPRECATION_WARNINGS
