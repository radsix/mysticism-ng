#include "skills.h"

// Global variables
std::vector<uintptr_t> newAVIList = {};
std::vector<uintptr_t> AVIList = {};
std::unordered_map<RE::ActorValueInfo*, std::string> actorValueNames;
std::vector<RE::ActorValueInfo*> tempAVIs;  // Store multiple AVIs
uintptr_t* listStart = nullptr;

std::vector<aviForm*> newActorValues = {
        new aviForm("Mysticism", "", 0x02000000, 4.0, 0.0, 2.0, 0.0),
        new aviForm("Divination", "", 0x02000000, 4.0, 0.0, 2.0, 0.0),
        new aviForm("Blood Magic", "", 0x02000000, 4.0, 0.0, 2.0, 0.0)
};

// Function to create a placeholder ActorValueInfo
RE::ActorValueInfo* createAVI(aviForm* aviSkill) {
    RE::ActorValueInfo* avi = RE::IFormFactory::GetConcreteFormFactoryByType<RE::ActorValueInfo>()->Create();

    if (avi) {
        avi->enumName = aviSkill->avName.c_str();
        avi->abbreviation = aviSkill->avAbbrev;
        avi->unk064 = aviSkill->avCNAM;
        if (aviSkill->avCNAM == 0x01000000 || aviSkill->avCNAM == 0x02000000 || aviSkill->avCNAM == 0x03000000)
            avi->skill = &aviSkill->avSkillMod;
        logs::debug("createAVI: ActorValue FormID (AVIF) is {} for {}", avi->GetFormID(), aviSkill->avName);
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