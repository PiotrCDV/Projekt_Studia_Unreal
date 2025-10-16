// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodeProjekt_Studia_init() {}
	PROJEKT_STUDIA_API UFunction* Z_Construct_UDelegateFunction_Projekt_Studia_OnEnemyDied__DelegateSignature();
	static FPackageRegistrationInfo Z_Registration_Info_UPackage__Script_Projekt_Studia;
	FORCENOINLINE UPackage* Z_Construct_UPackage__Script_Projekt_Studia()
	{
		if (!Z_Registration_Info_UPackage__Script_Projekt_Studia.OuterSingleton)
		{
			static UObject* (*const SingletonFuncArray[])() = {
				(UObject* (*)())Z_Construct_UDelegateFunction_Projekt_Studia_OnEnemyDied__DelegateSignature,
			};
			static const UECodeGen_Private::FPackageParams PackageParams = {
				"/Script/Projekt_Studia",
				SingletonFuncArray,
				UE_ARRAY_COUNT(SingletonFuncArray),
				PKG_CompiledIn | 0x00000000,
				0x50286B94,
				0x2A299347,
				METADATA_PARAMS(0, nullptr)
			};
			UECodeGen_Private::ConstructUPackage(Z_Registration_Info_UPackage__Script_Projekt_Studia.OuterSingleton, PackageParams);
		}
		return Z_Registration_Info_UPackage__Script_Projekt_Studia.OuterSingleton;
	}
	static FRegisterCompiledInInfo Z_CompiledInDeferPackage_UPackage__Script_Projekt_Studia(Z_Construct_UPackage__Script_Projekt_Studia, TEXT("/Script/Projekt_Studia"), Z_Registration_Info_UPackage__Script_Projekt_Studia, CONSTRUCT_RELOAD_VERSION_INFO(FPackageReloadVersionInfo, 0x50286B94, 0x2A299347));
PRAGMA_ENABLE_DEPRECATION_WARNINGS
