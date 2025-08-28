modded class SCR_VONController
{
	protected const string ACTION_CHANNEL_0 = "BA_VONChannel_0";
	protected const string ACTION_CHANNEL_1 = "BA_VONChannel_1";

	protected void BARI_SetActiveEntry(notnull SCR_VONEntry selectedEntry, EVONTransmitType type)
	{
		if (EVONTransmitType.LONG_RANGE == type)
		{
			m_LongRangeEntry = selectedEntry;
		}
		else
		{
			m_LongRangeEntry = null;
		}

		m_ActiveEntry = selectedEntry;
	}

	protected SCR_VONEntry BARI_SelectTransceiver(int channel)
	{
		SCR_VONEntryRadio activeRadioEntry = SCR_VONEntryRadio.Cast(m_ActiveEntry);
		if (!activeRadioEntry)
			return null;

		BaseTransceiver transceiver = activeRadioEntry.GetTransceiver();
		if (!transceiver)
			return null;

		BaseRadioComponent radio = transceiver.GetRadio();
		if (!radio)
			return null;

		array<SCR_VONEntry> entries = {};

		SCR_VONEntryRadio radioEntry;
		foreach (SCR_VONEntry entry : m_aEntries)
		{
			radioEntry = SCR_VONEntryRadio.Cast(entry);
			if (radioEntry && radioEntry.GetTransceiver().GetRadio() == radio)
				entries.Insert(entry);
		}

		if (entries.IsEmpty())
			return null;

		if (!entries.IsIndexValid(channel))
			return null;

		return entries[channel];
	}

	protected void BARI_SetVONBroadcastByChannelActivate(int channel, notnull SCR_VONEntry selectedEntry, EVONTransmitType transmitType)
	{
		if (selectedEntry != m_ActiveEntry && m_eVONType != EVONTransmitType.DIRECT)
		{
#ifdef BA_RADIOINPUTS_DEBUG
			Print("Deactivating current active entry: " + m_ActiveEntry, LogLevel.NORMAL);
#endif
			DeactivateVON(m_eVONType);
		}

		BARI_SetActiveEntry(selectedEntry, transmitType);

		if (m_VONDisplay)
			m_VONDisplay.ShowSelectedVONHint(selectedEntry);

		SetVONBroadcast(true, transmitType);

		if (1 == channel)
		{
			m_sActiveHoldAction = ACTION_CHANNEL_1;
		}
		else if (0 == channel)
		{
			m_sActiveHoldAction = ACTION_CHANNEL_0;
		}
	}

	protected void BARI_SetVONBroadcastByChannelDeactivate(int channel, notnull SCR_VONEntry selectedEntry, EVONTransmitType transmitType)
	{
		if (GetEntryByTransmitType(transmitType) != selectedEntry)
		{
#ifdef BA_RADIOINPUTS_DEBUG
			Print("Selected channel doesn't match active channel, cannot deactivate", LogLevel.NORMAL);
#endif
			return;
		}

		SetVONBroadcast(false, transmitType);
	}

	protected void BARI_ActionVONBroadcastByChannel(int channel, bool activate)
	{
		if (!m_VONComp)
			return;

		SCR_VONEntry selectedEntry = BARI_SelectTransceiver(channel);
		if (!selectedEntry)
			return;

		EVONTransmitType transmitType;
		if (m_bIsLongRangeToggled)
			transmitType = EVONTransmitType.LONG_RANGE;
		else
			transmitType = EVONTransmitType.CHANNEL;

#ifdef BA_RADIOINPUTS_DEBUG
		Print("Old m_ActiveEntry: " + m_ActiveEntry, LogLevel.NORMAL);
		Print("Old m_LongRangeEntry: " + m_LongRangeEntry, LogLevel.NORMAL);
		Print("selectedEntry: " + selectedEntry, LogLevel.NORMAL);
		Print("transmitType: " + transmitType, LogLevel.NORMAL);
#endif

		if (activate)
		{
			BARI_SetVONBroadcastByChannelActivate(channel, selectedEntry, transmitType);
		}
		else
		{
			BARI_SetVONBroadcastByChannelDeactivate(channel, selectedEntry, transmitType);
		}

#ifdef BA_RADIOINPUTS_DEBUG
		Print("New m_ActiveEntry: " + m_ActiveEntry, LogLevel.NORMAL);
		Print("New m_LongRangeEntry: " + m_LongRangeEntry, LogLevel.NORMAL);
#endif
	}

	protected void BARI_ActionVONBroadcastChannel0(float value, EActionTrigger reason = EActionTrigger.UP)
	{
#ifdef BA_RADIOINPUTS_DEBUG
		Print("ActionVONBroadcastChannel0", LogLevel.NORMAL);
#endif
		BARI_ActionVONBroadcastByChannel(0, reason != EActionTrigger.UP);
	}

	protected void BARI_ActionVONBroadcastChannel1(float value, EActionTrigger reason = EActionTrigger.UP)
	{
#ifdef BA_RADIOINPUTS_DEBUG
		Print("ActionVONBroadcastChannel1", LogLevel.NORMAL);
#endif
		BARI_ActionVONBroadcastByChannel(1, reason != EActionTrigger.UP);
	}

	override protected void Init(IEntity owner)
	{
		super.Init(owner);
		if (m_InputManager)
		{
			m_InputManager.AddActionListener(ACTION_CHANNEL_0, EActionTrigger.DOWN, BARI_ActionVONBroadcastChannel0);
			m_InputManager.AddActionListener(ACTION_CHANNEL_0, EActionTrigger.UP, BARI_ActionVONBroadcastChannel0);
			m_InputManager.AddActionListener(ACTION_CHANNEL_1, EActionTrigger.DOWN, BARI_ActionVONBroadcastChannel1);
			m_InputManager.AddActionListener(ACTION_CHANNEL_1, EActionTrigger.UP, BARI_ActionVONBroadcastChannel1);
		}
	}

	override protected void Cleanup()
	{
		if (m_InputManager)
		{
			m_InputManager.RemoveActionListener(ACTION_CHANNEL_0, EActionTrigger.DOWN, BARI_ActionVONBroadcastChannel0);
			m_InputManager.RemoveActionListener(ACTION_CHANNEL_0, EActionTrigger.UP, BARI_ActionVONBroadcastChannel0);
			m_InputManager.RemoveActionListener(ACTION_CHANNEL_1, EActionTrigger.DOWN, BARI_ActionVONBroadcastChannel1);
			m_InputManager.RemoveActionListener(ACTION_CHANNEL_1, EActionTrigger.UP, BARI_ActionVONBroadcastChannel1);
		}
		super.Cleanup();
	}

}
