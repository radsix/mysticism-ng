#pragma once

// controls the entry message for the mod (what gets displayed to the user)
const char* entryMessage = "Welcome to Mysticism, a magic mod for Skyrim by Sam Nerad";
const char* formsLoaded = "Forms functionality properly loaded.";

uint32_t currFormID = 0;

uint32_t baseAVTotal = static_cast<uint32_t>(RE::ActorValue::kTotal);

bool espExists = false;