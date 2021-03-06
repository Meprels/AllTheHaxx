/* (c) Magnus Auvinen. See licence.txt in the root of the distribution for more information. */
/* If you are missing that file, acquire a complete release at teeworlds.com.                */

#include <engine/graphics.h>
#include <engine/shared/config.h>
#include <game/generated/client_data.h>
#include <game/localization.h>

#include "menus.h"
#include "gametexture.h"

// TODO: make all that duplicate code better!

void CMenus::RenderSettingsTexture(CUIRect MainView)
{
	CALLSTACK_ADD();

	static int s_ControlPage = 0;

	CUIRect TabBar, Button;
	MainView.HSplitTop(20.0f, &TabBar, &MainView);
	MainView.Margin(10.0f, &MainView);

	// tab bar
	{
		TabBar.VSplitLeft(TabBar.w/4, &Button, &TabBar);
		static CButtonContainer s_Button0;
		if(DoButton_MenuTab(&s_Button0, Localize("Gameskin"), s_ControlPage == 0, &Button, CUI::CORNER_L))
			s_ControlPage = 0;

		TabBar.VSplitLeft(TabBar.w/3, &Button, &TabBar);
		static CButtonContainer s_Button1;
		if(DoButton_MenuTab(&s_Button1, Localize("Particles"), s_ControlPage == 1, &Button, 0))
			s_ControlPage = 1;

		TabBar.VSplitMid(&Button, &TabBar);
		static CButtonContainer s_Button2;
		if(DoButton_MenuTab(&s_Button2, Localize("Emoticons"), s_ControlPage == 2, &Button, 0))
			s_ControlPage = 2;

		static CButtonContainer s_Button3;
		if(DoButton_MenuTab(&s_Button3, Localize("Cursor"), s_ControlPage == 3, &TabBar, CUI::CORNER_R))
			s_ControlPage = 3;
	}

	// render page
	if(s_ControlPage == 0)
		RenderSettingsGameskin(MainView);
	else if(s_ControlPage == 1)
		RenderSettingsParticles(MainView);
	else if(s_ControlPage == 2)
		RenderSettingsEmoticons(MainView);
	else if(s_ControlPage == 3)
		RenderSettingsCursor(MainView);
	else
		s_ControlPage = 0;
}

void CMenus::RenderSettingsGameskin(CUIRect MainView)
{
	CALLSTACK_ADD();

	MainView.HSplitTop(10.0f, 0, &MainView);

	// skin selector
	static float s_ScrollValue = 0.0f;
	static const sorted_array<CGameTextureManager::CGameSkin>& s_aSkinList = m_pClient->m_pGameTextureManager->GetGroup(CGameTextureManager::TEXTURE_GROUP_GAME);

	int OldSelected = -1;
	static CButtonContainer s_Listbox;
	UiDoListboxStart(&s_Listbox, &MainView, 160.0f, Localize("Texture"), "", s_aSkinList.size(), 2, OldSelected, s_ScrollValue);

	for(int i = 0; i < s_aSkinList.size(); ++i)
	{
		const CGameTextureManager::CGameSkin *s = &s_aSkinList[i];
		if(s == 0)
			continue;

		if(str_comp(s->m_aName, g_Config.m_TexGame) == 0)
			OldSelected = i;

		CPointerContainer Container(s);
		CListboxItem Item = UiDoListboxNextItem(&Container, OldSelected == i);
		if(Item.m_Visible)
		{
			CUIRect Label;
			Item.m_Rect.Margin(5.0f, &Item.m_Rect);
			Item.m_Rect.HSplitBottom(10.0f, &Item.m_Rect, &Label);

			int gTexture = s->Texture();
			if(gTexture <= 0) if((gTexture = m_pClient->m_pGameTextureManager->FindTexture(CGameTextureManager::TEXTURE_GROUP_GAME, s->m_aName)) <= 0) continue;
			char gName[512];
			str_format(gName, sizeof(gName), "%s", s->m_aName);
			Graphics()->TextureSet(gTexture);
			Graphics()->QuadsBegin();
			IGraphics::CQuadItem QuadItem(Item.m_Rect.x+Item.m_Rect.w/2 - 120.0f, Item.m_Rect.y+Item.m_Rect.h/2 - 60.0f, 240.0f, 120.0f);
			Graphics()->QuadsDrawTL(&QuadItem, 1);
			Graphics()->QuadsEnd();
			UI()->DoLabel(&Label, gName, 10.0f, 0);
		}
	}

	const int NewSelected = UiDoListboxEnd(&s_ScrollValue, 0);
	if(OldSelected != NewSelected)
	{
		mem_copy(g_Config.m_TexGame, s_aSkinList[NewSelected].m_aName, sizeof(g_Config.m_TexGame));
		m_pClient->m_pGameTextureManager->SetTexture(IMAGE_GAME, g_Config.m_TexGame);
	}
}
	

