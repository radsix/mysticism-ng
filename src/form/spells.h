#pragma once

#include "form.h"

void createMagicEffect(
    RE::TESForm* baseEffect = nullptr, // Optional base effect
    std::string name = "Custom Magic Effect", // Custom name
    float baseCost = 0.0f, // Magicka cost

    RE::EffectArchetypes::ArchetypeID archetype = RE::EffectArchetypes::ArchetypeID::kNone, // Effect type
    RE::ActorValue associatedSkill = RE::ActorValue::kNone,
    RE::ActorValue resistVariable = RE::ActorValue::kNone,
    std::int32_t minimumSkill = 0,
    std::int32_t spellmakingArea = 0,
    RE::BGSProjectile* projectile = nullptr, // Projectile
    RE::BGSExplosion* explosion = nullptr, // Explosion effect
    RE::MagicSystem::CastingType castingType = RE::MagicSystem::CastingType::kConstantEffect,
    RE::MagicSystem::Delivery delivery = RE::MagicSystem::Delivery::kSelf,
    RE::ActorValue primaryAV = RE::ActorValue::kNone, // Primary associated AV
    RE::ActorValue secondaryAV = RE::ActorValue::kNone, // Secondary associated AV

    float taperWeight = 0.0f, // Taper weight
    float taperCurve = 1.0f, // Taper curve
    float taperDuration = 0.0f, // Taper duration
    float secondAVWeight = 0.0f, // Secondary AV weight

    //uint32_t flagNone = 0,
    //uint32_t flagHostile = 0,
    //uint32_t Recover = 0,
    //uint32_t Detrimental = 0,
    //uint32_t SnapToNavMesh = 0,
    //uint32_t NoHitEvent = 0,
    //uint32_t DispelWithKeywords = 0,
    //uint32_t NoDuration = 0,
    //uint32_t NoMagnitude = 0,
    //uint32_t NoArea = 0,
    //uint32_t FXPersist = 0,
    //uint32_t GoryVisuals = 0,
    //uint32_t HideInUI = 0,
    //uint32_t NoRecast = 0,
    //uint32_t PowerAffectsMagnitude = 0,
    //uint32_t PowerAffectsDuration = 0,
    //uint32_t Painless = 0,
    //uint32_t NoHitEffect = 0,
    //uint32_t NoDeathDispel = 0,

    //RE::TESEffectShader* effectShader = nullptr,
    //RE::TESEffectShader* enchantShader = nullptr,
    RE::BGSArtObject* castingArt = nullptr, // Casting visuals
    RE::BGSArtObject* hitEffectArt = nullptr, // Hit effect visuals
    RE::BGSArtObject* enchantEffect = nullptr, // Enchantment effect
    RE::BGSImpactDataSet* impactDataSet = nullptr, // Impact effect
    RE::BGSReferenceEffect* hitVisuals = nullptr,
    RE::BGSReferenceEffect* enchantVisuals = nullptr,

    RE::BGSDualCastData* dualCastData = nullptr,
    float dualCastScale = 0.0f,

    RE::SpellItem* equipAbility = nullptr,
    RE::TESImageSpaceModifier* imageSpaceMod = nullptr,
    RE::BGSPerk* perk = nullptr,
    float aiScore = 0.0f,
    float aiDelayTimer = 0.0f,

    RE::SOUND_LEVEL castingSoundLevel = RE::SOUND_LEVEL::kSilent
    //RE::BGSSoundDescriptorForm* castingSound = nullptr, // Casting sound
    //RE::BGSSoundDescriptorForm* boltSound = nullptr, // Bolt sound
    //RE::BGSSoundDescriptorForm* hitSound = nullptr, // Hit sound
    //RE::BGSSoundDescriptorForm* areaSound = nullptr // Area sound
);

void loadSpells();