// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

// IWYU pragma: private, include "Projekt_StudiaPlayerController.h"

#ifdef PROJEKT_STUDIA_Projekt_StudiaPlayerController_generated_h
#error "Projekt_StudiaPlayerController.generated.h already included, missing '#pragma once' in Projekt_StudiaPlayerController.h"
#endif
#define PROJEKT_STUDIA_Projekt_StudiaPlayerController_generated_h

#include "UObject/ObjectMacros.h"
#include "UObject/ScriptMacros.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS

// ********** Begin Class AProjekt_StudiaPlayerController ******************************************
PROJEKT_STUDIA_API UClass* Z_Construct_UClass_AProjekt_StudiaPlayerController_NoRegister();

#define FID_Projekt_Studia_Source_Projekt_Studia_Projekt_StudiaPlayerController_h_18_INCLASS_NO_PURE_DECLS \
private: \
	static void StaticRegisterNativesAProjekt_StudiaPlayerController(); \
	friend struct Z_Construct_UClass_AProjekt_StudiaPlayerController_Statics; \
	static UClass* GetPrivateStaticClass(); \
	friend PROJEKT_STUDIA_API UClass* Z_Construct_UClass_AProjekt_StudiaPlayerController_NoRegister(); \
public: \
	DECLARE_CLASS2(AProjekt_StudiaPlayerController, APlayerController, COMPILED_IN_FLAGS(CLASS_Abstract | CLASS_Config), CASTCLASS_None, TEXT("/Script/Projekt_Studia"), Z_Construct_UClass_AProjekt_StudiaPlayerController_NoRegister) \
	DECLARE_SERIALIZER(AProjekt_StudiaPlayerController)


#define FID_Projekt_Studia_Source_Projekt_Studia_Projekt_StudiaPlayerController_h_18_ENHANCED_CONSTRUCTORS \
	/** Standard constructor, called after all reflected properties have been initialized */ \
	NO_API AProjekt_StudiaPlayerController(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get()); \
	/** Deleted move- and copy-constructors, should never be used */ \
	AProjekt_StudiaPlayerController(AProjekt_StudiaPlayerController&&) = delete; \
	AProjekt_StudiaPlayerController(const AProjekt_StudiaPlayerController&) = delete; \
	DECLARE_VTABLE_PTR_HELPER_CTOR(NO_API, AProjekt_StudiaPlayerController); \
	DEFINE_VTABLE_PTR_HELPER_CTOR_CALLER(AProjekt_StudiaPlayerController); \
	DEFINE_ABSTRACT_DEFAULT_OBJECT_INITIALIZER_CONSTRUCTOR_CALL(AProjekt_StudiaPlayerController) \
	NO_API virtual ~AProjekt_StudiaPlayerController();


#define FID_Projekt_Studia_Source_Projekt_Studia_Projekt_StudiaPlayerController_h_15_PROLOG
#define FID_Projekt_Studia_Source_Projekt_Studia_Projekt_StudiaPlayerController_h_18_GENERATED_BODY \
PRAGMA_DISABLE_DEPRECATION_WARNINGS \
public: \
	FID_Projekt_Studia_Source_Projekt_Studia_Projekt_StudiaPlayerController_h_18_INCLASS_NO_PURE_DECLS \
	FID_Projekt_Studia_Source_Projekt_Studia_Projekt_StudiaPlayerController_h_18_ENHANCED_CONSTRUCTORS \
private: \
PRAGMA_ENABLE_DEPRECATION_WARNINGS


class AProjekt_StudiaPlayerController;

// ********** End Class AProjekt_StudiaPlayerController ********************************************

#undef CURRENT_FILE_ID
#define CURRENT_FILE_ID FID_Projekt_Studia_Source_Projekt_Studia_Projekt_StudiaPlayerController_h

PRAGMA_ENABLE_DEPRECATION_WARNINGS
