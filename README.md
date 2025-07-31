This is an Arma Reforger mod that creates additional inputs for the radio system.

# Features
As of now, the following inputs have been added:
1. Page Up: Adjust the selected channel up N frequency steps (input: keyboard=F7, gamepad=x; default: N = 10)
2. Page Down: Adjust the selected channel down N frequency steps (input: keyboard=F8, gamepad=y; N = 10)

# Testing
Right now, all testing is done with manually using the dedicated server tool. The following procedure is done using both US/USSR factions (i.e. their specific radios).

## Base Functionality
1. Test Flow A
    1. With starting channels.
    2. p1/p2 are connected on both channels.
2. Test Flow B
    1. With starting channels.
    2. p1 pages down on channel 1.
    3. p1/p2 are not connected on channel 1.
    4. p1/p2 are connected on channel 2.
3. Test Flow C
    1. With channel state after Test Flow B,
    2. p1 pages up on channel 1.
    3. p1/p2 are connected on both channel 1 and 2.
    4. p1 pages up on channel 2.
    5. p1/p2 are connected on channel 1.
    6. p1/p2 are not connected on channel 2.
    7. p1 pages down on channel 2.
    8. p1/p2 are connected on channel 1 and 2.
4. Test Flow D
    1. With starting channels.
    2. Page up as p1 to target frequency on channel 1.
    3. Scroll up as p2 to target frequency on channel 1.
    4. p1/p2 are connected on channel 1 and 2.
    5. p1/p2 page down on channel 1.
    6. p1/p2 are connected on channel 1 and 2.
5. Test Flow E
    1. With starting channels.
    2. p1 pages down on channel 1, and then scrolls up a single channel.
    3. p2 scrolls down to target channel.
    4. p1/p2 are connected on both channel 1 and 2.
6. Test Flow F
    1. p1 scroll to the highest available frequency on channel 1.
    2. p2 pages to the highest available frequency on channel 1.
    3. p1/p2 should be on the same frequency.
    4. p2 tries to page up again.
    5. p2 should be at the same frequency still.
6. Test Flow G
    1. p1 scroll to the lowest available frequency on channel 1.
    2. p2 pages to the lowest available frequency on channel 1.
    3. p1/p2 should be on the same frequency.
    4. p2 tries to page down again.
    5. p2 should be at the same frequency still.
7. Test Flow H
    1. p1 tap page up input twice as quickly as possible.
    2. p1 should have paged twice, rather than once.
7. Test Flow I
    1. p1 tap page down input twice as quickly as possible.
    2. p1 should have paged twice, rather than once.

## Testing Localization
Each language should be selected, and then:
1. Open the Control menu and go to the Radio QoL tab.
2. Open the radio radial UI menu (to exercise the control hints).

## Testing control re-binding
1. Open control menu and select new key bind for page up/page down actions.
2. Perform Test Flow A, B, and C

# Changelog
- v1.1.0: Added default inputs for console. Added control hints for new radio actions. Added control menu to change keybinds.
- v1.1.1: Added string localization.
- v1.1.2: Fixed input filter for keyboard inputs so they are consistent with console inputs. Now, holding/rapid inputs for keyboard should work more intuitively.
