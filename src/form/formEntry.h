#pragma once

// Class representing an entry for a form in the system
class formEntry {
public:

    // Default constructor
    formEntry() = default;

    // Default destructor
    ~formEntry() = default;

    // Constructor that initializes the form and its ID
    explicit formEntry(RE::TESForm* a_form)
        : form(a_form), formID(a_form ? a_form->GetFormID() : 0) {
    }

    /*
     * Creates a new formEntry with the specified form, form type, and form ID.
     * @param a_form Pointer to the form.
     * @param a_formType Type of the form.
     * @param a_formID Unique identifier for the form.
     * @return A unique pointer to the newly created formEntry.
     */
    static formEntry* CreateNew(RE::TESForm* a_form, RE::FormType a_formType, RE::FormID a_formID) {

        if (!a_form) return nullptr;

        formEntry* result = new formEntry(a_form);

        result->formType = a_formType;
        result->formID = a_formID;

        return result;
    }

    /*
     * Creates a reference to an existing form.
     * @param a_form Pointer to the form.
     * @return A unique pointer to the created formEntry, or nullptr if a_form is null.
     */
    static std::unique_ptr<formEntry> createFormRef(RE::TESForm* a_form) { return a_form ? std::make_unique<formEntry>(a_form) : nullptr; }

    /*
     * Creates an entry for a deleted form using only its form ID.
     * @param a_formID Unique identifier for the deleted form.
     * @return A unique pointer to the deleted formEntry.
     */
    static std::unique_ptr<formEntry> createEmpty(RE::FormID a_formID) {
        
        auto result = std::make_unique<formEntry>();

        result->formID = a_formID;
        result->isEmpty = true;

        return result;
    }

    /*
     * Restores a deleted reference and assigns it a new form.
     * @param a_form Pointer to the form.
     */
    void fillForm(RE::TESForm* a_form) {
        
        if (!a_form) return;

        form = a_form;
        formID = a_form->GetFormID();

        isEmpty = false;
    }

    /*
     * Restores a deleted form entry with a new form and form type.
     * @param a_form Pointer to the form.
     * @param a_formType Type of the form.
     */
    void fillForm(RE::TESForm* a_form, RE::FormType a_formType) {
        
        if (!a_form) return;

        form = a_form;
        formType = a_formType;

        isEmpty = false;
    }

    /*
     * Checks if the given form matches the stored form ID.
     * @param a_form Pointer to the form.
     * @return True if the form IDs match, false otherwise.
     */
    bool Match(RE::TESForm* a_form) const { return a_form && a_form->GetFormID() == formID; }

    /*
     * Checks if the given form ID matches the stored form ID.
     * @param a_formID The form ID to compare.
     * @return True if the form IDs match, false otherwise.
     */
    bool Match(RE::FormID a_formID) const { return formID == a_formID; }

    /*
     * Checks if the entry has a model associated with it.
     * @return True if a model exists, false otherwise.
     */
    bool HasModel() const { return modelForm != nullptr; }

    bool isEmptyEntry() const { return isEmpty; }

    RE::FormID getFormID() const { return formID; }

    RE::TESForm* getForm() const { return form; }

    RE::TESForm* getBaseForm() const { return baseForm; }

    RE::TESForm* getModelForm() const { return modelForm; }

    RE::FormType getFormType() const { return formType; }

    RE::TESForm* setBaseForm(RE::TESForm* a_formBase) { baseForm = a_formBase; return baseForm; }

private:
    RE::TESForm* form = nullptr;        // Pointer to the form instance
    RE::TESForm* baseForm = nullptr;    // Pointer to the base form (if applicable)
    RE::TESForm* modelForm = nullptr;   // Pointer to a model form (if applicable)
    RE::FormType formType{};            // The type of the form
    RE::FormID formID{};                // The unique identifier of the form
    bool isEmpty = false;               // Flag indicating if the form entry is deleted/empty
};