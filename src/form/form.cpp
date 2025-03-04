#include "form.h"

std::vector<formEntry*> formData = {};  // Stores form data
std::vector<formEntry*> formRef = {};   // Stores form references

// Global variables related to form handling
bool espFound = false;   // Indicates if ESP (plugin) was found
uint32_t currFormID = 0; // Last assigned form ID
uint32_t initFormID = 0; // First form ID in the ESP
uint32_t modFormID = 0;  // Mod index of the first form

RE::TESForm* baseMagic;
RE::EffectSetting* baseME;

// Message indicating successful form functionality loading
const char* formsLoaded = "Forms functionality properly loaded.";

void onGameLoad() {
    // Find the first available data index slot
    findFirstAvailableFormID(currFormID, initFormID, modFormID, espFound);

    // Lookup base magic effect (Flames spell MGEF) and store a pointer to it
    baseMagic = RE::TESForm::LookupByID(0x00013CA9);
    baseME = RE::TESForm::LookupByID<RE::EffectSetting>(0x00013CA9);    
}

/**
 * @brief Copies a specific component from one TESForm to another.
 *
 * @tparam T The component type to copy.
 * @param from Source TESForm.
 * @param to Target TESForm.
 */
template <class T>
void copyComponent(RE::TESForm* from, RE::TESForm* to) {
    auto fromT = from->As<T>();
    auto toT = to->As<T>();
    if (fromT && toT) {
        toT->CopyComponent(fromT);
    }
}

/**
 * @brief Applies form data patterns from a base form to a new instance.
 *
 * @param instance The form entry instance.
 */
static void applyPattern(formEntry* instance) {
    if (!instance) {
        return;
        logs::error("applyPattern: Form entry instance not found");
    }

    auto baseForm = instance->getBaseForm();
    auto newForm = instance->getForm();

    newForm->Copy(baseForm);

    if (baseForm && newForm) {
        // Copy multiple components from baseForm to newForm
        copyComponent<RE::TESDescription>(baseForm, newForm);
        copyComponent<RE::BGSKeywordForm>(baseForm, newForm);
        copyComponent<RE::BGSPickupPutdownSounds>(baseForm, newForm);
        copyComponent<RE::TESModelTextureSwap>(baseForm, newForm);
        copyComponent<RE::TESModel>(baseForm, newForm);
        copyComponent<RE::BGSMessageIcon>(baseForm, newForm);
        copyComponent<RE::TESIcon>(baseForm, newForm);
        copyComponent<RE::TESFullName>(baseForm, newForm);
        copyComponent<RE::TESValueForm>(baseForm, newForm);
        copyComponent<RE::TESWeightForm>(baseForm, newForm);
        copyComponent<RE::BGSDestructibleObjectForm>(baseForm, newForm);
        copyComponent<RE::TESEnchantableForm>(baseForm, newForm);
        copyComponent<RE::BGSBlockBashData>(baseForm, newForm);
        copyComponent<RE::BGSEquipType>(baseForm, newForm);
        copyComponent<RE::TESAttackDamageForm>(baseForm, newForm);
        copyComponent<RE::TESBipedModelForm>(baseForm, newForm);
    }
}

/**
 * @brief Adds a new form to the game by duplicating an existing base form.
 *
 * @param baseItem The base TESForm to duplicate.
 * @return Pointer to the newly created TESForm.
 */
RE::TESForm* AddForm(RE::TESForm* baseItem) {
    if (!espFound) {
        logs::error("AddForm: Unable to find ESP file");
        return nullptr;
    }

    RE::TESForm* result = nullptr;
    eachForm(formData, [&](formEntry* item) {
        if (item->isEmptyEntry()) {
            auto factory = RE::IFormFactory::GetFormFactoryByType(baseItem->GetFormType());
            result = factory->Create();
            result->SetFormID(item->getFormID(), false);
            item->fillForm(result, baseItem->GetFormType());
            item->setBaseForm(baseItem);
            applyPattern(item);
            return false;
        }
        return true;
        });

    if (result) {
        return result;
    }

    // Create a new form if no empty entry was found
    auto factory = RE::IFormFactory::GetFormFactoryByType(baseItem->GetFormType());
    auto newForm = factory->Create();
    newForm->SetFormID(currFormID, false);
    formEntry* slot = formEntry::CreateNew(newForm, baseItem->GetFormType(), currFormID);
    ++currFormID;
    slot->setBaseForm(baseItem);
    applyPattern(slot);
    addForm(formData, slot);
    return newForm;
}