void CMenus::RenderSettingsParticles(CUIRect MainView)
{
	CALLSTACK_ADD();

	MainView.HSplitTop(10.0f, 0, &MainView);

	// skin selector
	static const sorted_array<CGameTextureManager::CGameSkin>& s_aSkinList = m_pClient->m_pGameTextureManager->GetGroup(CGameTextureManager::TEXTURE_GROUP_PARTICLES);
	static float s_ScrollValue = 0.0f;


	int OldSelected = -1;
	static CButtonContainer s_Listbox;
	UiDoListboxStart(&s_Listbox, &MainView, 160.0f, Localize("Particles"), "", s_aSkinList.size(), 3, OldSelected, s_ScrollValue);

	for(int i = 0; i < s_aSkinList.size(); ++i)
	{
		const CGameTextureManager::CGameSkin *s = &s_aSkinList[i];
		if(s == 0)
			continue;

		if(str_comp(s->m_aName, g_Config.m_TexParticles) == 0)
			OldSelected = i;

		CPointerContainer Container(s);
		CListboxItem Item = UiDoListboxNextItem(&Container, OldSelected == i);
		if(Item.m_Visible)
		{
			CUIRect Label;
			Item.m_Rect.Margin(5.0f, &Item.m_Rect);
			Item.m_Rect.HSplitBottom(10.0f, &Item.m_Rect, &Label);

			int gTexture = s->Texture();
			if(gTexture <= 0) if((gTexture = m_pClient->m_pGameTextureManager->FindTexture(CGameTextureManager::TEXTURE_GROUP_PARTICLES, s->m_aName)) <= 0) continue;
			char gName[512];
			str_format(gName, sizeof(gName), "%s", s->m_aName);
			Graphics()->TextureSet(gTexture);
			Graphics()->QuadsBegin();
			IGraphics::CQuadItem QuadItem(Item.m_Rect.x+Item.m_Rect.w/2 - 60.0f, Item.m_Rect.y+Item.m_Rect.h/2 - 60.0f, 120.0f, 120.0f);
			Graphics()->QuadsDrawTL(&QuadItem, 1);
			Graphics()->QuadsEnd();
			UI()->DoLabel(&Label, gName, 10.0f, 0);
		}
	}

	const int NewSelected = UiDoListboxEnd(&s_ScrollValue, 0);
	if(OldSelected != NewSelected)
	{
		mem_copy(g_Config.m_TexParticles, s_aSkinList[NewSelected].m_aName, sizeof(g_Config.m_TexParticles));
		m_pClient->m_pGameTextureManager->SetTexture(IMAGE_PARTICLES, g_Config.m_TexParticles);
	}
}

