modded class SCR_VonDisplay
{
	[Attribute("false", UIWidgets.EditBox, "Gameplay", desc: "Enable nametags on radio transmissions")]
	protected bool enNameTagsRadio;
	//------------------------------------------------------------------------------------------------
	//! Update transmission data
	//! \param TransmissionData is the subject
	//! \param radioTransceiver is the used transceiver for the transmission
	//! \param IsReceiving is true when receiving transmission, false when transmitting
	//! \param isAdditionalSpeaker is true when all incomming transmission widgets are full
	//! \return false if the transimission is filtered out to not be visible
	override protected bool UpdateTransmission(TransmissionData data, BaseTransceiver radioTransceiver, int frequency, bool IsReceiving)
	{
		bool result = super.UpdateTransmission(data, radioTransceiver, frequency, IsReceiving);

		if (radioTransceiver && result)
		{
			data.m_Widgets.m_wName.SetVisible(enNameTagsRadio);
		}

		return result;
	}
}
