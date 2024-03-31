// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "CPPStudy/public/CSPlayerAnimation.h"
#include "../../Source/Runtime/Engine/Classes/Components/SkeletalMeshComponent.h"
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodeCSPlayerAnimation() {}
// Cross Module References
	CPPSTUDY_API UClass* Z_Construct_UClass_UCSPlayerAnimation();
	CPPSTUDY_API UClass* Z_Construct_UClass_UCSPlayerAnimation_NoRegister();
	ENGINE_API UClass* Z_Construct_UClass_UAnimInstance();
	UPackage* Z_Construct_UPackage__Script_CPPStudy();
// End Cross Module References
	void UCSPlayerAnimation::StaticRegisterNativesUCSPlayerAnimation()
	{
	}
	IMPLEMENT_CLASS_NO_AUTO_REGISTRATION(UCSPlayerAnimation);
	UClass* Z_Construct_UClass_UCSPlayerAnimation_NoRegister()
	{
		return UCSPlayerAnimation::StaticClass();
	}
	struct Z_Construct_UClass_UCSPlayerAnimation_Statics
	{
		static UObject* (*const DependentSingletons[])();
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam Class_MetaDataParams[];
#endif
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_speed_MetaData[];
#endif
		static const UECodeGen_Private::FFloatPropertyParams NewProp_speed;
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_direction_MetaData[];
#endif
		static const UECodeGen_Private::FFloatPropertyParams NewProp_direction;
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_isInAir_MetaData[];
#endif
		static void NewProp_isInAir_SetBit(void* Obj);
		static const UECodeGen_Private::FBoolPropertyParams NewProp_isInAir;
		static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
		static const FCppClassTypeInfoStatic StaticCppClassTypeInfo;
		static const UECodeGen_Private::FClassParams ClassParams;
	};
	UObject* (*const Z_Construct_UClass_UCSPlayerAnimation_Statics::DependentSingletons[])() = {
		(UObject* (*)())Z_Construct_UClass_UAnimInstance,
		(UObject* (*)())Z_Construct_UPackage__Script_CPPStudy,
	};
	static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_UCSPlayerAnimation_Statics::DependentSingletons) < 16);
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UClass_UCSPlayerAnimation_Statics::Class_MetaDataParams[] = {
#if !UE_BUILD_SHIPPING
		{ "Comment", "/**\n * \n */" },
#endif
		{ "HideCategories", "AnimInstance" },
		{ "IncludePath", "CSPlayerAnimation.h" },
		{ "ModuleRelativePath", "public/CSPlayerAnimation.h" },
	};
#endif
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UClass_UCSPlayerAnimation_Statics::NewProp_speed_MetaData[] = {
		{ "Category", "CSPlayerAnimation" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "// \xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xe2\xbf\xa1 \xef\xbf\xbd\xc3\xb7\xef\xbf\xbd\xef\xbf\xbd\xcc\xbe\xef\xbf\xbd \xef\xbf\xbd\xcc\xb5\xef\xbf\xbd\xef\xbf\xbd\xd3\xb5\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd \xef\xbf\xbd\xef\xbf\xbd \xef\xbf\xbd\xdf\xb0\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd?\n// abp \xc3\xa2\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd \xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd \xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xcf\xb1\xef\xbf\xbd \xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\n// \n" },
#endif
		{ "ModuleRelativePath", "public/CSPlayerAnimation.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xe2\xbf\xa1 \xef\xbf\xbd\xc3\xb7\xef\xbf\xbd\xef\xbf\xbd\xcc\xbe\xef\xbf\xbd \xef\xbf\xbd\xcc\xb5\xef\xbf\xbd\xef\xbf\xbd\xd3\xb5\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd \xef\xbf\xbd\xef\xbf\xbd \xef\xbf\xbd\xdf\xb0\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd?\nabp \xc3\xa2\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd \xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd \xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xcf\xb1\xef\xbf\xbd \xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd" },
#endif
	};
