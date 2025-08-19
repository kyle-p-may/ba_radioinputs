modded class SCR_VONController
{
	protected const string ACTION_CHANNEL_0 = "BA_VONChannel_0";
	protected const string ACTION_CHANNEL_1 = "BA_VONChannel_1";

	protected bool BA_SelectTransceiver(int channel)
	{
		SCR_VONEntryRadio activeRadioEntry = SCR_VONEntryRadio.Cast(m_ActiveEntry);
		if (!activeRadioEntry)
			return false;

		BaseTransceiver transceiver = activeRadioEntry.GetTransceiver();
		if (!transceiver)
			return false;

		BaseRadioComponent radio = transceiver.GetRadio();
		if (!radio)
			return false;

		array<SCR_VONEntry> entries = {};

		SCR_VONEntryRadio radioEntry;
		foreach (SCR_VONEntry entry : m_aEntries)
		{
			radioEntry = SCR_VONEntryRadio.Cast(entry);
			if (radioEntry && radioEntry.GetTransceiver().GetRadio() == radio)
				entries.Insert(entry);
		}

		SCR_VONEntry newEntry = m_ActiveEntry;

		if (entries.IsEmpty())
			return false;

		if (channel >= entries.Count())
			return false;

		newEntry = entries[channel];

		if (newEntry != m_ActiveEntry && m_eVONType != EVONTransmitType.DIRECT)
			DeactivateVON(m_eVONType);

		if (!ActivateVON(newEntry))
		{
#ifdef BA_RADIOINPUTS_DEBUG
			Print("Failed to activate VON for newEntry: " + newEntry, LogLevel.ERROR);
#endif
			return false;
		}

		if (m_VONDisplay)
			m_VONDisplay.ShowSelectedVONHint(newEntry);

		return true;

	}

	protected void BA_ActionVONBroadcastByChannel(int channel, bool activate)
	{
		if (!m_VONComp)
			return;

		if (activate)
		{
			if (!BA_SelectTransceiver(channel))
				return;
		}

		EVONTransmitType transmitType;

		if (m_bIsLongRangeToggled)
			transmitType = EVONTransmitType.LONG_RANGE;
		else
			transmitType = EVONTransmitType.CHANNEL;

		SetVONBroadcast(activate, transmitType);

		if (activate)
		{
			if (1 == channel)
			{
				m_sActiveHoldAction = ACTION_CHANNEL_1;
			}
			else
			{
				m_sActiveHoldAction = ACTION_CHANNEL_0;
			}
		}
	}

	protected void BA_ActionVONBroadcastChannel0(float value, EActionTrigger reason = EActionTrigger.UP)
	{
#ifdef BA_RADIOINPUTS_DEBUG
		Print("ActionVONBroadcastChannel0", LogLevel.DEBUG);
#endif
		BA_ActionVONBroadcastByChannel(0, reason != EActionTrigger.UP);
	}

	protected void BA_ActionVONBroadcastChannel1(float value, EActionTrigger reason = EActionTrigger.UP)
	{
#ifdef BA_RADIOINPUTS_DEBUG
		Print("ActionVONBroadcastChannel1", LogLevel.DEBUG);
#endif
		BA_ActionVONBroadcastByChannel(1, reason != EActionTrigger.UP);
	}

	override protected void Init(IEntity owner)
	{
		super.Init(owner);
		if (m_InputManager)
		{
			m_InputManager.AddActionListener(ACTION_CHANNEL_0, EActionTrigger.DOWN, BA_ActionVONBroadcastChannel0);
			m_InputManager.AddActionListener(ACTION_CHANNEL_0, EActionTrigger.UP, BA_ActionVONBroadcastChannel0);
			m_InputManager.AddActionListener(ACTION_CHANNEL_1, EActionTrigger.DOWN, BA_ActionVONBroadcastChannel1);
			m_InputManager.AddActionListener(ACTION_CHANNEL_1, EActionTrigger.UP, BA_ActionVONBroadcastChannel1);
		}
	}

	override protected void Cleanup()
	{
		if (m_InputManager)
		{
			m_InputManager.RemoveActionListener(ACTION_CHANNEL_0, EActionTrigger.DOWN, BA_ActionVONBroadcastChannel0);
			m_InputManager.RemoveActionListener(ACTION_CHANNEL_0, EActionTrigger.UP, BA_ActionVONBroadcastChannel0);
			m_InputManager.RemoveActionListener(ACTION_CHANNEL_1, EActionTrigger.DOWN, BA_ActionVONBroadcastChannel1);
			m_InputManager.RemoveActionListener(ACTION_CHANNEL_1, EActionTrigger.UP, BA_ActionVONBroadcastChannel1);
		}
		super.Cleanup();
	}

}
