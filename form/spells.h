#pragma once

#include "form.h"

class magicForm : public formTrackUtil {
private:
    RE::EffectSetting* magicData;
    std::unique_ptr<RE::Effect> effect;

public:
    magicForm() : magicData(nullptr), effect(std::make_unique<RE::Effect>()) {}

    magicForm(RE::TESForm* baseForm) {
        create(baseForm);
        magicData = getCreatedForm() ? getCreatedForm()->As<RE::EffectSetting>() : nullptr;
        initializeEffect();
    }

    magicForm(RE::TESForm* baseForm, const std::string& name) {
        create(baseForm);
        magicData = getCreatedForm() ? getCreatedForm()->As<RE::EffectSetting>() : nullptr;
        if (magicData) {
            magicData->fullName = name;
        }
        initializeEffect();
    }

    void initializeEffect() {
        effect = std::make_unique<RE::Effect>();
        effect->effectItem.area = 0;
        effect->effectItem.duration = 0;
        effect->effectItem.magnitude = 0;
        effect->baseEffect = magicData;
        effect->cost = 0.0;
    }

    void setName(const std::string& fullName) {
        if (magicData) {
            magicData->fullName = fullName;
        }
    }

    void setAssociatedSkill(RE::ActorValue skill) {
        if (magicData) {
            magicData->data.associatedSkill = skill;
        }
    }

    void setAIBehavior(float aiDelay, float aiScore) {
        if (magicData) {
            magicData->data.aiDelayTimer = aiDelay;
            magicData->data.aiScore = aiScore;
        }
    }

    void setArchetype(RE::EffectSetting::Archetype arch) {
        if (magicData) {
            magicData->data.archetype = arch;
        }
    }

    void setCost(float cost) {
        if (magicData) {
            magicData->data.baseCost = cost;
        }
        effect->cost = cost;
    }

    void setPrimSecAV(RE::ActorValue primaryAV, RE::ActorValue secondaryAV) {
        if (magicData) {
            magicData->data.primaryAV = primaryAV;
            magicData->data.secondaryAV = secondaryAV;
        }
    }

    void setTaper(float curve, float duration, float weight) {
        if (magicData) {
            magicData->data.taperCurve = curve;
            magicData->data.taperDuration = duration;
            magicData->data.taperWeight = weight;
        }
    }

    void setPerk(RE::BGSPerk* perk) {
        if (magicData) {
            magicData->data.perk = perk;
        }
    }

    void setSound(RE::BSTArray<RE::EffectSetting::SoundPair> womp) {
        if (magicData) {
            magicData->effectSounds = womp;
        }
    }

    void setEffectAttributes(uint32_t area, uint32_t duration, float magnitude) {
        effect->effectItem.area = area;
        effect->effectItem.duration = duration;
        effect->effectItem.magnitude = magnitude;
    }

    RE::EffectSetting* getMagicData() const { return magicData; }
    RE::Effect* getEffect() const { return effect.get(); }
};

class spellForm : public formTrackUtil {
private:
    RE::SpellItem* spellData;
public:
    spellForm() : spellData(nullptr) {}

    spellForm(RE::TESForm* baseForm) {
        create(baseForm);
        spellData = getCreatedForm() ? getCreatedForm()->As<RE::SpellItem>() : nullptr;
    }

    spellForm(RE::TESForm* baseForm, const char* name) {
        create(baseForm);
        spellData = getCreatedForm() ? getCreatedForm()->As<RE::SpellItem>() : nullptr;
        if (spellData) {
            spellData->SetFullName(name);
        }
    }

    void setName(const char* fullName) {
        if (spellData) {
            spellData->SetFullName(fullName);
        }
    }

    void addEffect(RE::Effect* magicEffect) {
        if (spellData && magicEffect) {
            spellData->effects.push_back(magicEffect);
        }
    }

    void clearEffects() {
        if (spellData) {
            spellData->effects.clear();
        }
    }
};

std::vector<std::unique_ptr<magicForm>> magicInitialization;
std::vector<std::unique_ptr<spellForm>> spellInitialization;

void mgefRegister(void) {
    auto magic = std::make_unique<magicForm>(RE::TESForm::LookupByID(0x00013CAA), "wompicus");
    magic->setEffectAttributes(0, 5, 10.0f);
    magic->setCost(5.0f);

    auto spell = std::make_unique<spellForm>(RE::TESForm::LookupByID(0x00012FCD), "beans");
    if (spell) {
        spell->setName("guacamole");
        spell->clearEffects();
        spell->addEffect(magic->getEffect());
    }

    magicInitialization.push_back(std::move(magic));
    spellInitialization.push_back(std::move(spell));
}

/*
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
*/