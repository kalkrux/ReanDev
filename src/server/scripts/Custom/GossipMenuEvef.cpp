#include "ScriptMgr.h"


class GossipMenuEvef : public CreatureScript /*Declaro la clase de tipo creaturescript y publica*/
{
public:
	GossipMenuEvef() : CreatureScript("GossipMenuEvef") {} /*Creamos un objeto tipo GossipMenuEvef*/

	bool OnGossipEvef(Player* plr, Creature* npc)
	{

		plr->ADD_GOSSIP_ITEM(0, "¿Deseas Enfretarte al gran Cachitos?", GOSSIP_SENDER_MAIN, 1); /*Añadimos las opciones del menú de dialogo*/
		plr->ADD_GOSSIP_ITEM(0, "!!No quieres enfrentarte al Gran Cachitos!!,Lo Entiendo Tienes miedo igual que Evef", GOSSIP_SENDER_MAIN, 2);
		plr->SEND_GOSSIP_MENU(DEFAULT_GOSSIP_MESSAGE, npc->GetGUID());
		return true;
	}

	bool OnGossipSelect(Player* plr, Creature* npc, uint32 sender, uint32 uiAction)
	{
		if (!plr)
			return false;
		plr->PlayerTalkClass->ClearMenus();

		switch (uiAction) /*Ponemos las modificaciones segun el menú elegido*/
		{
		case 1:
		{
			npc->setFaction(14);
			npc->SetReactState(REACT_AGGRESSIVE);
			plr->GetSession()->SendAreaTriggerMessage("Moriras ante el Gran Cachitos");
			plr->CLOSE_GOSSIP_MENU();
		}
		case 2:
		{

			plr->CLOSE_GOSSIP_MENU();
		}

		}
		return true;
	}


};

void AddSC_GossipMenuEvef()
{

	new GossipMenuEvef();

}