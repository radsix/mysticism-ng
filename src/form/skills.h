#pragma once

extern std::vector<uintptr_t> AVIList;
extern std::vector<uintptr_t> newAVIList;
extern std::unordered_map<RE::ActorValueInfo*, std::string> actorValueNames;
extern std::vector<RE::ActorValueInfo*> tempAVIs;
extern uintptr_t* listStart;

struct aviForm {
    const std::string avName;
    const std::string avAbbrev;
    uint32_t avCNAM;
    RE::ActorValueInfo::Skill avSkillMod;

    aviForm(std::string name, std::string abbrev, uint32_t CNAM, float useMult, float offMult, float impMult, float impOffset) : avName(name), avAbbrev(abbrev) {
        avCNAM = CNAM;
        avSkillMod.useMult = useMult;
        avSkillMod.offsetMult = offMult;
        avSkillMod.improveMult = impMult;
        avSkillMod.improveOffset = impOffset;
    }

    aviForm(std::string name, std::string abbrev, uint32_t CNAM) : avName(name), avAbbrev(abbrev), avCNAM(CNAM) {}
};

RE::ActorValueInfo* createAVI(aviForm* aviSkill);
bool extendActorValueList();
void debugLogActorValues();