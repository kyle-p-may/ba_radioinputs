modded class SCR_VonDisplay
{
	[Attribute("false", UIWidgets.EditBox, "Gameplay", desc: "Show friendly nametags on transmissions?")]
	protected bool m_bShowFriendlyNametagsOnRecv;

	override protected bool UpdateTransmission(TransmissionData data, BaseTransceiver radioTransceiver, int frequency, bool IsReceiving)
	{
		bool result = super.UpdateTransmission(data, radioTransceiver, frequency, IsReceiving);

		if (radioTransceiver && result)
		{
			data.m_Widgets.m_wName.SetVisible(m_bShowFriendlyNametagsOnRecv);
		}

		return result;
	}
}
