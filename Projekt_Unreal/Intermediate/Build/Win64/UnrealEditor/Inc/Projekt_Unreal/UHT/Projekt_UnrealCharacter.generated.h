// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

// IWYU pragma: private, include "Projekt_UnrealCharacter.h"

#ifdef PROJEKT_UNREAL_Projekt_UnrealCharacter_generated_h
#error "Projekt_UnrealCharacter.generated.h already included, missing '#pragma once' in Projekt_UnrealCharacter.h"
#endif
#define PROJEKT_UNREAL_Projekt_UnrealCharacter_generated_h

#include "UObject/ObjectMacros.h"
#include "UObject/ScriptMacros.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS

// ********** Begin Class AProjekt_UnrealCharacter *************************************************
#define FID_Projekt_Unreal_Source_Projekt_Unreal_Projekt_UnrealCharacter_h_24_RPC_WRAPPERS_NO_PURE_DECLS \
	DECLARE_FUNCTION(execDoJumpEnd); \
	DECLARE_FUNCTION(execDoJumpStart); \
	DECLARE_FUNCTION(execDoLook); \
	DECLARE_FUNCTION(execDoMove);


PROJEKT_UNREAL_API UClass* Z_Construct_UClass_AProjekt_UnrealCharacter_NoRegister();

#define FID_Projekt_Unreal_Source_Projekt_Unreal_Projekt_UnrealCharacter_h_24_INCLASS_NO_PURE_DECLS \
private: \
	static void StaticRegisterNativesAProjekt_UnrealCharacter(); \
	friend struct Z_Construct_UClass_AProjekt_UnrealCharacter_Statics; \
	static UClass* GetPrivateStaticClass(); \
	friend PROJEKT_UNREAL_API UClass* Z_Construct_UClass_AProjekt_UnrealCharacter_NoRegister(); \
public: \
	DECLARE_CLASS2(AProjekt_UnrealCharacter, ACharacter, COMPILED_IN_FLAGS(CLASS_Abstract | CLASS_Config), CASTCLASS_None, TEXT("/Script/Projekt_Unreal"), Z_Construct_UClass_AProjekt_UnrealCharacter_NoRegister) \
	DECLARE_SERIALIZER(AProjekt_UnrealCharacter)


#define FID_Projekt_Unreal_Source_Projekt_Unreal_Projekt_UnrealCharacter_h_24_ENHANCED_CONSTRUCTORS \
	/** Deleted move- and copy-constructors, should never be used */ \
	AProjekt_UnrealCharacter(AProjekt_UnrealCharacter&&) = delete; \
	AProjekt_UnrealCharacter(const AProjekt_UnrealCharacter&) = delete; \
	DECLARE_VTABLE_PTR_HELPER_CTOR(NO_API, AProjekt_UnrealCharacter); \
	DEFINE_VTABLE_PTR_HELPER_CTOR_CALLER(AProjekt_UnrealCharacter); \
	DEFINE_ABSTRACT_DEFAULT_CONSTRUCTOR_CALL(AProjekt_UnrealCharacter) \
	NO_API virtual ~AProjekt_UnrealCharacter();


#define FID_Projekt_Unreal_Source_Projekt_Unreal_Projekt_UnrealCharacter_h_21_PROLOG
#define FID_Projekt_Unreal_Source_Projekt_Unreal_Projekt_UnrealCharacter_h_24_GENERATED_BODY \
PRAGMA_DISABLE_DEPRECATION_WARNINGS \
public: \
	FID_Projekt_Unreal_Source_Projekt_Unreal_Projekt_UnrealCharacter_h_24_RPC_WRAPPERS_NO_PURE_DECLS \
	FID_Projekt_Unreal_Source_Projekt_Unreal_Projekt_UnrealCharacter_h_24_INCLASS_NO_PURE_DECLS \
	FID_Projekt_Unreal_Source_Projekt_Unreal_Projekt_UnrealCharacter_h_24_ENHANCED_CONSTRUCTORS \
private: \
PRAGMA_ENABLE_DEPRECATION_WARNINGS


class AProjekt_UnrealCharacter;

// ********** End Class AProjekt_UnrealCharacter ***************************************************

#undef CURRENT_FILE_ID
#define CURRENT_FILE_ID FID_Projekt_Unreal_Source_Projekt_Unreal_Projekt_UnrealCharacter_h

PRAGMA_ENABLE_DEPRECATION_WARNINGS