void CMenus::RenderSettingsEmoticons(CUIRect MainView)
{
	CALLSTACK_ADD();

	MainView.HSplitTop(10.0f, 0, &MainView);

	// skin selector
	static const sorted_array<CGameTextureManager::CGameSkin>& s_aSkinList = m_pClient->m_pGameTextureManager->GetGroup(CGameTextureManager::TEXTURE_GROUP_EMOTE);
	static float s_ScrollValue = 0.0f;

	int OldSelected = -1;
	static CButtonContainer s_Listbox;
	UiDoListboxStart(&s_Listbox, &MainView, 160.0f, Localize("Emoticons"), "", s_aSkinList.size(), 3, OldSelected, s_ScrollValue);

	for(int i = 0; i < s_aSkinList.size(); ++i)
	{
		const CGameTextureManager::CGameSkin *s = &s_aSkinList[i];
		if(s == 0)
			continue;

		if(str_comp(s->m_aName, g_Config.m_TexEmoticons) == 0)
			OldSelected = i;

		CPointerContainer Container(s);
		CListboxItem Item = UiDoListboxNextItem(&Container, OldSelected == i);
		if(Item.m_Visible)
		{
			CUIRect Label;
			Item.m_Rect.Margin(5.0f, &Item.m_Rect);
			Item.m_Rect.HSplitBottom(10.0f, &Item.m_Rect, &Label);

			int gTexture = s->Texture();
			if(gTexture <= 0) if((gTexture = m_pClient->m_pGameTextureManager->FindTexture(CGameTextureManager::TEXTURE_GROUP_EMOTE, s->m_aName)) <= 0) continue;
			char gName[512];
			str_format(gName, sizeof(gName), "%s", s->m_aName);
			Graphics()->TextureSet(gTexture);
			Graphics()->QuadsBegin();
			IGraphics::CQuadItem QuadItem(Item.m_Rect.x+Item.m_Rect.w/2 - 60.0f, Item.m_Rect.y+Item.m_Rect.h/2 - 60.0f, 120.0f, 120.0f);
			Graphics()->QuadsDrawTL(&QuadItem, 1);
			Graphics()->QuadsEnd();
			UI()->DoLabel(&Label, gName, 10.0f, 0);
		}
	}

	const int NewSelected = UiDoListboxEnd(&s_ScrollValue, 0);
	if(OldSelected != NewSelected)
	{
		mem_copy(g_Config.m_TexEmoticons, s_aSkinList[NewSelected].m_aName, sizeof(g_Config.m_TexEmoticons));
		m_pClient->m_pGameTextureManager->SetTexture(IMAGE_EMOTICONS, g_Config.m_TexEmoticons);
	}
}

void CMenus::RenderSettingsCursor(CUIRect MainView)
{
	CALLSTACK_ADD();

	MainView.HSplitTop(10.0f, 0, &MainView);

	// skin selector
	static const sorted_array<CGameTextureManager::CGameSkin>& s_aSkinList = m_pClient->m_pGameTextureManager->GetGroup(CGameTextureManager::TEXTURE_GROUP_CURSOR);
	static float s_ScrollValue = 0.0f;

	int OldSelected = -1;
	static CButtonContainer s_Listbox;
	UiDoListboxStart(&s_Listbox, &MainView, 160.0f, Localize("Cursor"), "", s_aSkinList.size(), 3, OldSelected, s_ScrollValue);

	for(int i = 0; i < s_aSkinList.size(); ++i)
	{
		const CGameTextureManager::CGameSkin *s = &s_aSkinList[i];
		if(s == 0)
			continue;

		if(str_comp(s->m_aName, g_Config.m_TexCursor) == 0)
			OldSelected = i;

		CPointerContainer Container(s);
		CListboxItem Item = UiDoListboxNextItem(&Container, OldSelected == i);
		if(Item.m_Visible)
		{
			CUIRect Label;
			Item.m_Rect.Margin(5.0f, &Item.m_Rect);
			Item.m_Rect.HSplitBottom(10.0f, &Item.m_Rect, &Label);

			int gTexture = s->Texture();
			if(gTexture <= 0) if((gTexture = m_pClient->m_pGameTextureManager->FindTexture(CGameTextureManager::TEXTURE_GROUP_CURSOR, s->m_aName)) <= 0) continue;
			char gName[512];
			str_format(gName, sizeof(gName), "%s", s->m_aName);
			Graphics()->TextureSet(gTexture);
			Graphics()->QuadsBegin();
			IGraphics::CQuadItem QuadItem(Item.m_Rect.x+Item.m_Rect.w/2 - 60.0f, Item.m_Rect.y+Item.m_Rect.h/2 - 60.0f, 120.0f, 120.0f);
			Graphics()->QuadsDrawTL(&QuadItem, 1);
			Graphics()->QuadsEnd();
			UI()->DoLabel(&Label, gName, 10.0f, 0);
		}
	}

	const int NewSelected = UiDoListboxEnd(&s_ScrollValue, 0);
	if(OldSelected != NewSelected)
	{
		mem_copy(g_Config.m_TexCursor, s_aSkinList[NewSelected].m_aName, sizeof(g_Config.m_TexCursor));
		m_pClient->m_pGameTextureManager->SetTexture(IMAGE_CURSOR, g_Config.m_TexCursor);
	}
}
