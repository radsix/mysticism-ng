#pragma once

#include "./utils/globals.h"

int32_t incrementFormID(uint32_t& currFormID) {
    currFormID++;
    return currFormID;
}

void findFirstAvailableFormID(uint32_t& currFormID, bool& existESP) {

    const auto dataHandler = RE::TESDataHandler::GetSingleton();

    RE::FormID id = dataHandler->LookupFormID(0x800, "dummy.esp");

    if (id != 0) { existESP = true; }

    currFormID = id;
}

class formTrackUtil {
private:
    RE::TESForm* createdForm;
public:
    void create(RE::TESForm* baseForm) {
        if (baseForm->IsInitialized()) {
            createdForm = RE::IFormFactory::GetFormFactoryByType(baseForm->GetFormType())->Create();
            createdForm->Copy(baseForm);
            createdForm->SetFormID(incrementFormID(currFormID), false);
        }
    }

    RE::TESForm* getCreatedForm(void) { return createdForm; }
};