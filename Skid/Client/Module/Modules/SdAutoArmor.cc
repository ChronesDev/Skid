#pragma once

#include "../InUI/Include.h"
#include <lib.horion.h>

#include <index_macros>

namespace Skid::Module
{
	using namespace Index;

	struct SdAutoArmor : IModule
	{
		class ArmorStruct {
		public:
			ArmorStruct(C_ItemStack* item, C_ArmorItem* yot, int slot) {
				armor = yot;
				m_slot = slot;
				m_item = item;
			}
			bool isEqual(ArmorStruct& src) {
				if (this->m_item->getArmorValueWithEnchants() == src.m_item->getArmorValueWithEnchants())
					return true;
				else
					return false;
			}

			bool operator()(ArmorStruct lhs, ArmorStruct rhs) {
				return (lhs.m_item->getArmorValueWithEnchants() > rhs.m_item->getArmorValueWithEnchants());
			}
			C_ArmorItem* armor = nullptr;
			C_ItemStack* m_item = nullptr;
			int m_slot = 0;
		};

	private:
		bool HasOpenInventoy_ = false;
		bool LastOpen_ = false;
		Int WaitCounter_ = 0;
		Int ArmorSlotCounter_ = 0;

		bool Setting_OnlyIfOpen_ = true;
		Int Setting_Wait_ = 1;

	public:
		SdAutoArmor() : IModule('H', Category::PLAYER, "Lol")
		{
			registerBoolSetting("Only If Open", &this->Setting_OnlyIfOpen_, this->Setting_OnlyIfOpen_);
			registerIntSetting("Wait", &this->Setting_Wait_, this->Setting_Wait_, 1, 20);
		}

		fun getModuleName() -> const char* override { return "SdAutoArmor"; }

		fun onTick(C_GameMode* gm) -> void override
		{
			C_PlayerInventoryProxy* supplies = g_Data.getLocalPlayer()->getSupplies();
			C_Inventory* inv = supplies->inventory;
			C_InventoryTransactionManager* manager = g_Data.getLocalPlayer()->getTransactionManager();
			C_InventoryAction* first = nullptr;
			C_InventoryAction* second = nullptr;

			static C_ItemStack* emptyItemStack = nullptr;
			if (emptyItemStack == 0x0) {
				uintptr_t sigOffset = FindSignature("48 8D 3D ? ? ? ? 80 B8 ? ? ? ? ? 75 19 48 8B 88 ? ? ? ? 48 8B 11 4C 8B 42 28 8B 50 10");
				int offset = *reinterpret_cast<int*>(sigOffset + 3);
				emptyItemStack = reinterpret_cast<C_ItemStack*>(sigOffset + offset + /*length of instruction*/ 7);
			}

			HasOpenInventoy_ = !g_Data.getLocalPlayer()->canOpenContainerScreen();
			if (!Setting_OnlyIfOpen_ || HasOpenInventoy_)
			{
				if (!LastOpen_) {
					WaitCounter_ = 0;
					ArmorSlotCounter_ = 2;
				}

				if (WaitCounter_ <= 0)
				{
					WaitCounter_ = Setting_Wait_;

					ArmorSlotCounter_ = (ArmorSlotCounter_ + 1) % 4;
					int i = ArmorSlotCounter_;
					// Beginning here
					{
						C_Player& player = *gm->player;

						List<ArmorStruct> armorList;
						armorList.reserve(36);

						struct CompareArmorStruct {
							bool operator()(ArmorStruct lhs, ArmorStruct rhs) {
								return (lhs.m_item->getArmorValueWithEnchants() > rhs.m_item->getArmorValueWithEnchants());
							}
						};

						// Collect all ItemStacks
						for (int n = 0; n < 36; n++)
						{
							C_ItemStack* stack = inv->getItemStack(n);
							if (stack->item != nullptr && (*stack->item)->isArmor() && reinterpret_cast<C_ArmorItem*>(*stack->item)->ArmorSlot == i)
							{
								armorList.Add(ArmorStruct(stack, reinterpret_cast<C_ArmorItem*>(*stack->item), n));
							}
						}

						// Collect current Armor ItemStack
						if (gm->player->getArmor(i)->item != nullptr)
						{
							armorList.Add(ArmorStruct(gm->player->getArmor(i), reinterpret_cast<C_ArmorItem*>(*gm->player->getArmor(i)->item), i));
						}

						// Move
						if (!armorList.empty())
						{
							std::sort(armorList.begin(), armorList.end(), CompareArmorStruct());
							C_ItemStack* armorItem = gm->player->getArmor(i);

							int emptyHotBarSlot = -1;
							for (int i2 = 0; i2 < 9; i2++)
							{
								auto itemStack = inv->getItemStack(i2);
								if (itemStack->item == nullptr)
								{
									emptyHotBarSlot = i2;
								}
							}

							if (emptyHotBarSlot != -1)
							{
								// Has Armor but is not the "best"
								if (armorItem->item != nullptr)
								{
									if (!ArmorStruct(armorItem, reinterpret_cast<C_ArmorItem*>(*armorItem->item), 0).isEqual(armorList[0]))
									{
										var& firstArmor = armorList.First;
										inv->moveItem(firstArmor.m_slot, emptyHotBarSlot);
										var selectedSlot = supplies->selectedHotbarSlot;
										inv->getItemStack(emptyHotBarSlot)->
									}
								}

								// Hasn't Armor
								if (armorItem->item == nullptr)
								{

								}
							}
						}

						armorList.Clear();
					}

				}

				WaitCounter_ -= 1;
			}
			LastOpen_ = HasOpenInventoy_;
		}
	};
}

#include <index_macros_end>