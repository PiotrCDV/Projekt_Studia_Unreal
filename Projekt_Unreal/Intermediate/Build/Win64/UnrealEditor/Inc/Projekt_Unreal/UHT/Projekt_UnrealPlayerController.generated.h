// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

// IWYU pragma: private, include "Projekt_UnrealPlayerController.h"

#ifdef PROJEKT_UNREAL_Projekt_UnrealPlayerController_generated_h
#error "Projekt_UnrealPlayerController.generated.h already included, missing '#pragma once' in Projekt_UnrealPlayerController.h"
#endif
#define PROJEKT_UNREAL_Projekt_UnrealPlayerController_generated_h

#include "UObject/ObjectMacros.h"
#include "UObject/ScriptMacros.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS

// ********** Begin Class AProjekt_UnrealPlayerController ******************************************
PROJEKT_UNREAL_API UClass* Z_Construct_UClass_AProjekt_UnrealPlayerController_NoRegister();

#define FID_Projekt_Unreal_Source_Projekt_Unreal_Projekt_UnrealPlayerController_h_19_INCLASS_NO_PURE_DECLS \
private: \
	static void StaticRegisterNativesAProjekt_UnrealPlayerController(); \
	friend struct Z_Construct_UClass_AProjekt_UnrealPlayerController_Statics; \
	static UClass* GetPrivateStaticClass(); \
	friend PROJEKT_UNREAL_API UClass* Z_Construct_UClass_AProjekt_UnrealPlayerController_NoRegister(); \
public: \
	DECLARE_CLASS2(AProjekt_UnrealPlayerController, APlayerController, COMPILED_IN_FLAGS(CLASS_Abstract | CLASS_Config), CASTCLASS_None, TEXT("/Script/Projekt_Unreal"), Z_Construct_UClass_AProjekt_UnrealPlayerController_NoRegister) \
	DECLARE_SERIALIZER(AProjekt_UnrealPlayerController)


#define FID_Projekt_Unreal_Source_Projekt_Unreal_Projekt_UnrealPlayerController_h_19_ENHANCED_CONSTRUCTORS \
	/** Standard constructor, called after all reflected properties have been initialized */ \
	NO_API AProjekt_UnrealPlayerController(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get()); \
	/** Deleted move- and copy-constructors, should never be used */ \
	AProjekt_UnrealPlayerController(AProjekt_UnrealPlayerController&&) = delete; \
	AProjekt_UnrealPlayerController(const AProjekt_UnrealPlayerController&) = delete; \
	DECLARE_VTABLE_PTR_HELPER_CTOR(NO_API, AProjekt_UnrealPlayerController); \
	DEFINE_VTABLE_PTR_HELPER_CTOR_CALLER(AProjekt_UnrealPlayerController); \
	DEFINE_ABSTRACT_DEFAULT_OBJECT_INITIALIZER_CONSTRUCTOR_CALL(AProjekt_UnrealPlayerController) \
	NO_API virtual ~AProjekt_UnrealPlayerController();


#define FID_Projekt_Unreal_Source_Projekt_Unreal_Projekt_UnrealPlayerController_h_16_PROLOG
#define FID_Projekt_Unreal_Source_Projekt_Unreal_Projekt_UnrealPlayerController_h_19_GENERATED_BODY \
PRAGMA_DISABLE_DEPRECATION_WARNINGS \
public: \
	FID_Projekt_Unreal_Source_Projekt_Unreal_Projekt_UnrealPlayerController_h_19_INCLASS_NO_PURE_DECLS \
	FID_Projekt_Unreal_Source_Projekt_Unreal_Projekt_UnrealPlayerController_h_19_ENHANCED_CONSTRUCTORS \
private: \
PRAGMA_ENABLE_DEPRECATION_WARNINGS


class AProjekt_UnrealPlayerController;

// ********** End Class AProjekt_UnrealPlayerController ********************************************

#undef CURRENT_FILE_ID
#define CURRENT_FILE_ID FID_Projekt_Unreal_Source_Projekt_Unreal_Projekt_UnrealPlayerController_h

PRAGMA_ENABLE_DEPRECATION_WARNINGS
