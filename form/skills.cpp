#include "skills.h"

// Global variables
std::vector<uintptr_t> newAVIList = {};
std::vector<uintptr_t> AVIList = {};
std::unordered_map<RE::ActorValueInfo*, std::string> actorValueNames;
std::vector<RE::ActorValueInfo*> tempAVIs;  // Store multiple AVIs
uintptr_t* listStart = nullptr;

std::vector<aviForm*> newActorValues = {
        new aviForm("Mysticism", "", "AVIllusion", magicSkill, 4.0, 0.0, 2.0, 0.0),
        new aviForm("MysticismMod", "", "AVMysticismMod", noSkill),
        new aviForm("MysticismPowerMod", "", "AVMysticismPowerMod", noSkill)
};

// Function to create a placeholder ActorValueInfo
RE::ActorValueInfo* createAVI(aviForm* aviSkill) {
    RE::ActorValueInfo* avi = RE::IFormFactory::GetConcreteFormFactoryByType<RE::ActorValueInfo>()->Create();

    if (avi) {
        avi->enumName = aviSkill->getAVName().c_str();
        avi->abbreviation = aviSkill->getAVAbbrev();
        avi->SetFormEditorID(aviSkill->getAVEDID().c_str());
        avi->unk064 = aviSkill->getAVCNAM();
        if (aviSkill->getAVCNAM() == combatSkill || aviSkill->getAVCNAM() == magicSkill || aviSkill->getAVCNAM() == thiefSkill)
            avi->skill = aviSkill->getAVSkill();
        logs::debug("createAVI: ActorValue FormID (AVIF) is {} for {} with EDID {}", avi->GetFormID(), avi->enumName, avi->GetFormEditorID());
    }
    else {
        logs::error("createAVI: ActorValueInfo did not generate");
    }

    return avi;
}

// Function to extend the Actor Value List
bool extendActorValueList() {

    uint32_t extraSize = static_cast<uint32_t>(newActorValues.size());

    if (extraSize == 0) {
        logs::debug("extendActorValueList: No new Actor Values detected/registered");
        return false;
    }

    auto actorValueList = RE::ActorValueList::GetSingleton();
    uint32_t baseSize = static_cast<uint32_t>(RE::ActorValue::kTotal);

    // Create and store multiple AVIs
    tempAVIs.reserve(extraSize);
    for (aviForm* avSkill : newActorValues) {
        RE::ActorValueInfo* newAVI = createAVI(avSkill);
        if (newAVI) {
            tempAVIs.push_back(newAVI);
        }
    }

    // Resize the list to fit the new values
    AVIList.resize(baseSize + extraSize + 1, reinterpret_cast<uintptr_t>(nullptr));

    // Copy original ActorValues to the new list
    size_t copy_size = sizeof(RE::ActorValueInfo*) * baseSize;
    std::memcpy(&AVIList[1], &actorValueList->actorValues, copy_size);

    // Add new ActorValues
    for (size_t i = 0; i < tempAVIs.size(); i++) {
        AVIList[baseSize + i + 1] = reinterpret_cast<uintptr_t>(tempAVIs[i]);
    }

    uintptr_t firstEntry = (actorValueList->unk00 << 4) | (actorValueList->pad04);
    AVIList[0] = firstEntry;

    listStart = AVIList.data();

    REL::RelocationID aviListPtr{ 514139, 400267 };
    REL::safe_write(aviListPtr.address(), &listStart, 0x8);

    return true;
}

void debugLogActorValues() {
    auto actorValueList = RE::ActorValueList::GetSingleton();
    if (!actorValueList) {
        logs::error("debugLogActorValues: ActorValueList not found");
        return;
    }

    logs::info("Logging all ActorValues:");

    for (uint32_t i = 0; i < AVIList.size(); i++) {
        auto avi = reinterpret_cast<RE::ActorValueInfo*>(AVIList[i]);
        if (avi)
            logs::info("Index {}: Enum Name: {}, Abbreviation: {}", i, std::string(avi->enumName), std::string(avi->abbreviation));
    }
}

void GetActorValueHook::install() {
    REL::Relocation<uintptr_t> pcharActorVTable { RE::VTABLE_PlayerCharacter[5] };
    REL::Relocation<uintptr_t> charActorVTable{ RE::VTABLE_Character[5] };

    func[0] = pcharActorVTable.write_vfunc(0x01, getActorValueHook<0>);
    func[1] = charActorVTable.write_vfunc(0x01, getActorValueHook<1>);
}

template <int T> float GetActorValueHook::getActorValueHook(RE::ActorValueOwner* avTarget, RE::ActorValue actorValue) {

    uint32_t actorValueRaw = static_cast<uint32_t>(actorValue);

    if (actorValueRaw < static_cast<uint32_t>(RE::ActorValue::kTotal))
        return func[T](avTarget, actorValue); // this is where the old functions need to be called

    return 50.0;
}

void LookupActorValueHook::install() {
/*
    // needs the correct virtual table
    REL::Relocation<uintptr_t> actorVTable{ RE::VTABLE_Actor[0] };   // Actor VTable
    REL::Relocation<uintptr_t> playerVTable{ RE::VTABLE_PlayerCharacter[0] };  // PlayerCharacter VTable

    // needs the correct offset
    func[0] = actorVTable.write_vfunc(74, lookupActorValueHook<0>);  // Hook function at index 74
    func[1] = playerVTable.write_vfunc(74, lookupActorValueHook<1>); // Hook function for player
*/
}


template <int T> RE::ActorValue LookupActorValueHook::lookupActorValueHook(char* avName) {

    for (size_t i = 0; i < AVIList.size(); i++) {
        auto avi = reinterpret_cast<RE::ActorValueInfo*>(AVIList[i]);
        if (avi) {
            if (avi->enumName == avName) {
                return static_cast<RE::ActorValue>(i-1);
            }
        }
    }

    return static_cast<RE::ActorValue>(1);
}