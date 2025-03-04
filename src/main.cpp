#include "utils/serializer.h"
#include "utils/globals.h"
#include "form/form.h"
#include "form/spells.h"
#include "form/skills.h"

SKSEPluginLoad(const SKSE::LoadInterface* a_skse)
{
	SKSE::Init(a_skse);

    logs::info("Plugin Loaded - Mysticism");

    auto messaging = SKSE::GetMessagingInterface();
    if (!messaging) {
        logs::error("Failed to get SKSE Messaging Interface.");
        return false;
    }

    messaging->RegisterListener([](SKSE::MessagingInterface::Message* message) {
        if (message->type == SKSE::MessagingInterface::kPostLoad) {
            logs::debug("Basegame actor values: {}", baseAVTotal);
        }
        else if (message->type == SKSE::MessagingInterface::kPostPostLoad) {
            
        }
        else if (message->type == SKSE::MessagingInterface::kDataLoaded) {
            extendActorValueList();

            onGameLoad();

            loadSpells();
            auto console = RE::ConsoleLog::GetSingleton();
            if (console) {
                console->Print(entryMessage);
                console->Print(formsLoaded);
                debugLogActorValues();
                logs::debug("Modgame womp: {}, {}", 1, newAVIList.size());
            }
            else {
                logs::error("ConsoleLog singleton is null. ");
            }
            createMagicEffect(baseMagic);
        }
        });

	return true;
}