#endif
	const UECodeGen_Private::FFloatPropertyParams Z_Construct_UClass_UCSPlayerAnimation_Statics::NewProp_speed = { "speed", nullptr, (EPropertyFlags)0x0010000000010005, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(UCSPlayerAnimation, speed), METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UClass_UCSPlayerAnimation_Statics::NewProp_speed_MetaData), Z_Construct_UClass_UCSPlayerAnimation_Statics::NewProp_speed_MetaData) };
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UClass_UCSPlayerAnimation_Statics::NewProp_direction_MetaData[] = {
		{ "Category", "CSPlayerAnimation" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "// \xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd \xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xcc\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd \xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd \xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\n" },
#endif
		{ "ModuleRelativePath", "public/CSPlayerAnimation.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd \xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xcc\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd \xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd \xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd" },
#endif
	};
#endif
	const UECodeGen_Private::FFloatPropertyParams Z_Construct_UClass_UCSPlayerAnimation_Statics::NewProp_direction = { "direction", nullptr, (EPropertyFlags)0x0010000000010005, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(UCSPlayerAnimation, direction), METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UClass_UCSPlayerAnimation_Statics::NewProp_direction_MetaData), Z_Construct_UClass_UCSPlayerAnimation_Statics::NewProp_direction_MetaData) };
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UClass_UCSPlayerAnimation_Statics::NewProp_isInAir_MetaData[] = {
		{ "Category", "CSPlayerAnimation" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "// \xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd \xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xcc\xbd\xef\xbf\xbd\xef\xbf\xbd\xd9\xb0\xef\xbf\xbd \xef\xbf\xbd\xc6\xb4\xef\xbf\xbd \xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xdf\xbf\xef\xbf\xbd \xef\xbf\xbd\xef\xbf\xbd \xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xc2\xb7\xef\xbf\xbd \xef\xbf\xbd\xc7\xb4\xef\xbf\xbd\xef\xbf\xbd\xcf\xb1\xef\xbf\xbd \xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd \xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xcc\xb3\xef\xbf\xbd \xef\xbf\xbd\xc6\xb4\xcf\xb3\xc4\xb7\xef\xbf\xbd \xef\xbf\xbd\xc7\xba\xef\xbf\xbd\n" },
#endif
		{ "ModuleRelativePath", "public/CSPlayerAnimation.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd \xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xcc\xbd\xef\xbf\xbd\xef\xbf\xbd\xd9\xb0\xef\xbf\xbd \xef\xbf\xbd\xc6\xb4\xef\xbf\xbd \xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xdf\xbf\xef\xbf\xbd \xef\xbf\xbd\xef\xbf\xbd \xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xc2\xb7\xef\xbf\xbd \xef\xbf\xbd\xc7\xb4\xef\xbf\xbd\xef\xbf\xbd\xcf\xb1\xef\xbf\xbd \xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd \xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xcc\xb3\xef\xbf\xbd \xef\xbf\xbd\xc6\xb4\xcf\xb3\xc4\xb7\xef\xbf\xbd \xef\xbf\xbd\xc7\xba\xef\xbf\xbd" },
#endif
	};
