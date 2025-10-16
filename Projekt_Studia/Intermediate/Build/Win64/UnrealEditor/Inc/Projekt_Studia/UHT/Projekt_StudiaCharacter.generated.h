// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

// IWYU pragma: private, include "Projekt_StudiaCharacter.h"

#ifdef PROJEKT_STUDIA_Projekt_StudiaCharacter_generated_h
#error "Projekt_StudiaCharacter.generated.h already included, missing '#pragma once' in Projekt_StudiaCharacter.h"
#endif
#define PROJEKT_STUDIA_Projekt_StudiaCharacter_generated_h

#include "UObject/ObjectMacros.h"
#include "UObject/ScriptMacros.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS

// ********** Begin Class AProjekt_StudiaCharacter *************************************************
#define FID_Projekt_Studia_Source_Projekt_Studia_Projekt_StudiaCharacter_h_24_RPC_WRAPPERS_NO_PURE_DECLS \
	DECLARE_FUNCTION(execDoJumpEnd); \
	DECLARE_FUNCTION(execDoJumpStart); \
	DECLARE_FUNCTION(execDoLook); \
	DECLARE_FUNCTION(execDoMove);


PROJEKT_STUDIA_API UClass* Z_Construct_UClass_AProjekt_StudiaCharacter_NoRegister();

#define FID_Projekt_Studia_Source_Projekt_Studia_Projekt_StudiaCharacter_h_24_INCLASS_NO_PURE_DECLS \
private: \
	static void StaticRegisterNativesAProjekt_StudiaCharacter(); \
	friend struct Z_Construct_UClass_AProjekt_StudiaCharacter_Statics; \
	static UClass* GetPrivateStaticClass(); \
	friend PROJEKT_STUDIA_API UClass* Z_Construct_UClass_AProjekt_StudiaCharacter_NoRegister(); \
public: \
	DECLARE_CLASS2(AProjekt_StudiaCharacter, ACharacter, COMPILED_IN_FLAGS(CLASS_Abstract | CLASS_Config), CASTCLASS_None, TEXT("/Script/Projekt_Studia"), Z_Construct_UClass_AProjekt_StudiaCharacter_NoRegister) \
	DECLARE_SERIALIZER(AProjekt_StudiaCharacter)


#define FID_Projekt_Studia_Source_Projekt_Studia_Projekt_StudiaCharacter_h_24_ENHANCED_CONSTRUCTORS \
	/** Deleted move- and copy-constructors, should never be used */ \
	AProjekt_StudiaCharacter(AProjekt_StudiaCharacter&&) = delete; \
	AProjekt_StudiaCharacter(const AProjekt_StudiaCharacter&) = delete; \
	DECLARE_VTABLE_PTR_HELPER_CTOR(NO_API, AProjekt_StudiaCharacter); \
	DEFINE_VTABLE_PTR_HELPER_CTOR_CALLER(AProjekt_StudiaCharacter); \
	DEFINE_ABSTRACT_DEFAULT_CONSTRUCTOR_CALL(AProjekt_StudiaCharacter) \
	NO_API virtual ~AProjekt_StudiaCharacter();


#define FID_Projekt_Studia_Source_Projekt_Studia_Projekt_StudiaCharacter_h_21_PROLOG
#define FID_Projekt_Studia_Source_Projekt_Studia_Projekt_StudiaCharacter_h_24_GENERATED_BODY \
PRAGMA_DISABLE_DEPRECATION_WARNINGS \
public: \
	FID_Projekt_Studia_Source_Projekt_Studia_Projekt_StudiaCharacter_h_24_RPC_WRAPPERS_NO_PURE_DECLS \
	FID_Projekt_Studia_Source_Projekt_Studia_Projekt_StudiaCharacter_h_24_INCLASS_NO_PURE_DECLS \
	FID_Projekt_Studia_Source_Projekt_Studia_Projekt_StudiaCharacter_h_24_ENHANCED_CONSTRUCTORS \
private: \
PRAGMA_ENABLE_DEPRECATION_WARNINGS


class AProjekt_StudiaCharacter;

// ********** End Class AProjekt_StudiaCharacter ***************************************************

#undef CURRENT_FILE_ID
#define CURRENT_FILE_ID FID_Projekt_Studia_Source_Projekt_Studia_Projekt_StudiaCharacter_h

PRAGMA_ENABLE_DEPRECATION_WARNINGS
