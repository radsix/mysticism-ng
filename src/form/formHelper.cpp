#include "formHelper.h"

/*
 * @brief Adds a form entry to the form data storage.
 * 
 * @param item Pointer to the formEntry to add.
 */
void addForm(std::vector<formEntry*>& formData, formEntry* entry) {

    if (!entry) { return; }

    formData.push_back(entry);
}

/*
 * @brief Iterates over all stored form data entries.
 * 
 * @param iteration Function to be applied to each formEntry.
 */
void eachForm(std::vector<formEntry*>& formData, std::function<bool(formEntry*)> const& iteration) {
    for (auto item : formData) { if (!iteration(item)) { return; } } 
}

/*
 * @brief Updates the currFormID based on the highest existing form ID in formStack.
 */
void updateID(std::vector<formEntry*>& formData, uint32_t& currFormID) {
    eachForm(formData, [&](formEntry* entry) {

        if (entry->Match(currFormID)) { currFormID = entry->Match(currFormID); }
        
        return true;
    });

    ++currFormID;
}

/*
 * @brief Resets the lastFormId back to the firstFormId.
 */
void resetID(uint32_t& currFormID, uint32_t& initFormID) { currFormID = initFormID; }

/*
 * @brief Reads the first form ID from the ESP and initializes form ID tracking.
 */
void findFirstAvailableFormID(uint32_t& currFormID, uint32_t& initFormID, uint32_t& modFormID, bool& existESP) {

    const auto dataHandler = RE::TESDataHandler::GetSingleton();

    auto id = dataHandler->LookupFormID(0x800, "dummy.esp");

    if (id != 0) { existESP = true; }

    initFormID = id + 1;
    currFormID = initFormID;
    modFormID = (initFormID >> 24) & 0xff;
}