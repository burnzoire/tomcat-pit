# AFCS
The Automatic Flight Control System panel includes SAS and Autopilot controls.

The real panel uses magnetic switches; without them the switches will quickly become out of sync with DCS. This means the pilot will need to reset switches from time to time.

A version of this panel with DIY magnetic switches is planned - as soon as I can figure out how to fit so many in close proximity.

## Hardware
| Component                  | DCS-BIOS Type*  | Control Reference | Part                     |
|----------------------------|-----------------|-------------------|--------------------------|
| PLT_AFCS_PITCH             | switch2pos      | SAS               | Toggle Switch (ON-ON)    |
| PLT_AFCS_ROLL              | switch2pos      | SAS               | Toggle Switch (ON-ON)    |
| T_AFCS_YAW                 | switch2pos      | SAS               | Toggle Switch (ON-ON)    |
| T_AUTOPLT_VECTOR_CARRIER   | switch3pos      | Autopilot         | Toggle Switch (ON-OFF-ON)|
| PLT_AUTOPLT_ALT            | switch3pos      | Autopilot         | Toggle Switch (ON-OFF-ON)|
| PLT_AUTOPLT_HDG            | switch3pos      | Autopilot         | Toggle Switch (ON-OFF-ON)|
| PLT_AUTOPLT_ENGAGE         | rotaryEncoder	 | Autopilot	       | Toggle Switch (ON-ON)    |

Using [DCS Flight Panel's fork of DCS BIOS](https://github.com/DCSFlightpanels/dcs-bios)
