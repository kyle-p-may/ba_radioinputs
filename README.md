This is an Arma Reforger mod that adds additional inputs for the radio system.

As of now, the following inputs have been added:
1. Page Up: Adjust the selected channel up N frequency steps (input: F7, default: N = 10)
2. Page Down: Adjust the selected channel down N frequency steps (input: F8, default: N = 10)

Right now, all testing is done with manually using the dedicated server tool. The following procedure is done using both US/USSR factions (i.e. their specific radios). This should be done with both channels. At each step, the other channel can be used to transmit, and shouldn't change.
1. Speak on channel as p1. p2 can hear.
2. Page down on channel as p1. p2 cannot hear.
3. Page up on platoon as p1. p2 can hear.
4. Page up on platoon as p1. p2 cannot hear.
5. Page down on platoon as p1. p2 can hear.
6. Page up as p1. Scroll up as p2. Both can hear.
7. Page up and then scroll up as p1. Scroll up as p2. Both can hear.

Additionally, to test localization, each language can be selected, and then:
1. Open the Control menu and go to the Radio QoL tab.
2. Open the radio radial UI menu (to exercise the control hints).

Changelog:
v1.1.0: Added default inputs for console. Added control hints for new radio actions. Added control menu to change keybinds.
v1.1.1: Added string localization.