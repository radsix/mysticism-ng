#pragma once

#include "formEntry.h"
#include "formHelper.h"

extern std::vector<formEntry*> formData;
extern std::vector<formEntry*> formRef;

extern bool espFound;
extern uint32_t currFormID;	// Last form ID assigned
extern uint32_t initFormID;	// First form ID in the ESP
extern uint32_t modFormID;		// Mod index of the first form
extern RE::TESForm* baseMagic;	// Flames spell MGEF
extern RE::EffectSetting* baseME; // Flames spell MGEF setting

void onGameLoad();
void copyComponent(RE::TESForm* from, RE::TESForm* to);
static void applyPattern(formEntry* instance);
RE::TESForm* AddForm(RE::TESForm* baseItem);

extern const char* formsLoaded;