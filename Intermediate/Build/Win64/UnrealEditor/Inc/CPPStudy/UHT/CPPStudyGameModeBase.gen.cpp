// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "CPPStudy/public/CPPStudyGameModeBase.h"
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodeCPPStudyGameModeBase() {}
// Cross Module References
	CPPSTUDY_API UClass* Z_Construct_UClass_ACPPStudyGameModeBase();
	CPPSTUDY_API UClass* Z_Construct_UClass_ACPPStudyGameModeBase_NoRegister();
	ENGINE_API UClass* Z_Construct_UClass_AGameModeBase();
	UPackage* Z_Construct_UPackage__Script_CPPStudy();
// End Cross Module References
	void ACPPStudyGameModeBase::StaticRegisterNativesACPPStudyGameModeBase()
	{
	}
	IMPLEMENT_CLASS_NO_AUTO_REGISTRATION(ACPPStudyGameModeBase);
	UClass* Z_Construct_UClass_ACPPStudyGameModeBase_NoRegister()
	{
		return ACPPStudyGameModeBase::StaticClass();
	}
	struct Z_Construct_UClass_ACPPStudyGameModeBase_Statics
	{
		static UObject* (*const DependentSingletons[])();
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam Class_MetaDataParams[];
#endif
		static const FCppClassTypeInfoStatic StaticCppClassTypeInfo;
		static const UECodeGen_Private::FClassParams ClassParams;
	};
	UObject* (*const Z_Construct_UClass_ACPPStudyGameModeBase_Statics::DependentSingletons[])() = {
		(UObject* (*)())Z_Construct_UClass_AGameModeBase,
		(UObject* (*)())Z_Construct_UPackage__Script_CPPStudy,
	};
	static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_ACPPStudyGameModeBase_Statics::DependentSingletons) < 16);
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UClass_ACPPStudyGameModeBase_Statics::Class_MetaDataParams[] = {
#if !UE_BUILD_SHIPPING
		{ "Comment", "/**\n * \n */" },
#endif
		{ "HideCategories", "Info Rendering MovementReplication Replication Actor Input Movement Collision Rendering HLOD WorldPartition DataLayers Transformation" },
		{ "IncludePath", "CPPStudyGameModeBase.h" },
		{ "ModuleRelativePath", "public/CPPStudyGameModeBase.h" },
		{ "ShowCategories", "Input|MouseInput Input|TouchInput" },
	};
#endif
	const FCppClassTypeInfoStatic Z_Construct_UClass_ACPPStudyGameModeBase_Statics::StaticCppClassTypeInfo = {
		TCppClassTypeTraits<ACPPStudyGameModeBase>::IsAbstract,
	};
	const UECodeGen_Private::FClassParams Z_Construct_UClass_ACPPStudyGameModeBase_Statics::ClassParams = {
		&ACPPStudyGameModeBase::StaticClass,
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
		0x009002ACu,
		METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UClass_ACPPStudyGameModeBase_Statics::Class_MetaDataParams), Z_Construct_UClass_ACPPStudyGameModeBase_Statics::Class_MetaDataParams)
	};
	UClass* Z_Construct_UClass_ACPPStudyGameModeBase()
	{
		if (!Z_Registration_Info_UClass_ACPPStudyGameModeBase.OuterSingleton)
		{
			UECodeGen_Private::ConstructUClass(Z_Registration_Info_UClass_ACPPStudyGameModeBase.OuterSingleton, Z_Construct_UClass_ACPPStudyGameModeBase_Statics::ClassParams);
		}
		return Z_Registration_Info_UClass_ACPPStudyGameModeBase.OuterSingleton;
	}
	template<> CPPSTUDY_API UClass* StaticClass<ACPPStudyGameModeBase>()
	{
		return ACPPStudyGameModeBase::StaticClass();
	}
	ACPPStudyGameModeBase::ACPPStudyGameModeBase(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer) {}
	DEFINE_VTABLE_PTR_HELPER_CTOR(ACPPStudyGameModeBase);
	ACPPStudyGameModeBase::~ACPPStudyGameModeBase() {}
	struct Z_CompiledInDeferFile_FID_UnrealProjects_CPPStudy_Source_CPPStudy_public_CPPStudyGameModeBase_h_Statics
	{
		static const FClassRegisterCompiledInInfo ClassInfo[];
	};
	const FClassRegisterCompiledInInfo Z_CompiledInDeferFile_FID_UnrealProjects_CPPStudy_Source_CPPStudy_public_CPPStudyGameModeBase_h_Statics::ClassInfo[] = {
		{ Z_Construct_UClass_ACPPStudyGameModeBase, ACPPStudyGameModeBase::StaticClass, TEXT("ACPPStudyGameModeBase"), &Z_Registration_Info_UClass_ACPPStudyGameModeBase, CONSTRUCT_RELOAD_VERSION_INFO(FClassReloadVersionInfo, sizeof(ACPPStudyGameModeBase), 3642776055U) },
	};
	static FRegisterCompiledInInfo Z_CompiledInDeferFile_FID_UnrealProjects_CPPStudy_Source_CPPStudy_public_CPPStudyGameModeBase_h_2549781144(TEXT("/Script/CPPStudy"),
		Z_CompiledInDeferFile_FID_UnrealProjects_CPPStudy_Source_CPPStudy_public_CPPStudyGameModeBase_h_Statics::ClassInfo, UE_ARRAY_COUNT(Z_CompiledInDeferFile_FID_UnrealProjects_CPPStudy_Source_CPPStudy_public_CPPStudyGameModeBase_h_Statics::ClassInfo),
		nullptr, 0,
		nullptr, 0);
PRAGMA_ENABLE_DEPRECATION_WARNINGS