#endif
	void Z_Construct_UClass_UCSPlayerAnimation_Statics::NewProp_isInAir_SetBit(void* Obj)
	{
		((UCSPlayerAnimation*)Obj)->isInAir = 1;
	}
	const UECodeGen_Private::FBoolPropertyParams Z_Construct_UClass_UCSPlayerAnimation_Statics::NewProp_isInAir = { "isInAir", nullptr, (EPropertyFlags)0x0010000000010005, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, sizeof(bool), sizeof(UCSPlayerAnimation), &Z_Construct_UClass_UCSPlayerAnimation_Statics::NewProp_isInAir_SetBit, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UClass_UCSPlayerAnimation_Statics::NewProp_isInAir_MetaData), Z_Construct_UClass_UCSPlayerAnimation_Statics::NewProp_isInAir_MetaData) };
	const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UClass_UCSPlayerAnimation_Statics::PropPointers[] = {
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UCSPlayerAnimation_Statics::NewProp_speed,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UCSPlayerAnimation_Statics::NewProp_direction,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UCSPlayerAnimation_Statics::NewProp_isInAir,
	};
	const FCppClassTypeInfoStatic Z_Construct_UClass_UCSPlayerAnimation_Statics::StaticCppClassTypeInfo = {
		TCppClassTypeTraits<UCSPlayerAnimation>::IsAbstract,
	};
	const UECodeGen_Private::FClassParams Z_Construct_UClass_UCSPlayerAnimation_Statics::ClassParams = {
		&UCSPlayerAnimation::StaticClass,
		nullptr,
		&StaticCppClassTypeInfo,
		DependentSingletons,
		nullptr,
		Z_Construct_UClass_UCSPlayerAnimation_Statics::PropPointers,
		nullptr,
		UE_ARRAY_COUNT(DependentSingletons),
		0,
		UE_ARRAY_COUNT(Z_Construct_UClass_UCSPlayerAnimation_Statics::PropPointers),
		0,
		0x009000A8u,
		METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UClass_UCSPlayerAnimation_Statics::Class_MetaDataParams), Z_Construct_UClass_UCSPlayerAnimation_Statics::Class_MetaDataParams)
	};
	static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_UCSPlayerAnimation_Statics::PropPointers) < 2048);
	UClass* Z_Construct_UClass_UCSPlayerAnimation()
	{
		if (!Z_Registration_Info_UClass_UCSPlayerAnimation.OuterSingleton)
		{
			UECodeGen_Private::ConstructUClass(Z_Registration_Info_UClass_UCSPlayerAnimation.OuterSingleton, Z_Construct_UClass_UCSPlayerAnimation_Statics::ClassParams);
		}
		return Z_Registration_Info_UClass_UCSPlayerAnimation.OuterSingleton;
	}
	template<> CPPSTUDY_API UClass* StaticClass<UCSPlayerAnimation>()
	{
		return UCSPlayerAnimation::StaticClass();
	}
	UCSPlayerAnimation::UCSPlayerAnimation(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer) {}
	DEFINE_VTABLE_PTR_HELPER_CTOR(UCSPlayerAnimation);
	UCSPlayerAnimation::~UCSPlayerAnimation() {}
	struct Z_CompiledInDeferFile_FID_UnrealProjects_CPPStudy_Source_CPPStudy_public_CSPlayerAnimation_h_Statics
	{
		static const FClassRegisterCompiledInInfo ClassInfo[];
	};
	const FClassRegisterCompiledInInfo Z_CompiledInDeferFile_FID_UnrealProjects_CPPStudy_Source_CPPStudy_public_CSPlayerAnimation_h_Statics::ClassInfo[] = {
		{ Z_Construct_UClass_UCSPlayerAnimation, UCSPlayerAnimation::StaticClass, TEXT("UCSPlayerAnimation"), &Z_Registration_Info_UClass_UCSPlayerAnimation, CONSTRUCT_RELOAD_VERSION_INFO(FClassReloadVersionInfo, sizeof(UCSPlayerAnimation), 3281138513U) },
	};
	static FRegisterCompiledInInfo Z_CompiledInDeferFile_FID_UnrealProjects_CPPStudy_Source_CPPStudy_public_CSPlayerAnimation_h_1720857199(TEXT("/Script/CPPStudy"),
		Z_CompiledInDeferFile_FID_UnrealProjects_CPPStudy_Source_CPPStudy_public_CSPlayerAnimation_h_Statics::ClassInfo, UE_ARRAY_COUNT(Z_CompiledInDeferFile_FID_UnrealProjects_CPPStudy_Source_CPPStudy_public_CSPlayerAnimation_h_Statics::ClassInfo),
		nullptr, 0,
		nullptr, 0);
PRAGMA_ENABLE_DEPRECATION_WARNINGS
