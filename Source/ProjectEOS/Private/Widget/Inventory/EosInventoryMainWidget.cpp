// Fill out your copyright notice in the Description page of Project Settings.


#include "Widget/Inventory/EosInventoryMainWidget.h"
#include "Engine/TextureRenderTarget2D.h"
#include "Kismet/GameplayStatics.h"
#include "Items/Inventory/EosInventoryPreview.h"
#include "Components/SceneCaptureComponent2D.h"
#include "Character/PlayerCharacter/EosBasePlayerCharacter.h"
#include "Components/Image.h"

void UEosInventoryMainWidget::NativeConstruct()
{
	Super::NativeConstruct();

	//PreviewRenderTarget = NewObject<UTextureRenderTarget2D>(this);
	//PreviewRenderTarget->InitAutoFormat(512, 512);
}

//void UEosInventoryMainWidget::OpenInventory()
//{
//	ShowcaseStage = Cast<AEosInventoryPreview>(UGameplayStatics::GetActorOfClass(GetWorld(), ShowcaseClass));
//
//	if (!ShowcaseStage) return;
//
//	ShowcaseStage->SceneCaptureComponent->TextureTarget = PreviewRenderTarget;
//	ShowcaseStage->SceneCaptureComponent->CaptureScene();
//
//	ShowcaseStage->SceneCaptureComponent->ShowOnlyActors.Empty();
//	ShowcaseStage->SceneCaptureComponent->ShowOnlyActors.Add(ShowcaseStage->PreviewMeshComponent->GetOwner());
//
//	if (AEosBasePlayerCharacter* Real = Cast<AEosBasePlayerCharacter>(GetOwningPlayerPawn()))
//	{
//		USkeletalMeshComponent* RealMesh = Real->GetMesh();
//		USkeletalMeshComponent* PreviewMesh = ShowcaseStage->PreviewMeshComponent;
//
//		PreviewMesh->SetSkeletalMesh(RealMesh->SkeletalMesh);
//		PreviewMesh->SetAnimInstanceClass(RealMesh->GetAnimClass());
//		for (int32 i = 0; i < RealMesh->GetNumMaterials(); ++i)
//		{
//			PreviewMesh->SetMaterial(i, RealMesh->GetMaterial(i));
//		}
//	}
//	if (CharacterPreviewImage && PreviewRenderTarget)
//	{
//		FSlateBrush Brush = CharacterPreviewImage->GetBrush();
//		Brush.SetResourceObject(PreviewRenderTarget);
//		CharacterPreviewImage->SetBrush(Brush);
//	}
//}

//void UEosInventoryMainWidget::CloseInventory()
//{
//}
