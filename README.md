# Mysticism — A Custom Magic Skill Tree for Skyrim

Mysticism is a Skyrim mod built using [CommonLibSSE](https://github.com/Ryan-rsm-McKenzie/CommonLibSSE) that introduces a new magical skill tree. By extending the Actor Value system and hooking into key virtual functions, Mysticism adds a flexible platform for new spells, skills, and gameplay mechanics centered around the arcane.

---

## Features

- **New Magic Skill: Mysticism**  
  Adds a new actor value representing a magical discipline separate from existing schools.

- **Custom Actor Values**  
  - `Mysticism`: The core skill.
  - `MysticismMod`: A modifiable stat for balancing and tuning.
  - `MysticismPowerMod`: A modifier to influence spell power, duration, etc.

- **Actor Value List Extension**  
  Dynamically creates and registers new `ActorValueInfo` entries during runtime.

- **Hooked Actor Value Functions**  
  Overrides `GetActorValue` and optionally `LookupActorValue` to support custom logic.

- **Logging and Debugging Tools**  
  Easily inspect the added actor values and verify integration during development.

---

## How It Works

### Actor Value Injection

At runtime, `extendActorValueList()`:
- Clones the current ActorValue list.
- Appends new `ActorValueInfo` objects created from `aviForm` definitions.
- Patches internal references to point to the new list.

### Example: New Actor Values

```cpp
new aviForm("Mysticism", "", "AVIllusion", magicSkill, 4.0, 0.0, 2.0, 0.0);
new aviForm("MysticismMod", "", "AVMysticismMod", noSkill);
new aviForm("MysticismPowerMod", "", "AVMysticismPowerMod", noSkill);
