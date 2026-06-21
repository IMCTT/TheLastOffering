#include "UI/TLOHUDWidget.h"
#include "Components/ProgressBar.h"
#include "Components/TextBlock.h"

void UTLOHUDWidget::UpdateHealth(float CurrentHealth, float MaxHealth)
{
	if (HealthBar)
		HealthBar->SetPercent(MaxHealth > 0.f ? CurrentHealth / MaxHealth : 0.f);
}

void UTLOHUDWidget::UpdateWave(int32 WaveNumber)
{
	if (WaveText)
		WaveText->SetText(FText::FromString(FString::Printf(TEXT("Oleada: %d"), WaveNumber)));
}

void UTLOHUDWidget::UpdateEnemiesRemaining(int32 EnemiesRemaining)
{
	if (EnemiesText)
		EnemiesText->SetText(FText::FromString(FString::Printf(TEXT("Enemigos: %d"), EnemiesRemaining)));
}

void UTLOHUDWidget::UpdateActiveSpell(FName SpellName)
{
	if (SpellText)
		SpellText->SetText(FText::FromName(SpellName));
}