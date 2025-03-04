#pragma once

#include "formEntry.h"

void addForm(std::vector<formEntry*>& formData, formEntry* entry);
void eachForm(std::vector<formEntry*>& formData, std::function<bool(formEntry*)> const& iteration);
void updateID(std::vector<formEntry*>& formData, uint32_t& currFormID);
void resetID(uint32_t& currFormID, uint32_t& initFormID);
void findFirstAvailableFormID(uint32_t& currFormID, uint32_t& initFormID, uint32_t& modFormID, bool& existESP);