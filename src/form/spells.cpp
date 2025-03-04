#include "spells.h"

void createMagicEffect(
    RE::TESForm * baseEffect, // Optional base effect
    std::string name, // Custom name
    float baseCost, // Magicka cost

    RE::EffectArchetypes::ArchetypeID archetype, // Effect type
    RE::ActorValue associatedSkill,
    RE::ActorValue resistVariable,
    std::int32_t minimumSkill,
    std::int32_t spellmakingArea,
    RE::BGSProjectile* projectile, // Projectile
    RE::BGSExplosion* explosion, // Explosion effect
    RE::MagicSystem::CastingType castingType,
    RE::MagicSystem::Delivery delivery,
    RE::ActorValue primaryAV, // Primary associated AV
    RE::ActorValue secondaryAV, // Secondary associated AV

    float taperWeight, // Taper weight
    float taperCurve, // Taper curve
    float taperDuration, // Taper duration
    float secondAVWeight, // Secondary AV weight

    //uint32_t None,
    //uint32_t Hostile,
    //uint32_t Recover,
    //uint32_t Detrimental,
    //uint32_t SnapToNavMesh,
    //uint32_t NoHitEvent,
    //uint32_t DispelWithKeywords,
    //uint32_t NoDuration,
    //uint32_t NoMagnitude,
    //uint32_t NoArea,
    //uint32_t FXPersist,
    //uint32_t GoryVisuals,
    //uint32_t HideInUI,
    //uint32_t NoRecast,
    //uint32_t PowerAffectsMagnitude,
    //uint32_t PowerAffectsDuration,
    //uint32_t Painless,
    //uint32_t NoHitEffect,
    //uint32_t NoDeathDispel,

    //RE::TESEffectShader* effectShader,
    //RE::TESEffectShader* enchantShader,
    RE::BGSArtObject* castingArt, // Casting visuals
    RE::BGSArtObject* hitEffectArt, // Hit effect visuals
    RE::BGSArtObject* enchantEffect, // Enchantment effect
    RE::BGSImpactDataSet* impactDataSet, // Impact effect
    RE::BGSReferenceEffect* hitVisuals,
    RE::BGSReferenceEffect* enchantVisuals,

    RE::BGSDualCastData* dualCastData,
    float dualCastScale,

    RE::SpellItem* equipAbility,
    RE::TESImageSpaceModifier* imageSpaceMod,
    RE::BGSPerk* perk,
    float aiScore,
    float aiDelayTimer,

    RE::SOUND_LEVEL castingSoundLevel
    //RE::BGSSoundDescriptorForm* castingSound, // Casting sound
    //RE::BGSSoundDescriptorForm* boltSound, // Bolt sound
    //RE::BGSSoundDescriptorForm* hitSound, // Hit sound
    //RE::BGSSoundDescriptorForm* areaSound // Area sound
)
{
    if (!baseEffect) {
        logs::error("createMagicEffect: Failed to find default base effect");
        return;
    }
    else {
        logs::debug("createMagicEffect: Default base effect {} ", baseEffect->formID);
    }

    auto* newEffectForm = AddForm(baseEffect);
    if (!newEffectForm) {
        logs::error("createMagicEffect: Failed to create new magic effect");
        return;
    }

    auto* newEffect = newEffectForm->As<RE::EffectSetting>();
    if (!newEffect) {
        logs::error("createMagicEffect: Cloned form is not an EffectSetting.");
        return;
    }

    newEffect->fullName = name;
    newEffect->data.archetype = archetype;
    newEffect->data.baseCost = baseCost;
    newEffect->data.primaryAV = primaryAV;
    newEffect->data.secondaryAV = secondaryAV;
    newEffect->data.taperWeight = taperWeight;
    newEffect->data.taperCurve = taperCurve;
    newEffect->data.taperDuration = taperDuration;
    newEffect->data.secondAVWeight = secondAVWeight;
    newEffect->data.associatedSkill = associatedSkill;
    newEffect->data.resistVariable = resistVariable;
    newEffect->data.minimumSkill = minimumSkill;
    newEffect->data.spellmakingArea = spellmakingArea;
    newEffect->data.projectileBase = projectile;
    newEffect->data.explosion = explosion;
    newEffect->data.castingType = castingType;
    newEffect->data.delivery = delivery;
    
    // TODO: add flags here in the future

    newEffect->data.castingArt = castingArt;
    newEffect->data.hitEffectArt = hitEffectArt;
    newEffect->data.enchantEffectArt = enchantEffect;
    newEffect->data.impactDataSet = impactDataSet;
    newEffect->data.hitVisuals = hitVisuals;
    newEffect->data.enchantVisuals = enchantVisuals;
    newEffect->data.dualCastData = dualCastData;
    newEffect->data.dualCastScale = dualCastScale;
    newEffect->data.equipAbility = equipAbility;
    newEffect->data.imageSpaceMod = imageSpaceMod;
    newEffect->data.perk = perk;
    newEffect->data.aiScore = aiScore;
    newEffect->data.aiDelayTimer = aiDelayTimer;
    newEffect->data.castingSoundLevel = castingSoundLevel;

    // TODO: add sound effects here in future

    logs::info("createMagicEffect: Successfully created '{}'", name);
}

void loadSpells() {
    return;
}