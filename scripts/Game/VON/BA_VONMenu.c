[BaseContainerProps()]
modded class SCR_VONMenu
{
	[Attribute("10", UIWidgets.EditBox, "Gameplay", desc: "N steps to adjust on single input")]
	protected int m_iNFreqSteps;

	protected void BARI_ActionFrequencyPageUp(float value, EActionTrigger reason)
	{
		if (0 == value)
			return;

		BARI_OnAdjustEntryNSteps(1 * m_iNFreqSteps);
	}

	protected void BARI_ActionFrequencyPageDown(float value, EActionTrigger reason)
	{
		if (0 == value)
			return;

		BARI_OnAdjustEntryNSteps(-1 * m_iNFreqSteps);
	}

	override protected void OnOpenMenu(SCR_SelectionMenu menu)
	{
		super.OnOpenMenu(menu);
		InputManager inputMgr = GetGame().GetInputManager();
		if (null == inputMgr)
		{
			return;
		}
		inputMgr.AddActionListener("BA_VONMenuFrequencyPageUp", EActionTrigger.DOWN, BARI_ActionFrequencyPageUp);
		inputMgr.AddActionListener("BA_VONMenuFrequencyPageDown", EActionTrigger.DOWN, BARI_ActionFrequencyPageDown);
	}

	override protected void OnCloseMenu(SCR_SelectionMenu menu)
	{
		super.OnCloseMenu(menu);
		InputManager inputMgr = GetGame().GetInputManager();
		if (null == inputMgr)
		{
			return;
		}
		inputMgr.RemoveActionListener("BA_VONMenuFrequencyPageUp", EActionTrigger.DOWN, BARI_ActionFrequencyPageUp);
		inputMgr.RemoveActionListener("BA_VONMenuFrequencyPageDown", EActionTrigger.DOWN, BARI_ActionFrequencyPageDown);
	}

	protected void BARI_OnAdjustEntryNSteps(int nSteps)
	{
		if (0 == nSteps)
			return;

		if (!m_RadialMenu.GetSelectionEntry())
			return;

		m_Display.SetFrequenciesVisible(true);
		m_FrequencyListTimer = 3;

		SCR_VONEntry entry = SCR_VONEntry.Cast(m_RadialMenu.GetSelectionEntry());
		if (!entry)
			return;

		entry.AdjustEntryModif(nSteps);

		SCR_VONEntryRadio radioEntry = SCR_VONEntryRadio.Cast(entry);
		if (radioEntry)
		{
			m_Display.UpdateFrequencyList(radioEntry);
			radioEntry.SetChannelText(GetKnownChannel(radioEntry.GetEntryFrequency()));
			radioEntry.Update();
		}
	}
}
