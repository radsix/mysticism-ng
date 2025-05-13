#pragma once

#define combatSkill 0x1000000
#define magicSkill 0x2000000
#define thiefSkill 0x3000000
#define noSkill 0x0

extern std::vector<uintptr_t> AVIList;
extern std::vector<uintptr_t> newAVIList;
extern std::unordered_map<RE::ActorValueInfo*, std::string> actorValueNames;
extern std::vector<RE::ActorValueInfo*> tempAVIs;
extern uintptr_t* listStart;

class aviForm {
private:
    std::string avName;
    std::string avAbbrev;
    std::string avEDID;
    uint32_t avCNAM;
    RE::ActorValueInfo::Skill avSkillMod;
public:
    aviForm(std::string name, std::string abbrev, std::string EDID, uint32_t CNAM, float useMult = 0, float offMult = 0, float impMult = 0, float impOffset = 0) : avName(name), avAbbrev(abbrev), avEDID(EDID), avCNAM(CNAM) {
        avSkillMod.useMult = useMult;
        avSkillMod.offsetMult = offMult;
        avSkillMod.improveMult = impMult;
        avSkillMod.improveOffset = impOffset;
    }

    const std::string& getAVName() { return this->avName; }
    void setAVName(std::string name) { this->avName = name; return; }

    const std::string& getAVAbbrev() { return this->avAbbrev; }
    void setAVAbbrev(std::string abbrev) { this->avAbbrev = abbrev; return; }

    const std::string& getAVEDID() { return this->avEDID; }
    void setAVEDID(std::string EDID) { this->avEDID = EDID; return; }

    const uint32_t& getAVCNAM() { return this->avCNAM; }
    void setAVCNAM(uint32_t CNAM) { this->avCNAM = CNAM; return; }

    RE::ActorValueInfo::Skill* getAVSkill() { return &this->avSkillMod; }
    void setAVuseMult(float useMult) { this->avSkillMod.useMult = useMult; return; }
    void setAVoffsetMult(float offMult) { this->avSkillMod.offsetMult = offMult; return; }
    void setAVimproveMult(float impMult) { this->avSkillMod.improveMult = impMult; return; }
    void setAVimproveOffset(float impOffset) { this->avSkillMod.improveOffset = impOffset; return; }

};

RE::ActorValueInfo* createAVI(aviForm* aviSkill);
bool extendActorValueList();
void debugLogActorValues();

struct GetActorValueHook {
    static void install();

    template <int T> static float getActorValueHook(RE::ActorValueOwner* avTarget, RE::ActorValue actorValue);

    static inline REL::Relocation<decltype(getActorValueHook<0>)> func[2];
};

struct SetActorValueHook {
    static void install();

    template <int T> static float setActorValueHook(RE::ActorValueOwner* avTarget, RE::ActorValue actorValue);

    static inline REL::Relocation<decltype(setActorValueHook<0>)> func[2];
};

struct ModActorValueHook {
    static void install();

    template <int T> static float modActorValueHook(RE::ActorValueOwner* avTarget, RE::ActorValue actorValue);

    static inline REL::Relocation<decltype(modActorValueHook<0>)> func[2];
};

struct LookupActorValueHook {
    static void install();

    template <int T> static RE::ActorValue lookupActorValueHook(char* avName);

    static inline REL::Relocation<decltype(lookupActorValueHook<0>)> func[2];
};